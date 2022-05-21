import fs from 'fs';
import path from 'path';
import samplesize from 'lodash.samplesize';
import pc from 'picocolors';

export async function split_data_set(image_dir: string) {
    const files = fs.readdirSync(image_dir).filter(f => f.endsWith(".jpg"));
    if (!files.length) {
        console.error(`no jpeg found in ${image_dir}`);
        return;
    }
    const testFile = path.resolve("snowman_test.txt");
    const trainFile = path.resolve("snowman_train.txt");
    const classesFile = path.resolve("classes.names");
    const weightsDir = path.resolve("weights");

    const f_val = fs.createWriteStream(testFile, { encoding: 'utf8', flags: 'w' });
    const f_train = fs.createWriteStream(trainFile, { encoding: 'utf8', flags: 'w' });

    const data_test_size = Math.floor(0.1 * files.length);
    const test_array = new Set(samplesize(files, data_test_size));

    for (const f of files) {
        const line = `${image_dir}/${f}\n`;
        if (test_array.has(f))
            f_val.write(path.resolve(line))
        else
            f_train.write(path.resolve(line))
    }
    console.log(`${data_test_size} test list saved to ${pc.yellow(testFile)}`)
    console.log(`${files.length - data_test_size} train image saved to ${pc.yellow(trainFile)}`)
    fs.writeFileSync(classesFile, 'snowman\n');
    fs.mkdirSync(weightsDir, { recursive: true });
    const darknet_data = `
classes = 1
train  = ${trainFile}
valid  = ${testFile}
names = ${classesFile}
backup = ${weightsDir}
`;
    fs.writeFileSync('darknet.data', darknet_data);
}
split_data_set(process.argv[process.argv.length - 1]);