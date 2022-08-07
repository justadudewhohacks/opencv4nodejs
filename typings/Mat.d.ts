import { Size } from './Size.d';
import { TermCriteria } from './TermCriteria.d';
import { RotatedRect } from './RotatedRect.d';
import { Rect } from './Rect.d';
import { Moments } from './Moments.d';
import { Contour } from './Contour.d';
import { Point2 } from './Point2.d';
import { Vec2 } from './Vec2.d';
import { Vec3 } from './Vec3.d';
import { Vec4 } from './Vec4.d';


export class DrawContoursOptions {
  /**
   * Maximal level for drawn contours. If it is 0, only the specified contour is drawn. If it is 1, the function draws the contour(s) and all the nested contours. If it is 2, the function draws the contours, all the nested contours, all the nested-to-nested contours, and so on. This parameter is only taken into account when there is hierarchy available.
   */
  maxLevel?: number;
  /**
   * Optional contour shift parameter. Shift all the drawn contours by the specified offset=(dx,dy) .
   */
  offset?: Point2;
  /**
   * Line connectivity. See LineTypes
   */
  lineType?: number;
  /**
   * Thickness of lines the contours are drawn with. If it is negative (for example, thickness=FILLED ), the contour interiors are drawn.
   */
  thickness?: number;
}

export class CalibrationMatrixValues {
  /**
   * Output field of view in degrees along the horizontal sensor axis.
   */
  fovx: number;
  /**
   * Output field of view in degrees along the vertical sensor axis.
   */
  fovy: number;
  /**
   * Focal length of the lens in mm.
   */
  focalLength: number;
  /**
   * Principal point in mm.
   */
  principalPoint: Point2;
  /**
   * f(y) / f(x)
   */
  aspectRatio: number;
}

export class StereoRectify {
  /**
   * 	Output 3x3 rectification transform (rotation matrix) for the first camera. This matrix brings points given in the unrectified first camera's coordinate system to points in the rectified first camera's coordinate system. In more technical terms, it performs a change of basis from the unrectified first camera's coordinate system to the rectified first camera's coordinate system.
   */
  R1: Mat;
  /**
   * 	Output 3x3 rectification transform (rotation matrix) for the second camera. This matrix brings points given in the unrectified second camera's coordinate system to points in the rectified second camera's coordinate system. In more technical terms, it performs a change of basis from the unrectified second camera's coordinate system to the rectified second camera's coordinate system.
   */
  R2: Mat;
  /**
   * 	Output 3x4 projection matrix in the new (rectified) coordinate systems for the first camera, i.e. it projects points given in the rectified first camera coordinate system into the rectified first camera's image.
   */
  P1: Mat;
  /**
   * 	Output 3x4 projection matrix in the new (rectified) coordinate systems for the second camera, i.e. it projects points given in the rectified first camera coordinate system into the rectified second camera's image.
   */
  P2: Mat;
  /**
   * Output 4×4 disparity-to-depth mapping matrix (see reprojectImageTo3D).
   */
  Q: Mat;
  /**
   * Optional output rectangles inside the rectified images where all the pixels are valid. If alpha=0 , the ROIs cover the whole images. Otherwise, they are likely to be smaller (see the picture below).
   */
  roi1: Rect;
  /**
   * 	Optional output rectangles inside the rectified images where all the pixels are valid. If alpha=0 , the ROIs cover the whole images. Otherwise, they are likely to be smaller (see the picture below).
   */
  roi2: Rect;
}

export class OptimalNewCameraMatrix {
  /**
   * Returns the new camera intrinsic matrix based on the free scaling parameter.
   */
  out: Mat;
  /**
   * 	Optional output rectangle that outlines all-good-pixels region in the undistorted image. See roi1, roi2 description in stereoRectify .
   */
  validPixROI: Rect;
}

export class Mat {
  /**
   * Mat height like python .shape[0]
   */
  readonly rows: number;
  /**
   * Mat width like python .shape[1]
   */
  readonly cols: number;
  readonly type: number;
  /**
   * Mat channels like python .shape[2]
   */
  readonly channels: number;
  readonly depth: number;
  readonly dims: number;
  readonly empty: boolean;
  readonly step: number;
  readonly elemSize: number;
  // called shape in python
  readonly sizes: number[];
  constructor();
  constructor(channels: Mat[]);
  /**
   * @param type CV_8U, CV_8S, CV_16U, CV_16S, CV_32S, CV_32F, CV_64F ...
   */
  constructor(rows: number, cols: number, type: number, fillValue?: number | number[]);
  /**
   * @param type CV_8U, CV_8S, CV_16U, CV_16S, CV_32S, CV_32F, CV_64F ...
   */
  constructor(rows: number, cols: number, type: number, data: Buffer, step?: number);
  /**
   * @param type CV_8U, CV_8S, CV_16U, CV_16S, CV_32S, CV_32F, CV_64F ...
   */
  constructor(dataArray: number[][] | number[][][] | number[][][][], type: number);
  /**
   * Create a Mat having the given size.
   * The constructor build n-Dimmentional Mat
   * 
   * added in opencv4node 6.2.0
   */
  constructor(sizes: number[], type: number);
  /**
   * @param type CV_8U, CV_8S, CV_16U, CV_16S, CV_32S, CV_32F, CV_64F ...
   */
  constructor(data: Buffer, rows: number, cols: number, type?: number);
  abs(): Mat;
  absdiff(otherMat: Mat): Mat;
  accumulate(src: Mat, mask?: Mat): Mat;
  accumulateAsync(src: Mat, mask?: Mat): Promise<Mat>;
  accumulateProduct(src1: Mat, src2: Mat, mask?: Mat): Mat;
  accumulateProductAsync(src1: Mat, src2: Mat, mask?: Mat): Promise<Mat>;
  accumulateSquare(src: Mat, mask?: Mat): Mat;
  accumulateSquareAsync(src: Mat, mask?: Mat): Promise<Mat>;
  accumulateWeighted(src: Mat, alpha: number, mask?: Mat): Mat;
  accumulateWeightedAsync(src: Mat, alpha: number, mask?: Mat): Promise<Mat>;
  adaptiveThreshold(maxVal: number, adaptiveMethod: number, thresholdType: number, blockSize: number, C: number): Mat;
  adaptiveThresholdAsync(maxVal: number, adaptiveMethod: number, thresholdType: number, blockSize: number, C: number): Promise<Mat>;
  add(otherMat: Mat): Mat;
  addWeighted(alpha: number, mat2: Mat, beta: number, gamma: number, dtype?: number): Mat;
  addWeightedAsync(alpha: number, mat2: Mat, beta: number, gamma: number, dtype?: number): Promise<Mat>;
  and(otherMat: Mat): Mat;
  at(row: number, col: number): number;
  at(row: number, col: number): Vec2;
  at(row: number, col: number): Vec3;
  at(row: number, col: number): Vec4;
  at(idx: number[]): number;
  at(idx: number[]): Vec2;
  at(idx: number[]): Vec3;
  at(idx: number[]): Vec4;
  atRaw(row: number, col: number): number;
  atRaw(row: number, col: number): number[];
  bgrToGray(): Mat;
  bgrToGrayAsync(): Promise<Mat>;
  bilateralFilter(d: number, sigmaColor: number, sigmaSpace: number, borderType?: number): Mat;
  bilateralFilterAsync(d: number, sigmaColor: number, sigmaSpace: number, borderType?: number): Promise<Mat>;
  bitwiseAnd(otherMat: Mat): Mat;
  bitwiseNot(): Mat;
  bitwiseOr(otherMat: Mat): Mat;
  bitwiseXor(otherMat: Mat): Mat;
  blur(kSize: Size, anchor?: Point2, borderType?: number): Mat;
  blurAsync(kSize: Size, anchor?: Point2, borderType?: number): Promise<Mat>;
  boxFilter(ddepth: number, ksize: Size, anchor?: Point2, normalize?: boolean, borderType?: number): Mat;
  boxFilterAsync(ddepth: number, ksize: Size, anchor?: Point2, normalize?: boolean, borderType?: number): Promise<Mat>;
  buildPyramid(maxLevel: number, borderType?: number): Mat[];
  buildPyramidAsync(maxLevel: number, borderType?: number): Promise<Mat[]>;

