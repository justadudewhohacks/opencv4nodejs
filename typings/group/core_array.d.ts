import { Mat } from "../Mat";
import { Point2 } from "../Point2";
import { Vec2 } from "../Vec2";
import { Vec3 } from "../Vec3";
import { Vec4 } from "../Vec4";

// void 	cv::absdiff (InputArray src1, InputArray src2, OutputArray dst)
// Calculates the per-element absolute difference between two arrays or between an array and a scalar. More...

// void 	cv::add (InputArray src1, InputArray src2, OutputArray dst, InputArray mask=noArray(), int dtype=-1)
//  	Calculates the per-element sum of two arrays or an array and a scalar. More...

/**
 * 
 * https://docs.opencv.org/4.x/d2/de8/group__core__array.html#gafafb2513349db3bcff51f54ee5592a19
 * @param src1	https://docs.opencv.org/4.x/d2/de8/group__core__array.html#gafafb2513349db3bcff51f54ee5592a19
 * @param alpha	weight of the first array elements.
 * @param src2	second input array of the same size and channel number as src1.
 * @param beta	weight of the second array elements.
 * @param gamma	scalar added to each sum.
 * @param dst	output array that has the same size and number of channels as the input arrays.
 * @param dtype	optional depth of the output array; when both input arrays have the same depth, dtype can be set to -1, which will be equivalent to src1.depth().
 * 
 * TODO Check binding dst was missing
 */
export function addWeighted(src1: Mat, alpha: number, src2: Mat, beta: number, gamma: number, dst: Mat, dtype?: number): Mat;
export function addWeightedAsync(src1: Mat, alpha: number, src2: Mat, beta: number, gamma: number, dst: Mat, dtype?: number): Promise<Mat>;

// void 	cv::batchDistance (InputArray src1, InputArray src2, OutputArray dist, int dtype, OutputArray nidx, int normType=NORM_L2, int K=0, InputArray mask=noArray(), int update=0, bool crosscheck=false)
// 	naive nearest neighbor finder More...

// void 	cv::bitwise_and (InputArray src1, InputArray src2, OutputArray dst, InputArray mask=noArray())
//  	computes bitwise conjunction of the two arrays (dst = src1 & src2) Calculates the per-element bit-wise conjunction of two arrays or an array and a scalar. More...
//  
// void 	cv::bitwise_not (InputArray src, OutputArray dst, InputArray mask=noArray())
//  	Inverts every bit of an array. More...
//  
// void 	cv::bitwise_or (InputArray src1, InputArray src2, OutputArray dst, InputArray mask=noArray())
//  	Calculates the per-element bit-wise disjunction of two arrays or an array and a scalar. More...
//  
// void 	cv::bitwise_xor (InputArray src1, InputArray src2, OutputArray dst, InputArray mask=noArray())
//  	Calculates the per-element bit-wise "exclusive or" operation on two arrays or an array and a scalar. More...
//  
// int 	cv::borderInterpolate (int p, int len, int borderType)
//  	Computes the source location of an extrapolated pixel. More...
//  
// void 	cv::calcCovarMatrix (const Mat *samples, int nsamples, Mat &covar, Mat &mean, int flags, int ctype=CV_64F)
//  	Calculates the covariance matrix of a set of vectors. More...
//  
// void 	cv::calcCovarMatrix (InputArray samples, OutputArray covar, InputOutputArray mean, int flags, int ctype=CV_64F)
//  
// void 	cv::cartToPolar (InputArray x, InputArray y, OutputArray magnitude, OutputArray angle, bool angleInDegrees=false)
//  	Calculates the magnitude and angle of 2D vectors. More...
/**
 * Calculates the magnitude and angle of 2D vectors.
 * 
 * https://docs.opencv.org/4.x/d2/de8/group__core__array.html#gac5f92f48ec32cacf5275969c33ee837d
 * @param x array of x-coordinates; this must be a single-precision or double-precision floating-point array.
 * @param y array of y-coordinates, that must have the same size and same type as x.
 * @param magnitude output array of magnitudes of the same size and type as x.
 * @param angle output array of angles that has the same size and type as x; the angles are measured in radians (from 0 to 2*Pi) or in degrees (0 to 360 degrees).
 * @param angleInDegrees a flag, indicating whether the angles are measured in radians (which is by default), or in degrees.
 * TODO Check binding magnitude, angle was missing
 */
