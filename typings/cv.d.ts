import { Mat } from './Mat.d';
import { Size } from './Size.d';
import { Vec2 } from './Vec2.d';
import { Vec3 } from './Vec3.d';
import { Vec4 } from './Vec4.d';
import { Point2 } from './Point2.d';
import { Point3 } from './Point3.d';
import { KeyPoint } from './KeyPoint.d';
import { DescriptorMatch } from './DescriptorMatch.d';
import { Rect } from './Rect.d';
import { OCRHMMClassifier } from './OCRHMMClassifier.d';

export class HistAxes {
  channel: number;
  bins: number;
  ranges: [number, number];

  constructor(channel: number, bins: number, ranges: [number, number]);
  constructor(opts: { channel: number, bins: number, ranges: [number, number] });
}

export * from './group/calib3d';
export * from './group/core_array';
export * from './group/core_cluster';
export * from './group/core_utils';
export * from './group/imgproc_motion';
export * from './group/dnn';
export * from './group/highgui.d';
export * from './group/imgcodecs.d';
export * from './group/imgproc_colormap';
export * from './group/imgproc_filter';
export * from './group/imgproc_motion';
// export * from './group/imgproc_draw';

/** @deprecated */
export function calcHist(img: Mat, histAxes: { channel: number, bins: number, ranges: [number, number] }[], mask?: Mat): Mat;
export function calcHist(img: Mat, histAxes: HistAxes[], mask?: Mat): Mat;
export function calcHistAsync(img: Mat, histAxes: HistAxes[], mask?: Mat): Promise<Mat>;

export function canny(dx: Mat, dy: Mat, threshold1: number, threshold2: number, L2gradient?: boolean): Mat;
export function composeRT(rvec1: Vec3, tvec1: Vec3, rvec2: Vec3, tvec2: Vec3): { rvec3: Vec3, tvec3: Vec3, dr3dr1: Mat, dr3dt1: Mat, dr3dr2: Mat, dr3dt2: Mat, dt3dr1: Mat, dt3dt1: Mat, dt3dr2: Mat, dt3dt2: Mat };
export function composeRTAsync(rvec1: Vec3, tvec1: Vec3, rvec2: Vec3, tvec2: Vec3): Promise<{ rvec3: Vec3, tvec3: Vec3, dr3dr1: Mat, dr3dt1: Mat, dr3dr2: Mat, dr3dt2: Mat, dt3dr1: Mat, dt3dt1: Mat, dt3dr2: Mat, dt3dt2: Mat }>;
export function computeCorrespondEpilines(points: Point2[], whichImage: number, F: Mat): Vec3[];
export function computeCorrespondEpilinesAsync(points: Point2[], whichImage: number, F: Mat): Promise<Vec3[]>;

export function createOCRHMMTransitionsTable(vocabulary: string, lexicon: string[]): Mat;
export function createOCRHMMTransitionsTableAsync(vocabulary: string, lexicon: string[]): Promise<Mat>;
export function drawKeyPoints(img: Mat, keyPoints: KeyPoint[]): Mat;
export function drawMatches(img1: Mat, img2: Mat, keyPoints1: KeyPoint[], keyPoints2: KeyPoint[], matches: DescriptorMatch[]): Mat;

