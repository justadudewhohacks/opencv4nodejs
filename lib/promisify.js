"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
/* eslint-disable @typescript-eslint/no-explicit-any */
const isFn = (obj) => typeof obj === 'function';
const isAsyncFn = (fn) => { var _a, _b, _c; return (_c = (_b = (_a = fn.prototype) === null || _a === void 0 ? void 0 : _a.constructor) === null || _b === void 0 ? void 0 : _b.name) === null || _c === void 0 ? void 0 : _c.endsWith('Async'); };
const promisify = (fn) => function (...params) {
    if (isFn(params[params.length - 1])) {
        return fn.apply(this, params);
    }
    return new Promise((resolve, reject) => {
        const args = Array.prototype.slice.call(params);
        args.push(function (err, res) {
            if (err) {
                return reject(err);
            }
            return resolve(res);
        });
        fn.apply(this, args);
    });
};
exports.default = (cv) => {
    const fns = Object.keys(cv).filter(k => isFn(cv[k])).map(k => cv[k]);
    const asyncFuncs = fns.filter(isAsyncFn);
    const clazzes = fns.filter(fn => fn.prototype && !!Object.keys(fn.prototype).length);
    clazzes.forEach((clazz) => {
        const protoFnKeys = Object.keys(clazz.prototype).filter(k => isAsyncFn(clazz.prototype[k]));
        protoFnKeys.forEach(k => clazz.prototype[k] = promisify(clazz.prototype[k]));
    });
    asyncFuncs.forEach((fn) => {
        cv[fn.prototype.constructor.name] = promisify(fn);
    });
    return cv;
};