export function cartToPolar(x: Mat, y: Mat, magnitude: Mat, angle: Mat, angleInDegrees?: boolean): { magnitude: Mat, angle: Mat };
export function cartToPolarAsync(x: Mat, y: Mat, magnitude: Mat, angle: Mat, angleInDegrees?: boolean): Promise<{ magnitude: Mat, angle: Mat }>;

// bool 	cv::checkRange (InputArray a, bool quiet=true, Point *pos=0, double minVal=-DBL_MAX, double maxVal=DBL_MAX)
//  	Checks every element of an input array for invalid values. More...
//  
// void 	cv::compare (InputArray src1, InputArray src2, OutputArray dst, int cmpop)
//  	Performs the per-element comparison of two arrays or an array and scalar value. More...
//  
// void 	cv::completeSymm (InputOutputArray m, bool lowerToUpper=false)
//  	Copies the lower or the upper half of a square matrix to its another half. More...
//  
// void 	cv::convertFp16 (InputArray src, OutputArray dst)
//  	Converts an array to half precision floating number. More...


// void 	cv::convertScaleAbs (InputArray src, OutputArray dst, double alpha=1, double beta=0)
//  	Scales, calculates absolute values, and converts the result to 8-bit. More...
/**
 * Scales, calculates absolute values, and converts the result to 8-bit.
 * 
 * https://docs.opencv.org/4.x/d2/de8/group__core__array.html#ga3460e9c9f37b563ab9dd550c4d8c4e7d
 * 
 * @param src 	input array
 * @param dst 	output array.
 * @param alpha optional scale factor.
 * @param beta 	optional delta added to the scaled values.
 * TODO Check binding dst was missing
 */
export function convertScaleAbs(src: Mat, dst: Mat, alpha?: number, beta?: number): Mat;
export function convertScaleAbsAsync(src: Mat, dst: Mat, alpha: number, beta: number): Promise<Mat>;

// void 	cv::copyMakeBorder (InputArray src, OutputArray dst, int top, int bottom, int left, int right, int borderType, const Scalar &value=Scalar())
//  	Forms a border around an image. More...
//  
// void 	cv::copyTo (InputArray src, OutputArray dst, InputArray mask)
//  	This is an overloaded member function, provided for convenience (python) Copies the matrix to another one. When the operation mask is specified, if the Mat::create call shown above reallocates the matrix, the newly allocated matrix is initialized with all zeros before copying the data. More...
//  

// int 	cv::countNonZero (InputArray src)
//  	Counts non-zero array elements. More...
/**
 * https://docs.opencv.org/4.x/d2/de8/group__core__array.html#gaa4b89393263bb4d604e0fe5986723914
 * Counts non-zero array elements.
 * @param mat single-channel array.
 */
export function countNonZero(mat: Mat): number;
export function countNonZeroAsync(mat: Mat): Promise<number>;

//  
// void 	cv::dct (InputArray src, OutputArray dst, int flags=0)
//  	Performs a forward or inverse discrete Cosine transform of 1D or 2D array. More...
//  
// double 	cv::determinant (InputArray mtx)
//  	Returns the determinant of a square floating-point matrix. More...
//  
// void 	cv::dft (InputArray src, OutputArray dst, int flags=0, int nonzeroRows=0)
//  	Performs a forward or inverse Discrete Fourier transform of a 1D or 2D floating-point array. More...
//  
// void 	cv::divide (InputArray src1, InputArray src2, OutputArray dst, double scale=1, int dtype=-1)
//  	Performs per-element division of two arrays or a scalar by an array. More...
//  
// void 	cv::divide (double scale, InputArray src2, OutputArray dst, int dtype=-1)
//  
// bool 	cv::eigen (InputArray src, OutputArray eigenvalues, OutputArray eigenvectors=noArray())
//  	Calculates eigenvalues and eigenvectors of a symmetric matrix. More...
/**
 * https://docs.opencv.org/4.x/d2/de8/group__core__array.html#ga9fa0d58657f60eaa6c71f6fbb40456e3
 * 
 * Calculates eigenvalues and eigenvectors of a symmetric matrix.
 * 
 * @param src	input matrix (CV_32FC1 or CV_64FC1 type).
 * @param eigenvalues	output vector of eigenvalues (type is the same type as src).
 * @param eigenvectors	output matrix of eigenvectors (type is the same type as src). The eigenvectors are stored as subsequent matrix rows, in the same order as the corresponding eigenvalues.
 * TODO Check binding eigenvalues, eigenvectors was missing
 */
