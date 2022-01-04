import { Mat } from '../typings';
import { cv, getCachedFile } from './utils';


async function main() {
  if (!cv.xmodules || !cv.xmodules.face) {
    console.error(`exiting: opencv4nodejs (${cv.version.major}.${cv.version.minor}) compiled without face module`);
    return;
  }
  
  const modelFile = await getCachedFile("../data/face/lbfmodel.yaml", 'https://raw.githubusercontent.com/kurnianggoro/GSOC2017/master/data/lbfmodel.yaml', 'could not find landmarks model');
  const classifier = new cv.CascadeClassifier(cv.HAAR_FRONTALFACE_ALT2);
  // create the facemark object with the landmarks model
  const facemark = new cv.FacemarkLBF();
  facemark.loadModel(modelFile);

  // give the facemark object it's face detection callback
  facemark.setFaceDetector((frame: Mat) => {
    const { objects } = classifier.detectMultiScale(frame, 1.12);
    return objects;
  });

  // retrieve faces using the facemark face detector callback
  const image = cv.imread("../data/got.jpg");
  const gray = image.bgrToGray();
  const faces = facemark.getFaces(gray);

  // use the detected faces to detect the landmarks
  const faceLandmarks = facemark.fit(gray, faces);

  for (let i = 0; i < faceLandmarks.length; i++) {
    const landmarks = faceLandmarks[i];
    for (let x = 0; x < landmarks.length; x++) {
      image.drawCircle(landmarks[x], 1, new cv.Vec3(0, 255, 0), 1, cv.LINE_8);
    }
  }

  cv.imshowWait("VideoCapture", image);
}
main();