  /**
   * Computes useful camera characteristics from the camera intrinsic matrix.
   * 
   * Do keep in mind that the unity measure 'mm' stands for whatever unit of measure one chooses for the chessboard pitch (it can thus be any value).
   * 
   * https://docs.opencv.org/4.x/d9/d0c/group__calib3d.html#ga87955f4330d5c20e392b265b7f92f691
   * 
   * @param imageSize Input image size in pixels.
   * @param apertureWidth Physical width in mm of the sensor.
   * @param apertureHeight Physical height in mm of the sensor.
   */
  calibrationMatrixValues(imageSize: Size, apertureWidth: number, apertureHeight: number): CalibrationMatrixValues;
  calibrationMatrixValuesAsync(imageSize: Size, apertureWidth: number, apertureHeight: number): Promise<CalibrationMatrixValues>;
  canny(threshold1: number, threshold2: number, apertureSize?: number, L2gradient?: boolean): Mat;
  cannyAsync(threshold1: number, threshold2: number, apertureSize?: number, L2gradient?: boolean): Promise<Mat>;
  compareHist(H2: Mat, method: number): number;
  compareHistAsync(H2: Mat, method: number): Promise<number>;
  connectedComponents(connectivity?: number, ltype?: number): Mat;
  connectedComponentsAsync(connectivity?: number, ltype?: number): Promise<Mat>;
  connectedComponentsWithStats(connectivity?: number, ltype?: number): { labels: Mat, stats: Mat, centroids: Mat };
  connectedComponentsWithStatsAsync(connectivity?: number, ltype?: number): Promise<{ labels: Mat, stats: Mat, centroids: Mat }>;
  convertScaleAbs(alpha: number, beta: number): Mat;
  convertScaleAbsAsync(alpha: number, beta: number): Promise<Mat>;
  convertTo(type: number, alpha?: number, beta?: number): Mat;
  convertToAsync(type: number, alpha?: number, beta?: number): Promise<Mat>;
  copy(mask?: Mat): Mat;
  copyAsync(mask?: Mat): Promise<Mat>;
  copyMakeBorder(top: number, bottom: number, left: number, right: number, borderType?: number, value?: number | Vec2 | Vec3 | Vec4): Mat;
  copyMakeBorderAsync(top: number, bottom: number, left: number, right: number, borderType?: number, value?: number | Vec2 | Vec3 | Vec4): Promise<Mat>;
  copyTo(dst: Mat, mask?: Mat): Mat;
  copyToAsync(dst: Mat, mask?: Mat): Promise<Mat>;
  cornerEigenValsAndVecs(blockSize: number, ksize?: number, borderType?: number): Mat;
  cornerEigenValsAndVecsAsync(blockSize: number, ksize?: number, borderType?: number): Promise<Mat>;
  cornerHarris(blockSize: number, ksize: number, k: number, borderType?: number): Mat;
  cornerHarrisAsync(blockSize: number, ksize: number, k: number, borderType?: number): Promise<Mat>;
  cornerMinEigenVal(blockSize: number, ksize?: number, borderType?: number): Mat;
  cornerMinEigenValAsync(blockSize: number, ksize?: number, borderType?: number): Promise<Mat>;
  cornerSubPix(corners: Point2[], winSize: Size, zeroZone: Size, criteria: TermCriteria): Point2[];
  cornerSubPixAsync(corners: Point2[], winSize: Size, zeroZone: Size, criteria: TermCriteria): Promise<Point2[]>;
  correctMatches(points1: Point2[], points2: Point2[]): { newPoints1: Point2[], newPoints2: Point2[] };
  correctMatchesAsync(points1: Point2[], points2: Point2[]): Promise<{ newPoints1: Point2[], newPoints2: Point2[] }>;
  countNonZero(): number;
  countNonZeroAsync(): Promise<number>;
  cvtColor(code: number, dstCn?: number): Mat;
  cvtColorAsync(code: number, dstCn?: number): Promise<Mat>;
  dct(flags?: number): Mat;
  dctAsync(flags?: number): Promise<Mat>;
  decomposeEssentialMat(): { R1: Mat, R2: Mat, T: Vec3 };
  decomposeEssentialMatAsync(): Promise<{ R1: Mat, R2: Mat, T: Vec3 }>;
  decomposeHomographyMat(K: Mat): { returnValue: number, rotations: Mat[], translations: Mat[], normals: Mat[] };
  decomposeHomographyMatAsync(K: Mat): Promise<{ returnValue: number, rotations: Mat[], translations: Mat[], normals: Mat[] }>;
  decomposeProjectionMatrix(): { cameraMatrix: Mat, rotMatrix: Mat, transVect: Vec4, rotMatrixX: Mat, rotMatrixY: Mat, rotMatrixZ: Mat, eulerAngles: Mat };
  decomposeProjectionMatrixAsync(): Promise<{ cameraMatrix: Mat, rotMatrix: Mat, transVect: Vec4, rotMatrixX: Mat, rotMatrixY: Mat, rotMatrixZ: Mat, eulerAngles: Mat }>;
  determinant(): number;
  dft(flags?: number, nonzeroRows?: number): Mat;
  dftAsync(flags?: number, nonzeroRows?: number): Promise<Mat>;
  dilate(kernel: Mat, anchor?: Point2, iterations?: number, borderType?: number): Mat;
  dilateAsync(kernel: Mat, anchor?: Point2, iterations?: number, borderType?: number): Promise<Mat>;
  /**
   * Calculates the distance to the closest zero pixel for each pixel of the source image.
   *
   * https://docs.opencv.org/4.x/d7/d1b/group__imgproc__misc.html#ga8a0b7fdfcb7a13dde018988ba3a43042
   *
   * @param distanceType Type of distance, see DistanceTypes
   * @param maskSize Size of the distance transform mask, see DistanceTransformMasks. DIST_MASK_PRECISE is not supported by this variant. In case of the DIST_L1 or DIST_C distance type, the parameter is forced to 3 because a 3×3 mask gives the same result as 5×5 or any larger aperture.
   * @param dstType Type of output image. It can be CV_8U or CV_32F. Type CV_8U can be used only for the first variant of the function and distanceType == DIST_L1.
   */
  distanceTransform(distanceType: number, maskSize: number, dstType?: number): Mat;
  distanceTransformAsync(distanceType: number, maskSize: number, dstType?: number): Promise<Mat>;
  distanceTransformWithLabels(distanceType: number, maskSize: number, labelType?: number): { labels: Mat, dist: Mat };
  distanceTransformWithLabelsAsync(distanceType: number, maskSize: number, labelType?: number): Promise<{ labels: Mat, dist: Mat }>;
  div(s: number): Mat;
  dot(m?: Mat): Mat;
  drawArrowedLine(pt0: Point2, pt1: Point2, color?: Vec3, thickness?: number, lineType?: number, shift?: number, tipLength?: number): void;
  drawChessboardCorners(patternSize: Size, corners: Point2[], patternWasFound: boolean): void;
  drawChessboardCornersAsync(patternSize: Size, corners: Point2[], patternWasFound: boolean): Promise<void>;
  drawCircle(center: Point2, radius: number, color?: Vec3, thickness?: number, lineType?: number, shift?: number): void;
  // alternate signature
  /**
   * Draws contours outlines or filled contours.
   * 
   * The function draws contour outlines in the image if thickness≥0 or fills the area bounded by the contours if thickness<0 . The example below shows how to retrieve connected components from the binary image and label them: :
   * 
   * https://docs.opencv.org/4.5.4/d6/d6e/group__imgproc__draw.html#ga746c0625f1781f1ffc9056259103edbc
   * 
   * MatImgprocBindings.h
   * @param contours list of contours
   * @param contourIdx 0 based contour index to draw
   */
  drawContours(contours: Point2[][], contourIdx: number, color: Vec3, opts: DrawContoursOptions): void;
  drawContours(contours: Point2[][], contourIdx: number, color: Vec3, thickness?: number, lineType?: number, hierarchy?: Vec4[], maxLevel?: number, offset?: Point2): void;
  // drawContours(contours: Point2[][], contourIdx: number, color: Vec3, maxLevel?: number, offset?: Point2, lineType?: number, thickness?: number, shift?: number): void;
  // alternate signature
  drawEllipse(box: RotatedRect, opts: { color?: Vec3, thickness?: number, lineType?: number }): void;
  drawEllipse(box: RotatedRect, color?: Vec3, thickness?: number, lineType?: number): void;
  drawEllipse(center: Point2, axes: Size, angle: number, startAngle: number, endAngle: number, color?: Vec3, thickness?: number, lineType?: number, shift?: number): void;

