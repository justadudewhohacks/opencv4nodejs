const {
  assert,
  expect
} = require('chai');

const {
  assertError,
  asyncFuncShouldRequireArgs,
  _funcShouldRequireArgs,
  funcShouldRequireArgs: __funcShouldRequireArgs
} = require('./testUtils');

const getEmptyArray = () => ([]);
const emptyFunc = () => {};

exports.generateAPITests = ({
  beforeHook = null,
  afterHook = null,
  getDut,
  methodName,
  methodNameSpace,
  getRequiredArgs = getEmptyArray,
  getOptionalArgs: _getOptionalArgs,
  getOptionalArgsMap = getEmptyArray,
  expectOutput,
  otherSyncTests = emptyFunc,
  otherAsyncCallbackedTests = emptyFunc,
  otherAsyncPromisedTests = emptyFunc,
  hasAsync = true,
  // provide backwards compatibility for bindings implemented with
  // macro-inferno macros
  usesMacroInferno = false
}) => {
  const methodNameAsync = `${methodName}Async`;
  const getOptionalArgs = _getOptionalArgs || (() => getOptionalArgsMap().map(kv => kv[1]));
  const getOptionalArgsObject = () => {
    const optionalArgsObject = {};
    getOptionalArgsMap().forEach((kv) => { optionalArgsObject[kv[0]] = kv[1]; });
    return optionalArgsObject;
  };

  const funcShouldRequireArgs = usesMacroInferno ? __funcShouldRequireArgs : _funcShouldRequireArgs;

  const hasRequiredArgs = !!getRequiredArgs().length;
  const hasOptArgs = !!getOptionalArgs().length;
  const hasOptArgsObject = getOptionalArgs().length > 1;

  const expectOutputCallbacked = (done, dut, args) => (err, res) => {
    expectOutput(res, dut, args);
    done();
  };

  const expectOutputPromisified = (done, dut, args) => (res) => {
    expectOutput(res, dut, args);
    done();
  };

  const generateTests = (type) => {
    const isCallbacked = type === 'callbacked';
    const isPromised = type === 'promised';
    const isAsync = isCallbacked || isPromised;

    const method = isAsync ? methodNameAsync : methodName;
    const capitalize = str => str.charAt(0).toUpperCase() + str.slice(1);

    const getErrPrefix = () => `${(methodNameSpace ? `${methodNameSpace}::` : '')}${capitalize(method)} -${usesMacroInferno ? '' : ' Error:'}`;
    const typeErrMsg = argN => `${getErrPrefix()} expected ${usesMacroInferno ? 'arg' : 'argument'} ${argN} to be of type`;
    const propErrMsg = prop => `${getErrPrefix()} expected property ${prop} to be of type`;

    const expectSuccess = (args, done) => {
      const dut = getDut();
      if (isPromised) {
        return dut[method].apply(dut, args)
          .then(expectOutputPromisified(done, dut, args))
          .catch(done);
      } else if (isCallbacked) {
        args.push(expectOutputCallbacked(done, dut, args));
        return dut[method].apply(dut, args);
      }
      expectOutput(dut[method].apply(dut, args), dut, args);
      return done();
    };

    const expectError = (args, errMsg, done) => {
      const dut = getDut();
      if (isPromised) {
        return dut[method].apply(dut, args)
          .then(() => {
            done('expected an error to be thrown');
          })
          .catch((err) => {
            assert.include(err.toString(), errMsg);
            done();
          })
          .catch(done);
      }

      if (isCallbacked) {
        const argsWithCb = args.concat((err) => {
          try {
            expect(err).to.be.an('error');
            assert.include(err.toString(), errMsg);
            done();
          } catch (e) {
            done(e);
          }
        });

        return dut[method].apply(dut, argsWithCb);
      }

      assertError(
        () => dut[method].apply(dut, args),
        errMsg
      );
      return done();
    };

    it('should be callable with required args', (done) => {
      const args = getRequiredArgs().slice();
      expectSuccess(args, done);
    });

    if (hasRequiredArgs) {
      it('should throw if required arg invalid', (done) => {
        const args = [undefined];
        expectError(args, typeErrMsg(0), done);
      });
    }

    if (hasOptArgs) {
      it('should be callable with optional args', (done) => {
        const args = getRequiredArgs().slice().concat(getOptionalArgs());
        expectSuccess(args, done);
      });

      it('should throw if opt arg invalid', (done) => {
        const args = getRequiredArgs().slice().concat(undefined);
        expectError(args, typeErrMsg(getRequiredArgs().length), done);
      });

      if (hasOptArgsObject) {
        it('should be callable with optional args object', (done) => {
          const args = getRequiredArgs().slice().concat(getOptionalArgsObject());
          expectSuccess(args, done);
        });

        it('should throw if opt arg object prop invalid', (done) => {
          const prop = getOptionalArgsMap()[0][0];
          const args = getRequiredArgs().slice().concat({
            [prop]: undefined
          });
          expectError(args, propErrMsg(prop), done);
        });
      }
    }
  };

  describe('sync', () => {
    if (beforeHook) {
      beforeEach(() => beforeHook());
    }
    if (afterHook) {
      afterEach(() => afterHook());
    }

    if (hasRequiredArgs) {
      funcShouldRequireArgs(() => getDut()[methodName]());
    }

    generateTests();

    otherSyncTests();
  });

  if (hasAsync) {
    describe('async', () => {
      if (hasRequiredArgs) {
        asyncFuncShouldRequireArgs(() => getDut()[methodNameAsync]());
      }

      describe('callbacked', () => {
        if (beforeHook) {
          beforeEach(() => beforeHook());
        }
        if (afterHook) {
          afterEach(() => afterHook());
        }

        generateTests('callbacked');

        otherAsyncCallbackedTests();
      });

      describe('promisified', () => {
        if (beforeHook) {
          beforeEach(() => beforeHook());
        }
        if (afterHook) {
          afterEach(() => afterHook());
        }

        generateTests('promised');

        otherAsyncPromisedTests();
      });
    });
  }
};
