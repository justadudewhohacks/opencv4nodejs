/**
 * Please refer to the python version of "YOLO object detection with OpenCV" by Adrian Rosebrock.
 * For more detail: https://www.pyimagesearch.com/2018/11/12/yolo-object-detection-with-opencv/
 */
import fs from "fs";
import { Mat, Net, Rect } from '@u4/opencv4nodejs';
import { cv, getCachedFile, runVideoDetection } from "./utils";

class dnnDarknetYOLORealTimeObjectDetection {
  // set webcam port
  webcamPort = 0;
  minConfidence = 0.5;
  nmsThreshold = 0.3;
  labels: string[] = [];
  net!: Net;
  allLayerNames!: string[];
  layerNames!: string[];
  unconnectedOutLayers: number[] = [];

  private classifyImg(img: Mat) {
    // object detection model works with 416 x 416 images
    const size = new cv.Size(416, 416);
    const vec3 = new cv.Vec3(0, 0, 0);
    const [imgHeight, imgWidth] = img.sizes;

    // network accepts blobs as input
    const inputBlob = cv.blobFromImage(img, 1 / 255.0, size, vec3, true, false);
    this.net.setInput(inputBlob);

    console.time("net.forward");
    // forward pass input through entire network
    const layerOutputs = this.net.forward(this.layerNames);
    console.timeEnd("net.forward");

    const boxes: Rect[] = [];
    const confidences: number[] = [];
    const classIDs: number[] = [];

    layerOutputs.forEach(mat => {
      const output = mat.getDataAsArray();
      output.forEach(detection => {
        const scores = detection.slice(5);
        const classId = scores.indexOf(Math.max(...scores));
        const confidence = scores[classId];

        if (confidence > this.minConfidence) {
          const box = detection.slice(0, 4);

          const centerX = Math.floor(box[0] * imgWidth);
          const centerY = Math.floor(box[1] * imgHeight);
          const width = Math.floor(box[2] * imgWidth);
          const height = Math.floor(box[3] * imgHeight);

          const x = Math.floor(centerX - width / 2);
          const y = Math.floor(centerY - height / 2);

          boxes.push(new cv.Rect(x, y, width, height));
          confidences.push(confidence);
          classIDs.push(classId);

          const indices = cv.NMSBoxes(
            boxes,
            confidences,
            this.minConfidence,
            this.nmsThreshold
          );

          indices.forEach(i => {
            const rect = boxes[i];

            const pt1 = new cv.Point2(rect.x, rect.y);
            const pt2 = new cv.Point2(rect.x + rect.width, rect.y + rect.height);
            const rectColor = new cv.Vec3(255, 0, 0);
            const rectThickness = 2;
            const rectLineType = cv.LINE_8;

            // draw the rect for the object
            img.drawRectangle(pt1, pt2, rectColor, rectThickness, rectLineType);

            const text = this.labels[classIDs[i]];
            const org = new cv.Point2(rect.x, rect.y + 15);
            const fontFace = cv.FONT_HERSHEY_SIMPLEX;
            const fontScale = 0.5;
            const textColor = new cv.Vec3(123, 123, 255);
            const thickness = 2;

            // put text on the object
            img.putText(text, org, fontFace, fontScale, textColor, thickness);
          });
        }
      });
    });

    cv.imshow("Darknet YOLO Object Detection", img);
  }

  async run() {
    if (!cv.xmodules || !cv.xmodules.dnn) {
      console.error(`exiting: opencv4nodejs (${cv.version.major}.${cv.version.minor}) compiled without dnn module`);
      return;
    }

    const darknetPath = "../data/dnn/yolo-object-detection";
    const cfgFile = await getCachedFile(`${darknetPath}/yolov3-tiny.cfg`, 'https://raw.githubusercontent.com/pjreddie/darknet/master/cfg/yolov3-tiny.cfg', {notice: 'See https://pjreddie.com/darknet/yolo/'})
    const weightsFile = await getCachedFile(`${darknetPath}/yolov3-tiny.weights`, 'https://pjreddie.com/media/files/yolov3-tiny.weights', {notice: 'See https://pjreddie.com/darknet/yolo/'});
    const labelsFile = await getCachedFile(`${darknetPath}/coco.names`, 'https://raw.githubusercontent.com/pjreddie/darknet/master/data/coco.names', {notice: 'See https://pjreddie.com/darknet/yolo/'});
    if (
      !fs.existsSync(weightsFile) ||
      !fs.existsSync(cfgFile) ||
      !fs.existsSync(labelsFile)
    ) {
      console.log("could not find darknet model");
      console.log("Download the model from: https://pjreddie.com/darknet/yolo/");
      throw new Error("exiting");
    }

    // read classNames and store them in an array
    this.labels = fs
      .readFileSync(labelsFile)
      .toString()
      .split("\n");

    // initialize tensorflow darknet model from modelFile
    this.net = cv.readNetFromDarknet(cfgFile, weightsFile);
    this.allLayerNames = this.net.getLayerNames();
    this.unconnectedOutLayers = this.net.getUnconnectedOutLayers();

    // determine only the *output* layer names that we need from YOLO
    this.layerNames = this.unconnectedOutLayers.map(layerIndex => {
      return this.allLayerNames[layerIndex - 1];
    });

    runVideoDetection(this.webcamPort, (mat) => this.classifyImg(mat));
  }
}

new dnnDarknetYOLORealTimeObjectDetection().run();
