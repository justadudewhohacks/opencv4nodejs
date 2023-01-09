import { Mat } from '../Mat.d';
import { Size } from '../Size.d';
import { Point3 } from '../Point3.d';
import { Point2 } from '../Point2.d';
import { Vec3 } from '../Vec3.d';
import { TermCriteria } from '../TermCriteria.d';


// https://docs.opencv.org/4.x/d9/d0c/group__calib3d.html#ga396afb6411b30770e56ab69548724715

//double 	cv::calibrateCamera (InputArrayOfArrays objectPoints, InputArrayOfArrays imagePoints, Size imageSize, InputOutputArray cameraMatrix, InputOutputArray distCoeffs, OutputArrayOfArrays rvecs, OutputArrayOfArrays tvecs, OutputArray stdDeviationsIntrinsics, OutputArray stdDeviationsExtrinsics, OutputArray perViewErrors, int flags=0, TermCriteria criteria=TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, 30, DBL_EPSILON))
// 	Finds the camera intrinsic and extrinsic parameters from several views of a calibration pattern. More...
// 
//double 	cv::calibrateCamera (InputArrayOfArrays objectPoints, InputArrayOfArrays imagePoints, Size imageSize, InputOutputArray cameraMatrix, InputOutputArray distCoeffs, OutputArrayOfArrays rvecs, OutputArrayOfArrays tvecs, int flags=0, TermCriteria criteria=TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, 30, DBL_EPSILON))

export interface CalibrateCameraRet {
    returnValue: number;
    rvecs: Vec3[];
    tvecs: Vec3[];
    distCoeffs: number[];
}

export function calibrateCamera(objectPoints: Point3[], imagePoints: Point2[], imageSize: Size, cameraMatrix: Mat, distCoeffs: number[], flags?: number, criteria?: TermCriteria): CalibrateCameraRet;
export function calibrateCameraAsync(objectPoints: Point3[], imagePoints: Point2[], imageSize: Size, cameraMatrix: Mat, distCoeffs: number[], flags?: number, criteria?: TermCriteria): Promise<CalibrateCameraRet>;

export function calibrateCameraExtended(objectPoints: Point3[], imagePoints: Point2[], imageSize: Size, cameraMatrix: Mat, distCoeffs: number[], flags?: number, criteria?: TermCriteria): { returnValue: number, rvecs: Vec3[], tvecs: Vec3[], distCoeffs: number[], stdDeviationsIntrinsics: Mat, stdDeviationsExtrinsics: Mat, perViewErrors: number[] };
export function calibrateCameraExtendedAsync(objectPoints: Point3[], imagePoints: Point2[], imageSize: Size, cameraMatrix: Mat, distCoeffs: number[], flags?: number, criteria?: TermCriteria): Promise<{ returnValue: number, rvecs: Vec3[], tvecs: Vec3[], distCoeffs: number[], stdDeviationsIntrinsics: Mat, stdDeviationsExtrinsics: Mat, perViewErrors: number[] }>;