  drawFillConvexPoly(pts: Point2[], color?: Vec3, lineType?: number, shift?: number): void;
  drawFillPoly(pts: Point2[][], color?: Vec3, lineType?: number, shift?: number, offset?: Point2): void;
  // alternate signature
  drawLine(pt0: Point2, pt1: Point2, opts: { color?: Vec3, thickness?: number, lineType?: number, shift?: number }): void;
  drawLine(pt0: Point2, pt1: Point2, color?: Vec3, thickness?: number, lineType?: number, shift?: number): void;
  drawPolylines(pts: Point2[][], isClosed: boolean, color?: Vec3, thickness?: number, lineType?: number, shift?: number): void;
  drawRectangle(pt0: Point2, pt1: Point2, color?: Vec3, thickness?: number, lineType?: number, shift?: number): void;
  // alternate signature
  /**
   * 
   * @param pt0 Vertex of the rectangle.
   * @param pt1 Vertex of the rectangle opposite to pt1 . 
   * @param opt.color 	Rectangle color or brightness (grayscale image). 
   * @param opt.thickness 	Thickness of lines that make up the rectangle. Negative values, like FILLED, mean that the function has to draw a filled rectangle. {@see https://docs.opencv.org/4.x/d6/d6e/group__imgproc__draw.html#ggaf076ef45de481ac96e0ab3dc2c29a777a89c5f6beef080e6df347167f85e07b9e}
   * @param opt.lineType	Type of the line. See LineTypes {@see https://docs.opencv.org/4.x/d6/d6e/group__imgproc__draw.html#gaf076ef45de481ac96e0ab3dc2c29a777}
   * @param opt.shift	shift	Number of fractional bits in the point coordinates. 
   */
  drawRectangle(pt0: Point2, pt1: Point2, opt: { color?: Vec3, thickness?: number, lineType?: number, shift?: number }): void;
  drawRectangle(rect: Rect, color?: Vec3, thickness?: number, lineType?: number, shift?: number): void;
  eigen(): Mat;
  eigenAsync(): Promise<Mat>;
  equalizeHist(): Mat;
  equalizeHistAsync(): Promise<Mat>;
  erode(kernel: Mat, anchor?: Point2, iterations?: number, borderType?: number): Mat;
  erodeAsync(kernel: Mat, anchor?: Point2, iterations?: number, borderType?: number): Promise<Mat>;
  exp(): Mat;
  log(): Mat;
  filter2D(ddepth: number, kernel: Mat, anchor?: Point2, delta?: number, borderType?: number): Mat;
  filter2DAsync(ddepth: number, kernel: Mat, anchor?: Point2, delta?: number, borderType?: number): Promise<Mat>;
  filterSpeckles(newVal: number, maxSpeckleSize: number, maxDiff: number): { newPoints1: Point2[], newPoints2: Point2[] };
  filterSpecklesAsync(newVal: number, maxSpeckleSize: number, maxDiff: number): Promise<{ newPoints1: Point2[], newPoints2: Point2[] }>;
  find4QuadCornerSubpix(corners: Point2[], regionSize: Size): boolean;
  find4QuadCornerSubpixAsync(corners: Point2[], regionSize: Size): Promise<boolean>;
  findChessboardCorners(patternSize: Size, flags?: number): { returnValue: boolean, corners: Point2[] };
  findChessboardCornersAsync(patternSize: Size, flags?: number): Promise<{ returnValue: boolean, corners: Point2[] }>;
  findContours(mode: number, method: number, offset?: Point2): Contour[];
  findContoursAsync(mode: number, method: number, offset?: Point2): Promise<Contour[]>;
  findEssentialMat(points1: Point2[], points2: Point2[], method?: number, prob?: number, threshold?: number): { E: Mat, mask: Mat };
  findEssentialMatAsync(points1: Point2[], points2: Point2[], method?: number, prob?: number, threshold?: number): Promise<{ E: Mat, mask: Mat }>;
  findNonZero(): Point2[];
  findNonZeroAsync(): Promise<Point2[]>;
  flattenFloat(rows: number, cols: number): Mat;
  flip(flipCode: number): Mat;
  flipAsync(flipCode: number): Promise<Mat>;
  /**
   * Fills a connected component with the given color.
   *
   * The function cv::floodFill fills a connected component starting from the seed point with the specified color. The connectivity is determined by the color/brightness closeness of the neighbor pixels. The pixel at (x,y) is considered to belong to the repainted domain if:
   *
   * https://docs.opencv.org/4.x/d7/d1b/group__imgproc__misc.html#ga366aae45a6c1289b341d140839f18717
   *
   * @param seedPoint Starting point.
   * @param newVal New value of the repainted domain pixels.
   * @param mask Operation mask that should be a single-channel 8-bit image, 2 pixels wider and 2 pixels taller than image. Since this is both an input and output parameter, you must take responsibility of initializing it. Flood-filling cannot go across non-zero pixels in the input mask. For example, an edge detector output can be used as a mask to stop filling at edges. On output, pixels in the mask corresponding to filled pixels in the image are set to 1 or to the a value specified in flags as described below. Additionally, the function fills the border of the mask with ones to simplify internal processing. It is therefore possible to use the same mask in multiple calls to the function to make sure the filled areas do not overlap.
   * @param loDiff Maximal lower brightness/color difference between the currently observed pixel and one of its neighbors belonging to the component, or a seed pixel being added to the component.
   * @param upDiff Maximal upper brightness/color difference between the currently observed pixel and one of its neighbors belonging to the component, or a seed pixel being added to the component.
   * @param flags Operation flags. The first 8 bits contain a connectivity value. The default value of 4 means that only the four nearest neighbor pixels (those that share an edge) are considered. A connectivity value of 8 means that the eight nearest neighbor pixels (those that share a corner) will be considered. The next 8 bits (8-16) contain a value between 1 and 255 with which to fill the mask (the default value is 1). For example, 4 | ( 255 << 8 ) will consider 4 nearest neighbours and fill the mask with a value of 255. The following additional options occupy higher bits and therefore may be further combined with the connectivity and mask fill values using bit-wise or (|), see FloodFillFlags.
   */
  floodFill<T extends number | Vec3>(seedPoint: Point2, newVal: T, mask?: Mat, loDiff?: T, upDiff?: T, flags?: T): { returnValue: number, rect: Rect };
  floodFill<T extends number | Vec3>(seedPoint: Point2, newVal: T, opts: { mask?: Mat, loDiff?: T, upDiff?: T, flags?: T }): { returnValue: number, rect: Rect };

