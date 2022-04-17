"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
const opencv_build_1 = require("@u4/opencv-build");
const fs_1 = __importDefault(require("fs"));
const path_1 = __importDefault(require("path"));
const commons_1 = require("./commons");
const picocolors_1 = __importDefault(require("picocolors"));
const npmlog_1 = require("npmlog");
const logDebug = process.env.OPENCV4NODES_DEBUG_REQUIRE ? npmlog_1.info : () => { };
function getOpenCV(opt) {
    if (!opt)
        opt = { prebuild: 'latestBuild' };
    const builder = new opencv_build_1.OpenCVBuilder(opt);
    function tryGetOpencvBinDir() {
        if (process.env.OPENCV_BIN_DIR) {
            logDebug('tryGetOpencvBinDir', `${picocolors_1.default.yellow('OPENCV_BIN_DIR')} environment variable is set`);
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
    let opencvBuild = null;
    let requirePath = '';
    if ((0, commons_1.isElectronWebpack)()) {
        requirePath = '../build/Release/opencv4nodejs.node';
    }
    else {
        requirePath = path_1.default.join(__dirname, process.env.BINDINGS_DEBUG ? '../build/Debug/opencv4nodejs' : '../build/Release/opencv4nodejs');
    }
    try {
        logDebug('require', `require path is ${picocolors_1.default.yellow(requirePath)}`);
        opencvBuild = require(requirePath);
    }
    catch (err) {
        // err.code === 'ERR_DLOPEN_FAILED'
        logDebug('require', `failed to require cv with exception: ${picocolors_1.default.red(err.toString())}`);
        logDebug('require', 'attempting to add opencv binaries to path');
        if (!process.env.path) {
            logDebug('require', 'there is no path environment variable, skipping...');
            throw err;
        }
        const opencvBinDir = tryGetOpencvBinDir();
        logDebug('require', 'adding opencv binary dir to path: ' + opencvBinDir);
        if (!fs_1.default.existsSync(opencvBinDir)) {
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
                const msg = `require("${picocolors_1.default.yellow(requirePath)}"); 
Failed with: ${e.message}, openCV binding not available, reed: 
build-opencv --help
And build missing file with:
build-opencv --version 4.5.4 rebuild

PS: a 'npm link' may help
`;
                throw Error(msg);
            }
            throw e;
        }
    }
    // resolve haarcascade files
    const { haarCascades, lbpCascades } = opencvBuild;
    Object.keys(haarCascades).forEach(key => opencvBuild[key] = (0, commons_1.resolvePath)(path_1.default.join(__dirname, 'haarcascades'), haarCascades[key]));
    Object.keys(lbpCascades).forEach(key => opencvBuild[key] = (0, commons_1.resolvePath)(path_1.default.join(__dirname, 'lbpcascades'), lbpCascades[key]));
    return opencvBuild;
}
module.exports = getOpenCV;