//double 	cv::calibrateCameraRO (InputArrayOfArrays objectPoints, InputArrayOfArrays imagePoints, Size imageSize, int iFixedPoint, InputOutputArray cameraMatrix, InputOutputArray distCoeffs, OutputArrayOfArrays rvecs, OutputArrayOfArrays tvecs, OutputArray newObjPoints, OutputArray stdDeviationsIntrinsics, OutputArray stdDeviationsExtrinsics, OutputArray stdDeviationsObjPoints, OutputArray perViewErrors, int flags=0, TermCriteria criteria=TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, 30, DBL_EPSILON))
// 	Finds the camera intrinsic and extrinsic parameters from several views of a calibration pattern. More...
// 
//double 	cv::calibrateCameraRO (InputArrayOfArrays objectPoints, InputArrayOfArrays imagePoints, Size imageSize, int iFixedPoint, InputOutputArray cameraMatrix, InputOutputArray distCoeffs, OutputArrayOfArrays rvecs, OutputArrayOfArrays tvecs, OutputArray newObjPoints, int flags=0, TermCriteria criteria=TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, 30, DBL_EPSILON))
// 
//void 	cv::calibrateHandEye (InputArrayOfArrays R_gripper2base, InputArrayOfArrays t_gripper2base, InputArrayOfArrays R_target2cam, InputArrayOfArrays t_target2cam, OutputArray R_cam2gripper, OutputArray t_cam2gripper, HandEyeCalibrationMethod method=CALIB_HAND_EYE_TSAI)
// 	Computes Hand-Eye calibration: gTc. More...
// 
//void 	cv::calibrateRobotWorldHandEye (InputArrayOfArrays R_world2cam, InputArrayOfArrays t_world2cam, InputArrayOfArrays R_base2gripper, InputArrayOfArrays t_base2gripper, OutputArray R_base2world, OutputArray t_base2world, OutputArray R_gripper2cam, OutputArray t_gripper2cam, RobotWorldHandEyeCalibrationMethod method=CALIB_ROBOT_WORLD_HAND_EYE_SHAH)
// 	Computes Robot-World/Hand-Eye calibration: wTb and cTg. More...
// 
//void 	cv::calibrationMatrixValues (InputArray cameraMatrix, Size imageSize, double apertureWidth, double apertureHeight, double &fovx, double &fovy, double &focalLength, Point2d &principalPoint, double &aspectRatio)
// 	Computes useful camera characteristics from the camera intrinsic matrix. More...
// 
//bool 	cv::checkChessboard (InputArray img, Size size)
// 

export interface ComposeRTRet {
    rvec3: Vec3;
    tvec3: Vec3;
    dr3dr1: Mat;
    dr3dt1: Mat;
    dr3dr2: Mat;
    dr3dt2: Mat;
    dt3dr1: Mat;
    dt3dt1: Mat;
    dt3dr2: Mat;
    dt3dt2: Mat;
}

export function composeRT(rvec1: Vec3, tvec1: Vec3, rvec2: Vec3, tvec2: Vec3): ComposeRTRet;
export function composeRTAsync(rvec1: Vec3, tvec1: Vec3, rvec2: Vec3, tvec2: Vec3): Promise<ComposeRTRet>;

//void 	cv::composeRT (InputArray rvec1, InputArray tvec1, InputArray rvec2, InputArray tvec2, OutputArray rvec3, OutputArray tvec3, OutputArray dr3dr1=noArray(), OutputArray dr3dt1=noArray(), OutputArray dr3dr2=noArray(), OutputArray dr3dt2=noArray(), OutputArray dt3dr1=noArray(), OutputArray dt3dt1=noArray(), OutputArray dt3dr2=noArray(), OutputArray dt3dt2=noArray())
// 	Combines two rotation-and-shift transformations. More...
// 
//void 	cv::computeCorrespondEpilines (InputArray points, int whichImage, InputArray F, OutputArray lines)
// 	For points in an image of a stereo pair, computes the corresponding epilines in the other image. More...
// 
//void 	cv::convertPointsFromHomogeneous (InputArray src, OutputArray dst)
// 	Converts points from homogeneous to Euclidean space. More...
// 
//void 	cv::convertPointsHomogeneous (InputArray src, OutputArray dst)
// 	Converts points to/from homogeneous coordinates. More...
// 
//void 	cv::convertPointsToHomogeneous (InputArray src, OutputArray dst)
// 	Converts points from Euclidean to homogeneous space. More...
// 
//void 	cv::correctMatches (InputArray F, InputArray points1, InputArray points2, OutputArray newPoints1, OutputArray newPoints2)
// 	Refines coordinates of corresponding points. More...
// 
//void 	cv::decomposeEssentialMat (InputArray E, OutputArray R1, OutputArray R2, OutputArray t)
// 	Decompose an essential matrix to possible rotations and translation. More...
// 
//int 	cv::decomposeHomographyMat (InputArray H, InputArray K, OutputArrayOfArrays rotations, OutputArrayOfArrays translations, OutputArrayOfArrays normals)
// 	Decompose a homography matrix to rotation(s), translation(s) and plane normal(s). More...
// 
//void 	cv::decomposeProjectionMatrix (InputArray projMatrix, OutputArray cameraMatrix, OutputArray rotMatrix, OutputArray transVect, OutputArray rotMatrixX=noArray(), OutputArray rotMatrixY=noArray(), OutputArray rotMatrixZ=noArray(), OutputArray eulerAngles=noArray())
// 	Decomposes a projection matrix into a rotation matrix and a camera intrinsic matrix. More...
// 
//void 	cv::drawChessboardCorners (InputOutputArray image, Size patternSize, InputArray corners, bool patternWasFound)
// 	Renders the detected chessboard corners. More...
// 
//void 	cv::drawFrameAxes (InputOutputArray image, InputArray cameraMatrix, InputArray distCoeffs, InputArray rvec, InputArray tvec, float length, int thickness=3)
// 	Draw axes of the world/object coordinate system from pose estimation. More...
// 
//cv::Mat 	cv::estimateAffine2D (InputArray from, InputArray to, OutputArray inliers=noArray(), int method=RANSAC, double ransacReprojThreshold=3, size_t maxIters=2000, double confidence=0.99, size_t refineIters=10)
// 	Computes an optimal affine transformation between two 2D point sets. More...
// 

