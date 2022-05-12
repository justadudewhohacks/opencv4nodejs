import fs from 'fs';
import samplesize from 'lodash.samplesize';

export async function split_data_set(image_dir: string) {
    const files = fs.readdirSync(image_dir).filter(f => f.endsWith(".jpg"));
    if (!files.length) {
        console.error(`no jpeg found in ${image_dir}`);
        return;
    }
    const f_val = fs.createWriteStream("snowman_test.txt", { encoding: 'utf8', flags: 'w' });
    const f_train = fs.createWriteStream("snowman_train.txt", { encoding: 'utf8', flags: 'w' });

    const data_test_size = Math.floor(0.1 * files.length);
    const test_array = new Set(samplesize(files, data_test_size));

    for (const f of files) {
        const line = `${image_dir}/${f}\n`;
        if (test_array.has(f))
            f_val.write(line)
        else
            f_train.write(line)
    }
    console.log(`${data_test_size} test list saved to ${"snowman_test.txt"}`)
    console.log(`${files.length - data_test_size} train image saved to ${"snowman_train.txt"}`)
}
split_data_set(process.argv[process.argv.length - 1]);