  floodFillAsync<T extends number | Vec3>(seedPoint: Point2, newVal: T, mask?: Mat, loDiff?: T, upDiff?: T, flags?: number): Promise<{ returnValue: number, rect: Rect }>;
  floodFillAsync<T extends number | Vec3>(seedPoint: Point2, newVal: T, opts: { mask?: Mat, loDiff?: T, upDiff?: T, flags?: number }): Promise<{ returnValue: number, rect: Rect }>;

  gaussianBlur(kSize: Size, sigmaX: number, sigmaY?: number, borderType?: number): Mat;
  gaussianBlurAsync(kSize: Size, sigmaX: number, sigmaY?: number, borderType?: number): Promise<Mat>;
  getData(): Buffer;
  getDataAsync(): Promise<Buffer>;
  /**
   * if Mat.dims <= 2
   * 
   * @see https://github.com/justadudewhohacks/opencv4nodejs/issues/329
   * 
   * Note this method offer low performances, use getData instead.
   */
  getDataAsArray(): number[][];
  /**
   * if Mat.dims > 2 (3D)
   */
  getDataAsArray(): number[][][];
  /**
   * The function computes and returns the optimal new camera intrinsic matrix based on the free scaling parameter. By varying this parameter, you may retrieve only sensible pixels alpha=0 , keep all the original image pixels if there is valuable information in the corners alpha=1 , or get something in between. When alpha>0 , the undistorted result is likely to have some black pixels corresponding to "virtual" pixels outside of the captured distorted image. The original camera intrinsic matrix, distortion coefficients, the computed new camera intrinsic matrix, and newImageSize should be passed to initUndistortRectifyMap to produce the maps for remap.
   * 
   * https://docs.opencv.org/4.x/d9/d0c/group__calib3d.html#ga7a6c4e032c97f03ba747966e6ad862b1
   * 
   * @param distCoeffs 	Input vector of distortion coefficients (k1,k2,p1,p2[,k3[,k4,k5,k6[,s1,s2,s3,s4[,τx,τy]]]]) of 4, 5, 8, 12 or 14 elements. If the vector is NULL/empty, the zero distortion coefficients are assumed.
   * @param imageSize Original image size.
   * @param alpha Free scaling parameter between 0 (when all the pixels in the undistorted image are valid) and 1 (when all the source image pixels are retained in the undistorted image). See stereoRectify for details.
   * @param newImageSize 	Image size after rectification. By default, it is set to imageSize .
   * @param centerPrincipalPoint Optional flag that indicates whether in the new camera intrinsic matrix the principal point should be at the image center or not. By default, the principal point is chosen to best fit a subset of the source image (determined by alpha) to the corrected image.
   */
  getOptimalNewCameraMatrix(distCoeffs: number[], imageSize: Size, alpha: number, newImageSize?: Size, centerPrincipalPoint?: boolean): OptimalNewCameraMatrix;
  getOptimalNewCameraMatrixAsync(distCoeffs: number[], imageSize: Size, alpha: number, newImageSize?: Size, centerPrincipalPoint?: boolean): Promise<OptimalNewCameraMatrix>;
  /**
   * crop a region from the image
   * like python Mat[x1,y1,x2,y2]
   * @param region
   */
  getRegion(region: Rect): Mat;
  goodFeaturesToTrack(maxCorners: number, qualityLevel: number, minDistance: number, mask?: Mat, blockSize?: number, gradientSize?: number, useHarrisDetector?: boolean, harrisK?: number): Point2[];
  goodFeaturesToTrackAsync(maxCorners: number, qualityLevel: number, minDistance: number, mask?: Mat, blockSize?: number, gradientSize?: number, useHarrisDetector?: boolean, harrisK?: number): Promise<Point2[]>;
  grabCut(mask: Mat, rect: Rect, bgdModel: Mat, fgdModel: Mat, iterCount: number, mode: number): void;
  grabCutAsync(mask: Mat, rect: Rect, bgdModel: Mat, fgdModel: Mat, iterCount: number, mode: number): Promise<void>;
  guidedFilter(guide: Mat, radius: number, eps: number, ddepth?: number): Mat;
  guidedFilterAsync(guide: Mat, radius: number, eps: number, ddepth?: number): Promise<Mat>;
  hDiv(otherMat: Mat): Mat;
  hMul(otherMat: Mat): Mat;
  houghCircles(method: number, dp: number, minDist: number, param1?: number, param2?: number, minRadius?: number, maxRadius?: number): Vec3[];
  houghCirclesAsync(method: number, dp: number, minDist: number, param1?: number, param2?: number, minRadius?: number, maxRadius?: number): Promise<Vec3[]>;
  houghLines(rho: number, theta: number, threshold: number, srn?: number, stn?: number, min_theta?: number, max_theta?: number): Vec2[];
  houghLinesAsync(rho: number, theta: number, threshold: number, srn?: number, stn?: number, min_theta?: number, max_theta?: number): Promise<Vec2[]>;
  houghLinesP(rho: number, theta: number, threshold: number, minLineLength?: number, maxLineGap?: number): Vec4[];
  houghLinesPAsync(rho: number, theta: number, threshold: number, minLineLength?: number, maxLineGap?: number): Promise<Vec4[]>;
  idct(flags?: number): Mat;
  idctAsync(flags?: number): Promise<Mat>;
  idft(flags?: number, nonzeroRows?: number): Mat;
  idftAsync(flags?: number, nonzeroRows?: number): Promise<Mat>;
  inRange(lower: number, upper: number): Mat;
  inRange(lower: Vec3, upper: Vec3): Mat;
  inRangeAsync(lower: number, upper: number): Promise<Mat>;
  inRangeAsync(lower: Vec3, upper: Vec3): Promise<Mat>;
  /**
   * Calculates the integral of an image.
   *
   * https://docs.opencv.org/4.x/d7/d1b/group__imgproc__misc.html#ga97b87bec26908237e8ba0f6e96d23e28
   *
   * @param sdepth desired depth of the integral and the tilted integral images, CV_32S, CV_32F, or CV_64F.
   * @param sqdepth desired depth of the integral image of squared pixel values, CV_32F or CV_64F.
   */
  integral(sdepth?: number, sqdepth?: number): { sum: Mat, sqsum: Mat, tilted: Mat };
  integral(opts: { sdepth?: number, sqdepth?: number }): { sum: Mat, sqsum: Mat, tilted: Mat };
  integralAsync(sdepth?: number, sqdepth?: number): Promise<{ sum: Mat, sqsum: Mat, tilted: Mat }>;
  integralAsync(opts: { sdepth?: number, sqdepth?: number }): Promise<{ sum: Mat, sqsum: Mat, tilted: Mat }>;
  inv(): Mat;
  laplacian(ddepth: number, ksize?: number, scale?: number, delta?: number, borderType?: number): Mat;
  laplacianAsync(ddepth: number, ksize?: number, scale?: number, delta?: number, borderType?: number): Promise<Mat>;
  matMul(B: Mat): Mat;
  matMulDeriv(B: Mat): { dABdA: Mat, dABdB: Mat };
  matMulDerivAsync(B: Mat): Promise<{ dABdA: Mat, dABdB: Mat }>;
  /**
   * Compares a template against overlapped image regions.
   *
   * The function slides through image , compares the overlapped patches of size w×h against templ using the specified method and stores the comparison results in result . TemplateMatchModes describes the formulae for the available comparison methods ( I denotes image, T template, R result, M the optional mask ). The summation is done over template and/or the image patch: x′=0...w−1,y′=0...h−1
   * After the function finishes the comparison, the best matches can be found as global minimums (when TM_SQDIFF was used) or maximums (when TM_CCORR or TM_CCOEFF was used) using the minMaxLoc function. In case of a color image, template summation in the numerator and each sum in the denominator is done over all of the channels and separate mean values are used for each channel. That is, the function can take a color template and a color image. The result will still be a single-channel image, which is easier to analyze.
   *
   * https://docs.opencv.org/4.x/df/dfb/group__imgproc__object.html#ga586ebfb0a7fb604b35a23d85391329be
   *
   * @param template Searched template. It must be not greater than the source image and have the same data type.
   * @param method Parameter specifying the comparison method, can be one of TM_SQDIFF, TM_SQDIFF_NORMED, TM_CCORR, TM_CCORR_NORMED, TM_CCOEFF, TM_CCOEFF_NORMED.
   * @param mask Optional mask. It must have the same size as templ. It must either have the same number of channels as template or only one channel, which is then used for all template and image channels. If the data type is CV_8U, the mask is interpreted as a binary mask, meaning only elements where mask is nonzero are used and are kept unchanged independent of the actual mask value (weight equals 1). For data tpye CV_32F, the mask values are used as weights. The exact formulas are documented in TemplateMatchModes.
   * 
   * @return Map of comparison results. It must be single-channel 32-bit floating-point. If image is W×H and templ is w×h , then result is (W−w+1)×(H−h+1) .
   */
  matchTemplate(template: Mat, method: number, mask?: Mat): Mat;
  matchTemplateAsync(template: Mat, method: number, mask?: Mat): Promise<Mat>;
  mean(): Vec4;
  meanAsync(): Promise<Vec4>;
  meanStdDev(mask?: Mat): { mean: Mat, stddev: Mat };
  meanStdDevAsync(mask?: Mat): Promise<{ mean: Mat, stddev: Mat }>;
  medianBlur(kSize: number): Mat;
  medianBlurAsync(kSize: number): Promise<Mat>;
  /**
   * Finds the global minimum and maximum in an array.
   *
   * The function cv::minMaxLoc finds the minimum and maximum element values and their positions. The extremums are searched across the whole array or, if mask is not an empty array, in the specified array region.
   *
   * The function do not work with multi-channel arrays. If you need to find minimum or maximum elements across all the channels, use Mat::reshape first to reinterpret the array as single-channel. Or you may extract the particular channel using either extractImageCOI , or mixChannels , or split .
   *
   * https://docs.opencv.org/4.x/d2/de8/group__core__array.html#gab473bf2eb6d14ff97e89b355dac20707
   *
   * @param mask 	optional mask used to select a sub-array.
   */
  minMaxLoc(mask?: Mat): { minVal: number, maxVal: number, minLoc: Point2, maxLoc: Point2 };
  minMaxLocAsync(mask?: Mat): Promise<{ minVal: number, maxVal: number, minLoc: Point2, maxLoc: Point2 }>;
  moments(): Moments;
  momentsAsync(): Promise<Moments>;
  morphologyEx(kernel: Mat, morphType: number, anchor?: Point2, iterations?: number, borderType?: number): Mat;
  morphologyExAsync(kernel: Mat, morphType: number, anchor?: Point2, iterations?: number, borderType?: number): Promise<Mat>;
  mul(s: number): Mat;
  mulSpectrums(mat2: Mat, dftRows?: boolean, conjB?: boolean): Mat;
  mulSpectrumsAsync(mat2: Mat, dftRows?: boolean, conjB?: boolean): Promise<Mat>;
  norm(src2: Mat, normType?: number, mask?: Mat): number;
  norm(normType?: number, mask?: Mat): number;