export interface EstimateAffine2DRet {
    out: Mat;
    inliers: Mat;
}

//cv::Mat 	cv::estimateAffine2D (InputArray pts1, InputArray pts2, OutputArray inliers, const UsacParams &params)
export function estimateAffine2D(from: Point2[], to: Point2[], method?: number, ransacReprojThreshold?: number, maxIters?: number, confidence?: number, refineIters?: number): EstimateAffine2DRet;
export function estimateAffine2DAsync(from: Point2[], to: Point2[], method?: number, ransacReprojThreshold?: number, maxIters?: number, confidence?: number, refineIters?: number): Promise<EstimateAffine2DRet>;

//int 	cv::estimateAffine3D (InputArray src, InputArray dst, OutputArray out, OutputArray inliers, double ransacThreshold=3, double confidence=0.99)
// 	Computes an optimal affine transformation between two 3D point sets. More...
// 
//cv::Mat 	cv::estimateAffine3D (InputArray src, InputArray dst, double *scale=nullptr, bool force_rotation=true)
// 	Computes an optimal affine transformation between two 3D point sets. More...

export interface EstimateAffine3DRet {
    returnValue: number; // optional ?
    out: Mat;
    inliers: Mat;
}

export function estimateAffine3D(src: Point3[], dst: Point3[], ransacThreshold?: number, confidence?: number): EstimateAffine3DRet;
export function estimateAffine3D(from: Point2[], to: Point2[], method?: number, ransacReprojThreshold?: number, maxIters?: number, confidence?: number, refineIters?: number): EstimateAffine3DRet;
export function estimateAffine3DAsync(src: Point3[], dst: Point3[], ransacThreshold?: number, confidence?: number): Promise<EstimateAffine3DRet>;
export function estimateAffine3DAsync(from: Point2[], to: Point2[], method?: number, ransacReprojThreshold?: number, maxIters?: number, confidence?: number, refineIters?: number): Promise<EstimateAffine3DRet>;

//cv::Mat 	cv::estimateAffinePartial2D (InputArray from, InputArray to, OutputArray inliers=noArray(), int method=RANSAC, double ransacReprojThreshold=3, size_t maxIters=2000, double confidence=0.99, size_t refineIters=10)
// 	Computes an optimal limited affine transformation with 4 degrees of freedom between two 2D point sets. More...
export function estimateAffinePartial2D(from: Point2[], to: Point2[], method?: number, ransacReprojThreshold?: number, maxIters?: number, confidence?: number, refineIters?: number):EstimateAffine2DRet;
export function estimateAffinePartial2DAsync(from: Point2[], to: Point2[], method?: number, ransacReprojThreshold?: number, maxIters?: number, confidence?: number, refineIters?: number): Promise<EstimateAffine2DRet>;


