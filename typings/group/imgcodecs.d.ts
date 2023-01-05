import { Mat } from '../Mat.d';

// bool 	cv::haveImageReader (const String &filename)
//  	Returns true if the specified image can be decoded by OpenCV. More...
//  
// bool 	cv::haveImageWriter (const String &filename)
//  	Returns true if an image with the specified filename can be encoded by OpenCV. More...
//  
// size_t 	cv::imcount (const String &filename, int flags=IMREAD_ANYCOLOR)
//  	Returns the number of images inside the give file. More...
//  
// Mat 	cv::imdecode (InputArray buf, int flags)
//  	Reads an image from a buffer in memory. More...
//  
// Mat 	cv::imdecode (InputArray buf, int flags, Mat *dst)
//  
export function imdecode(buffer: Buffer, flags?: number): Mat;
export function imdecodeAsync(buffer: Buffer, flags?: number): Promise<Mat>;

// bool 	cv::imencode (const String &ext, InputArray img, std::vector< uchar > &buf, const std::vector< int > &params=std::vector< int >())
//  	Encodes an image into a memory buffer. More...

export function imencode(fileExt: string, img: Mat, flags?: number[]): Buffer;
export function imencodeAsync(fileExt: string, img: Mat, flags?: number[]): Promise<Buffer>;


// Mat 	cv::imread (const String &filename, int flags=IMREAD_COLOR)
//  	Loads an image from a file. More...
export function imread(filePath: string, flags?: number): Mat;
export function imreadAsync(filePath: string, flags?: number): Promise<Mat>;

// bool 	cv::imreadmulti (const String &filename, std::vector< Mat > &mats, int flags=IMREAD_ANYCOLOR)
//  	Loads a multi-page image from a file. More...
//  
// bool 	cv::imreadmulti (const String &filename, std::vector< Mat > &mats, int start, int count, int flags=IMREAD_ANYCOLOR)
//  	Loads a of images of a multi-page image from a file. More...
//  
// bool 	cv::imwrite (const String &filename, InputArray img, const std::vector< int > &params=std::vector< int >())
//  	Saves an image to a specified file. More...
export function imwrite(filePath: string, img: Mat, flags?: number[]): void;
export function imwriteAsync(filePath: string, img: Mat, flags?: number[]): Promise<void>;
  
// static bool 	cv::imwritemulti (const String &filename, InputArrayOfArrays img, const std::vector< int > &params=std::vector< int >())
