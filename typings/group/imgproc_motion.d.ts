import { Mat } from "..";

/**
 * Adds an image to the accumulator image.
 * 
 * https://docs.opencv.org/4.x/d7/df3/group__imgproc__motion.html#ga1a567a79901513811ff3b9976923b199
 * 
 * @param src Input image of type CV_8UC(n), CV_16UC(n), CV_32FC(n) or CV_64FC(n), where n is a positive integer.
 * @param dst Accumulator image with the same number of channels as input image, and a depth of CV_32F or CV_64F.
 * @param mask Optional operation mask.
 */
 export function accumulate(src: Mat, dst: Mat, mask?: Mat): void;
 export function accumulateAsync(src: Mat, dst: Mat, mask?: Mat): Promise<void>;
 
 /**
  * Adds the per-element product of two input images to the accumulator image.
  * 
  * https://docs.opencv.org/4.x/d7/df3/group__imgproc__motion.html#ga82518a940ecfda49460f66117ac82520
  * 
  * @param src1 First input image, 1- or 3-channel, 8-bit or 32-bit floating point.
  * @param src2 Second input image of the same type and the same size as src1 .
  * @param dst Accumulator image with the same number of channels as input images, 32-bit or 64-bit floating-point.
  * @param mask Optional operation mask.
  */
 export function accumulateProduct(src1: Mat, src2: Mat, dst: Mat, mask?: Mat): void;
 export function accumulateProductAsync(src1: Mat, src2: Mat, dst: Mat, mask?: Mat): Promise<void>;
 
 /**
  * Adds the square of a source image to the accumulator image.
  * 
  * https://docs.opencv.org/4.x/d7/df3/group__imgproc__motion.html#gacb75e7ffb573227088cef9ceaf80be8c
  * 
  * @param src Input image as 1- or 3-channel, 8-bit or 32-bit floating point.
  * @param dst Accumulator image with the same number of channels as input image, 32-bit or 64-bit floating-point.
  * @param mask Optional operation mask.
  */
 export function accumulateSquare(src: Mat, dst: Mat, mask?: Mat): void;
 export function accumulateSquareAsync(src: Mat, dst: Mat, mask?: Mat): Promise<void>;
 
 /**
  * Updates a running average.
  * 
  * https://docs.opencv.org/4.x/d7/df3/group__imgproc__motion.html#ga4f9552b541187f61f6818e8d2d826bc7
  * 
  * @param src Input image as 1- or 3-channel, 8-bit or 32-bit floating point.
  * @param dst Accumulator image with the same number of channels as input image, 32-bit or 64-bit floating-point.
  * @param alpha Weight of the input image.
  * @param mask Optional operation mask.
  */
 export function accumulateWeighted(src: Mat, dst: Mat, alpha: number, mask?: Mat): void;
 export function accumulateWeightedAsync(src: Mat, dst: Mat, alpha: number, mask?: Mat): Promise<void>;
 
// missing:
// createHanningWindow (OutputArray dst, Size winSize, int type)
// 	This function computes a Hanning window coefficients in two dimensions. More...
// void divSpectrums (InputArray a, InputArray b, OutputArray c, int flags, bool conjB=false)
//  Performs the per-element division of the first Fourier spectrum by the second Fourier spectrum. More...
// phaseCorrelate (InputArray src1, InputArray src2, InputArray window=noArray(), double *response=0)
// 	The function is used to detect translational shifts that occur between two images. More...
 