export function eigen(src: Mat, eigenvalues?: Mat, eigenvectors?: Mat): Mat;
export function eigenAsync(src: Mat, eigenvalues?: Mat, eigenvectors?: Mat): Promise<Mat>;
// void 	cv::eigenNonSymmetric (InputArray src, OutputArray eigenvalues, OutputArray eigenvectors)
//  	Calculates eigenvalues and eigenvectors of a non-symmetric matrix (real eigenvalues only). More...
//  
// void 	cv::exp (InputArray src, OutputArray dst)
//  	Calculates the exponent of every array element. More...
//  
// void 	cv::extractChannel (InputArray src, OutputArray dst, int coi)
//  	Extracts a single channel from src (coi is 0-based index) More...

/**
 * Returns the list of locations of non-zero pixels. More...
 * @param src single-channel array
 * @param idx the output array, type of cv::Mat or std::vector<Point>, corresponding to non-zero indices in the input
 * TODO Check binding idx was missing
 */
export function findNonZero(src: Mat, idx?: Mat): Point2[];
export function findNonZeroAsync(src: Mat, idx?: Mat): Promise<Point2[]>;

//  
// void 	cv::flip (InputArray src, OutputArray dst, int flipCode)
//  	Flips a 2D array around vertical, horizontal, or both axes. More...
//  
// void 	cv::gemm (InputArray src1, InputArray src2, double alpha, InputArray src3, double beta, OutputArray dst, int flags=0)
//  	Performs generalized matrix multiplication. More...
//  
// int 	cv::getOptimalDFTSize (int vecsize)
//  	Returns the optimal DFT size for a given vector size. More...
//  
// void 	cv::hconcat (const Mat *src, size_t nsrc, OutputArray dst)
//  	Applies horizontal concatenation to given matrices. More...
//  
// void 	cv::hconcat (InputArray src1, InputArray src2, OutputArray dst)
//  
// void 	cv::hconcat (InputArrayOfArrays src, OutputArray dst)
//  
// void 	cv::idct (InputArray src, OutputArray dst, int flags=0)
//  	Calculates the inverse Discrete Cosine Transform of a 1D or 2D array. More...
//  
// void 	cv::idft (InputArray src, OutputArray dst, int flags=0, int nonzeroRows=0)
//  	Calculates the inverse Discrete Fourier Transform of a 1D or 2D array. More...
//  
// void 	cv::inRange (InputArray src, InputArray lowerb, InputArray upperb, OutputArray dst)
//  	Checks if array elements lie between the elements of two other arrays. More...
//  
// void 	cv::insertChannel (InputArray src, InputOutputArray dst, int coi)
//  	Inserts a single channel to dst (coi is 0-based index) More...
//  
// double 	cv::invert (InputArray src, OutputArray dst, int flags=DECOMP_LU)
//  	Finds the inverse or pseudo-inverse of a matrix. More...
//  
// void 	cv::log (InputArray src, OutputArray dst)
//  	Calculates the natural logarithm of every array element. More...
//  
// void 	cv::LUT (InputArray src, InputArray lut, OutputArray dst)
//  	Performs a look-up table transform of an array. More...
//  
// void 	cv::magnitude (InputArray x, InputArray y, OutputArray magnitude)
//  	Calculates the magnitude of 2D vectors. More...
//  
// double 	cv::Mahalanobis (InputArray v1, InputArray v2, InputArray icovar)
//  	Calculates the Mahalanobis distance between two vectors. More...
//  
// void 	cv::max (InputArray src1, InputArray src2, OutputArray dst)
//  	Calculates per-element maximum of two arrays or an array and a scalar. More...
//  
// void 	cv::max (const Mat &src1, const Mat &src2, Mat &dst)
//  
// void 	cv::max (const UMat &src1, const UMat &src2, UMat &dst)
//  

/**
 * Calculates a mean and standard deviation of array elements.
 * 
 * https://docs.opencv.org/4.x/d2/de8/group__core__array.html#ga191389f8a0e58180bb13a727782cd461
 * 
 * @param src	input array that should have from 1 to 4 channels so that the result can be stored in Scalar_ .
 * @param mask	optional operation mask.
 */
export function mean(src: Mat, mask: Mat): Vec4;
export function meanAsync(src: Mat, mask: Mat): Promise<Vec4>;


