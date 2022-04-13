import { Mat } from '../Mat.d';

// https://docs.opencv.org/4.x/d3/d50/group__imgproc__colormap.html#gadf478a5e5ff49d8aa24e726ea6f65d15

// void 	cv::applyColorMap (InputArray src, OutputArray dst, int colormap)
// Applies a GNU Octave/MATLAB equivalent colormap on a given image. More...
// 
// void 	cv::applyColorMap (InputArray src, OutputArray dst, InputArray userColor)
// Applies a user colormap on a given image. More...

export function applyColorMap(src: Mat, colormap: number | Mat): Mat;
