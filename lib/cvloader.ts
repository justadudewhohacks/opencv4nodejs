import { OpenCVBuilder } from '@u4/opencv-build';
import { OpenCVBuildEnvParams } from '@u4/opencv-build';
import fs from 'fs';
import path from 'path';
import { resolvePath } from './commons';
import pc from 'picocolors'
import { info } from 'npmlog';
import * as openCV from '..';
import { EOL } from 'os';

const logDebug = process.env.OPENCV4NODES_DEBUG_REQUIRE ? info : () => { /* ignore */}

function getOpenCV(opt?: OpenCVBuildEnvParams): typeof openCV {
  if (!opt)
    opt = { prebuild: 'latestBuild' }
  const builder = new OpenCVBuilder(opt);

  function tryGetOpencvBinDir() {
    if (process.env.OPENCV_BIN_DIR) {
      logDebug('tryGetOpencvBinDir', `${pc.yellow('OPENCV_BIN_DIR')} environment variable is set`)
      return process.env.OPENCV_BIN_DIR
    }
    // if the auto build is not disabled via environment do not even attempt
    // to read package.json
    if (!builder.env.isAutoBuildDisabled) {
      logDebug('tryGetOpencvBinDir', 'auto build has not been disabled via environment variable, using opencv bin dir of opencv-build')
      return builder.env.opencvBinDir
    }

    logDebug('tryGetOpencvBinDir', 'auto build has not been explicitly disabled via environment variable, attempting to read envs from package.json...')
    // const envs = builder.env.readEnvsFromPackageJson()

    if (!builder.env.isAutoBuildDisabled && process.env.OPENCV_BIN_DIR) {
      logDebug('tryGetOpencvBinDir', 'auto build has not been disabled via package.json, using opencv bin dir of opencv-build')
      return process.env.OPENCV_BIN_DIR //.opencvBinDir
    }

    if (builder.env.opencvBinDir) {
      logDebug('tryGetOpencvBinDir', 'found opencv binary environment variable in package.json')
      return builder.env.opencvBinDir as string
    }
    logDebug('tryGetOpencvBinDir', 'failed to find opencv binary environment variable in package.json')
    return null
  }

  let opencvBuild = null
  const requirePath = path.join(__dirname, process.env.BINDINGS_DEBUG ? '../build/Debug/opencv4nodejs' : '../build/Release/opencv4nodejs')
  try {
    logDebug('require', `require path is ${pc.yellow(requirePath)}`)
    opencvBuild = require(requirePath);
  } catch (err) {
    // err.code === 'ERR_DLOPEN_FAILED'
    logDebug('require', `failed to require cv with exception: ${pc.red(err.toString())}`)
    logDebug('require', 'attempting to add opencv binaries to path')

    if (!process.env.path) {
      logDebug('require', 'there is no path environment variable, skipping...')
      throw err
    }

    const opencvBinDir = tryGetOpencvBinDir()
    logDebug('require', 'adding opencv binary dir to path: ' + opencvBinDir)
    if (!fs.existsSync(opencvBinDir)) {
      throw new Error('opencv binary dir does not exist: ' + opencvBinDir)
    }
    // ensure binaries are added to path on windows
    if (!process.env.path.includes(opencvBinDir)) {
      process.env.path = `${process.env.path};${opencvBinDir};`
    }
    logDebug('require', 'process.env.path: ' + process.env.path)
    try {
      opencvBuild = require(requirePath);
    } catch(e) {
      if (e instanceof Error) {
        const msg = `${e.message}, openCV binding not available, see: ${EOL}build-opencv --help${EOL}${EOL}And start a build with:${EOL}build-opencv --version 4.5.4 build${EOL}`;
        throw Error(msg)
      }
      throw e;
    }
  }

  // resolve haarcascade files
  const { haarCascades, lbpCascades } = opencvBuild;
  Object.keys(haarCascades).forEach(
    key => opencvBuild[key] = resolvePath(path.join(__dirname, 'haarcascades'), haarCascades[key]));
  Object.keys(lbpCascades).forEach(
    key => opencvBuild[key] = resolvePath(path.join(__dirname, 'lbpcascades'), lbpCascades[key]));
  return opencvBuild;
}

 export = getOpenCV;