/**
 * Calculates a mean and standard deviation of array elements.
 * 
 * https://docs.opencv.org/4.x/d2/de8/group__core__array.html#ga846c858f4004d59493d7c6a4354b301d
 * 
 * @param src	input array that should have from 1 to 4 channels so that the results can be stored in Scalar_ 's.
 * @param mean	output parameter: calculated mean value.
 * @param stddev	output parameter: calculated standard deviation.
 * @param  mask	optional operation mask.
 * 
 * cv.meanStdDev(	src[, mean[, stddev[, mask]]]	) ->	mean, stddev
 * TODO
 */ 
export function meanStdDev(mat: Mat, mask?: Mat): { mean: Mat, stddev: Mat };
export function meanStdDevAsync(mat: Mat, mask?: Mat): Promise<{ mean: Mat, stddev: Mat }>;

//  
// void 	cv::merge (const Mat *mv, size_t count, OutputArray dst)
//  	Creates one multi-channel array out of several single-channel ones. More...
//  
// void 	cv::merge (InputArrayOfArrays mv, OutputArray dst)
//  
// void 	cv::min (InputArray src1, InputArray src2, OutputArray dst)
//  	Calculates per-element minimum of two arrays or an array and a scalar. More...
//  
// void 	cv::min (const Mat &src1, const Mat &src2, Mat &dst)
//  
// void 	cv::min (const UMat &src1, const UMat &src2, UMat &dst)
//  
// void 	cv::minMaxIdx (InputArray src, double *minVal, double *maxVal=0, int *minIdx=0, int *maxIdx=0, InputArray mask=noArray())
//  	Finds the global minimum and maximum in an array. More...
//  
// void 	cv::minMaxLoc (InputArray src, double *minVal, double *maxVal=0, Point *minLoc=0, Point *maxLoc=0, InputArray mask=noArray())
//  	Finds the global minimum and maximum in an array. More...
//  
// void 	cv::minMaxLoc (const SparseMat &a, double *minVal, double *maxVal, int *minIdx=0, int *maxIdx=0)
//  
// void 	cv::mixChannels (const Mat *src, size_t nsrcs, Mat *dst, size_t ndsts, const int *fromTo, size_t npairs)
//  	Copies specified channels from input arrays to the specified channels of output arrays. More...
//  
// void 	cv::mixChannels (InputArrayOfArrays src, InputOutputArrayOfArrays dst, const int *fromTo, size_t npairs)
//  
// void 	cv::mixChannels (InputArrayOfArrays src, InputOutputArrayOfArrays dst, const std::vector< int > &fromTo)
//  
/**
 * Performs the per-element multiplication of two Fourier spectrums.
 * 
 * https://docs.opencv.org/4.x/d2/de8/group__core__array.html#ga3ab38646463c59bf0ce962a9d51db64f
 * 
 * @param a	first input array.
 * @param b	second input array of the same size and type as src1 .
 * @param c	output array of the same size and type as src1 .
 * @param flags	operation flags; currently, the only supported flag is cv::DFT_ROWS, which indicates that each row of src1 and src2 is an independent 1D Fourier spectrum. If you do not want to use this flag, then simply add a 0 as value.
 * @param conjB	optional flag that conjugates the second input array before the multiplication (true) or not (false).
 * 	cv.mulSpectrums(	a, b, flags[, c[, conjB]]	) ->	c
 * TODO
 */
export function mulSpectrums(src1: Mat, src2: Mat, dftRows?: boolean, conjB?: boolean): Mat;
export function mulSpectrumsAsync(src1: Mat, src2: Mat, dftRows?: boolean, conjB?: boolean): Promise<Mat>;