export function fastNlMeansDenoisingColored(src: Mat, h?: number, hColor?: number, templateWindowSize?: number, searchWindowSize?: number): Mat;
export function inpaint(src: Mat, mask: Mat, inpaintRadius: number, flags: number): Mat;
export function inpaintAsync(src: Mat, mask: Mat, inpaintRadius: number, flags: number): Promise<Mat>;
export function findEssentialMat(points1: Point2[], points2: Point2[], focal?: number, pp?: Point2, method?: number, prob?: number, threshold?: number): { E: Mat, mask: Mat };
export function findEssentialMatAsync(points1: Point2[], points2: Point2[], focal?: number, pp?: Point2, method?: number, prob?: number, threshold?: number): Promise<{ E: Mat, mask: Mat }>;
export function findFundamentalMat(points1: Point2[], points2: Point2[], method?: number, param1?: number, param2?: number): { F: Mat, mask: Mat };
export function findFundamentalMatAsync(points1: Point2[], points2: Point2[], method?: number, param1?: number, param2?: number): Promise<{ F: Mat, mask: Mat }>;
export function findHomography(srcPoints: Point2[], dstPoints: Point2[], method?: number, ransacReprojThreshold?: number, maxIters?: number, confidence?: number): { homography: Mat, mask: Mat };
export function fitLine(points: Point2[], distType: number, param: number, reps: number, aeps: number): Vec4;
export function fitLine(points: Point3[], distType: number, param: number, reps: number, aeps: number): number[];
export function getAffineTransform(srcPoints: Point2[], dstPoints: Point2[]): Mat;
export function getBuildInformation(): string;
export function getPerspectiveTransform(srcPoints: Point2[], dstPoints: Point2[]): Mat;
export function getRotationMatrix2D(center: Point2, angle: number, scale?: number): Mat;


/**
 * openCV 3 and 4 are not compatible
 * 
 * Calculates the width and height of a text string.
 * param text	Input text string.
 * param fontHeight	Drawing font size by pixel unit.
 * param thickness	Thickness of lines used to render the text. See putText for details.
 * param baseLine	y-coordinate of the baseline relative to the bottom-most text point.
 * 
 * @param text	Input text string.
 * @param fontFace	Font to use, see HersheyFonts.
 * @param fontScale	Font scale factor that is multiplied by the font-specific base size.
 * @param thickness	Thickness of lines used to render the text. See putText for details.
 * @param [out]	baseLine	y-coordinate of the baseline relative to the bottom-most text point.
 */
export function getTextSize(text: string, fontFace: number, fontScale: number, thickness: number): { size: Size, baseLine: number };
export function getTextSizeAsync(text: string, fontFace: number, fontScale: number, thickness: number): Promise<{ size: Size, baseLine: number }>;

export function getValidDisparityROI(roi1: Rect[], roi2: Rect[], minDisparity: number, numberOfDisparities: number, SADWindowSize: number): Rect;
export function getValidDisparityROIAsync(roi1: Rect[], roi2: Rect[], minDisparity: number, numberOfDisparities: number, SADWindowSize: number): Promise<Rect>;
export function goodFeaturesToTrack(mat: Mat, maxCorners: number, qualityLevel: number, minDistance: number, mask?: Mat, blockSize?: number, gradientSize?: number, useHarrisDetector?: boolean, harrisK?: number): Point2[];
export function goodFeaturesToTrackAsync(mat: Mat, maxCorners: number, qualityLevel: number, minDistance: number, mask?: Mat, blockSize?: number, gradientSize?: number, useHarrisDetector?: boolean, harrisK?: number): Promise<Point2[]>;

/**
 * sane as imshow(winName, img); waitKey()
 */