//Scalar 	cv::estimateChessboardSharpness (InputArray image, Size patternSize, InputArray corners, float rise_distance=0.8F, bool vertical=false, OutputArray sharpness=noArray())
// 	Estimates the sharpness of a detected chessboard. More...
// 
//int 	cv::estimateTranslation3D (InputArray src, InputArray dst, OutputArray out, OutputArray inliers, double ransacThreshold=3, double confidence=0.99)
// 	Computes an optimal translation between two 3D point sets. More...
// 
//void 	cv::filterHomographyDecompByVisibleRefpoints (InputArrayOfArrays rotations, InputArrayOfArrays normals, InputArray beforePoints, InputArray afterPoints, OutputArray possibleSolutions, InputArray pointsMask=noArray())
// 	Filters homography decompositions based on additional information. More...
// 
//void 	cv::filterSpeckles (InputOutputArray img, double newVal, int maxSpeckleSize, double maxDiff, InputOutputArray buf=noArray())
// 	Filters off small noise blobs (speckles) in the disparity map. More...
// 
//bool 	cv::find4QuadCornerSubpix (InputArray img, InputOutputArray corners, Size region_size)
// 	finds subpixel-accurate positions of the chessboard corners More...
// 
//bool 	cv::findChessboardCorners (InputArray image, Size patternSize, OutputArray corners, int flags=CALIB_CB_ADAPTIVE_THRESH+CALIB_CB_NORMALIZE_IMAGE)
// 	Finds the positions of internal corners of the chessboard. More...
// 
//bool 	cv::findChessboardCornersSB (InputArray image, Size patternSize, OutputArray corners, int flags, OutputArray meta)
// 	Finds the positions of internal corners of the chessboard using a sector based approach. More...
// 
//bool 	cv::findChessboardCornersSB (InputArray image, Size patternSize, OutputArray corners, int flags=0)
// 
//bool 	cv::findCirclesGrid (InputArray image, Size patternSize, OutputArray centers, int flags, const Ptr< FeatureDetector > &blobDetector, const CirclesGridFinderParameters &parameters)
// 	Finds centers in the grid of circles. More...
// 
//bool 	cv::findCirclesGrid (InputArray image, Size patternSize, OutputArray centers, int flags=CALIB_CB_SYMMETRIC_GRID, const Ptr< FeatureDetector > &blobDetector=SimpleBlobDetector::create())
// 
//Mat 	cv::findEssentialMat (InputArray points1, InputArray points2, InputArray cameraMatrix, int method=RANSAC, double prob=0.999, double threshold=1.0, int maxIters=1000, OutputArray mask=noArray())
// 	Calculates an essential matrix from the corresponding points in two images. More...
// 
//Mat 	cv::findEssentialMat (InputArray points1, InputArray points2, InputArray cameraMatrix, int method, double prob, double threshold, OutputArray mask)
// 
//Mat 	cv::findEssentialMat (InputArray points1, InputArray points2, double focal=1.0, Point2d pp=Point2d(0, 0), int method=RANSAC, double prob=0.999, double threshold=1.0, int maxIters=1000, OutputArray mask=noArray())
// 
//Mat 	cv::findEssentialMat (InputArray points1, InputArray points2, double focal, Point2d pp, int method, double prob, double threshold, OutputArray mask)
// 
//Mat 	cv::findEssentialMat (InputArray points1, InputArray points2, InputArray cameraMatrix1, InputArray distCoeffs1, InputArray cameraMatrix2, InputArray distCoeffs2, int method=RANSAC, double prob=0.999, double threshold=1.0, OutputArray mask=noArray())
// 	Calculates an essential matrix from the corresponding points in two images from potentially two different cameras. More...
// 
//Mat 	cv::findEssentialMat (InputArray points1, InputArray points2, InputArray cameraMatrix1, InputArray cameraMatrix2, InputArray dist_coeff1, InputArray dist_coeff2, OutputArray mask, const UsacParams &params)
// 
//Mat 	cv::findFundamentalMat (InputArray points1, InputArray points2, int method, double ransacReprojThreshold, double confidence, int maxIters, OutputArray mask=noArray())
// 	Calculates a fundamental matrix from the corresponding points in two images. More...
// 
//Mat 	cv::findFundamentalMat (InputArray points1, InputArray points2, int method=FM_RANSAC, double ransacReprojThreshold=3., double confidence=0.99, OutputArray mask=noArray())
// 
//Mat 	cv::findFundamentalMat (InputArray points1, InputArray points2, OutputArray mask, int method=FM_RANSAC, double ransacReprojThreshold=3., double confidence=0.99)
// 
//Mat 	cv::findFundamentalMat (InputArray points1, InputArray points2, OutputArray mask, const UsacParams &params)
// 
//Mat 	cv::findHomography (InputArray srcPoints, InputArray dstPoints, int method=0, double ransacReprojThreshold=3, OutputArray mask=noArray(), const int maxIters=2000, const double confidence=0.995)

