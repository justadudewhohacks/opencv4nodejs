const isFn = obj => typeof obj === 'function';
const isAsyncFn = fn => fn.prototype.constructor.name.endsWith('Async');

const promisify = (fn) => function () {
  if (isFn(arguments[arguments.length - 1])) {
    return fn.apply(this, arguments);
  }

  return new Promise((resolve, reject) => {
    const args = Array.prototype.slice.call(arguments);
    args.push(function(err, res) {
      if (err) {
        return reject(err);
      }
      return resolve(res);
    });

    fn.apply(this, args);
  });
};

module.exports = (cv) => {
  const fns = Object.keys(cv).filter(k => isFn(cv[k])).map(k => cv[k]);
  const asyncFuncs = fns.filter(isAsyncFn);
  const clazzes = fns.filter(fn => !!Object.keys(fn.prototype).length);

  clazzes.forEach((clazz) => {
    const protoFnKeys = Object.keys(clazz.prototype).filter(k => isAsyncFn(clazz.prototype[k]));
    protoFnKeys.forEach(k => clazz.prototype[k] = promisify(clazz.prototype[k]));
  });

  asyncFuncs.forEach((fn) => {
    cv[fn.prototype.constructor.name] = promisify(fn);
  });

  return cv;
};