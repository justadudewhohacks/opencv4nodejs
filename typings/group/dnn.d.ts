import { Mat } from '../Mat.d';
import { Rect } from '../Rect';
import { Net } from '../Net.d';
import { Vec3 } from '../Vec3';
import { Size } from '../Size';

//Mat 	cv::dnn::blobFromImage (InputArray image, double scalefactor=1.0, const Size &size=Size(), const Scalar &mean=Scalar(), bool swapRB=false, bool crop=false, int ddepth=CV_32F)
//Creates 4-dimensional blob from image. Optionally resizes and crops image from center, subtract mean values, scales values by scalefactor, swap Blue and Red channels. More...
//
//void 	cv::dnn::blobFromImage (InputArray image, OutputArray blob, double scalefactor=1.0, const Size &size=Size(), const Scalar &mean=Scalar(), bool swapRB=false, bool crop=false, int ddepth=CV_32F)
//Creates 4-dimensional blob from image. More...


export function blobFromImage(image: Mat, scaleFactor?: number, size?: Size, mean?: Vec3, swapRB?: boolean, crop?: boolean, ddepth?: number): Mat;
export function blobFromImageAsync(image: Mat, scaleFactor?: number, size?: Size, mean?: Vec3, swapRB?: boolean, crop?: boolean, ddepth?: number): Promise<Mat>;



//Mat 	cv::dnn::blobFromImages (InputArrayOfArrays images, double scalefactor=1.0, Size size=Size(), const Scalar &mean=Scalar(), bool swapRB=false, bool crop=false, int ddepth=CV_32F)
//Creates 4-dimensional blob from series of images. Optionally resizes and crops images from center, subtract mean values, scales values by scalefactor, swap Blue and Red channels. More...
//
//void 	cv::dnn::blobFromImages (InputArrayOfArrays images, OutputArray blob, double scalefactor=1.0, Size size=Size(), const Scalar &mean=Scalar(), bool swapRB=false, bool crop=false, int ddepth=CV_32F)
//Creates 4-dimensional blob from series of images. More...
export function blobFromImages(image: Mat[], scaleFactor?: number, size?: Size, mean?: Vec3, swapRB?: boolean, crop?: boolean, ddepth?: number): Mat;
export function blobFromImagesAsync(image: Mat[], scaleFactor?: number, size?: Size, mean?: Vec3, swapRB?: boolean, crop?: boolean, ddepth?: number): Promise<Mat>;




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
export function NMSBoxes(bboxes: Rect[], scores: number[], scoreThreshold: number, nmsThreshold: number): number[];



//Net 	cv::dnn::readNet (const String &model, const String &config="", const String &framework="")
//Read deep learning network represented in one of the supported formats. More...
//
//Net 	cv::dnn::readNet (const String &framework, const std::vector< uchar > &bufferModel, const std::vector< uchar > &bufferConfig=std::vector< uchar >())
//Read deep learning network represented in one of the supported formats. More...
//
//Net 	cv::dnn::readNetFromCaffe (const String &prototxt, const String &caffeModel=String())
//Reads a network model stored in Caffe framework's format. More...
export function readNetFromCaffe(prototxt: string, modelPath?: string): Net;
export function readNetFromCaffeAsync(prototxt: string, modelPath?: string): Promise<Net>;


//Net 	cv::dnn::readNetFromCaffe (const std::vector< uchar > &bufferProto, const std::vector< uchar > &bufferModel=std::vector< uchar >())
//Reads a network model stored in Caffe model in memory. More...
//
//Net 	cv::dnn::readNetFromCaffe (const char *bufferProto, size_t lenProto, const char *bufferModel=NULL, size_t lenModel=0)
//Reads a network model stored in Caffe model in memory. More...
//
//Net 	cv::dnn::readNetFromDarknet (const String &cfgFile, const String &darknetModel=String())
//Reads a network model stored in Darknet model files. More...
//
//Net 	cv::dnn::readNetFromDarknet (const std::vector< uchar > &bufferCfg, const std::vector< uchar > &bufferModel=std::vector< uchar >())
//Reads a network model stored in Darknet model files. More...
//
//Net 	cv::dnn::readNetFromDarknet (const char *bufferCfg, size_t lenCfg, const char *bufferModel=NULL, size_t lenModel=0)
//Reads a network model stored in Darknet model files. More...
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



//Net 	cv::dnn::readNetFromONNX (const String &onnxFile)
//Reads a network model ONNX. More...
//
//Net 	cv::dnn::readNetFromONNX (const char *buffer, size_t sizeBuffer)
//Reads a network model from ONNX in-memory buffer. More...
//
//Net 	cv::dnn::readNetFromONNX (const std::vector< uchar > &buffer)
//Reads a network model from ONNX in-memory buffer. More...

export function readNetFromONNX(onnxFile: string): Net;
export function readNetFromONNXAsync(onnxFile: string): Promise<Net>;


//Net 	cv::dnn::readNetFromTensorflow (const String &model, const String &config=String())
//Reads a network model stored in TensorFlow framework's format. More...
//
//Net 	cv::dnn::readNetFromTensorflow (const std::vector< uchar > &bufferModel, const std::vector< uchar > &bufferConfig=std::vector< uchar >())
//Reads a network model stored in TensorFlow framework's format. More...
//
//Net 	cv::dnn::readNetFromTensorflow (const char *bufferModel, size_t lenModel, const char *bufferConfig=NULL, size_t lenConfig=0)
//Reads a network model stored in TensorFlow framework's format. More...
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