  normalize(alpha?: number, beta?: number, normType?: number, dtype?: number, mask?: Mat): Mat;
  normalize(opt: { alpha?: number, beta?: number, normType?: number, dtype?: number, mask?: Mat }): Mat;

  normalizeAsync(alpha?: number, beta?: number, normType?: number, dtype?: number, mask?: Mat): Promise<Mat>;
  normalizeAsync(opt: { alpha?: number, beta?: number, normType?: number, dtype?: number, mask?: Mat }): Promise<Mat>;

  or(otherMat: Mat): Mat;
  padToSquare(color: Vec3): Mat;

  perspectiveTransform(m: Mat): Mat;
  perspectiveTransformAsync(m: Mat): Promise<Mat>;

  pop_back(numRows?: number): Mat;
  pop_backAsync(numRows?: number): Promise<Mat>;

  popBack(numRows?: number): Mat;
  popBackAsync(numRows?: number): Promise<Mat>;

  push_back(mat: Mat): Mat;
  push_backAsync(mat: Mat): Promise<Mat>;

  pushBack(mat: Mat): Mat;
  pushBackAsync(mat: Mat): Promise<Mat>;

  putText(text: string, origin: Point2, fontFace: number, fontScale: number, color?: Vec3, thickness?: number, lineType?: number, bottomLeftOrigin?: boolean | 0): void;
  putText(text: string, origin: Point2, fontFace: number, fontScale: number, opts?: { color?: Vec3, thickness?: number, lineType?: number, bottomLeftOrigin?: boolean | 0 }): void;