export interface FindHomographyRet {
    homography: Mat;
    mask: Mat;
}

export function findHomography(srcPoints: Point2[], dstPoints: Point2[], method?: number, ransacReprojThreshold?: number, maxIters?: number, confidence?: number): FindHomographyRet;

// 	Finds a perspective transformation between two planes. More...
// 
//Mat 	cv::findHomography (InputArray srcPoints, InputArray dstPoints, OutputArray mask, int method=0, double ransacReprojThreshold=3)
// 
//Mat 	cv::findHomography (InputArray srcPoints, InputArray dstPoints, OutputArray mask, const UsacParams &params)
// 
//Mat 	cv::getDefaultNewCameraMatrix (InputArray cameraMatrix, Size imgsize=Size(), bool centerPrincipalPoint=false)
// 	Returns the default new camera matrix. More...
// 
//Mat 	cv::getOptimalNewCameraMatrix (InputArray cameraMatrix, InputArray distCoeffs, Size imageSize, double alpha, Size newImgSize=Size(), Rect *validPixROI=0, bool centerPrincipalPoint=false)
// 	Returns the new camera intrinsic matrix based on the free scaling parameter. More...
// 
//Rect 	cv::getValidDisparityROI (Rect roi1, Rect roi2, int minDisparity, int numberOfDisparities, int blockSize)
// 	computes valid disparity ROI from the valid ROIs of the rectified images (that are returned by stereoRectify) More...
// 
//Mat 	cv::initCameraMatrix2D (InputArrayOfArrays objectPoints, InputArrayOfArrays imagePoints, Size imageSize, double aspectRatio=1.0)
// 	Finds an initial camera intrinsic matrix from 3D-2D point correspondences. More...
// 
//void 	cv::initInverseRectificationMap (InputArray cameraMatrix, InputArray distCoeffs, InputArray R, InputArray newCameraMatrix, const Size &size, int m1type, OutputArray map1, OutputArray map2)
// 	Computes the projection and inverse-rectification transformation map. In essense, this is the inverse of initUndistortRectifyMap to accomodate stereo-rectification of projectors ('inverse-cameras') in projector-camera pairs. More...
// 
//void 	cv::initUndistortRectifyMap (InputArray cameraMatrix, InputArray distCoeffs, InputArray R, InputArray newCameraMatrix, Size size, int m1type, OutputArray map1, OutputArray map2)
// 	Computes the undistortion and rectification transformation map. More...
// 
//float 	cv::initWideAngleProjMap (InputArray cameraMatrix, InputArray distCoeffs, Size imageSize, int destImageWidth, int m1type, OutputArray map1, OutputArray map2, enum UndistortTypes projType=PROJ_SPHERICAL_EQRECT, double alpha=0)
// 	initializes maps for remap for wide-angle More...
// 
//static float 	cv::initWideAngleProjMap (InputArray cameraMatrix, InputArray distCoeffs, Size imageSize, int destImageWidth, int m1type, OutputArray map1, OutputArray map2, int projType, double alpha=0)
// 
//void 	cv::matMulDeriv (InputArray A, InputArray B, OutputArray dABdA, OutputArray dABdB)
// 	Computes partial derivatives of the matrix product for each multiplied matrix. More...
// 
//void 	cv::projectPoints (InputArray objectPoints, InputArray rvec, InputArray tvec, InputArray cameraMatrix, InputArray distCoeffs, OutputArray imagePoints, OutputArray jacobian=noArray(), double aspectRatio=0)
// 	Projects 3D points to an image plane. More...
// 
//int 	cv::recoverPose (InputArray points1, InputArray points2, InputArray cameraMatrix1, InputArray distCoeffs1, InputArray cameraMatrix2, InputArray distCoeffs2, OutputArray E, OutputArray R, OutputArray t, int method=cv::RANSAC, double prob=0.999, double threshold=1.0, InputOutputArray mask=noArray())
// 	Recovers the relative camera rotation and the translation from corresponding points in two images from two different cameras, using cheirality check. Returns the number of inliers that pass the check. More...
// 
//int 	cv::recoverPose (InputArray E, InputArray points1, InputArray points2, InputArray cameraMatrix, OutputArray R, OutputArray t, InputOutputArray mask=noArray())
// 	Recovers the relative camera rotation and the translation from an estimated essential matrix and the corresponding points in two images, using cheirality check. Returns the number of inliers that pass the check. More...
// 
//int 	cv::recoverPose (InputArray E, InputArray points1, InputArray points2, OutputArray R, OutputArray t, double focal=1.0, Point2d pp=Point2d(0, 0), InputOutputArray mask=noArray())
// 
//int 	cv::recoverPose (InputArray E, InputArray points1, InputArray points2, InputArray cameraMatrix, OutputArray R, OutputArray t, double distanceThresh, InputOutputArray mask=noArray(), OutputArray triangulatedPoints=noArray())
// 
//float 	cv::rectify3Collinear (InputArray cameraMatrix1, InputArray distCoeffs1, InputArray cameraMatrix2, InputArray distCoeffs2, InputArray cameraMatrix3, InputArray distCoeffs3, InputArrayOfArrays imgpt1, InputArrayOfArrays imgpt3, Size imageSize, InputArray R12, InputArray T12, InputArray R13, InputArray T13, OutputArray R1, OutputArray R2, OutputArray R3, OutputArray P1, OutputArray P2, OutputArray P3, OutputArray Q, double alpha, Size newImgSize, Rect *roi1, Rect *roi2, int flags)
// 	computes the rectification transformations for 3-head camera, where all the heads are on the same line. More...
// 
//void 	cv::reprojectImageTo3D (InputArray disparity, OutputArray _3dImage, InputArray Q, bool handleMissingValues=false, int ddepth=-1)
// 	Reprojects a disparity image to 3D space. More...
// 
//void 	cv::Rodrigues (InputArray src, OutputArray dst, OutputArray jacobian=noArray())
// 	Converts a rotation matrix to a rotation vector or vice versa. More...
// 
//Vec3d 	cv::RQDecomp3x3 (InputArray src, OutputArray mtxR, OutputArray mtxQ, OutputArray Qx=noArray(), OutputArray Qy=noArray(), OutputArray Qz=noArray())
// 	Computes an RQ decomposition of 3x3 matrices. More...
// 
//double 	cv::sampsonDistance (InputArray pt1, InputArray pt2, InputArray F)
// 	Calculates the Sampson Distance between two points. More...
// 


