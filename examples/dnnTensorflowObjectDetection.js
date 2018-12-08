/**
 * Please refer to the python version of "ExploreOpencvDnn" by Saumya Shovan Roy.
 * For more detail: https://github.com/rdeepc/ExploreOpencvDnn
 */
const fs = require("fs");
const path = require("path");
const classNames = require("./dnnTensorflowObjectDetectionClassNames");
const { cv, runVideoDetection } = require("./utils");

if (!cv.xmodules.dnn) {
  throw new Error("exiting: opencv4nodejs compiled without dnn module");
}

// replace with path where you unzipped detection model
const detectionModelPath = "../data/dnn/tf-detection";

const pbFile = path.resolve(detectionModelPath, "frozen_inference_graph.pb");
const pbtxtFile = path.resolve(
  detectionModelPath,
  "ssd_mobilenet_v2_coco_2018_03_29.pbtxt"
);

if (!fs.existsSync(pbFile) || !fs.existsSync(pbtxtFile)) {
  console.log("could not find detection model");
  console.log(
    "download the model from: https://github.com/opencv/opencv/wiki/TensorFlow-Object-Detection-API#use-existing-config-file-for-your-model"
  );
  throw new Error("exiting");
}

// set webcam port
const webcamPort = 0;

// initialize tensorflow darknet model from modelFile
const net = cv.readNetFromTensorflow(pbFile, pbtxtFile);

const classifyImg = img => {
  // object detection model works with 300 x 300 images
  const size = new cv.Size(300, 300);
  const vec3 = new cv.Vec(0, 0, 0);

  // network accepts blobs as input
  const inputBlob = cv.blobFromImage(img, 1, size, vec3, true, true);
  net.setInput(inputBlob);

  console.time("net.forward");
  // forward pass input through entire network, will return
  // classification result as 1x1xNxM Mat
  const outputBlob = net.forward();
  console.timeEnd("net.forward");

  // get height and width from the image
  const [imgHeight, imgWidth] = img.sizes;
  const numRows = outputBlob.sizes.slice(2, 3);

  for (let y = 0; y < numRows; y += 1) {
    const confidence = outputBlob.at([0, 0, y, 2]);
    if (confidence > 0.5) {
      const classId = outputBlob.at([0, 0, y, 1]);
      const className = classNames[classId];
      const boxX = imgWidth * outputBlob.at([0, 0, y, 3]);
      const boxY = imgHeight * outputBlob.at([0, 0, y, 4]);
      const boxWidht = imgWidth * outputBlob.at([0, 0, y, 5]);
      const boxHeight = imgHeight * outputBlob.at([0, 0, y, 6]);

      const pt1 = new cv.Point(boxX, boxY);
      const pt2 = new cv.Point(boxWidht, boxHeight);
      const rectColor = new cv.Vec(23, 230, 210);
      const rectThickness = 2;
      const rectLineType = cv.LINE_8;

      // draw the rect for the object
      img.drawRectangle(pt1, pt2, rectColor, rectThickness, rectLineType);

      const text = `${className} ${confidence.toFixed(5)}`;
      const org = new cv.Point(boxX, boxY + 15);
      const fontFace = cv.FONT_HERSHEY_SIMPLEX;
      const fontScale = 0.5;
      const textColor = new cv.Vec(255, 0, 0);
      const thickness = 2;

      // put text on the object
      img.putText(text, org, fontFace, fontScale, textColor, thickness);
    }
  }

  cv.imshow("Temsorflow Object Detection", img);
};

runVideoDetection(webcamPort, classifyImg);
