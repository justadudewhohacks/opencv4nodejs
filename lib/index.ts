import promisify from './promisify';
import extendWithJsSources from './src';
import * as OpenCV from './typings/cv';

const isElectronWebpack =
  // assume module required by webpack if no system path inv envs
  !process.env.path
  // detect if electron https://github.com/electron/electron/issues/2288
  && global.window && global.window.process && (global.window.process as any).type
  && global.navigator && ((global.navigator.userAgent || '').toLowerCase().indexOf(' electron/') > -1)

let cvBase = isElectronWebpack ? require('../build/Release/opencv4nodejs.node') : require('./cv')
if (cvBase.default)
  cvBase = cvBase.default
// promisify async methods

let cv: typeof OpenCV = promisify(cvBase);
cv = extendWithJsSources(cv);

// module.exports = cv;
export default cv;