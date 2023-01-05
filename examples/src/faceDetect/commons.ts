import { cv, grabFrames, drawBlueRect } from '../utils';
import loadFacenet from '../dnn/loadFacenet';
import { extractResults } from '../dnn/ssdUtils';
import { Mat, Net, Rect } from '@u4/opencv4nodejs';

/**
 * 
 * @param src video file name or capture device ID
 * @param detectFaces sync face detection method
 * @returns 
 */
export const runVideoFaceDetection = (src: string | number, detectFaces: (img: Mat) => Rect[]) => grabFrames(src, 1, (frame, frmId) => {
  const timerName = `detection time ${frmId}`
  console.time(timerName);
  const frameResized = frame.resizeToMax(800);

  // detect faces
  const faceRects = detectFaces(frameResized);
  if (faceRects.length) {
    // draw detection
    faceRects.forEach(faceRect => drawBlueRect(frameResized, faceRect));
  }
  cv.imshow('face detection', frameResized);
  console.timeEnd(timerName);
});


export const runVideoFaceDetectionAsync = (src: string | number, detectFaces: (img: Mat) => Promise<Rect[]>) => grabFrames(src, 1, async (frame, frmId) => {
  const timerName = `detection time ${frmId}`
  console.time(timerName);
  const frameResized = await frame.resizeToMaxAsync(800);
  // detect faces
  const faceRects = await detectFaces(frameResized);
  if (faceRects.length) {
    // draw detection
    faceRects.forEach(faceRect => drawBlueRect(frameResized, faceRect));
  }

  cv.imshow('face detection', frameResized);
  console.timeEnd(timerName);
});


function classifyImg(net: Net, img: Mat) {
  // facenet model works with 300 x 300 images
  const imgResized = img.resizeToMax(300);

  // network accepts blobs as input
  const inputBlob = cv.blobFromImage(imgResized);
  net.setInput(inputBlob);

  // forward pass input through entire network, will return
  // classification result as 1x1xNxM Mat
  let outputBlob = net.forward();
  // extract NxM Mat
  outputBlob = outputBlob.flattenFloat(outputBlob.sizes[2], outputBlob.sizes[3]);

  return extractResults(outputBlob, img);
}

export const makeRunDetectFacenetSSD = function () {
  const net = loadFacenet();
  return function (img: Mat, minConfidence: number) {
    const predictions = classifyImg(net, img);

    predictions
      .filter(res => res.confidence > minConfidence)
      .forEach(p => drawBlueRect(img, p.rect));

    return img;
  }
}