// void 	cv::mulSpectrums (InputArray a, InputArray b, OutputArray c, int flags, bool conjB=false)
//  	Performs the per-element multiplication of two Fourier spectrums. More...
//  
// void 	cv::multiply (InputArray src1, InputArray src2, OutputArray dst, double scale=1, int dtype=-1)
//  	Calculates the per-element scaled product of two arrays. More...
//  
// void 	cv::mulTransposed (InputArray src, OutputArray dst, bool aTa, InputArray delta=noArray(), double scale=1, int dtype=-1)
//  	Calculates the product of a matrix and its transposition. More...
//  
// double 	cv::norm (InputArray src1, int normType=NORM_L2, InputArray mask=noArray())
//  	Calculates the absolute norm of an array. More...
//  
// double 	cv::norm (InputArray src1, InputArray src2, int normType=NORM_L2, InputArray mask=noArray())
//  	Calculates an absolute difference norm or a relative difference norm. More...
//  
// double 	cv::norm (const SparseMat &src, int normType)
//  
// void 	cv::normalize (InputArray src, InputOutputArray dst, double alpha=1, double beta=0, int norm_type=NORM_L2, int dtype=-1, InputArray mask=noArray())
//  	Normalizes the norm or value range of an array. More...
//  
// void 	cv::normalize (const SparseMat &src, SparseMat &dst, double alpha, int normType)
//  
// void 	cv::patchNaNs (InputOutputArray a, double val=0)
//  	converts NaNs to the given number More...
//  
// void 	cv::PCABackProject (InputArray data, InputArray mean, InputArray eigenvectors, OutputArray result)
//  
// void 	cv::PCACompute (InputArray data, InputOutputArray mean, OutputArray eigenvectors, int maxComponents=0)
//  
// void 	cv::PCACompute (InputArray data, InputOutputArray mean, OutputArray eigenvectors, OutputArray eigenvalues, int maxComponents=0)
//  
// void 	cv::PCACompute (InputArray data, InputOutputArray mean, OutputArray eigenvectors, double retainedVariance)
//  
// void 	cv::PCACompute (InputArray data, InputOutputArray mean, OutputArray eigenvectors, OutputArray eigenvalues, double retainedVariance)
//  
// void 	cv::PCAProject (InputArray data, InputArray mean, InputArray eigenvectors, OutputArray result)
//  
/**
 * Performs the perspective matrix transformation of vectors.
 *
 * @param src	input two-channel or three-channel floating-point array; each element is a 2D/3D vector to be transformed.
 * @param dst	output array of the same size and type as src.
 * @param m	3x3 or 4x4 floating-point transformation matrix.
 */
export function perspectiveTransform(mat: Mat, m: Mat): Mat;
export function perspectiveTransformAsync(mat: Mat, m: Mat): Promise<Mat>;

// void 	cv::phase (InputArray x, InputArray y, OutputArray angle, bool angleInDegrees=false)
//  	Calculates the rotation angle of 2D vectors. More...
//  
// void 	cv::polarToCart (InputArray magnitude, InputArray angle, OutputArray x, OutputArray y, bool angleInDegrees=false)
//  	Calculates x and y coordinates of 2D vectors from their magnitude and angle. More...
/**
 * Calculates x and y coordinates of 2D vectors from their magnitude and angle.
 * 
 * @param magnitude	input floating-point array of magnitudes of 2D vectors; it can be an empty matrix (=Mat()), in this case, the function assumes that all the magnitudes are =1; if it is not empty, it must have the same size and type as angle.
 * @param angle	input floating-point array of angles of 2D vectors.
 * @param x	output array of x-coordinates of 2D vectors; it has the same size and type as angle.
 * @param y	output array of y-coordinates of 2D vectors; it has the same size and type as angle.
 * @param angleInDegrees	when true, the input angles are measured in degrees, otherwise, they are measured in radians.
 */
export function polarToCart(magnitude: Mat, angle: Mat, angleInDegrees?: boolean): { x: Mat, y: Mat };
export function polarToCartAsync(magnitude: Mat, angle: Mat, angleInDegrees?: boolean): Promise<{ x: Mat, y: Mat }>;


// void 	cv::pow (InputArray src, double power, OutputArray dst)
//  	Raises every array element to a power. More...
//  
// double 	cv::PSNR (InputArray src1, InputArray src2, double R=255.)
//  	Computes the Peak Signal-to-Noise Ratio (PSNR) image quality metric. More...
//  
// void 	cv::randn (InputOutputArray dst, InputArray mean, InputArray stddev)
//  	Fills the array with normally distributed random numbers. More...
//  
// void 	cv::randShuffle (InputOutputArray dst, double iterFactor=1., RNG *rng=0)
//  	Shuffles the array elements randomly. More...
//  
// void 	cv::randu (InputOutputArray dst, InputArray low, InputArray high)
//  	Generates a single uniformly-distributed random number or an array of random numbers. More...
//  
// void 	cv::reduce (InputArray src, OutputArray dst, int dim, int rtype, int dtype=-1)
//  	Reduces a matrix to a vector. More...
export function reduce(mat: Mat, dim: number, rtype: number, dtype?: number): Mat;
export function reduceAsync(mat: Mat, dim: number, rtype: number, dtype?: number): Promise<Mat>;

