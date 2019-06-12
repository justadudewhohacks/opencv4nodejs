const {
  assert,
  expect
} = require('chai');

const {
  assertError,
  asyncFuncShouldRequireArgs,
  _funcShouldRequireArgs: funcShouldRequireArgs
} = require('./testUtils');

const {
  emptyFunc,
  getEmptyArray
} = require('./commons');

const getDefaultAPITestOpts = (opts) => ({
  getRequiredArgs: getEmptyArray,
  getOptionalArgsMap: getEmptyArray,
  hasAsync: true,
  otherSyncTests: emptyFunc,
  otherAsyncCallbackedTests: emptyFunc,
  otherAsyncPromisedTests: emptyFunc,
  beforeHook: null,
  afterHook: null,
  explicitHasRequiredArgs: false,
  ...opts
})

exports.getDefaultAPITestOpts = getDefaultAPITestOpts

exports.generateAPITests = (opts) => {
  const {
    getDut,
    methodName,
    methodNameSpace,
    expectOutput,
    getRequiredArgs,
    getOptionalArgsMap,
    hasAsync,
    otherSyncTests,
    otherAsyncCallbackedTests,
    otherAsyncPromisedTests,
    beforeHook,
    afterHook,
    explicitHasRequiredArgs
  } = getDefaultAPITestOpts(opts)

  const methodNameAsync = `${methodName}Async`;
  const getOptionalArgs = opts.getOptionalArgs || (() => getOptionalArgsMap().map(kv => kv[1]));
  const getOptionalArgsObject = () => {
    const optionalArgsObject = {};
    getOptionalArgsMap().forEach((kv) => { optionalArgsObject[kv[0]] = kv[1]; });
    return optionalArgsObject;
  };

  // use explicitHasRequiredArgs if getRequiredArgs would throw because args
  // may be initialized in a before statement and are undefined during test creation
  const hasRequiredArgs = explicitHasRequiredArgs || !!getRequiredArgs().length;
  const hasOptArgs = !!getOptionalArgs().length;
  const hasOptArgsObject = getOptionalArgs().length > 1;

  const expectAsyncOutput = (done, dut, args, res) => {
    try {
      expectOutput(res, dut, args);
      done();
    } catch (err) {
      done(err);
    }

  }

  const expectOutputCallbacked = (done, dut, args) => (err, res) => {
    if (err) {
      return done(err);
    }
    expectAsyncOutput(done, dut, args, res);
  };

  const expectOutputPromisified = (done, dut, args) => res => expectAsyncOutput(done, dut, args, res);

  const generateTests = (type) => {
    const isCallbacked = type === 'callbacked';
    const isPromised = type === 'promised';
    const isAsync = isCallbacked || isPromised;

    const method = isAsync ? methodNameAsync : methodName;
    const capitalize = str => str.charAt(0).toUpperCase() + str.slice(1);

    const getErrPrefix = () => `${(methodNameSpace ? `${methodNameSpace}::` : '')}${capitalize(method)} - Error:`;
    const typeErrMsg = argN => `${getErrPrefix()} expected argument ${argN} to be of type`;
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
