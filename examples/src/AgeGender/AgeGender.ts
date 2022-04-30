import fs from 'fs';
import mri from 'mri';
import { Mat, Net, Point2, Rect, Size, Vec3, VideoCapture } from '@u4/opencv4nodejs';
import { cv, getCachedFile } from '../utils';
import path from 'path';

// ported from https://github.com/spmallick/learnopencv/blob/master/AgeGender/AgeGender.py

const getMaxIndex = (scores: number[]): number => {
    let max = Number.MIN_VALUE;
    let classId = -1;
    const len = scores.length;
    for (let i = 0; i < len; i++) {
        if (scores[i] > max) {
            max = scores[i];
            classId = i;
        }
    }
    return classId;
}


function getFaceBox(net: Net, frame: Mat, conf_threshold = 0.7): { frameFace: Mat, bboxes: Rect[] } {
    const frameOpencvDnn: Mat = frame.copy();
    const frameHeight = frameOpencvDnn.rows;
    const frameWidth = frameOpencvDnn.cols;
    const blob: Mat = cv.blobFromImage(frameOpencvDnn, { scaleFactor: 1.0, size: new Size(300, 300), mean: new Vec3(104, 117, 123), swapRB: true, crop: false });
    net.setInput(blob)
    const detections: Mat = net.forward()
    const bboxes: Rect[] = []
    // console.log('size:', detections.sizes);
    const max = detections.sizes[2];
    for (let i = 0; i < max; i++) {
        const confidence = detections.at([0, 0, i, 2])
        if (confidence > conf_threshold) {
            const x1 = detections.at([0, 0, i, 3]) * frameWidth;
            const y1 = detections.at([0, 0, i, 4]) * frameHeight;
            const x2 = detections.at([0, 0, i, 5]) * frameWidth;
            const y2 = detections.at([0, 0, i, 6]) * frameHeight;
            bboxes.push(new Rect(x1, y1, x2 - x1, y2 - y1))
            frameOpencvDnn.drawRectangle(new Point2(x1, y1), new Point2(x2, y2), new Vec3(0, 255, 0), Math.round(frameHeight / 150), cv.LINE_8);
        }
    }
    return { frameFace: frameOpencvDnn, bboxes };
}

const args: { input?: string, device?: string, help?: boolean } = mri(process.argv.slice(2), { default: { device: 'cpu' }, alias: { h: 'help' } });

if (args.help) {
    console.log('Use this script to run age and gender recognition using OpenCV.');
    console.log('--input  Path to input image or video file. Skip this argument to capture frames from a camera.');
    console.log('--device "Device to inference on');
    process.exit(0);
}