  putTextAsync(text: string, origin: Point2, fontFace: number, fontScale: number, color?: Vec3, thickness?: number, lineType?: number, bottomLeftOrigin?: boolean | 0): Promise<void>;
  putTextAsync(text: string, origin: Point2, fontFace: number, fontScale: number, opts?: { color?: Vec3, thickness?: number, lineType?: number, bottomLeftOrigin?: boolean | 0 }): Promise<void>;

  pyrDown(size?: Size, borderType?: number): Mat;
  pyrDownAsync(size?: Size, borderType?: number): Promise<Mat>;

  pyrUp(size?: Size, borderType?: number): Mat;
  pyrUpAsync(size?: Size, borderType?: number): Promise<Mat>;

  recoverPose(E: Mat, points1: Point2[], points2: Point2[], mask?: Mat): { returnValue: number, R: Mat, T: Vec3 };
  recoverPoseAsync(E: Mat, points1: Point2[], points2: Point2[], mask?: Mat): Promise<{ returnValue: number, R: Mat, T: Vec3 }>;

  rectify3Collinear(distCoeffs1: number[], cameraMatrix2: Mat, distCoeffs2: number[], cameraMatrix3: Mat, distCoeffs3: number[], imageSize: Size, R12: Mat, T12: Vec3, R13: Mat, T13: Vec3, alpha: number, newImageSize: Size, flags: number): { returnValue: number, R1: Mat, R2: Mat, R3: Mat, P1: Mat, P2: Mat, P3: Mat, Q: Mat, roi1: Rect, roi2: Rect };
  rectify3CollinearAsync(distCoeffs1: number[], cameraMatrix2: Mat, distCoeffs2: number[], cameraMatrix3: Mat, distCoeffs3: number[], imageSize: Size, R12: Mat, T12: Vec3, R13: Mat, T13: Vec3, alpha: number, newImageSize: Size, flags: number): Promise<{ returnValue: number, R1: Mat, R2: Mat, R3: Mat, P1: Mat, P2: Mat, P3: Mat, Q: Mat, roi1: Rect, roi2: Rect }>;

  reduce(dim: number, rtype: number, dtype?: number): Mat;
  reduceAsync(dim: number, rtype: number, dtype?: number): Promise<Mat>;

  reprojectImageTo3D(Q: Mat, handleMissingValues?: boolean, ddepth?: number): Mat;
  reprojectImageTo3DAsync(Q: Mat, handleMissingValues?: boolean, ddepth?: number): Promise<Mat>;

  rescale(factor: number): Mat;
  rescaleAsync(factor: number): Promise<Mat>;

  resize(rows: number, cols: number, fx?: number, fy?: number, interpolation?: number): Mat;
  resize(dsize: Size, fx?: number, fy?: number, interpolation?: number): Mat;

  resizeAsync(rows: number, cols: number, fx?: number, fy?: number, interpolation?: number): Promise<Mat>;
  resizeAsync(dsize: Size, fx?: number, fy?: number, interpolation?: number): Promise<Mat>;

  resizeToMax(maxRowsOrCols: number): Mat;
  resizeToMaxAsync(maxRowsOrCols: number): Promise<Mat>;