export function imshowWait(winName: string, img: Mat): void;
export function initCameraMatrix2D(objectPoints: Point3[], imagePoints: Point2[], imageSize: Size, aspectRatio?: number): Mat;
export function initCameraMatrix2DAsync(objectPoints: Point3[], imagePoints: Point2[], imageSize: Size, aspectRatio?: number): Promise<Mat>;
export function loadOCRHMMClassifierCNN(file: string): OCRHMMClassifier;
export function loadOCRHMMClassifierCNNAsync(file: string): Promise<OCRHMMClassifier>;
export function loadOCRHMMClassifierNM(file: string): OCRHMMClassifier;
export function loadOCRHMMClassifierNMAsync(file: string): Promise<OCRHMMClassifier>;
export function matchBruteForce(descriptors1: Mat, descriptors2: Mat): DescriptorMatch[];
export function matchBruteForceAsync(descriptors1: Mat, descriptors2: Mat): Promise<DescriptorMatch[]>;
export function matchBruteForceHamming(descriptors1: Mat, descriptors2: Mat): DescriptorMatch[];
export function matchBruteForceHammingAsync(descriptors1: Mat, descriptors2: Mat): Promise<DescriptorMatch[]>;
export function matchBruteForceHammingLut(descriptors1: Mat, descriptors2: Mat): DescriptorMatch[];
export function matchBruteForceHammingLutAsync(descriptors1: Mat, descriptors2: Mat): Promise<DescriptorMatch[]>;
export function matchBruteForceL1(descriptors1: Mat, descriptors2: Mat): DescriptorMatch[];
export function matchBruteForceL1Async(descriptors1: Mat, descriptors2: Mat): Promise<DescriptorMatch[]>;
export function matchBruteForceSL2(descriptors1: Mat, descriptors2: Mat): DescriptorMatch[];
export function matchBruteForceSL2Async(descriptors1: Mat, descriptors2: Mat): Promise<DescriptorMatch[]>;
export function matchFlannBased(descriptors1: Mat, descriptors2: Mat): DescriptorMatch[];
export function matchFlannBasedAsync(descriptors1: Mat, descriptors2: Mat): Promise<DescriptorMatch[]>;
export function matchKnnBruteForce(descriptors1: Mat, descriptors2: Mat, k: number): DescriptorMatch[][];
export function matchKnnBruteForceAsync(descriptors1: Mat, descriptors2: Mat, k: number): Promise<DescriptorMatch[][]>;
export function matchKnnBruteForceHamming(descriptors1: Mat, descriptors2: Mat, k: number): DescriptorMatch[][];
export function matchKnnBruteForceHammingAsync(descriptors1: Mat, descriptors2: Mat, k: number): Promise<DescriptorMatch[][]>;
export function matchKnnBruteForceHammingLut(descriptors1: Mat, descriptors2: Mat, k: number): DescriptorMatch[][];
export function matchKnnBruteForceHammingLutAsync(descriptors1: Mat, descriptors2: Mat, k: number): Promise<DescriptorMatch[][]>;
export function matchKnnBruteForceL1(descriptors1: Mat, descriptors2: Mat, k: number): DescriptorMatch[][];
export function matchKnnBruteForceL1Async(descriptors1: Mat, descriptors2: Mat, k: number): Promise<DescriptorMatch[][]>;
export function matchKnnBruteForceSL2(descriptors1: Mat, descriptors2: Mat, k: number): DescriptorMatch[][];
export function matchKnnBruteForceSL2Async(descriptors1: Mat, descriptors2: Mat, k: number): Promise<DescriptorMatch[][]>;
export function matchKnnFlannBased(descriptors1: Mat, descriptors2: Mat, k: number): DescriptorMatch[][];
export function matchKnnFlannBasedAsync(descriptors1: Mat, descriptors2: Mat, k: number): Promise<DescriptorMatch[][]>;

export function minMaxLoc(mat: Mat, mask?: Mat): { minVal: number, maxVal: number, minLoc: Point2, maxLoc: Point2 };
export function minMaxLocAsync(mat: Mat, mask?: Mat): Promise<{ minVal: number, maxVal: number, minLoc: Point2, maxLoc: Point2 }>;

export function plot1DHist(hist: Mat, plotImg: Mat, color: Vec3, lineType?: number, thickness?: number, shift?: number): Mat;
export function getNumThreads(): number;
export function setNumThreads(nthreads: number): void;
export function getThreadNum(): number;
export function projectPoints(objectPoints: Point3[], imagePoints: Point2[], rvec: Vec3, tvec: Vec3, cameraMatrix: Mat, distCoeffs: number[], aspectRatio?: number): { imagePoints: Point2[], jacobian: Mat };
export function projectPointsAsync(objectPoints: Point3[], imagePoints: Point2[], rvec: Vec3, tvec: Vec3, cameraMatrix: Mat, distCoeffs: number[], aspectRatio?: number): Promise<{ imagePoints: Point2[], jacobian: Mat }>;

export function recoverPose(E: Mat, points1: Point2[], points2: Point2[], focal?: number, pp?: Point2, mask?: Mat): { returnValue: number, R: Mat, T: Vec3 };
export function recoverPoseAsync(E: Mat, points1: Point2[], points2: Point2[], focal?: number, pp?: Point2, mask?: Mat): Promise<{ returnValue: number, R: Mat, T: Vec3 }>;
export function sampsonDistance(pt1: Vec2, pt2: Vec2, F: Mat): number;
export function sampsonDistanceAsync(pt1: Vec2, pt2: Vec2, F: Mat): Promise<number>;
export function seamlessClone(src: Mat, dst: Mat, mask: Mat, p: Point2, flags: number): Mat;
export function seamlessCloneAsync(src: Mat, dst: Mat, mask: Mat, p: Point2, flags: number): Promise<Mat>;

