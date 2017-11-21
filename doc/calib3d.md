# calib3d

<a name="findHomography"></a>

### findHomography
``` javascript
Mat : findHomography([Point2] srcPoints, [Point2] dstPoints, Uint method = 0, Number ransacReprojThreshold = 3, Mat mask = noArray(), Uint maxIters = 2000, Number confidence = 0.995)
```

<a name="composeRT"></a>

### composeRT
``` javascript
{ rvec3: Vec3, tvec3: Vec3, dr3dr1: Mat, dr3dt1: Mat, dr3dr2: Mat, dr3dt2: Mat, dt3dr1: Mat, dt3dt1: Mat, dt3dr2: Mat, dt3dt2: Mat } : composeRT(Vec3 rvec1. Vec3 tvec1, Vec3 rvec2, Vec3 tvec2)
```

<a name="composeRTAsync"></a>

### composeRTAsync
``` javascript
composeRTAsync(Vec3 rvec1. Vec3 tvec1, Vec3 rvec2, Vec3 tvec2, callback(Error err, { rvec3: Vec3, tvec3: Vec3, dr3dr1: Mat, dr3dt1: Mat, dr3dr2: Mat, dr3dt2: Mat, dt3dr1: Mat, dt3dt1: Mat, dt3dr2: Mat, dt3dt2: Mat } result))
```

<a name="solvePnP"></a>

### solvePnP
``` javascript
{ returnValue: Boolean, rvec: Vec3, tvec: Vec3 } : solvePnP([Point3] objectPoints, [Point2] imagePoints, Mat cameraMatrix, [Number] distCoeffs, Boolean useExtrinsicGuess = false, Int flags = cv.SOLVEPNP_ITERATIVE)
```

<a name="solvePnPAsync"></a>

### solvePnPAsync
``` javascript
solvePnPAsync([Point3] objectPoints, [Point2] imagePoints, Mat cameraMatrix, [Number] distCoeffs, callback(Error err, { returnValue: Boolean, rvec: Vec3, tvec: Vec3 } result))
solvePnPAsync([Point3] objectPoints, [Point2] imagePoints, Mat cameraMatrix, [Number] distCoeffs, ...opts, callback(Error err, { returnValue: Boolean, rvec: Vec3, tvec: Vec3 } result))
solvePnPAsync([Point3] objectPoints, [Point2] imagePoints, Mat cameraMatrix, [Number] distCoeffs, { opts }, callback(Error err, { returnValue: Boolean, rvec: Vec3, tvec: Vec3 } result))
```

<a name="solvePnPRansac"></a>

### solvePnPRansac
``` javascript
{ returnValue: Boolean, rvec: Vec3, tvec: Vec3, inliers: [Int] } : solvePnP([Point3] objectPoints, [Point2] imagePoints, Mat cameraMatrix, [Number] distCoeffs, Boolean useExtrinsicGuess = false, Int iterationsCount = 100, Number reprojectionError = 8.0, Number confidence = 0.99, Int flags = cv.SOLVEPNP_ITERATIVE)
```

<a name="solvePnPRansacAsync"></a>

### solvePnPRansacAsync
``` javascript
solvePnPRansacAsync([Point3] objectPoints, [Point2] imagePoints, Mat cameraMatrix, [Number] distCoeffs, callback(Error err, { returnValue: Boolean, rvec: Vec3, tvec: Vec3, inliers: [Int] } result))
solvePnPRansacAsync([Point3] objectPoints, [Point2] imagePoints, Mat cameraMatrix, [Number] distCoeffs, ...opts, callback(Error err, { returnValue: Boolean, rvec: Vec3, tvec: Vec3, inliers: [Int] } result))
solvePnPRansacAsync([Point3] objectPoints, [Point2] imagePoints, Mat cameraMatrix, [Number] distCoeffs, { opts }, callback(Error err, { returnValue: Boolean, rvec: Vec3, tvec: Vec3, inliers: [Int] } result))
```

<a name="projectPoints"></a>

### projectPoints
``` javascript
{ imagePoints: [Point2], jacobian: Mat } : projectPoints([Point3] objectPoints, [Point2] imagePoints, Vec3 rvec, Vec3 tvec, Mat cameraMatrix, [Number] distCoeffs, Number aspectRatio = 0)
```

<a name="projectPointsAsync"></a>

### projectPointsAsync
``` javascript
projectPointsAsync([Point3] objectPoints, [Point2] imagePoints, Vec3 rvec, Vec3 tvec, Mat cameraMatrix, [Number] distCoeffs, callback(Error err, { imagePoints: [Point2], jacobian: Mat }  result))
projectPointsAsync([Point3] objectPoints, [Point2] imagePoints, Vec3 rvec, Vec3 tvec, Mat cameraMatrix, [Number] distCoeffs, Number aspectRatio, callback(Error err, { imagePoints: [Point2], jacobian: Mat }  result))
```

