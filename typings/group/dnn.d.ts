import { Mat } from '../Mat.d';
import { Rect } from '../Rect';
import { Net } from '../Net.d';
import { Vec3 } from '../Vec3';
import { Size } from '../Size';

/**
 * Creates 4-dimensional blob from image. Optionally resizes and crops image from center, subtract mean values, scales values by scalefactor, swap Blue and Red channels.
 * 
 * if crop is true, input image is resized so one side after resize is equal to corresponding dimension in size and another one is equal or larger. Then, crop from the center is performed. If crop is false, direct resize without cropping and preserving aspect ratio is performed.
 * 
 * https://docs.opencv.org/4.x/d6/d0f/group__dnn.html#ga29f34df9376379a603acd8df581ac8d7
 *
 * @pram image	input image (with 1-, 3- or 4-channels).
 * @pram scalefactor	multiplier for image values.
 * @pram size	spatial size for output image
 * @pram mean	scalar with mean values which are subtracted from channels. Values are intended to be in (mean-R, mean-G, mean-B) order if image has BGR ordering and swapRB is true.
 * @pram swapRB	flag which indicates that swap first and last channels in 3-channel image is necessary.
 * @pram crop	flag which indicates whether image will be cropped after resize or not
 * @pram ddepth	Depth of output blob. Choose CV_32F or CV_8U.
 * 
 * 
 * @return 4-dimensional Mat with NCHW dimensions order.
 */
export function blobFromImage(image: Mat, scaleFactor?: number, size?: Size, mean?: Vec3, swapRB?: boolean, crop?: boolean, ddepth?: number): Mat;
export function blobFromImage(image: Mat, opts: { scaleFactor?: number, size?: Size, mean?: Vec3, swapRB?: boolean, crop?: boolean, ddepth?: number }): Mat;
export function blobFromImageAsync(image: Mat, scaleFactor?: number, size?: Size, mean?: Vec3, swapRB?: boolean, crop?: boolean, ddepth?: number): Promise<Mat>;
export function blobFromImageAsync(image: Mat, opts: { scaleFactor?: number, size?: Size, mean?: Vec3, swapRB?: boolean, crop?: boolean, ddepth?: number }): Promise<Mat>;

/**
 * Creates 4-dimensional blob from series of images. Optionally resizes and crops images from center, subtract mean values, scales values by scalefactor, swap Blue and Red channels.
 * 
 * if crop is true, input image is resized so one side after resize is equal to corresponding dimension in size and another one is equal or larger. Then, crop from the center is performed. If crop is false, direct resize without cropping and preserving aspect ratio is performed.
 * 
 * https://docs.opencv.org/4.x/d6/d0f/group__dnn.html#ga0b7b7c3c530b747ef738178835e1e70f
 * 
 * @param images	input images (all with 1-, 3- or 4-channels).
 * @param scalefactor	multiplier for images values.
 * @param size	spatial size for output image
 * @param mean	scalar with mean values which are subtracted from channels. Values are intended to be in (mean-R, mean-G, mean-B) order if image has BGR ordering and swapRB is true.
 * @param swapRB	flag which indicates that swap first and last channels in 3-channel image is necessary.
 * @param crop	flag which indicates whether image will be cropped after resize or not
 * @param ddepth	Depth of output blob. Choose CV_32F or CV_8U.
 * 
 * @returns 4-dimensional Mat with NCHW dimensions order.
 */
export function blobFromImages(images: Mat[], scaleFactor?: number, size?: Size, mean?: Vec3, swapRB?: boolean, crop?: boolean, ddepth?: number): Mat;
export function blobFromImages(images: Mat[], opts: { scaleFactor?: number, size?: Size, mean?: Vec3, swapRB?: boolean, crop?: boolean, ddepth?: number }): Mat;

export function blobFromImagesAsync(images: Mat[], scaleFactor?: number, size?: Size, mean?: Vec3, swapRB?: boolean, crop?: boolean, ddepth?: number): Promise<Mat>;
export function blobFromImagesAsync(images: Mat[], opts: { scaleFactor?: number, size?: Size, mean?: Vec3, swapRB?: boolean, crop?: boolean, ddepth?: number }): Promise<Mat>;