const main = async () => {
    const faceProto = path.resolve(__dirname, "opencv_face_detector.pbtxt")
    const faceModel = await getCachedFile(path.resolve(__dirname, "opencv_face_detector_uint8.pb"), 'https://github.com/spmallick/learnopencv/raw/master/AgeGender/opencv_face_detector_uint8.pb')

    const ageProto = path.resolve(__dirname, "age_deploy.prototxt")
    const ageModel = path.resolve(__dirname, "age_net.caffemodel")

    const genderProto = path.resolve(__dirname, "gender_deploy.prototxt")
    const genderModel = path.resolve(__dirname, "gender_net.caffemodel")

    const MODEL_MEAN_VALUES = new Vec3(78.4263377603, 87.7689143744, 114.895847746)
    const ageList = ['(0-2)', '(4-6)', '(8-12)', '(15-20)', '(25-32)', '(38-43)', '(48-53)', '(60-100)']
    const genderList = ['Male', 'Female']

    // Load network
    if (!fs.existsSync(ageModel)) {
        throw Error(`fail to read ${ageModel}`);
    }
    if (!fs.existsSync(ageProto)) {
        throw Error(`fail to read ${ageProto}`);
    }
    const ageNet = cv.readNet(ageModel, ageProto)
    const genderNet = cv.readNet(genderModel, genderProto)
    const faceNet = cv.readNet(faceModel, faceProto)

    // const ageNet = cv.readNet(ageProto, ageModel)
    // const genderNet = cv.readNetFromCaffe(genderProto, genderModel)
    // const faceNet = cv.readNetFromTensorflow(faceProto, faceModel)


    if (args.device == "cpu") {
        ageNet.setPreferableBackend(cv.DNN_TARGET_CPU);
        genderNet.setPreferableBackend(cv.DNN_TARGET_CPU);
        faceNet.setPreferableBackend(cv.DNN_TARGET_CPU);
        console.log("Using CPU device")
    } else if (args.device == "gpu") {
        ageNet.setPreferableBackend(cv.DNN_BACKEND_CUDA)
        ageNet.setPreferableTarget(cv.DNN_TARGET_CUDA)
        genderNet.setPreferableBackend(cv.DNN_BACKEND_CUDA)
        genderNet.setPreferableTarget(cv.DNN_TARGET_CUDA)
        genderNet.setPreferableBackend(cv.DNN_BACKEND_CUDA)
        genderNet.setPreferableTarget(cv.DNN_TARGET_CUDA)
        console.log("Using GPU device")
    }

    // Open a video file or an image file or a camera stream
    let cap: VideoCapture;
    if (args.input) {
        // Open the image file
        if (!fs.existsSync(args.input)) {
            console.error("Input input file ", args.input, " doesn't exist")
            process.exit(1)
        }
        cap = new cv.VideoCapture(args.input)
    } else {
        cap = new cv.VideoCapture(0);
    }
    const padding = 20
    while (cv.waitKey(1) < 0) {
        // Read frame
        const t = Date.now()
        // hasFrame, frame = cap.read()
        const frame: Mat = cap.read()
        if (!frame || frame.sizes.length === 0) { // hasFrame:
            cv.waitKey(100)
            // Release device
            cap.release()
            break
        }
        const { frameFace, bboxes } = getFaceBox(faceNet, frame)
        if (!bboxes.length) {
            console.log("No face Detected, Checking next frame")
            continue
        }

        for (const bboxOrg of bboxes) {
            // console.log(bboxOrg);
            // const bbox = bboxOrg.toSquare();
            //console.log(bbox);
            const bbox = new Rect(Math.round(bboxOrg.x - padding), Math.round(bboxOrg.y - padding), Math.round(bboxOrg.width + padding * 2), Math.round(bboxOrg.height + padding * 2));
            const face = frame.getRegion(bbox);
            // TODO add padding
            // const face = frame[max(0,bbox[1]-padding):min(bbox[3]+padding,frame.shape[0]-1),max(0,bbox[0]-padding):min(bbox[2]+padding, frame.shape[1]-1)]
            const blob = cv.blobFromImage(face, { scaleFactor: 1.0, size: new Size(227, 227), mean: MODEL_MEAN_VALUES, swapRB: false });
            genderNet.setInput(blob)
            const genderPreds = genderNet.forward()
            const data1 = genderPreds.getDataAsArray();
            const maxId1 = getMaxIndex(data1[0])
            const gender = genderList[maxId1] // .argmax()
            console.log(`Gender Output : ${genderPreds}`);
            console.log(`Gender : ${gender}, conf = ${data1[0][maxId1]}`)
            ageNet.setInput(blob)
            const agePreds = ageNet.forward()
            const data2 = agePreds.getDataAsArray();
            const maxId2 = getMaxIndex(data2[0])
            const age = ageList[maxId2]
            console.log(`Age Output : ${agePreds}`)
            console.log(`Age : ${age}, conf = ${data2[0][maxId2]}`)
            const label = `${gender},${age}`
            frameFace.putText(label, new Point2(bbox.x, bbox.y - 10), cv.FONT_HERSHEY_SIMPLEX, 0.8, new Vec3(0, 255, 255), 2, cv.LINE_AA)
            cv.imshow("Age Gender Demo", frameFace)
            cv.imwrite(`age-gender-out-${args.input}`, frameFace)
        }
        console.log(`time : ${Date.now() - t} ms`);
    }
};
main().catch(console.error);