<a name="initCameraMatrix2D"></a>

### initCameraMatrix2D
``` javascript
Mat : initCameraMatrix2D([Point3] objectPoints, [Point2] imagePoints, Size imageSize, Number aspectRatio = 1.0)
```

<a name="initCameraMatrix2DAsync"></a>

### initCameraMatrix2DAsync
``` javascript
initCameraMatrix2DAsync([Point3] objectPoints, [Point2] imagePoints, Size imageSize, callback(Error err, Mat  result))
initCameraMatrix2DAsync([Point3] objectPoints, [Point2] imagePoints, Size imageSize, Number aspectRatio, callback(Error err, Mat  result))
```

<a name="calibrateCamera"></a>

### calibrateCamera
``` javascript
{ returnValue: Number, rvecs: [Vec3], tvecs: [Vec3] } : calibrateCamera([Point3] objectPoints, [Point2] imagePoints, Size imageSize, Mat cameraMatrix, [Number] distCoeffs, Int flags = 0, TermCriteria criteria = new TermCriteria(cv.TermCriteria.COUNT + cv.TermCriteria.EPS, 30, DBL_EPSILON))
```

<a name="calibrateCameraAsync"></a>

### calibrateCameraAsync
``` javascript
calibrateCameraAsync([Point3] objectPoints, [Point2] imagePoints, Size imageSize, Mat cameraMatrix, [Number] distCoeffs, callback(Error err, { returnValue: Number, rvecs: [Vec3], tvecs: [Vec3] } result))
calibrateCameraAsync([Point3] objectPoints, [Point2] imagePoints, Size imageSize, Mat cameraMatrix, [Number] distCoeffs, ...opts, callback(Error err, { returnValue: Number, rvecs: [Vec3], tvecs: [Vec3] } result))
calibrateCameraAsync([Point3] objectPoints, [Point2] imagePoints, Size imageSize, Mat cameraMatrix, [Number] distCoeffs, { opts }, callback(Error err, { returnValue: Number, rvecs: [Vec3], tvecs: [Vec3] } result))
```

<a name="stereoCalibrate"></a>

### stereoCalibrate
``` javascript
{ returnValue: Number, R: Mat, T: [Vec3], E: Mat, F: Mat } : stereoCalibrate([Point3] objectPoints, [Point2] imagePoints1, [Point2] imagePoints2, Mat cameraMatrix1, [Number] distCoeffs1, Mat cameraMatrix2, [Number] distCoeffs2, Size imageSize, Int flags = cv.CALIB_FIX_INTRINSIC, TermCriteria criteria = new TermCriteria(cv.TermCriteria.COUNT + cv.TermCriteria.EPS, 30, 1e-6))
```

<a name="stereoCalibrateAsync"></a>

### stereoCalibrateAsync
``` javascript
stereoCalibrateAsync([Point3] objectPoints, [Point2] imagePoints1, [Point2] imagePoints2, Mat cameraMatrix1, [Number] distCoeffs1, Mat cameraMatrix2, [Number] distCoeffs2, Size imageSize, callback(Error err, { returnValue: Number, R: Mat, T: [Vec3], E: Mat, F: Mat } result))
stereoCalibrateAsync([Point3] objectPoints, [Point2] imagePoints1, [Point2] imagePoints2, Mat cameraMatrix1, [Number] distCoeffs1, Mat cameraMatrix2, [Number] distCoeffs2, Size imageSize, ...opts, callback(Error err, { returnValue: Number, R: Mat, T: [Vec3], E: Mat, F: Mat } result))
stereoCalibrateAsync([Point3] objectPoints, [Point2] imagePoints1, [Point2] imagePoints2, Mat cameraMatrix1, [Number] distCoeffs1, Mat cameraMatrix2, [Number] distCoeffs2, Size imageSize, { opts }, callback(Error err, { returnValue: Number, R: Mat, T: [Vec3], E: Mat, F: Mat } result))
```

<a name="stereoRectifyUncalibrated"></a>

### stereoRectifyUncalibrated
``` javascript
{ returnValue: Boolean, H1: Mat, H2: Mat } : stereoRectifyUncalibrated([Point2] points1, [Point2] points2, Mat F, Size imageSize, Number threshold = 5.0)
```

<a name="stereoRectifyUncalibratedAsync"></a>

### stereoRectifyUncalibratedAsync
``` javascript
stereoRectifyUncalibratedAsync([Point2] points1, [Point2] points2, Mat F, Size imageSize, callback(Error err, { returnValue: Boolean, H1: Mat, H2: Mat } result))
stereoRectifyUncalibratedAsync([Point2] points1, [Point2] points2, Mat F, Size imageSize, Number threshold, callback(Error err, { returnValue: Boolean, H1: Mat, H2: Mat } result))
```

