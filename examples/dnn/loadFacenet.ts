import fs from 'fs';
import path from 'path';
import { cv } from '../utils';

export default function () {
  const modelPath = path.resolve(path.join(__dirname, '..', '..', 'data', 'dnn', 'facenet'));

  const prototxt = path.resolve(modelPath, 'facenet.prototxt');
  const modelFile = path.resolve(modelPath, 'res10_300x300_ssd_iter_140000.caffemodel');

  if (!fs.existsSync(prototxt) || !fs.existsSync(modelFile)) {
    console.log(`could not find facenet model in ${modelPath}`);
    fs.mkdirSync(modelPath, {recursive: true});
    if (!fs.existsSync(prototxt))
      console.log(`download the prototxt from: https://raw.githubusercontent.com/opencv/opencv/master/samples/dnn/face_detector/deploy.prototxt to ${prototxt}`);

    if (!fs.existsSync(modelFile))
      console.log(`download the model from: https://raw.githubusercontent.com/opencv/opencv_3rdparty/dnn_samples_face_detector_20170830/res10_300x300_ssd_iter_140000.caffemodel to ${modelFile}`);
    throw new Error('exiting');
  }
  return cv.readNetFromCaffe(prototxt, modelFile);
};