  rodrigues(): { dst: Mat, jacobian: Mat };
  rodriguesAsync(): Promise<{ dst: Mat, jacobian: Mat }>;
  rotate(rotateCode: number): Mat;
  rotateAsync(rotateCode: number): Promise<Mat>;
  rqDecomp3x3(): { returnValue: Vec3, mtxR: Mat, mtxQ: Mat, Qx: Mat, Qy: Mat, Qz: Mat };
  rqDecomp3x3Async(): Promise<{ returnValue: Vec3, mtxR: Mat, mtxQ: Mat, Qx: Mat, Qy: Mat, Qz: Mat }>;
  scharr(ddepth: number, dx: number, dy: number, scale?: number, delta?: number, borderType?: number): Mat;
  scharrAsync(ddepth: number, dx: number, dy: number, scale?: number, delta?: number, borderType?: number): Promise<Mat>;
  seamlessClone(dst: Mat, mask: Mat, p: Point2, flags: number): Mat;
  seamlessCloneAsync(dst: Mat, mask: Mat, p: Point2, flags: number): Promise<Mat>;
  /**
   * Applies a separable linear filter to an image.
   *
   * The function applies a separable linear filter to the image. That is, first, every row of src is filtered with the 1D kernel kernelX. Then, every column of the result is filtered with the 1D kernel kernelY. The final result shifted by delta is stored in dst .
   *
   * https://docs.opencv.org/4.x/d4/d86/group__imgproc__filter.html#ga910e29ff7d7b105057d1625a4bf6318d
   *
   * @param ddepth Destination image depth, see combinations
   * @param kernelX Coefficients for filtering each row.
   * @param kernelY Coefficients for filtering each column.
   * @param anchor Anchor position within the kernel. The default value (−1,−1) means that the anchor is at the kernel center.
   * @param delta Value added to the filtered results before storing them.
   * @param borderType Pixel extrapolation method, see BorderTypes. BORDER_WRAP is not supported.
   */
  sepFilter2D(ddepth: number, kernelX: Mat, kernelY: Mat, anchor?: Point2, delta?: number, borderType?: number): Mat;
  sepFilter2D(ddepth: number, kernelX: Mat, kernelY: Mat, opts: { anchor?: Point2, delta?: number, borderType?: number }): Mat;
  sepFilter2DAsync(ddepth: number, kernelX: Mat, kernelY: Mat, anchor?: Point2, delta?: number, borderType?: number): Promise<Mat>;
  sepFilter2DAsync(ddepth: number, kernelX: Mat, kernelY: Mat, opts: { anchor?: Point2, delta?: number, borderType?: number }): Promise<Mat>;

  set(row: number, col: number, value: number | Vec2 | Vec3 | Vec4 | number[]): void;
  setTo(value: number | Vec2 | Vec3 | Vec4, mask?: Mat): Mat;
  setToAsync(value: number | Vec2 | Vec3 | Vec4, mask?: Mat): Promise<Mat>;
  /**
   *
   * https://docs.opencv.org/4.x/d4/d86/group__imgproc__filter.html#gacea54f142e81b6758cb6f375ce782c8d
   *
   * @param ddepth output image depth, see combinations; in the case of 8-bit input images it will result in truncated derivatives.
   * @param dx 	order of the derivative x.
   * @param dy 	order of the derivative y.
   * @param ksize size of the extended Sobel kernel; it must be 1, 3, 5, or 7.
   * @param scale optional scale factor for the computed derivative values; by default, no scaling is applied (see getDerivKernels for details).
   * @param delta optional delta value that is added to the results prior to storing them in dst.
   * @param borderType pixel extrapolation method, see BorderTypes. BORDER_WRAP is not supported.
   */
  sobel(ddepth: number, dx: number, dy: number, ksize?: 1 | 3 | 5 | 7, scale?: number, delta?: number, borderType?: number): Mat;
  sobel(ddepth: number, dx: number, dy: number, opts: { ksize?: 1 | 3 | 5 | 7, scale?: number, delta?: number, borderType?: number }): Mat;
  sobelAsync(ddepth: number, dx: number, dy: number, ksize?: 1 | 3 | 5 | 7, scale?: number, delta?: number, borderType?: number): Promise<Mat>;
  sobelAsync(ddepth: number, dx: number, dy: number, opts: { ksize?: 1 | 3 | 5 | 7, scale?: number, delta?: number, borderType?: number }): Promise<Mat>;

  solve(mat2: Mat, flags?: number): Mat;
  solveAsync(mat2: Mat, flags?: number): Promise<Mat>;
  split(): Mat[];
  splitAsync(): Promise<Mat[]>;
  splitChannels(): Mat[];
  splitChannelsAsync(): Promise<Mat[]>;
  sqrBoxFilter(ddepth: number, ksize: Size, anchor?: Point2, normalize?: boolean, borderType?: number): Mat;
  sqrBoxFilterAsync(ddepth: number, ksize: Size, anchor?: Point2, normalize?: boolean, borderType?: number): Promise<Mat>;
  sqrt(): Mat;
  /**
   * Computes rectification transforms for each head of a calibrated stereo camera.
   * 
   * https://docs.opencv.org/4.x/d9/d0c/group__calib3d.html#ga617b1685d4059c6040827800e72ad2b6
   * 
   * @param distCoeffs1 First camera distortion parameters.
   * @param cameraMatrix2 Second camera intrinsic matrix.
   * @param distCoeffs2 Second camera distortion parameters.
   * @param imageSize Size of the image used for stereo calibration.
   * @param R Rotation matrix from the coordinate system of the first camera to the second camera, see stereoCalibrate.
   * @param T Translation vector from the coordinate system of the first camera to the second camera, see stereoCalibrate.
   * @param flags Operation flags that may be zero or CALIB_ZERO_DISPARITY . If the flag is set, the function makes the principal points of each camera have the same pixel coordinates in the rectified views. And if the flag is not set, the function may still shift the images in the horizontal or vertical direction (depending on the orientation of epipolar lines) to maximize the useful image area.
   * @param alpha Free scaling parameter. If it is -1 or absent, the function performs the default scaling. Otherwise, the parameter should be between 0 and 1. alpha=0 means that the rectified images are zoomed and shifted so that only valid pixels are visible (no black areas after rectification). alpha=1 means that the rectified image is decimated and shifted so that all the pixels from the original images from the cameras are retained in the rectified images (no source image pixels are lost). Any intermediate value yields an intermediate result between those two extreme cases.
   * @param newImageSize New image resolution after rectification. The same size should be passed to initUndistortRectifyMap (see the stereo_calib.cpp sample in OpenCV samples directory). When (0,0) is passed (default), it is set to the original imageSize . Setting it to a larger value can help you preserve details in the original image, especially when there is a big radial distortion.
   */
  stereoRectify(distCoeffs1: number[], cameraMatrix2: Mat, distCoeffs2: number[], imageSize: Size, R: Mat, T: Vec3, flags?: number, alpha?: number, newImageSize?: Size): StereoRectify;
  stereoRectifyAsync(distCoeffs1: number[], cameraMatrix2: Mat, distCoeffs2: number[], imageSize: Size, R: Mat, T: Vec3, flags?: number, alpha?: number, newImageSize?: Size): Promise<StereoRectify>;
  sub(otherMat: Mat): Mat;
  /**
   * Calculates the sum of array elements.
   * The function cv::sum calculates and returns the sum of array elements, independently for each channel.
   * https://docs.opencv.org/4.x/d2/de8/group__core__array.html#ga716e10a2dd9e228e4d3c95818f106722
   * Mat must have from 1 to 4 channels.
   */
  sum(): number | Vec2 | Vec3 | Vec4;
  sumAsync(): Promise<number | Vec2 | Vec3 | Vec4>;
  /**
   * Applies a fixed-level threshold to each array element.
   *
   * The function applies fixed-level thresholding to a multiple-channel array. The function is typically used to get a bi-level (binary) image out of a grayscale image ( compare could be also used for this purpose) or for removing a noise, that is, filtering out pixels with too small or too large values. There are several types of thresholding supported by the function. They are determined by type parameter.
   *
   * Also, the special values THRESH_OTSU or THRESH_TRIANGLE may be combined with one of the above values. In these cases, the function determines the optimal threshold value using the Otsu's or Triangle algorithm and uses it instead of the specified thresh.
   *
   * Note: Currently, the Otsu's and Triangle methods are implemented only for 8-bit single-channel images.
   * https://docs.opencv.org/4.x/d7/d1b/group__imgproc__misc.html#gae8a4a146d1ca78c626a53577199e9c57
   * @param thresh threshold value.
   * @param maxVal maximum value to use with the THRESH_BINARY and THRESH_BINARY_INV thresholding types
   * @param type thresholding type (see ThresholdTypes).
   */
  threshold(thresh: number, maxVal: number, type: number): Mat;
  thresholdAsync(thresh: number, maxVal: number, type: number): Promise<Mat>;

