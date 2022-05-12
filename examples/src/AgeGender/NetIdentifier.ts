import cv, { Net, Mat } from "@u4/opencv4nodejs";


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
/**
 * Input must be an image having the same size as the network
 * Output is a list of score list, the number of score must match the size of profided Labels
 */
export default class NetIdentifier {
    /**
     * @param model	Binary file contains trained weights. The following file extensions are expected for models from different frameworks:
     * *.caffemodel (Caffe, http://caffe.berkeleyvision.org/),
     * *.pb (TensorFlow, https://www.tensorflow.org/),
     * *.t7 | *.net (Torch, http://torch.ch/),
     * *.weights (Darknet, https://pjreddie.com/darknet/),
     * *.bin (DLDT, https://software.intel.com/openvino-toolkit),
     * *.onnx (ONNX, https://onnx.ai/)  
     * @param proto Text file contains network configuration. It could be a file with the following extensions:
     * *.prototxt (Caffe, http://caffe.berkeleyvision.org/),
     * *.pbtxt (TensorFlow, https://www.tensorflow.org/),
     * *.cfg (Darknet, https://pjreddie.com/darknet/),
     * *.xml (DLDT, https://software.intel.com/openvino-toolkit)
     * @param labels Label list in the proper order
     */
    constructor(private model: string, private proto: string, private labels: string[]) { }

    private net?: Promise<Net>;
    getNet(): Promise<Net> {
        if (!this.net) {
            this.net = cv.readNetAsync(this.model, this.proto);
        }
        return this.net;
    }

    async preferCpu() {
        const net = await this.getNet();
        net.setPreferableBackend(cv.DNN_TARGET_CPU);
    }

    async preferGpu() {
        const net = await this.getNet();
        net.setPreferableBackend(cv.DNN_BACKEND_CUDA);
        net.setPreferableTarget(cv.DNN_BACKEND_CUDA);
    }


    async setInput(blob: Mat): Promise<void> {
        const net = await this.getNet();
        return net.setInputAsync(blob);
    }

    /**
     * Runs forward pass to compute output of layer with name outputName.
     * 
     * https://docs.opencv.org/3.4/db/d30/classcv_1_1dnn_1_1Net.html#a98ed94cb6ef7063d3697259566da310b
     * 
     * @param inputName name for layer which output is needed to get
     */
    async forward(inputName?: string): Promise<Mat> {
        const net = await this.getNet();
        // console.log(net.getLayerNames());
        // console.log(net.dump());
        if (inputName)
            return net.forwardAsync(inputName);
        else
            return net.forwardAsync();
    }

    async getResult(idx = 0): Promise<{id: number, name: string, score: number}> {
        const mat = await this.forward()
        if (mat.type !== cv.CV_32F) {
            throw Error('Net output format should be CV_32F');
        }
        if (mat.dims !== 2) {
            throw Error('Net output dimmention should be 2');
        }
        // mat.sizes[0] number of result using idx param
        // mat.sizes[1] => last size
        if (mat.sizes[1] !== this.labels.length) { // cols
            throw Error(`Net output vector size(${mat.cols}) must match labels count (${this.labels.length}), check our data or do not use this Net helper`);
        }
        const data: Array<number[]> = mat.getDataAsArray();
        const id = getMaxIndex(data[idx]);
        const name = this.labels[id];
        const score = data[idx][id];
        return { id, name, score };
    }
}