<a name="findFundamentalMat"></a>

### findFundamentalMat
``` javascript
{ F: Mat, mask: Mat } : findFundamentalMat([Point2] points1, [Point2] points2, Int method = cv.FM_RANSAC, Number param1 = 3.0, Number param2 = 0.99)
```

<a name="findFundamentalMatAsync"></a>

### findFundamentalMatAsync
``` javascript
findFundamentalMatAsync([Point2] points1, [Point2] points2, callback(Error err, { F: Mat, mask: Mat } result))
findFundamentalMatAsync([Point2] points1, [Point2] points2, ...opts, callback(Error err, { F: Mat, mask: Mat } result))
findFundamentalMatAsync([Point2] points1, [Point2] points2, { opts }, callback(Error err, { F: Mat, mask: Mat } result))
```

<a name="findEssentialMat"></a>

### findEssentialMat
``` javascript
{ E: Mat, mask: Mat } : findEssentialMat([Point2] points1, [Point2] points2, Number focal = 1.0, Point2 pp = new Point(0, 0), Int method = cv.RANSAC, Number prob = 0.999,  Number threshold = 1.0)
```

<a name="findEssentialMatAsync"></a>

### findEssentialMatAsync
``` javascript
findEssentialMatAsync([Point2] points1, [Point2] points2, callback(Error err, { E: Mat, mask: Mat } result))
findEssentialMatAsync([Point2] points1, [Point2] points2, ...opts, callback(Error err, { E: Mat, mask: Mat } result))
findEssentialMatAsync([Point2] points1, [Point2] points2, { opts }, callback(Error err, { E: Mat, mask: Mat } result))
```

<a name="recoverPose"></a>

### recoverPose
``` javascript
{ returnValue: Int, R: Mat, T: Vec3 } : mat.recoverPose(Mat E, [Point2] points1, [Point2] points2, Number focal = 1.0, Point2 pp = new Point(0, 0), Mat mask = noArray())
```

<a name="recoverPoseAsync"></a>

### recoverPoseAsync
``` javascript
recoverPoseAsync(Mat E, [Point2] points1, [Point2] points2, callback(Error err, { returnValue: Int, R: Mat, T: Vec3 } result))
recoverPoseAsync(Mat E, [Point2] points1, [Point2] points2, ...opts, callback(Error err, { returnValue: Int, R: Mat, T: Vec3 } result))
recoverPoseAsync(Mat E, [Point2] points1, [Point2] points2, { opts }, callback(Error err, { returnValue: Int, R: Mat, T: Vec3 } result))
```

<a name="computeCorrespondEpilines"></a>

### computeCorrespondEpilines
``` javascript
[Vec3] : mat.computeCorrespondEpilines([Point2] points, Int whichImage, Mat F)
```

<a name="computeCorrespondEpilinesAsync"></a>

### computeCorrespondEpilinesAsync
``` javascript
mat.computeCorrespondEpilinesAsync([Point2] points, Int whichImage, Mat F, callback(Error err, [Vec3] result))
```

<a name="getValidDisparityROI"></a>

### getValidDisparityROI
``` javascript
Rect : mat.getValidDisparityROI([Rect] roi1, [Rect] roi2, Int minDisparity, Int numberOfDisparities, Int SADWindowSize)
```

<a name="getValidDisparityROIAsync"></a>

### getValidDisparityROIAsync
``` javascript
mat.getValidDisparityROIAsync(Rect roi1, Rect roi2, Int minDisparity, Int numberOfDisparities, Int SADWindowSize), callback(Error err, Rect result))
```

<a name="estimateAffine3D"></a>

### estimateAffine3D
``` javascript
{ returnValue: Int, out: Mat, inliers: Mat } : estimateAffine3D([Point3] src, [Point3] dst, Number ransacThreshold = 3.0, Number confidence = 0.99)
```

<a name="estimateAffine3DAsync"></a>

### estimateAffine3DAsync
``` javascript
estimateAffine3DAsync([Point3] src, [Point3] dst, callback(Error err, { returnValue: Int, out: Mat, inliers: Mat } result))
estimateAffine3DAsync([Point3] src, [Point3] dst, ...opts, callback(Error err, { returnValue: Int, out: Mat, inliers: Mat } result))
estimateAffine3DAsync([Point3] src, [Point3] dst, { opts }, callback(Error err, { returnValue: Int, out: Mat, inliers: Mat } result))
```

<a name="sampsonDistance"></a>

### sampsonDistance (v3.1+)
``` javascript
Number : sampsonDistance(Vec pt1, Vec2d pt2, Mat F)
```

<a name="sampsonDistanceAsync"></a>

### sampsonDistanceAsync (v3.1+)
``` javascript
Number : sampsonDistanceAsync(Vec pt1, Vec2d pt2, Mat F, callback(Error err, Number result))
```

