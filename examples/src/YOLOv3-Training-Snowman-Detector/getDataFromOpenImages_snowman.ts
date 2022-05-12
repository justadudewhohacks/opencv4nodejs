import { getCachedFile } from "../utils";
import fs from 'fs';
// import rimraf from 'rimraf';
import readline from 'readline';
import pLimit from 'p-limit';

/**
 * imported from https://github.com/spmallick/learnopencv/blob/master/YOLOv3-Training-Snowman-Detector/getDataFromOpenImages_snowman.py
 */

async function getDataFromOpenImages_snowman() {
    const limit = pLimit(30);
    const runMode = "train";
    const classes = ["Snowman"];

    const dataPath = "../../data/dnn/openimages";

    const boxes = await getCachedFile(`${dataPath}/class-descriptions-boxable.csv`, 'https://storage.googleapis.com/openimages/2018_04/class-descriptions-boxable.csv');
    const trainAnotation = await getCachedFile(`${dataPath}/train-annotations-bbox.csv`, 'https://storage.googleapis.com/openimages/2018_04/train/train-annotations-bbox.csv');

    const boxesData = await fs.promises.readFile(boxes, { encoding: 'utf8' })
    const folderMapping: { [key: string]: string } = {};
    boxesData.split(/[\r\n]+/g).map(line => line.split(',')).forEach(d => folderMapping[d[1]] = d[0]);
    //const dict_list = boxesData.split(/\r\n+/g).map(line => line.split(',')).map(d => ({ name: d[1], file: d[0] }));
    // rimraf.sync('JPEGImages');
    fs.mkdirSync('JPEGImages', { recursive: true });
    // rimraf.sync('labels');
    fs.mkdirSync('labels', { recursive: true });

    for (let ind = 0; ind < classes.length; ind++) {
        const className = classes[ind];
        console.log(`Class ${ind} : ${className}`);
        const target = folderMapping[className];
        const rl = readline.createInterface({
            input: fs.createReadStream(trainAnotation),
            //output: process.stdout,
            terminal: false
        });

        const annotations: Array<string> = [];
        rl.on('line', (line) => {
            if (line.includes(target)) {
                annotations.push(line);
            }
        });

        await new Promise((resolve, reject) => {
            rl.on('close', resolve);
            rl.on('error', reject);
        });
        console.log(`Total number of annotations : ${annotations.length}`);
        Promise.all(annotations.map((annotation, index) => limit(() => {
            const lineParts = annotation.split(',')
            try {
            return getCachedFile(`JPEGImages/${lineParts[0]}.jpg`, `https://s3.amazonaws.com/open-images-dataset/${runMode}/${lineParts[0]}.jpg`, { notice: `get file#${index}: ${lineParts[0]}`, noProgress: true });
            } catch (e) {
                console.error(`download ${lineParts[0]}.jpg failed`, e);
            }
        })));

        Promise.all(annotations.map((annotation, index) => limit(() => {
            const lineParts = annotation.split(',');
            const data = [
                `${index}`,
                `${(Number(lineParts[5]) + Number(lineParts[4]))/2}`, // center X
                `${(Number(lineParts[7]) + Number(lineParts[6]))/2}`, // center Y
                `${Number(lineParts[5]) - Number(lineParts[4])}`, // X1
                `${Number(lineParts[7]) - Number(lineParts[6])}`  // y1
            ].join(' ') + '\n';
            return fs.promises.writeFile(`labels/${lineParts[0]}.txt`, data, { encoding: 'utf8' });
        })));
    }
}
getDataFromOpenImages_snowman();