//void 	cv::dnn::enableModelDiagnostics (bool isDiagnosticsMode)
//Enables detailed logging of the DNN model loading with CV DNN API. More...
//
//std::vector< std::pair< Backend, Target > > 	cv::dnn::getAvailableBackends ()
//
//std::vector< Target > 	cv::dnn::getAvailableTargets (dnn::Backend be)
//
//LayerFactory_Impl & 	cv::dnn::getLayerFactoryImpl ()
//
//Mutex & 	cv::dnn::getLayerFactoryMutex ()
//Get the mutex guarding LayerFactory_Impl, see getLayerFactoryImpl() function. More...
//
//void 	cv::dnn::imagesFromBlob (const cv::Mat &blob_, OutputArrayOfArrays images_)
//Parse a 4D blob and output the images it contains as 2D arrays through a simpler data structure (std::vector<cv::Mat>). More...
//
//void 	cv::dnn::NMSBoxes (const std::vector< Rect > &bboxes, const std::vector< float > &scores, const float score_threshold, const float nms_threshold, std::vector< int > &indices, const float eta=1.f, const int top_k=0)
//Performs non maximum suppression given boxes and corresponding scores. More...
//
//void 	cv::dnn::NMSBoxes (const std::vector< Rect2d > &bboxes, const std::vector< float > &scores, const float score_threshold, const float nms_threshold, std::vector< int > &indices, const float eta=1.f, const int top_k=0)
//
//void 	cv::dnn::NMSBoxes (const std::vector< RotatedRect > &bboxes, const std::vector< float > &scores, const float score_threshold, const float nms_threshold, std::vector< int > &indices, const float eta=1.f, const int top_k=0)
/**
 * Performs non maximum suppression given boxes and corresponding scores.
 * 
 * https://docs.opencv.org/4.x/d6/d0f/group__dnn.html#ga9d118d70a1659af729d01b10233213ee
 * 
 * 
 * @param bboxes	a set of bounding boxes to apply NMS.
 * @param scores	a set of corresponding confidences.
 * @param scoreThreshold	a threshold used to filter boxes by score.
 * @param nmsThreshold	a threshold used in non maximum suppression.
 * @param eta	a coefficient in adaptive threshold formula: nms_thresholdi+1=eta⋅nms_thresholdi.
 * @param top_k	if >0, keep at most top_k picked indices.
 * 
 * @return the kept indices of bboxes after NMS.
 */
export function NMSBoxes(bboxes: Rect[], scores: number[], scoreThreshold: number, nmsThreshold: number, eta?: number, topK?: number): number[];
export function NMSBoxes(bboxes: Rect[], scores: number[], scoreThreshold: number, nmsThreshold: number, opts: { eta?: number, topK?: number }): number[];

/**
 * Read deep learning network represented in one of the supported formats.
 * 
 * https://docs.opencv.org/3.4.17/d6/d0f/group__dnn.html#ga3b34fe7a29494a6a4295c169a7d32422
 * 
 * @param model	Binary file contains trained weights. The following file extensions are expected for models from different frameworks:
 * *.caffemodel (Caffe, http://caffe.berkeleyvision.org/),
 * *.pb (TensorFlow, https://www.tensorflow.org/),
 * *.t7 | *.net (Torch, http://torch.ch/),
 * *.weights (Darknet, https://pjreddie.com/darknet/),
 * *.bin (DLDT, https://software.intel.com/openvino-toolkit),
 * *.onnx (ONNX, https://onnx.ai/) 
 * @param modelPath Text file contains network configuration. It could be a file with the following extensions:
 * *.prototxt (Caffe, http://caffe.berkeleyvision.org/),
 * *.pbtxt (TensorFlow, https://www.tensorflow.org/),
 * *.cfg (Darknet, https://pjreddie.com/darknet/),
 * *.xml (DLDT, https://software.intel.com/openvino-toolkit)
 */
export function readNet(model: string, config?: string, framework?: string): Net;
export function readNet(model: string, opts: { config?: string, framework?: string }): Net;

export function readNetAsync(model: string, config?: string, framework?: string): Promise<Net>;
export function readNetAsync(model: string, opts: { config?: string, framework?: string }): Promise<Net>;