//  
// void 	cv::reduceArgMax (InputArray src, OutputArray dst, int axis, bool lastIndex=false)
//  	Finds indices of max elements along provided axis. More...
//  
// void 	cv::reduceArgMin (InputArray src, OutputArray dst, int axis, bool lastIndex=false)
//  	Finds indices of min elements along provided axis. More...
//  
// void 	cv::repeat (InputArray src, int ny, int nx, OutputArray dst)
//  	Fills the output array with repeated copies of the input array. More...
//  
// Mat 	cv::repeat (const Mat &src, int ny, int nx)
//  
// void 	cv::rotate (InputArray src, OutputArray dst, int rotateCode)
//  	Rotates a 2D array in multiples of 90 degrees. The function cv::rotate rotates the array in one of three different ways: Rotate by 90 degrees clockwise (rotateCode = ROTATE_90_CLOCKWISE). Rotate by 180 degrees clockwise (rotateCode = ROTATE_180). Rotate by 270 degrees clockwise (rotateCode = ROTATE_90_COUNTERCLOCKWISE). More...
//  
// void 	cv::scaleAdd (InputArray src1, double alpha, InputArray src2, OutputArray dst)
//  	Calculates the sum of a scaled array and another array. More...
//  
// void 	cv::setIdentity (InputOutputArray mtx, const Scalar &s=Scalar(1))
//  	Initializes a scaled identity matrix. More...
//  
// void 	cv::setRNGSeed (int seed)
//  	Sets state of default random number generator. More...
//  




// bool 	cv::solve (InputArray src1, InputArray src2, OutputArray dst, int flags=DECOMP_LU)
//  	Solves one or more linear systems or least-squares problems. More...
export function solve(mat: Mat, mat2: Mat, flags?: number): Mat;
export function solveAsync(mat: Mat, mat2: Mat, flags?: number): Promise<Mat>;


// int 	cv::solveCubic (InputArray coeffs, OutputArray roots)
//  	Finds the real roots of a cubic equation. More...
//  
// double 	cv::solvePoly (InputArray coeffs, OutputArray roots, int maxIters=300)
//  	Finds the real or complex roots of a polynomial equation. More...
//  



// void 	cv::sort (InputArray src, OutputArray dst, int flags)
//  	Sorts each row or each column of a matrix. More...
//  
// void 	cv::sortIdx (InputArray src, OutputArray dst, int flags)
//  	Sorts each row or each column of a matrix. More...
//  
// void 	cv::split (const Mat &src, Mat *mvbegin)
//  	Divides a multi-channel array into several single-channel arrays. More...
//  
// void 	cv::split (InputArray m, OutputArrayOfArrays mv)
//  

export function split(mat: Mat): Mat[];
export function splitAsync(mat: Mat): Promise<Mat[]>;


// void 	cv::sqrt (InputArray src, OutputArray dst)
//  	Calculates a square root of array elements. More...
//  
// void 	cv::subtract (InputArray src1, InputArray src2, OutputArray dst, InputArray mask=noArray(), int dtype=-1)
//  	Calculates the per-element difference between two arrays or array and a scalar. More...
//  
// Scalar 	cv::sum (InputArray src)
//  	Calculates the sum of array elements. More...
export function sum(mat: Mat): number;
export function sum(mat: Mat): Vec2;
export function sum(mat: Mat): Vec3;
export function sum(mat: Mat): Vec4;
export function sumAsync(mat: Mat): Promise<number>;
export function sumAsync(mat: Mat): Promise<Vec2>;
export function sumAsync(mat: Mat): Promise<Vec3>;
export function sumAsync(mat: Mat): Promise<Vec4>;

//  
// void 	cv::SVBackSubst (InputArray w, InputArray u, InputArray vt, InputArray rhs, OutputArray dst)
//  
// void 	cv::SVDecomp (InputArray src, OutputArray w, OutputArray u, OutputArray vt, int flags=0)
//  
// RNG & 	cv::theRNG ()
//  	Returns the default random number generator. More...
//  
// Scalar 	cv::trace (InputArray mtx)
//  	Returns the trace of a matrix. More...
//  
// void 	cv::transform (InputArray src, OutputArray dst, InputArray m)
//  	Performs the matrix transformation of every array element. More...
export function transform(mat: Mat, m: Mat): Mat;
export function transformAsync(mat: Mat, m: Mat): Promise<Mat>;

// void 	cv::transpose (InputArray src, OutputArray dst)
//  	Transposes a matrix. More...
//  
// void 	cv::vconcat (const Mat *src, size_t nsrc, OutputArray dst)
//  	Applies vertical concatenation to given matrices. More...
//  
// void 	cv::vconcat (InputArray src1, InputArray src2, OutputArray dst)
//  
// void 	cv::vconcat (InputArrayOfArrays src, OutputArray dst)