  transform(m: Mat): Mat;
  transformAsync(m: Mat): Promise<Mat>;

  transpose(): Mat;
  /**
   * This function reconstructs 3-dimensional points (in homogeneous coordinates) by using their observations with a stereo camera.
   *
   * https://docs.opencv.org/4.x/d9/d0c/group__calib3d.html#gad3fc9a0c82b08df034234979960b778c
   * @param projPoints1 2xN array of feature points in the first image. In the case of the c++ version, it can be also a vector of feature points or two-channel matrix of size 1xN or Nx1.
   * @param projPoints2 2xN array of corresponding points in the second image. In the case of the c++ version, it can be also a vector of feature points or two-channel matrix of size 1xN or Nx1.
   */
  triangulatePoints(projPoints1: Point2[], projPoints2: Point2[]): Mat;
  triangulatePointsAsync(projPoints1: Point2[], projPoints2: Point2[]): Promise<Mat>;

  /**
   * Transforms an image to compensate for lens distortion.
   *
   * The function transforms an image to compensate radial and tangential lens distortion.
   *
   * The function is simply a combination of initUndistortRectifyMap (with unity R ) and remap (with bilinear interpolation). See the former function for details of the transformation being performed.
   *
   * Those pixels in the destination image, for which there is no correspondent pixels in the source image, are filled with zeros (black color).
   *
   * A particular subset of the source image that will be visible in the corrected image can be regulated by newCameraMatrix. You can use getOptimalNewCameraMatrix to compute the appropriate newCameraMatrix depending on your requirements.
   *
   * The camera matrix and the distortion parameters can be determined using calibrateCamera. If the resolution of images is different from the resolution used at the calibration stage, fx,fy,cx and cy need to be scaled accordingly, while the distortion coefficients remain the same.
   *
   * https://docs.opencv.org/4.x/d9/d0c/group__calib3d.html#ga69f2545a8b62a6b0fc2ee060dc30559d
   *
   * @param cameraMatrix Input camera matrix
   * @param distCoeffs 	Input vector of distortion coefficients (k1,k2,p1,p2[,k3[,k4,k5,k6[,s1,s2,s3,s4[,τx,τy]]]]) of 4, 5, 8, 12 or 14 elements. If the vector is NULL/empty, the zero distortion coefficients are assumed.
   */
  undistort(cameraMatrix: Mat, distCoeffs: Mat): Mat;
  undistortAsync(cameraMatrix: Mat, distCoeffs: Mat): Promise<Mat>;
  validateDisparity(cost: Mat, minDisparity: number, numberOfDisparities: number, disp12MaxDisp?: number): void;
  validateDisparityAsync(cost: Mat, minDisparity: number, numberOfDisparities: number, disp12MaxDisp?: number): Promise<void>;
  warpAffine(transforMationMatrix: Mat, size?: Size, flags?: number, borderMode?: number, borderValue?: Vec3): Mat;
  warpAffineAsync(transforMationMatrix: Mat, size?: Size, flags?: number, borderMode?: number, borderValue?: Vec3): Promise<Mat>;
  warpPerspective(transforMationMatrix: Mat, size?: Size, flags?: number, borderMode?: number, borderValue?: Vec3): Mat;
  warpPerspectiveAsync(transforMationMatrix: Mat, size?: Size, flags?: number, borderMode?: number, borderValue?: Vec3): Promise<Mat>;
  watershed(markers: Mat): Mat;
  watershedAsync(markers: Mat): Promise<Mat>;
  release(): void;
  /**
   * Returns an identity matrix of the specified size and type.
   *
   * The method returns a Matlab-style identity matrix initializer, similarly to Mat::zeros. Similarly to Mat::ones, you can use a scale operation to create a scaled identity matrix efficiently:
   *
   * // make a 4x4 diagonal matrix with 0.1's on the diagonal.
   * Mat A = Mat::eye(4, 4, CV_32F)*0.1;
   *
   * Note: In case of multi-channels type, identity matrix will be initialized only for the first channel, the others will be set to 0's
   * https://docs.opencv.org/4.x/d3/d63/classcv_1_1Mat.html#a458874f0ab8946136254da37ba06b78b
   * @param rows Number of rows.
   * @param cols Number of columns.
   * @param type Created matrix type.
   */
  static eye(rows: number, cols: number, type: number): Mat;
}
