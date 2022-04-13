// void 	cv::bilateralFilter (InputArray src, OutputArray dst, int d, double sigmaColor, double sigmaSpace, int borderType=BORDER_DEFAULT)
//  	Applies the bilateral filter to an image. More...
//  
// void 	cv::blur (InputArray src, OutputArray dst, Size ksize, Point anchor=Point(-1,-1), int borderType=BORDER_DEFAULT)

import { Mat } from "../Mat";
import { Point2 } from "../Point2";
import { Size } from "../Size";

//  	Blurs an image using the normalized box filter. More...
export function blur(mat: Mat, kSize: Size, anchor?: Point2, borderType?: number): Mat;
export function blurAsync(mat: Mat, kSize: Size, anchor?: Point2, borderType?: number): Promise<Mat>;

// void 	cv::boxFilter (InputArray src, OutputArray dst, int ddepth, Size ksize, Point anchor=Point(-1,-1), bool normalize=true, int borderType=BORDER_DEFAULT)
//  	Blurs an image using the box filter. More...
//  
// void 	cv::buildPyramid (InputArray src, OutputArrayOfArrays dst, int maxlevel, int borderType=BORDER_DEFAULT)
//  	Constructs the Gaussian pyramid for an image. More...
//  
// void 	cv::dilate (InputArray src, OutputArray dst, InputArray kernel, Point anchor=Point(-1,-1), int iterations=1, int borderType=BORDER_CONSTANT, const Scalar &borderValue=morphologyDefaultBorderValue())
//  	Dilates an image by using a specific structuring element. More...
//  
// void 	cv::erode (InputArray src, OutputArray dst, InputArray kernel, Point anchor=Point(-1,-1), int iterations=1, int borderType=BORDER_CONSTANT, const Scalar &borderValue=morphologyDefaultBorderValue())
//  	Erodes an image by using a specific structuring element. More...
//  
// void 	cv::filter2D (InputArray src, OutputArray dst, int ddepth, InputArray kernel, Point anchor=Point(-1,-1), double delta=0, int borderType=BORDER_DEFAULT)
//  	Convolves an image with the kernel. More...
//  
// void 	cv::GaussianBlur (InputArray src, OutputArray dst, Size ksize, double sigmaX, double sigmaY=0, int borderType=BORDER_DEFAULT)
//  	Blurs an image using a Gaussian filter. More...
export function gaussianBlur(mat: Mat, kSize: Size, sigmaX: number, sigmaY?: number, borderType?: number): Mat;
export function gaussianBlurAsync(mat: Mat, kSize: Size, sigmaX: number, sigmaY?: number, borderType?: number): Promise<Mat>;

// void 	cv::getDerivKernels (OutputArray kx, OutputArray ky, int dx, int dy, int ksize, bool normalize=false, int ktype=CV_32F)
//  	Returns filter coefficients for computing spatial image derivatives. More...
//  
// Mat 	cv::getGaborKernel (Size ksize, double sigma, double theta, double lambd, double gamma, double psi=CV_PI *0.5, int ktype=CV_64F)
//  	Returns Gabor filter coefficients. More...
//  
// Mat 	cv::getGaussianKernel (int ksize, double sigma, int ktype=CV_64F)
//  	Returns Gaussian filter coefficients. More...
//
// Mat 	cv::getStructuringElement (int shape, Size ksize, Point anchor=Point(-1,-1))
//  	Returns a structuring element of the specified size and shape for morphological operations. More...
export function getStructuringElement(shape: number, kernelSize: Size, anchor?: Point2): Mat;

//  
// void 	cv::Laplacian (InputArray src, OutputArray dst, int ddepth, int ksize=1, double scale=1, double delta=0, int borderType=BORDER_DEFAULT)
//  	Calculates the Laplacian of an image. More...
//  
// void 	cv::medianBlur (InputArray src, OutputArray dst, int ksize)
//  	Blurs an image using the median filter. More...
export function medianBlur(mat: Mat, kSize: number): Mat;
export function medianBlurAsync(mat: Mat, kSize: number): Promise<Mat>;


// static Scalar 	cv::morphologyDefaultBorderValue ()
//  	returns "magic" border value for erosion and dilation. It is automatically transformed to Scalar::all(-DBL_MAX) for dilation. More...
//  
// void 	cv::morphologyEx (InputArray src, OutputArray dst, int op, InputArray kernel, Point anchor=Point(-1,-1), int iterations=1, int borderType=BORDER_CONSTANT, const Scalar &borderValue=morphologyDefaultBorderValue())
//  	Performs advanced morphological transformations. More...
//  
// void 	cv::pyrDown (InputArray src, OutputArray dst, const Size &dstsize=Size(), int borderType=BORDER_DEFAULT)
//  	Blurs an image and downsamples it. More...
//  
// void 	cv::pyrMeanShiftFiltering (InputArray src, OutputArray dst, double sp, double sr, int maxLevel=1, TermCriteria termcrit=TermCriteria(TermCriteria::MAX_ITER+TermCriteria::EPS, 5, 1))
//  	Performs initial step of meanshift segmentation of an image. More...
//  
// void 	cv::pyrUp (InputArray src, OutputArray dst, const Size &dstsize=Size(), int borderType=BORDER_DEFAULT)
//  	Upsamples an image and then blurs it. More...
//  
// void 	cv::Scharr (InputArray src, OutputArray dst, int ddepth, int dx, int dy, double scale=1, double delta=0, int borderType=BORDER_DEFAULT)
//  	Calculates the first x- or y- image derivative using Scharr operator. More...
//  
// void 	cv::sepFilter2D (InputArray src, OutputArray dst, int ddepth, InputArray kernelX, InputArray kernelY, Point anchor=Point(-1,-1), double delta=0, int borderType=BORDER_DEFAULT)
//  	Applies a separable linear filter to an image. More...
//  
// void 	cv::Sobel (InputArray src, OutputArray dst, int ddepth, int dx, int dy, int ksize=3, double scale=1, double delta=0, int borderType=BORDER_DEFAULT)
//  	Calculates the first, second, third, or mixed image derivatives using an extended Sobel operator. More...
//  
// void 	cv::spatialGradient (InputArray src, OutputArray dx, OutputArray dy, int ksize=3, int borderType=BORDER_DEFAULT)
//  	Calculates the first order image derivative in both x and y using a Sobel operator. More...
//  
// void 	cv::sqrBoxFilter (InputArray src, OutputArray dst, int ddepth, Size ksize, Point anchor=Point(-1, -1), bool normalize=true, int borderType=BORDER_DEFAULT)
//  	Calculates the normalized sum of squares of the pixel values overlapping the filter. More...