export interface SolveP3PRet {
    returnValue: boolean;
    rvecs: Mat[];
    tvecs: Mat[];
}

//int 	cv::solveP3P (InputArray objectPoints, InputArray imagePoints, InputArray cameraMatrix, InputArray distCoeffs, OutputArrayOfArrays rvecs, OutputArrayOfArrays tvecs, int flags)
// 	Finds an object pose from 3 3D-2D point correspondences. More...
export function solveP3P(objectPoints: Point3[], imagePoints: Point2[], cameraMatrix: Mat, distCoeffs: number[], flags?: number): SolveP3PRet;
export function solveP3PAsync(objectPoints: Point3[], imagePoints: Point2[], cameraMatrix: Mat, distCoeffs: number[], flags?: number): Promise<SolveP3PRet>;


export interface SolvePnPRet {
    returnValue: boolean;
    rvec: Vec3;
    tvec: Vec3;
}

//bool 	cv::solvePnP (InputArray objectPoints, InputArray imagePoints, InputArray cameraMatrix, InputArray distCoeffs, OutputArray rvec, OutputArray tvec, bool useExtrinsicGuess=false, int flags=SOLVEPNP_ITERATIVE)
// 	Finds an object pose from 3D-2D point correspondences. More...
export function solvePnP(objectPoints: Point3[], imagePoints: Point2[], cameraMatrix: Mat, distCoeffs: number[], useExtrinsicGuess?: boolean, flags?: number): SolvePnPRet;
export function solvePnP(objectPoints: Point3[], imagePoints: Point2[], cameraMatrix: Mat, distCoeffs: number[], useExtrinsicGuess?: boolean, iterationsCount?: number, reprojectionError?: number, confidence?: number, flags?: number): SolvePnPRet;

