import { OpenCVParamBuildOptions } from '@u4/opencv-build/build/BuildEnv';
import promisify from './promisify';
import extendWithJsSources from './src';
// import * as OpenCV from './typings/cv';
import * as OpenCV from './typings/openCV';

function loadOpenCV(opt?: OpenCVParamBuildOptions): typeof OpenCV {
  //const isElectronWebpack =
  //  // assume module required by webpack if no system path inv envs
  //  !process.env.path
  //  // detect if electron https://github.com/electron/electron/issues/2288
  //  && global.window && global.window.process && (global.window.process as any).type
  //  && global.navigator && ((global.navigator.userAgent || '').toLowerCase().indexOf(' electron/') > -1)
  // let cvBase = isElectronWebpack ? require('../build/Release/opencv4nodejs.node') : require('./cv')
  let raw = require('./cv')
  if (raw.default)
    raw = raw.default

  const cvBase = raw(opt);
  if (!cvBase.accumulate) {
    throw Error('failed to load opencv basic accumulate not found.')
  }
  if (!cvBase.blur) {
    throw Error('failed to load opencv basic blur not found.')
  }
  // promisify async methods

  let cvObj: typeof OpenCV = promisify(cvBase);
  cvObj = extendWithJsSources(cvObj);
  return cvObj;
}

const cv = loadOpenCV({ prebuild: 'latestBuild' });

export default cv;