/**
 * Reads a network model stored in Caffe framework's format.
 * 
 * https://docs.opencv.org/4.x/d6/d0f/group__dnn.html#ga29d0ea5e52b1d1a6c2681e3f7d68473a
 * @param prototxt path to the .prototxt file with text description of the network architecture.
 * @param modelPath path to the .caffemodel file with learned network.
 */
export function readNetFromCaffe(prototxt: string, modelPath?: string): Net;
export function readNetFromCaffeAsync(prototxt: string, modelPath?: string): Promise<Net>;

/**
 * Reads a network model stored in Darknet model files.
 * 
 * https://docs.opencv.org/4.x/d6/d0f/group__dnn.html#gafde362956af949cce087f3f25c6aff0d
 * 
 * @param cfgPath 	path to the .cfg file with text description of the network architecture. (should be an absolute path)
 * @param modelPath to the .weights file with learned network. (should be an absolute path)
 */
export function readNetFromDarknet(cfgPath: string, modelPath: string): Net;
export function readNetFromDarknetAsync(cfgPath: string, modelPath: string): Promise<Net>;


//Net 	cv::dnn::readNetFromModelOptimizer (const String &xml, const String &bin)
//Load a network from Intel's Model Optimizer intermediate representation. More...
//
//Net 	cv::dnn::readNetFromModelOptimizer (const std::vector< uchar > &bufferModelConfig, const std::vector< uchar > &bufferWeights)
//Load a network from Intel's Model Optimizer intermediate representation. More...
//
//Net 	cv::dnn::readNetFromModelOptimizer (const uchar *bufferModelConfigPtr, size_t bufferModelConfigSize, const uchar *bufferWeightsPtr, size_t bufferWeightsSize)
//Load a network from Intel's Model Optimizer intermediate representation. More...

/**
 * Reads a network model ONNX.
 * https://docs.opencv.org/4.x/d6/d0f/group__dnn.html#ga7faea56041d10c71dbbd6746ca854197
 * 
 * @param onnxFile 	path to the .onnx file with text description of the network architecture.
 */
export function readNetFromONNX(onnxFile: string): Net;
export function readNetFromONNXAsync(onnxFile: string): Promise<Net>;

/**
 * Reads a network model stored in TensorFlow framework's format.
 * 
 * https://docs.opencv.org/4.x/d6/d0f/group__dnn.html#gad820b280978d06773234ba6841e77e8d
 * 
 * @param modelPath path to the .pb file with binary protobuf description of the network architecture
 * @param config path to the .pbtxt file that contains text graph definition in protobuf format. Resulting Net object is built by text graph using weights from a binary one that let us make it more flexible.
 */
export function readNetFromTensorflow(modelPath: string, config?: string): Net;
export function readNetFromTensorflowAsync(modelPath: string): Promise<Net>;


//Net 	cv::dnn::readNetFromTorch (const String &model, bool isBinary=true, bool evaluate=true)
//Reads a network model stored in Torch7 framework's format. More...
//
//Mat 	cv::dnn::readTensorFromONNX (const String &path)
//Creates blob from .pb file. More...
//
//Mat 	cv::dnn::readTorchBlob (const String &filename, bool isBinary=true)
//Loads blob which was serialized as torch.Tensor object of Torch7 framework. More...
//
//void 	cv::dnn::shrinkCaffeModel (const String &src, const String &dst, const std::vector< String > &layersTypes=std::vector< String >())
//Convert all weights of Caffe network to half precision floating point. More...
//
//void 	cv::dnn::softNMSBoxes (const std::vector< Rect > &bboxes, const std::vector< float > &scores, std::vector< float > &updated_scores, const float score_threshold, const float nms_threshold, std::vector< int > &indices, size_t top_k=0, const float sigma=0.5, SoftNMSMethod method=SoftNMSMethod::SOFTNMS_GAUSSIAN)
//Performs soft non maximum suppression given boxes and corresponding scores. Reference: https://arxiv.org/abs/1704.04503. More...
//
//void 	cv::dnn::writeTextGraph (const String &model, const String &output)
//Create a text representation for a binary network stored in protocol buffer format. More...
