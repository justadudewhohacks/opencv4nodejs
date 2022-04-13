import { assert } from 'console';
import fs from 'fs';
import mri from 'mri';
import { Mat, Net, Point2, Rect, Size, Vec3, VideoCapture, VideoWriter } from '@u4/opencv4nodejs';
import { cv, getCachedFile } from '../utils';
import path from 'path';

// ported from https://github.com/spmallick/learnopencv/blob/master/ObjectDetection-YOLO/object_detection_yolo.py

const conf = {
    confThreshold: 0.5,// Confidence threshold
    nmsThreshold: 0.4, // Non-maximum suppression threshold
    inpWidth: 416,     // Width of network's input image
    inpHeight: 416,    // Height of network's input image}
}

const args: { image?: string, video?: string, device?: string, help?: boolean } = mri(process.argv.slice(2), { default: { device: 'cpu' }, alias: { h: 'help' } });

if (args.help) {
    console.log('Object Detection using YOLO in OPENCV');
    console.log('--device Device to perform inference on \'cpu\' or \'gpu\'. (default is cpu)');
    console.log('--image  Path to image file.');
    console.log('--video  Path to video file.');
    process.exit(0);
}

const device = args.device || 'cpu';

async function main() {
    // # Load names of classes
    const classesFile = path.resolve(__dirname, "coco.names");
    // classes = None
    const classes = fs.readFileSync(classesFile, 'utf8').split(/[\r\n]+/);

    // Give the configuration and weight files for the model and load the network using them.
    const modelConfiguration = path.resolve(__dirname, "yolov3.cfg")
    const modelWeights = await getCachedFile("yolov3.weights", 'https://pjreddie.com/media/files/yolov3.weights')

    const net: Net = cv.readNetFromDarknet(modelConfiguration, modelWeights)

    if (device == 'cpu') {
        net.setPreferableBackend(cv.DNN_BACKEND_OPENCV)
        net.setPreferableTarget(cv.DNN_TARGET_CPU)
        console.log('Using CPU device.')
    } else if (device == 'gpu') {
        net.setPreferableBackend(cv.DNN_BACKEND_CUDA)
        net.setPreferableTarget(cv.DNN_TARGET_CUDA)
        console.log('Using GPU device.')
    }

    // Get the names of the output layers
    const getOutputsNames = (net: Net): string[] => {
        // Get the names of all the layers in the network
        const layersNames = net.getLayerNames()
        // Get the names of the output layers, i.e. the layers with unconnected outputs
        return net.getUnconnectedOutLayers().map(i => layersNames[i - 1]);
        // return [layersNames[i[0] - 1]// for i in net.getUnconnectedOutLayers()]
    }

    // Draw the predicted bounding box
    const drawPred = (frame: Mat, classId: number, conf: number, left: number, top: number, right: number, bottom: number): void => {
        // Draw a bounding box.
        frame.drawRectangle(new Point2(left, top), new Point2(right, bottom), new Vec3(255, 178, 50), 3)
        let label = Math.round(conf * 100) + '%';

        // Get the label for the class name and its confidence
        if (classes) {
            assert(classId < classes.length, 'classId < classes.length')
            label = `${classes[classId]}:${label}`
        }
        //Display the label at the top of the bounding box
        const { size: labelSize, baseLine } = cv.getTextSize(label, cv.FONT_HERSHEY_SIMPLEX, 0.5, 1)
        top = Math.max(top, labelSize.height)
        frame.drawRectangle(new Point2(left, top - Math.round(1.5 * labelSize.height)), new Point2(left + Math.round(1.5 * labelSize.width), top + baseLine), new Vec3(255, 255, 255), cv.FILLED)
        frame.putText(label, new Point2(left, top), cv.FONT_HERSHEY_SIMPLEX, 0.75, new Vec3(0, 0, 0), 1)
    }

    // Remove the bounding boxes with low confidence using non-maxima suppression
    const postprocess = (frame: Mat, outs: Mat[]) => {
        const frameHeight = frame.rows;
        const frameWidth = frame.cols;

        // Scan through all the bounding boxes output from the network and keep only the
        // ones with high confidence scores. Assign the box's class label as the class with the highest score.
        const classIds: number[] = []
        const confidences: number[] = []
        const boxes: Rect[] = []
        for (const out of outs) {
            for (const detection of out.getDataAsArray()) {
                const scores = detection.slice(5);
                let classId = -1;
                let confidence = 0;
                for (let i = 0; i < scores.length; i++) {
                    if (scores[i] > confidence) {
                        confidence = scores[i];
                        classId = i;
                    }
                }
                if (confidence > conf.confThreshold) {
                    const [cx, cy, w, h] = detection;
                    const center_x = Math.round(cx * frameWidth)
                    const center_y = Math.round(cy * frameHeight)
                    const width = Math.round(w * frameWidth)
                    const height = Math.round(h * frameHeight)
                    const left = Math.round(center_x - width / 2)
                    const top = Math.round(center_y - height / 2)

                    classIds.push(classId)
                    confidences.push(confidence)
                    boxes.push(new Rect(left, top, width, height))
                }
            }
        }
        // Perform non maximum suppression to eliminate redundant overlapping boxes with
        // lower confidences.
        const indices = cv.NMSBoxes(boxes, confidences, conf.confThreshold, conf.nmsThreshold)
        for (const i of indices) {
            // i = i[0]
            const box = boxes[i]
            const left = box.x
            const top = box.y
            const width = box.width
            const height = box.height
            drawPred(frame, classIds[i], confidences[i], left, top, left + width, top + height)
        }
    }
    // Process inputs
    const winName = 'Deep learning object detection in OpenCV'
    cv.namedWindow(winName, cv.WINDOW_NORMAL)

    let outputFile = "yolo_out_py.avi"
    let cap: VideoCapture;
    if (args.image) {
        // Open the image file
        if (!fs.existsSync(args.image)) {
            console.error("Input image file ", args.image, " doesn't exist")
            process.exit(1)
        }
        cap = new cv.VideoCapture(args.image)
        outputFile = args.image.substring(0, args.image.length - 4) + '_yolo_out.jpg'
    } else if (args.video) {
        // Open the video file
        if (!fs.existsSync(args.video)) {
            console.error("Input video file ", args.video, " doesn't exist")
            process.exit(1)
        }
        cap = new cv.VideoCapture(args.video)
        outputFile = args.video.substring(0, args.video.length - 4) + '_yolo_out.avi'
    } else {
        // Webcam input
        cap = new cv.VideoCapture(0)
    }
    let vid_writer: VideoWriter | null = null;
    // Get the video writer initialized to save the output video
    if (!args.image) {
        const fps = 25;
        const frameSize = new cv.Size(cap.get(cv.CAP_PROP_FRAME_WIDTH), cap.get(cv.CAP_PROP_FRAME_HEIGHT));
        vid_writer = new VideoWriter(outputFile, VideoWriter.fourcc('MJPG'), fps, frameSize);
    }
    const size = new Size(conf.inpWidth, conf.inpHeight);
    const mean = new Vec3(0, 0, 0);
    while (cv.waitKey(1) < 0) {
        //# get frame from the video
        const frame: Mat = cap.read()
        // Stop the program if reached end of video
        if (!frame || frame.sizes.length === 0) { // hasFrame:
            console.log("Done processing !!!")
            console.log("Output file is stored as ", outputFile)
            cv.waitKey(6000)
            // Release device
            cap.release()
            break
        }
        // Create a 4D blob from a frame.
        const blob: Mat = cv.blobFromImage(frame, { scaleFactor: 1 / 255, size, mean, swapRB: true, crop: false })
        // Sets the input to the network
        net.setInput(blob)
        // Runs the forward pass to get output of the output layers
        const layersNames: string[] = getOutputsNames(net);
        const outs = net.forward(layersNames)
        // Remove the bounding boxes with low confidence
        postprocess(frame, outs)
        // Put efficiency information. The function getPerfProfile returns the overall time for inference(t) and the timings for each of the layers(in layersTimes)
        const { retval } = net.getPerfProfile()
        const label = `Inference time: ${(retval * 1000.0 / cv.getTickFrequency()).toFixed(2)} ms`;
        // Write the frame with the detection boxes
        frame.putText(label, new Point2(0, 15), cv.FONT_HERSHEY_SIMPLEX, 0.5, new Vec3(0, 0, 255))
        if (vid_writer)
            vid_writer.write(frame)
        else
            cv.imwrite(outputFile, frame)
        cv.imshow(winName, frame)
    }
}

main();