export function solvePnPAsync(objectPoints: Point3[], imagePoints: Point2[], cameraMatrix: Mat, distCoeffs: number[], useExtrinsicGuess?: boolean, flags?: number): Promise<SolvePnPRet>;
export function solvePnPAsync(objectPoints: Point3[], imagePoints: Point2[], cameraMatrix: Mat, distCoeffs: number[], useExtrinsicGuess?: boolean, iterationsCount?: number, reprojectionError?: number, confidence?: number, flags?: number): Promise<SolvePnPRet>;

//int 	cv::solvePnPGeneric (InputArray objectPoints, InputArray imagePoints, InputArray cameraMatrix, InputArray distCoeffs, OutputArrayOfArrays rvecs, OutputArrayOfArrays tvecs, bool useExtrinsicGuess=false, SolvePnPMethod flags=SOLVEPNP_ITERATIVE, InputArray rvec=noArray(), InputArray tvec=noArray(), OutputArray reprojectionError=noArray())
// 	Finds an object pose from 3D-2D point correspondences. More...
// 
//bool 	cv::solvePnPRansac (InputArray objectPoints, InputArray imagePoints, InputArray cameraMatrix, InputArray distCoeffs, OutputArray rvec, OutputArray tvec, bool useExtrinsicGuess=false, int iterationsCount=100, float reprojectionError=8.0, double confidence=0.99, OutputArray inliers=noArray(), int flags=SOLVEPNP_ITERATIVE)
// 	Finds an object pose from 3D-2D point correspondences using the RANSAC scheme. More...
// 
//bool 	cv::solvePnPRansac (InputArray objectPoints, InputArray imagePoints, InputOutputArray cameraMatrix, InputArray distCoeffs, OutputArray rvec, OutputArray tvec, OutputArray inliers, const UsacParams &params=UsacParams())
// 

export interface SolvePnPRansacRet extends SolvePnPRet {
    inliers: number[];
}

export function solvePnPRansac(objectPoints: Point3[], imagePoints: Point2[], cameraMatrix: Mat, distCoeffs: number[], args: {
    rvec: Vec3,
    tvec: Vec3,
    useExtrinsicGuess: boolean,
    iterationsCount: number,
    reprojectionError: number,
    confidence: number,
    flags: number,
}): SolvePnPRansacRet;



//void 	cv::solvePnPRefineLM (InputArray objectPoints, InputArray imagePoints, InputArray cameraMatrix, InputArray distCoeffs, InputOutputArray rvec, InputOutputArray tvec, TermCriteria criteria=TermCriteria(TermCriteria::EPS+TermCriteria::COUNT, 20, FLT_EPSILON))
// 	Refine a pose (the translation and the rotation that transform a 3D point expressed in the object coordinate frame to the camera coordinate frame) from a 3D-2D point correspondences and starting from an initial solution. More...
// 
//void 	cv::solvePnPRefineVVS (InputArray objectPoints, InputArray imagePoints, InputArray cameraMatrix, InputArray distCoeffs, InputOutputArray rvec, InputOutputArray tvec, TermCriteria criteria=TermCriteria(TermCriteria::EPS+TermCriteria::COUNT, 20, FLT_EPSILON), double VVSlambda=1)
// 	Refine a pose (the translation and the rotation that transform a 3D point expressed in the object coordinate frame to the camera coordinate frame) from a 3D-2D point correspondences and starting from an initial solution. More...
// 
//double 	cv::stereoCalibrate (InputArrayOfArrays objectPoints, InputArrayOfArrays imagePoints1, InputArrayOfArrays imagePoints2, InputOutputArray cameraMatrix1, InputOutputArray distCoeffs1, InputOutputArray cameraMatrix2, InputOutputArray distCoeffs2, Size imageSize, InputOutputArray R, InputOutputArray T, OutputArray E, OutputArray F, OutputArray perViewErrors, int flags=CALIB_FIX_INTRINSIC, TermCriteria criteria=TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, 30, 1e-6))
// 	Calibrates a stereo camera set up. This function finds the intrinsic parameters for each of the two cameras and the extrinsic parameters between the two cameras. More...
//double 	cv::stereoCalibrate (InputArrayOfArrays objectPoints, InputArrayOfArrays imagePoints1, InputArrayOfArrays imagePoints2, InputOutputArray cameraMatrix1, InputOutputArray distCoeffs1, InputOutputArray cameraMatrix2, InputOutputArray distCoeffs2, Size imageSize, OutputArray R, OutputArray T, OutputArray E, OutputArray F, int flags=CALIB_FIX_INTRINSIC, TermCriteria criteria=TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, 30, 1e-6))
// 


