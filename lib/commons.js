"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.isElectronWebpack = exports.resolvePath = void 0;
const path = require("path");
function resolvePath(filePath, file) {
    if (!filePath) {
        return '';
    }
    return (file ? path.resolve(filePath, file) : path.resolve(filePath)).replace(/\\/g, '/');
}
exports.resolvePath = resolvePath;
/**
  * detect if electron https://github.com/electron/electron/issues/2288
 */
function isElectronWebpack() {
    // return process.versions.hasOwnProperty('electron');
    // assume module required by webpack if no system path inv envs
    return !process.env.path
        // eslint-disable-next-line @typescript-eslint/no-explicit-any
        && global.window && global.window.process && global.window.process.type
        && global.navigator && ((global.navigator.userAgent || '').toLowerCase().indexOf(' electron/') > -1);
}
exports.isElectronWebpack = isElectronWebpack;