<a name="calibrateCameraExtended"></a>

### calibrateCameraExtended (v3.2+)
``` javascript
{ returnValue: Number, rvecs: [Vec3], tvecs: [Vec3], stdDeviationsIntrinsics: Mat, stdDeviationsExtrinsics: Mat, perViewErrors: [Number] } : calibrateCameraExtended([Point3] objectPoints, [Point2] imagePoints, Size imageSize, Mat cameraMatrix, [Number] distCoeffs, Int flags = 0, TermCriteria criteria = new TermCriteria(cv.TermCriteria.COUNT + cv.TermCriteria.EPS, 30, DBL_EPSILON))
```

<a name="calibrateCameraExtendedAsync"></a>

### calibrateCameraExtendedAsync (v3.2+)
``` javascript
calibrateCameraExtendedAsync([Point3] objectPoints, [Point2] imagePoints, Size imageSize, Mat cameraMatrix, [Number] distCoeffs, callback(Error err, { returnValue: Number, rvecs: [Vec3], tvecs: [Vec3], stdDeviationsIntrinsics: Mat, stdDeviationsExtrinsics: Mat, perViewErrors: [Number] } result))
calibrateCameraExtendedAsync([Point3] objectPoints, [Point2] imagePoints, Size imageSize, Mat cameraMatrix, [Number] distCoeffs, ...opts, callback(Error err, { returnValue: Number, rvecs: [Vec3], tvecs: [Vec3], stdDeviationsIntrinsics: Mat, stdDeviationsExtrinsics: Mat, perViewErrors: [Number] } result))
calibrateCameraExtendedAsync([Point3] objectPoints, [Point2] imagePoints, Size imageSize, Mat cameraMatrix, [Number] distCoeffs, { opts }, callback(Error err, { returnValue: Number, rvecs: [Vec3], tvecs: [Vec3], stdDeviationsIntrinsics: Mat, stdDeviationsExtrinsics: Mat, perViewErrors: [Number] } result))
```

<a name="estimateAffine2D"></a>

### estimateAffine2D (v3.2+)
``` javascript
{ out: Mat, inliers: Mat } : estimateAffine3D([Point2] from, [Point2] to, Int method = cv.RANSAC, Number ransacReprojThreshold = 3.0, Int maxIters = 2000, Number confidence = 0.99, Int refineIters = 10)
```

<a name="estimateAffine2DAsync"></a>

### estimateAffine2DAsync (v3.2+)
``` javascript
estimateAffine2DAsync([Point2] from, [Point2] to, callback(Error err, { out: Mat, inliers: Mat } result))
estimateAffine2DAsync([Point2] from, [Point2] to, ...opts, callback(Error err, { out: Mat, inliers: Mat } result))
estimateAffine2DAsync([Point2] from, [Point2] to, { opts }, callback(Error err, { out: Mat, inliers: Mat } result))
```

<a name="estimateAffinePartial2D"></a>

### estimateAffinePartial2D (v3.2+)
``` javascript
{ out: Mat, inliers: Mat } : estimateAffinePartial2D([Point2] from, [Point2] to, Int method = cv.RANSAC, Number ransacReprojThreshold = 3.0, Int maxIters = 2000, Number confidence = 0.99, Int refineIters = 10)
```

<a name="estimateAffinePartial2DAsync"></a>

### estimateAffinePartial2DAsync (v3.2+)
``` javascript
estimateAffinePartial2DAsync([Point2] from, [Point2] to, callback(Error err, { out: Mat, inliers: Mat } result))
estimateAffinePartial2DAsync([Point2] from, [Point2] to, ...opts, callback(Error err, { out: Mat, inliers: Mat } result))
estimateAffinePartial2DAsync([Point2] from, [Point2] to, { opts }, callback(Error err, { out: Mat, inliers: Mat } result))
```

<a name="solveP3P"></a>

### solveP3P (v3.3+)
``` javascript
{ returnValue: Boolean, rvecs: [Mat], tvecs: [Mat] } : solveP3P([Point3] objectPoints, [Point2] imagePoints, Mat cameraMatrix, [Number] distCoeffs, Int flags = cv.SOLVEPNP_P3P)
```

<a name="solveP3PAsync"></a>

### solveP3PAsync (v3.3+)
``` javascript
solveP3PAsync([Point3] objectPoints, [Point2] imagePoints, Mat cameraMatrix, [Number] distCoeffs, callback(Error err, { returnValue: Boolean, rvecs: [Mat], tvecs: [Mat] } result))
solveP3PAsync([Point3] objectPoints, [Point2] imagePoints, Mat cameraMatrix, [Number] distCoeffs, Int flags, callback(Error err, { returnValue: Boolean, rvecs: [Mat], tvecs: [Mat] } result))
```