export function solveP3P(objectPoints: Point3[], imagePoints: Point2[], cameraMatrix: Mat, distCoeffs: number[], flags?: number): { returnValue: boolean, rvecs: Mat[], tvecs: Mat[] };
export function solveP3PAsync(objectPoints: Point3[], imagePoints: Point2[], cameraMatrix: Mat, distCoeffs: number[], flags?: number): Promise<{ returnValue: boolean, rvecs: Mat[], tvecs: Mat[] }>;
export function solvePnP(objectPoints: Point3[], imagePoints: Point2[], cameraMatrix: Mat, distCoeffs: number[], useExtrinsicGuess?: boolean, flags?: number): { returnValue: boolean, rvec: Vec3, tvec: Vec3 };
export function solvePnP(objectPoints: Point3[], imagePoints: Point2[], cameraMatrix: Mat, distCoeffs: number[], useExtrinsicGuess?: boolean, iterationsCount?: number, reprojectionError?: number, confidence?: number, flags?: number): { returnValue: boolean, rvec: Vec3, tvec: Vec3, inliers: number[] };
export function solvePnPAsync(objectPoints: Point3[], imagePoints: Point2[], cameraMatrix: Mat, distCoeffs: number[], useExtrinsicGuess?: boolean, flags?: number): Promise<{ returnValue: boolean, rvec: Vec3, tvec: Vec3 }>;
export function solvePnPAsync(objectPoints: Point3[], imagePoints: Point2[], cameraMatrix: Mat, distCoeffs: number[], useExtrinsicGuess?: boolean, iterationsCount?: number, reprojectionError?: number, confidence?: number, flags?: number): Promise<{ returnValue: boolean, rvec: Vec3, tvec: Vec3, inliers: number[] }>;

export function isCustomMatAllocatorEnabled(): boolean;
export function dangerousEnableCustomMatAllocator(): boolean;
export function dangerousDisableCustomMatAllocator(): boolean;
export function getMemMetrics(): { TotalAlloc: number, TotalKnownByJS: number, NumAllocations: number, NumDeAllocations: number };

export type DrawParams = {
  thickness?: number;
  lineType?: number;
  color?: Vec3;
}

export interface DrawDetectionParams extends DrawParams {
  segmentFraction?: number;
}

export interface FontParams extends DrawParams {
  fontType?: number;
  fontSize?: number;
}

export interface TextLine extends FontParams {
  text: string;
}



// non Natif
export function drawDetection(img: Mat, inputRect: Rect, opts?: DrawDetectionParams): Rect;
// non Natif
export function drawTextBox(img: Mat, upperLeft: { x: number, y: number }, textLines: TextLine[], alpha: number): Mat;
/**
 * Convert a Mat type to string for easy read
 * non Natif code
 * @param type Mat type as int value
 */
export function toMatTypeName(type: number): string | undefined;
/**
 * Find values greater than threshold in a 32bit float matrix and return a list of matchs formated as [[x1, y1, score1]. [x2, y2, score2], [x3, y3, score3]]
 * add to be used with matchTemplate
 * non Natif code
 * @param scoreMat Matric containing scores as 32Bit float (CV_32F)
 * @param threshold Minimal score to collect
 * @param region search region
 * @returns a list of matchs
 */
export function getScoreMax(scoreMat: Mat, threshold: number, region?: Rect): Array<[number, number, number]>;

/**
 * Drop overlaping zones, keeping best one
 * add to be used with matchTemplate
 * non Natif code
 * @param template template Matrix used to get dimentions.
 * @param matches list of matches as a list in [x,y,score]. (this data will be altered)
 * @returns best match without colisions
 */
export function dropOverlappingZone(template: Mat, matches: Array<[number, number, number]>): Array<[number, number, number]>;