export interface stereoCalibrateRet {
    returnValue: number;
    R: Mat;
    T: Vec3;// [];
    E: Mat;
    F: Mat;
    distCoeffs1: number[];
    distCoeffs2: number[];
}

export function stereoCalibrate(objectPoints: Point3[], imagePoints1: Point2[], imagePoints2: Point2[], cameraMatrix1: Mat, distCoeffs1: number[], cameraMatrix2: Mat, distCoeffs2: number[], imageSize: Size, flags?: number, criteria?: TermCriteria): stereoCalibrateRet;
export function stereoCalibrateAsync(objectPoints: Point3[], imagePoints1: Point2[], imagePoints2: Point2[], cameraMatrix1: Mat, distCoeffs1: number[], cameraMatrix2: Mat, distCoeffs2: number[], imageSize: Size, flags?: number, criteria?: TermCriteria): Promise<stereoCalibrateRet>;


//void 	cv::stereoRectify (InputArray cameraMatrix1, InputArray distCoeffs1, InputArray cameraMatrix2, InputArray distCoeffs2, Size imageSize, InputArray R, InputArray T, OutputArray R1, OutputArray R2, OutputArray P1, OutputArray P2, OutputArray Q, int flags=CALIB_ZERO_DISPARITY, double alpha=-1, Size newImageSize=Size(), Rect *validPixROI1=0, Rect *validPixROI2=0)
// 	Computes rectification transforms for each head of a calibrated stereo camera. More...
// 
//bool 	cv::stereoRectifyUncalibrated (InputArray points1, InputArray points2, InputArray F, Size imgSize, OutputArray H1, OutputArray H2, double threshold=5)
// 	Computes a rectification transform for an uncalibrated stereo camera. More...

export interface StereoRectifyUncalibratedRet  {
    returnValue: boolean;
    H1: Mat;
    H2: Mat;
}
export function stereoRectifyUncalibrated(points1: Point2[], points2: Point2[], F: Mat, imageSize: Size, threshold?: number): StereoRectifyUncalibratedRet;
export function stereoRectifyUncalibratedAsync(points1: Point2[], points2: Point2[], F: Mat, imageSize: Size, threshold?: number): Promise<StereoRectifyUncalibratedRet>;



//void 	cv::triangulatePoints (InputArray projMatr1, InputArray projMatr2, InputArray projPoints1, InputArray projPoints2, OutputArray points4D)
// 	This function reconstructs 3-dimensional points (in homogeneous coordinates) by using their observations with a stereo camera. More...
// 
//void 	cv::undistort (InputArray src, OutputArray dst, InputArray cameraMatrix, InputArray distCoeffs, InputArray newCameraMatrix=noArray())
// 	Transforms an image to compensate for lens distortion. More...
// 
//void 	cv::undistortPoints (InputArray src, OutputArray dst, InputArray cameraMatrix, InputArray distCoeffs, InputArray R=noArray(), InputArray P=noArray())
// 	Computes the ideal point coordinates from the observed point coordinates. More...
// 
//void 	cv::undistortPoints (InputArray src, OutputArray dst, InputArray cameraMatrix, InputArray distCoeffs, InputArray R, InputArray P, TermCriteria criteria)

export function undistortPoints(srcPoints: Point2[], cameraMatrix: Mat, distCoeffs: Mat): Point2[];
export function undistortPointsAsync(srcPoints: Point2[], cameraMatrix: Mat, distCoeffs: Mat): Promise<Point2[]>;


//void 	cv::validateDisparity (InputOutputArray disparity, InputArray cost, int minDisparity, int numberOfDisparities, int disp12MaxDisp=1)
// 	validates disparity using the left-right check. The matrix "cost" should be computed by the stereo correspondence algorithm More...
    