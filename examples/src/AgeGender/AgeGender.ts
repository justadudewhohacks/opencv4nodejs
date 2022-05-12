import fs from 'fs';
import mri from 'mri';
import { Mat, Net, Point2, Rect, Size, Vec3, VideoCapture } from '@u4/opencv4nodejs';
import { cv, getCachedFile, wait4key } from '../utils';
import path from 'path';
import NetIdentifier from './NetIdentifier';

// ported from https://github.com/spmallick/learnopencv/blob/master/AgeGender/AgeGender.py

function getFaceBox(net: Net, frame: Mat, conf_threshold = 0.7): { frameFace: Mat, bboxes: Rect[] } {
    const frameOpencvDnn: Mat = frame.copy();
    const frameHeight = frameOpencvDnn.rows;
    const frameWidth = frameOpencvDnn.cols;
    const blob: Mat = cv.blobFromImage(frameOpencvDnn, { scaleFactor: 1.0, size: new Size(300, 300), mean: new Vec3(104, 117, 123), swapRB: true, crop: false });
    net.setInput(blob)
    const detections: Mat = net.forward()
    const bboxes: Rect[] = []
    // dimmentions [1, 1, 200, 7]
    // look to me sorted by score.
    const max = detections.sizes[2];
    for (let i = 0; i < max; i++) {
        // detections.at([0, 0, i, 1]) == 0
        // detections.at([0, 0, i, 2]) == 1
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

const args: { input?: string, device?: string, help?: boolean } = mri(process.argv.slice(2), { default: { device: 'cpu' }, alias: { h: 'help' } }) as any;

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
    // 44 MB file
    const ageModel = path.resolve(__dirname, "age_net.caffemodel") // https://www.dropbox.com/s/xfb20y596869vbb/age_net.caffemodel?dl=0

    const genderProto = path.resolve(__dirname, "gender_deploy.prototxt")
    // 44 MB file
    const genderModel = path.resolve(__dirname, "gender_net.caffemodel") // https://www.dropbox.com/s/iyv483wz7ztr9gh/gender_net.caffemodel?dl=0

    const MODEL_MEAN_VALUES = new Vec3(78.4263377603, 87.7689143744, 114.895847746)

    // Load network
    if (!fs.existsSync(ageModel)) {
        throw Error(`fail to read ${ageModel}`);
    }
    if (!fs.existsSync(ageProto)) {
        throw Error(`fail to read ${ageProto}`);
    }
    const ageNet = new NetIdentifier(ageModel, ageProto, ['(0-2)', '(4-6)', '(8-12)', '(15-20)', '(25-32)', '(38-43)', '(48-53)', '(60-100)']);
    const genderNet = new NetIdentifier(genderModel, genderProto, ['Male', 'Female'])
    const faceNet = cv.readNet(faceModel, faceProto)

    // const ageNet = cv.readNet(ageProto, ageModel)
    // const genderNet = cv.readNetFromCaffe(genderProto, genderModel)
    // const faceNet = cv.readNetFromTensorflow(faceProto, faceModel)


    if (args.device == "cpu") {
        ageNet.preferCpu();
        genderNet.preferCpu();
        faceNet.setPreferableBackend(cv.DNN_TARGET_CPU);
        console.log("Using CPU device")
    } else if (args.device == "gpu") {
        ageNet.preferGpu()
        genderNet.preferGpu();
        faceNet.setPreferableBackend(cv.DNN_BACKEND_CUDA)
        faceNet.setPreferableTarget(cv.DNN_TARGET_CUDA)
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
            const bbox = new Rect(
                Math.max(Math.round(bboxOrg.x - padding), 0),
                Math.max(Math.round(bboxOrg.y - padding), 0),
                Math.round(bboxOrg.width + padding * 2),
                Math.round(bboxOrg.height + padding * 2));
            const face = frame.getRegion(bbox);
            // TODO add padding
            // const face = frame[max(0,bbox[1]-padding):min(bbox[3]+padding,frame.shape[0]-1),max(0,bbox[0]-padding):min(bbox[2]+padding, frame.shape[1]-1)]
            const blob = cv.blobFromImage(face, { scaleFactor: 1.0, size: new Size(227, 227), mean: MODEL_MEAN_VALUES, swapRB: false });

            await genderNet.setInput(blob)

            const gender = await genderNet.getResult();
            console.log(`Gender : ${gender.name}, conf = ${gender.score}`)

            await ageNet.setInput(blob)
            const age = await ageNet.getResult();
            console.log(`Age : ${age.name}, conf = ${age.score}`)
            const label = `${gender.name},${age.name}`
            frameFace.putText(label, new Point2(bbox.x, bbox.y - 10), cv.FONT_HERSHEY_SIMPLEX, 0.8, new Vec3(0, 255, 255), 2, cv.LINE_AA)
            cv.imshow("Age Gender Demo", frameFace)
            cv.imwrite(`age-gender-out-${args.input}`, frameFace)
            cv.waitKey(1);
        }
        console.log(`time : ${Date.now() - t} ms`);
        await wait4key();
    }
};
main().catch(console.error);