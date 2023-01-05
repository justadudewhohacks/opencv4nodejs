"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.getOpenCV = void 0;
const opencv_build_1 = require("@u4/opencv-build");
const fs = require("fs");
const path = require("path");
const commons_js_1 = require("./commons.js");
const pc = require("picocolors");
const npmlog_1 = require("npmlog");
const logDebug = process.env.OPENCV4NODES_DEBUG_REQUIRE ? npmlog_1.info : () => { };
function tryGetOpencvBinDir(builder) {
    if (process.env.OPENCV_BIN_DIR) {
        logDebug('tryGetOpencvBinDir', `${pc.yellow('OPENCV_BIN_DIR')} environment variable is set`);
        return process.env.OPENCV_BIN_DIR;
    }
    // if the auto build is not disabled via environment do not even attempt
    // to read package.json
    if (!builder.env.isAutoBuildDisabled) {
        logDebug('tryGetOpencvBinDir', 'auto build has not been disabled via environment variable, using opencv bin dir of opencv-build');
        return builder.env.opencvBinDir;
    }
    logDebug('tryGetOpencvBinDir', 'auto build has not been explicitly disabled via environment variable, attempting to read envs from package.json...');
    // const envs = builder.env.readEnvsFromPackageJson()
    if (!builder.env.isAutoBuildDisabled && process.env.OPENCV_BIN_DIR) {
        logDebug('tryGetOpencvBinDir', 'auto build has not been disabled via package.json, using opencv bin dir of opencv-build');
        return process.env.OPENCV_BIN_DIR; //.opencvBinDir
    }
    if (builder.env.opencvBinDir) {
        logDebug('tryGetOpencvBinDir', 'found opencv binary environment variable in package.json');
        return builder.env.opencvBinDir;
    }
    logDebug('tryGetOpencvBinDir', 'failed to find opencv binary environment variable in package.json');
    return null;
}
function getOpenCV(opt) {
    if (!opt)
        opt = { prebuild: 'latestBuild' };
    const builder = new opencv_build_1.OpenCVBuilder(opt);
    let opencvBuild = null;
    let requirePath = '';
    if ((0, commons_js_1.isElectronWebpack)()) {
        requirePath = '../build/Release/opencv4nodejs.node';
    }
    else {
        requirePath = path.join(__dirname, '../build/Debug/opencv4nodejs.node');
        if (!fs.existsSync(requirePath)) {
            requirePath = path.join(__dirname, '../build/Release/opencv4nodejs.node');
        }
        requirePath = requirePath.replace(/\.node$/, '');
        // path.join(__dirname, process.env.BINDINGS_DEBUG ? '../build/Debug/opencv4nodejs' : '../build/Release/opencv4nodejs')
    }
    try {
        logDebug('require', `require path is ${pc.yellow(requirePath)}`);
        opencvBuild = require(requirePath);
    }
    catch (err) {
        // err.code === 'ERR_DLOPEN_FAILED'
        logDebug('require', `failed to require cv with exception: ${pc.red(err.toString())}`);
        logDebug('require', 'attempting to add opencv binaries to path');
        if (!process.env.path) {
            logDebug('require', 'there is no path environment variable, skipping...');
            throw err;
        }
        const opencvBinDir = tryGetOpencvBinDir(builder);
        logDebug('require', 'adding opencv binary dir to path: ' + opencvBinDir);
        if (!fs.existsSync(opencvBinDir)) {
            throw new Error('opencv binary dir does not exist: ' + opencvBinDir);
        }
        // ensure binaries are added to path on windows
        if (!process.env.path.includes(opencvBinDir)) {
            process.env.path = `${process.env.path};${opencvBinDir};`;
        }
        logDebug('require', 'process.env.path: ' + process.env.path);
        try {
            opencvBuild = require(requirePath);
        }
        catch (e) {
            if (e instanceof Error) {
                let msg = '';
                const message = e.message;
                if (message.startsWith('Cannot find module')) {
                    msg = `require("${pc.yellow(requirePath)}"); 
          Failed with: ${pc.red(message)}, openCV binding not available, reed: 
          build-opencv --help
          And build missing file with:
          npx build-opencv --version 4.6.0 rebuild
          
          PS: a 'npm link' may help
          `;
                }
                else if (message.startsWith('The specified module could not be found.')) {
                    msg = `require("${pc.yellow(requirePath)}"); 
          Failed with: ${pc.red(message)}, openCV module looks broken, clean you builds directory and rebuild everything
          rm -r <path to your build directory>
          npx build-opencv --version 4.6.0 rebuild
          `;
                }
                else {
                    msg = `require("${pc.yellow(requirePath)}"); 
          Failed with: ${pc.red(message)}
          `;
                }
                throw Error(msg);
            }
            throw e;
        }
    }
    // resolve haarcascade files
    // eslint-disable-next-line @typescript-eslint/no-explicit-any
    const { haarCascades, lbpCascades } = opencvBuild;
    Object.keys(haarCascades).forEach(key => opencvBuild[key] = (0, commons_js_1.resolvePath)(path.join(__dirname, 'haarcascades'), haarCascades[key]));
    Object.keys(lbpCascades).forEach(key => opencvBuild[key] = (0, commons_js_1.resolvePath)(path.join(__dirname, 'lbpcascades'), lbpCascades[key]));
    return opencvBuild;
}
exports.getOpenCV = getOpenCV;
exports.default = getOpenCV;
