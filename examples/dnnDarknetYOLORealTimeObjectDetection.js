/**
 * Please refer to the python version of "YOLO object detection with OpenCV" by Adrian Rosebrock.
 * For more detail: https://www.pyimagesearch.com/2018/11/12/yolo-object-detection-with-opencv/
 */
const fs = require("fs");
const path = require("path");
const { cv, drawBlueRect, runVideoDetection } = require("./utils");

if (!cv.xmodules.dnn) {
  throw new Error("exiting: opencv4nodejs compiled without dnn module");
}

// replace with path where you unzipped darknet model
const darknetPath = "../data/dnn/yolo-object-detection";

const cfgFile = path.resolve(darknetPath, "yolov3-tiny.cfg");
const weightsFile = path.resolve(darknetPath, "yolov3-tiny.weights");
const labelsFile = path.resolve(darknetPath, "coco.names");

if (
  !fs.existsSync(weightsFile) ||
  !fs.existsSync(cfgFile) ||
  !fs.existsSync(labelsFile)
) {
  console.log("could not find darknet model");
  console.log("download the model from: https://pjreddie.com/darknet/yolo/");
  throw new Error("exiting");
}

// set webcam port
const webcamPort = 0;

const minConfidence = 0.5;
const nmsThreshold = 0.3;

// read classNames and store them in an array
const labels = fs
  .readFileSync(labelsFile)
  .toString()
  .split("\n");

// initialize tensorflow darknet model from modelFile
const net = cv.readNetFromDarknet(cfgFile, weightsFile);

const classifyImg = img => {
  // object detection model works with 416 x 416 images
  const size = new cv.Size(416, 416);
  const vec3 = new cv.Vec(0, 0, 0);
  const [imgHeight, imgWidth] = img.sizes;

  // network accepts blobs as input
  const inputBlob = cv.blobFromImage(img, 1 / 255.0, size, vec3, true, true);
  net.setInput(inputBlob);

  // specify two layers "yolo_16" and "yolo_23"
  const layerNames = ["yolo_16", "yolo_23"];

  console.time("net.forward");
  // forward pass input through entire network
  const layerOutputs = net.forward(layerNames);
  console.timeEnd("net.forward");

  let boxes = [];
  let confidences = [];
  let classIDs = [];

  layerOutputs.forEach(mat => {
    const output = mat.getDataAsArray();
    output.forEach(detection => {
      const scores = detection.slice(5);
      const classId = scores.indexOf(Math.max(...scores));
      const confidence = scores[classId];

      if (confidence > minConfidence) {
        const box = detection.slice(0, 4);

        const centerX = parseInt(box[0] * imgWidth);
        const centerY = parseInt(box[1] * imgHeight);
        const width = parseInt(box[2] * imgWidth);
        const height = parseInt(box[3] * imgHeight);

        const x = parseInt(centerX - width / 2);
        const y = parseInt(centerY - height / 2);

        boxes.push(new cv.Rect(x, y, width, height));
        confidences.push(confidence);
        classIDs.push(classId);

        const indices = cv.NMSBoxes(
          boxes,
          confidences,
          minConfidence,
          nmsThreshold
        );

        indices.forEach(i => {
          const rect = boxes[i];
          const imgRect = new cv.Rect(rect.x, rect.y, rect.width, rect.height);
          drawBlueRect(img, imgRect);
          const text = labels[classIDs[i]];
          img.putText(
            text,
            new cv.Point(rect.x, rect.y + 0.1 * imgHeight),
            cv.FONT_ITALIC,
            2,
            {
              color: new cv.Vec(255, 0, 0),
              thickness: 2
            }
          );
          drawBlueRect(img, imgRect);
        });
      }
    });
  });

  cv.imshow("Darknet YOLO Object Detection", img);
};

runVideoDetection(webcamPort, classifyImg);
