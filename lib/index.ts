import promisify from './promisify';
import extendWithJsSources from './src';
import * as OpenCV from './typings/cv';
// import './typings/Mat';

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

let cvObj: typeof OpenCV = promisify(cvBase);
cvObj = extendWithJsSources(cvObj);
//TMP test TYping
if (false) {
  const a = new cvObj.Mat();
  // do not works
  // const b: cv.Mat = a;
  new cvObj.HistAxes({ channel: 1, bins: 1, ranges: [10, 10] })
  new cvObj.DescriptorMatch();
  new cvObj.DetectionROI();
  new cvObj.EigenFaceRecognizer();
  new cvObj.Facemark();
  new cvObj.FacemarkLBF();
}


// module.exports = cv;
export default cvObj;