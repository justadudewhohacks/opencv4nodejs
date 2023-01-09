
/**
 * const syntax:
 * 
 * CV_[The number of bits per item][Signed or Unsigned][Type Prefix]C[The channel number]
 */
export const CV_8U: number;
export const CV_8S: number;
export const CV_16U: number;
export const CV_16S: number;
export const CV_32S: number;
export const CV_32F: number;
export const CV_64F: number;
export const CV_16F: number; // NEW

export const CV_8UC1: number;
export const CV_8UC2: number;
export const CV_8UC3: number;
export const CV_8UC4: number;

export const CV_8SC1: number;
export const CV_8SC2: number;
export const CV_8SC3: number;
export const CV_8SC4: number;

export const CV_16UC1: number;
export const CV_16UC2: number;
export const CV_16UC3: number;
export const CV_16UC4: number;

export const CV_16SC1: number;
export const CV_16SC2: number;
export const CV_16SC3: number;
export const CV_16SC4: number;

export const CV_32SC1: number;
export const CV_32SC2: number;
export const CV_32SC3: number;
export const CV_32SC4: number;

export const CV_32FC1: number;
export const CV_32FC2: number;
export const CV_32FC3: number;
export const CV_32FC4: number;

export const CV_64FC1: number;
export const CV_64FC2: number;
export const CV_64FC3: number;
export const CV_64FC4: number;

export const CV_16FC1: number;
export const CV_16FC2: number;
export const CV_16FC3: number;
export const CV_16FC4: number;

// TODO inject value of REDUCE_SUM REDUCE_...
export const REDUCE_SUM: number;
export const REDUCE_AVG: number;
export const REDUCE_MAX: number;
export const REDUCE_MIN: number;

// Gaussian elimination with the optimal pivot element chosen.
export const DECOMP_LU: number;

// singular value decomposition (SVD) method; the system can be over-defined and/or the matrix src1 can be singular
export const DECOMP_SVD: number;

// eigenvalue decomposition; the matrix src1 must be symmetrical
export const DECOMP_EIG: number; 

// Cholesky LLT factorization; the matrix src1 must be symmetrical and positively defined
export const DECOMP_CHOLESKY: number;

// QR factorization; the system can be over-defined and/or the matrix src1 can be singular
export const DECOMP_QR: number;

// while all the previous flags are mutually exclusive, this flag can be used together with any of the previous; it means that the normal equations src1T⋅src1⋅dst=src1Tsrc2 are solved instead of the original system src1⋅dst=src2
export const DECOMP_NORMAL: number;

// https://docs.opencv.org/4.x/df/d6c/group__ximgproc__superpixel.html
export const SLIC: number;// 100;
export const SLICO: number;// = 101;
export const MSLIC: number;//  = 102;

export const DNN_BACKEND_OPENCV: number;
export const DNN_BACKEND_INFERENCE_ENGINE: number;
export const DNN_BACKEND_HALIDE: number;
export const DNN_BACKEND_CUDA: number;

export const DNN_TARGET_CPU: number;
export const DNN_TARGET_OPENCL: number;
export const DNN_TARGET_OPENCL_FP16: number;
export const DNN_TARGET_MYRIAD: number;
export const DNN_TARGET_FPGA: number;
export const DNN_TARGET_CUDA: number;
export const DNN_TARGET_CUDA_FP16: number;
export const DNN_TARGET_HDDL: number;

export const ADAPTIVE_THRESH_GAUSSIAN_C: number;
export const ADAPTIVE_THRESH_MEAN_C: number;
export const BORDER_CONSTANT: number;
export const BORDER_DEFAULT: number;
export const BORDER_ISOLATED: number;
export const BORDER_REFLECT: number;
export const BORDER_REFLECT_101: number;
export const BORDER_REPLICATE: number;
export const BORDER_TRANSPARENT: number;
export const BORDER_WRAP: number;
export const CALIB_CB_ADAPTIVE_THRESH: number;
export const CALIB_CB_ASYMMETRIC_GRID: number;
export const CALIB_CB_CLUSTERING: number;
export const CALIB_CB_FAST_CHECK: number;
export const CALIB_CB_FILTER_QUADS: number;
export const CALIB_CB_NORMALIZE_IMAGE: number;
export const CALIB_CB_SYMMETRIC_GRID: number;
export const CALIB_FIX_ASPECT_RATIO: number;
export const CALIB_FIX_FOCAL_LENGTH: number;
export const CALIB_FIX_INTRINSIC: number;
export const CALIB_FIX_K1: number;
export const CALIB_FIX_K2: number;
export const CALIB_FIX_K3: number;
export const CALIB_FIX_K4: number;
export const CALIB_FIX_K5: number;
export const CALIB_FIX_K6: number;
export const CALIB_FIX_PRINCIPAL_POINT: number;
export const CALIB_FIX_S1_S2_S3_S4: number;
export const CALIB_FIX_TANGENT_DIST: number;
export const CALIB_FIX_TAUX_TAUY: number;
export const CALIB_RATIONAL_MODEL: number;
export const CALIB_SAME_FOCAL_LENGTH: number;
export const CALIB_THIN_PRISM_MODEL: number;
export const CALIB_TILTED_MODEL: number;
export const CALIB_USE_INTRINSIC_GUESS: number;
export const CALIB_USE_LU: number;
export const CALIB_USE_QR: number;
export const CALIB_ZERO_DISPARITY: number;
export const CALIB_ZERO_TANGENT_DIST: number;
/**
 * Android - not used.
 */
export const CAP_ANDROID: number;
/**
 * Auto detect == 0.
 */
export const CAP_ANY: number;
/**
 * Aravis SDK.
 */
export const CAP_ARAVIS: number;
/**
 * AVFoundation framework for iOS (OS X Lion will have the same API)
 */
export const CAP_AVFOUNDATION: number;
export const CAP_CMU1394: number;
export const CAP_DC1394: number;
/**
 * DirectShow (via videoInput)
 */
export const CAP_DSHOW: number;
/**
 * Open and record video file or stream using the FFMPEG library.
 */
export const CAP_FFMPEG: number;
/**
 * IEEE 1394 drivers.
 */
export const CAP_FIREWIRE: number;
/**
 * Smartek Giganetix GigEVisionSDK.
 */
export const CAP_GIGANETIX: number;
/**
 * gPhoto2 connection
 */
export const CAP_GPHOTO2: number;
/**
 * GStreamer.
 */
export const CAP_GSTREAMER: number;
export const CAP_IEEE1394: number;
/**
 * OpenCV Image Sequence (e.g. img_%02d.jpg)
 */
export const CAP_IMAGES: number;
/**
 * RealSense (former Intel Perceptual Computing SDK)
 */
export const CAP_INTELPERC: number;
export const CAP_MODE_BGR: number;
export const CAP_MODE_GRAY: number;
export const CAP_MODE_RGB: number;
export const CAP_MODE_YUYV: number;
/**
 * Microsoft Media Foundation (via videoInput)
 */
export const CAP_MSMF: number;
/**
 * OpenNI (for Kinect)
 */
export const CAP_OPENNI: number;
/**
 * OpenNI2 (for Kinect)
 */
export const CAP_OPENNI2: number;
/**
 * OpenNI2 (for Asus Xtion and Occipital Structure sensors)
 */
export const CAP_OPENNI2_ASUS: number;
/**
 * OpenNI (for Asus Xtion)
 */
export const CAP_OPENNI_ASUS: number;
export const CAP_PROP_AUTOFOCUS: number;
/**
 * DC1394: exposure control done by camera, user can adjust reference level using this feature.
 */
export const CAP_PROP_AUTO_EXPOSURE: number;
export const CAP_PROP_BACKLIGHT: number;
/**
 * Brightness of the image (only for those cameras that support).
 */
export const CAP_PROP_BRIGHTNESS: number;
export const CAP_PROP_BUFFERSIZE: number;
/**
 * Contrast of the image (only for cameras).
 */
export const CAP_PROP_CONTRAST: number;
/**
 * Boolean flags indicating whether images should be converted to RGB.
 * GStreamer note: The flag is ignored in case if custom pipeline is used. It's user responsibility to interpret pipeline output.
 */
export const CAP_PROP_CONVERT_RGB: number;
/**
 * Exposure (only for those cameras that support).
 */
export const CAP_PROP_EXPOSURE: number;
export const CAP_PROP_FOCUS: number;
/**
 * Format of the Mat objects (see Mat::type()) returned by VideoCapture::retrieve(). Set value -1 to fetch undecoded RAW video streams (as Mat 8UC1).
 */
export const CAP_PROP_FORMAT: number;
/**
 * 4-character code of codec. see VideoWriter::fourcc .
 */
export const CAP_PROP_FOURCC: number;
/**
 * Frame rate.
 */
export const CAP_PROP_FPS: number;
/**
 * Number of frames in the video file.
 */
export const CAP_PROP_FRAME_COUNT: number;
/**
 * Height of the frames in the video stream.
 */
export const CAP_PROP_FRAME_HEIGHT: number;
/**
 * Width of the frames in the video stream.
 */
export const CAP_PROP_FRAME_WIDTH: number;
/**
 * Gain of the image (only for those cameras that support).
 */
export const CAP_PROP_GAIN: number;
export const CAP_PROP_GAMMA: number;
export const CAP_PROP_GUID: number;
/**
 * Hue of the image (only for cameras).
 */
export const CAP_PROP_HUE: number;
export const CAP_PROP_IRIS: number;
export const CAP_PROP_ISO_SPEED: number;
/**
 * Backend-specific value indicating the current capture mode.
 */
export const CAP_PROP_MODE: number;
/**
 * 
 */
export const CAP_PROP_MONOCHROME: number;
export const CAP_PROP_PAN: number;
/**
 * Relative position of the video file: 0=start of the film, 1=end of the film.
 */
export const CAP_PROP_POS_AVI_RATIO: number;
/**
 * 0-based index of the frame to be decoded/captured next.
 */
export const CAP_PROP_POS_FRAMES: number;
/**
 * Current position of the video file in milliseconds.
 */
export const CAP_PROP_POS_MSEC: number;
/**
 * Rectification flag for stereo cameras (note: only supported by DC1394 v 2.x backend currently).
 */
export const CAP_PROP_RECTIFICATION: number;
export const CAP_PROP_ROLL: number;
/**
 * Saturation of the image (only for cameras).
 */
export const CAP_PROP_SATURATION: number;
/**
 * Pop up video/camera filter dialog (note: only supported by DSHOW backend currently. The property value is ignored)
 */
export const CAP_PROP_SETTINGS: number;
/**
 * 
 */
export const CAP_PROP_SHARPNESS: number;
export const CAP_PROP_TEMPERATURE: number;
export const CAP_PROP_TILT: number;
export const CAP_PROP_TRIGGER: number;
export const CAP_PROP_TRIGGER_DELAY: number;
/**
 * Currently unsupported.
 */
export const CAP_PROP_WHITE_BALANCE_BLUE_U: number;
export const CAP_PROP_WHITE_BALANCE_RED_V: number;
export const CAP_PROP_ZOOM: number;
/**
 * PvAPI, Prosilica GigE SDK.
 */
export const CAP_PVAPI: number;
/**
 * QuickTime (obsolete, removed)
 */
export const CAP_QT: number;
/**
 * Unicap drivers (obsolete, removed)
 */
export const CAP_UNICAP: number;
/**
 * V4L/V4L2 capturing support.
 */
export const CAP_V4L: number;
/**
 * Same as CAP_V4L.
 */
export const CAP_V4L2: number;
/**
 * Video For Windows (obsolete, removed)
 */
export const CAP_VFW: number;
/**
 * Microsoft Windows Runtime using Media Foundation.
 */
export const CAP_WINRT: number;
/**
 * XIMEA Camera API.
 */
export const CAP_XIAPI: number;
export const CC_STAT_AREA: number;
export const CC_STAT_HEIGHT: number;
export const CC_STAT_LEFT: number;
export const CC_STAT_MAX: number;
export const CC_STAT_TOP: number;
export const CC_STAT_WIDTH: number;
export const CHAIN_APPROX_NONE: number;
export const CHAIN_APPROX_SIMPLE: number;
export const CHAIN_APPROX_TC89_KCOS: number;
export const CHAIN_APPROX_TC89_L1: number;
export const COLOR_BGR2BGR555: number;
export const COLOR_BGR2BGR565: number;
export const COLOR_BGR2BGRA: number;
export const COLOR_BGR2GRAY: number;
export const COLOR_BGR2HLS: number;
export const COLOR_BGR2HLS_FULL: number;
export const COLOR_BGR2HSV: number;
export const COLOR_BGR2HSV_FULL: number;
export const COLOR_BGR2Lab: number;
export const COLOR_BGR2Luv: number;
export const COLOR_BGR2RGB: number;
export const COLOR_BGR2RGBA: number;
export const COLOR_BGR2XYZ: number;
export const COLOR_BGR2YCrCb: number;
export const COLOR_BGR2YUV: number;
export const COLOR_BGR2YUV_I420: number;
export const COLOR_BGR2YUV_IYUV: number;
export const COLOR_BGR2YUV_YV12: number;
export const COLOR_BGR5552BGR: number;
export const COLOR_BGR5552BGRA: number;
export const COLOR_BGR5552GRAY: number;
export const COLOR_BGR5552RGB: number;
export const COLOR_BGR5552RGBA: number;
export const COLOR_BGR5652BGR: number;
export const COLOR_BGR5652BGRA: number;
export const COLOR_BGR5652GRAY: number;
export const COLOR_BGR5652RGB: number;
export const COLOR_BGR5652RGBA: number;
export const COLOR_BGRA2BGR: number;
export const COLOR_BGRA2BGR555: number;
export const COLOR_BGRA2BGR565: number;
export const COLOR_BGRA2GRAY: number;
export const COLOR_BGRA2RGB: number;
export const COLOR_BGRA2RGBA: number;
export const COLOR_BGRA2YUV_I420: number;
export const COLOR_BGRA2YUV_IYUV: number;
export const COLOR_BGRA2YUV_YV12: number;
export const COLOR_BayerBG2BGR: number;
export const COLOR_BayerBG2BGR_EA: number;
export const COLOR_BayerBG2BGR_VNG: number;
export const COLOR_BayerBG2GRAY: number;
export const COLOR_BayerBG2RGB: number;
export const COLOR_BayerBG2RGB_EA: number;
export const COLOR_BayerBG2RGB_VNG: number;
export const COLOR_BayerGB2BGR: number;
export const COLOR_BayerGB2BGR_EA: number;
export const COLOR_BayerGB2BGR_VNG: number;
export const COLOR_BayerGB2GRAY: number;
export const COLOR_BayerGB2RGB: number;
export const COLOR_BayerGB2RGB_EA: number;
export const COLOR_BayerGB2RGB_VNG: number;
export const COLOR_BayerGR2BGR: number;
export const COLOR_BayerGR2BGR_EA: number;
export const COLOR_BayerGR2BGR_VNG: number;
export const COLOR_BayerGR2GRAY: number;
export const COLOR_BayerGR2RGB: number;
export const COLOR_BayerGR2RGB_EA: number;
export const COLOR_BayerGR2RGB_VNG: number;
export const COLOR_BayerRG2BGR: number;
export const COLOR_BayerRG2BGR_EA: number;
export const COLOR_BayerRG2BGR_VNG: number;
export const COLOR_BayerRG2GRAY: number;
export const COLOR_BayerRG2RGB: number;
export const COLOR_BayerRG2RGB_EA: number;
export const COLOR_BayerRG2RGB_VNG: number;
export const COLOR_COLORCVT_MAX: number;
export const COLOR_GRAY2BGR: number;
export const COLOR_GRAY2BGR555: number;
export const COLOR_GRAY2BGR565: number;
export const COLOR_GRAY2BGRA: number;
export const COLOR_GRAY2RGB: number;
export const COLOR_GRAY2RGBA: number;
export const COLOR_HLS2BGR: number;
export const COLOR_HLS2BGR_FULL: number;
export const COLOR_HLS2RGB: number;
export const COLOR_HLS2RGB_FULL: number;
export const COLOR_HSV2BGR: number;
export const COLOR_HSV2BGR_FULL: number;
export const COLOR_HSV2RGB: number;
export const COLOR_HSV2RGB_FULL: number;
export const COLOR_LBGR2Lab: number;
export const COLOR_LBGR2Luv: number;
export const COLOR_LRGB2Lab: number;
export const COLOR_LRGB2Luv: number;
export const COLOR_Lab2BGR: number;
export const COLOR_Lab2LBGR: number;
export const COLOR_Lab2LRGB: number;
export const COLOR_Lab2RGB: number;
export const COLOR_Luv2BGR: number;
export const COLOR_Luv2LBGR: number;
export const COLOR_Luv2LRGB: number;
export const COLOR_Luv2RGB: number;
export const COLOR_RGB2BGR: number;
export const COLOR_RGB2BGR555: number;
export const COLOR_RGB2BGR565: number;
export const COLOR_RGB2BGRA: number;
export const COLOR_RGB2GRAY: number;
export const COLOR_RGB2HLS: number;
export const COLOR_RGB2HLS_FULL: number;
export const COLOR_RGB2HSV: number;
export const COLOR_RGB2HSV_FULL: number;
export const COLOR_RGB2Lab: number;
export const COLOR_RGB2Luv: number;
export const COLOR_RGB2RGBA: number;
export const COLOR_RGB2XYZ: number;
export const COLOR_RGB2YCrCb: number;
export const COLOR_RGB2YUV: number;
export const COLOR_RGB2YUV_I420: number;
export const COLOR_RGB2YUV_IYUV: number;
export const COLOR_RGB2YUV_YV12: number;
export const COLOR_RGBA2BGR: number;
export const COLOR_RGBA2BGR555: number;
export const COLOR_RGBA2BGR565: number;
export const COLOR_RGBA2BGRA: number;
export const COLOR_RGBA2GRAY: number;
export const COLOR_RGBA2RGB: number;
export const COLOR_RGBA2YUV_I420: number;
export const COLOR_RGBA2YUV_IYUV: number;
export const COLOR_RGBA2YUV_YV12: number;
export const COLOR_RGBA2mRGBA: number;
export const COLOR_XYZ2BGR: number;
export const COLOR_XYZ2RGB: number;
export const COLOR_YCrCb2BGR: number;
export const COLOR_YCrCb2RGB: number;
export const COLOR_YUV2BGR: number;
export const COLOR_YUV2BGRA_I420: number;
export const COLOR_YUV2BGRA_IYUV: number;
export const COLOR_YUV2BGRA_NV12: number;
export const COLOR_YUV2BGRA_NV21: number;
export const COLOR_YUV2BGRA_UYNV: number;
export const COLOR_YUV2BGRA_UYVY: number;
export const COLOR_YUV2BGRA_Y422: number;
export const COLOR_YUV2BGRA_YUNV: number;
export const COLOR_YUV2BGRA_YUY2: number;
export const COLOR_YUV2BGRA_YUYV: number;
export const COLOR_YUV2BGRA_YV12: number;
export const COLOR_YUV2BGRA_YVYU: number;
export const COLOR_YUV2BGR_I420: number;
export const COLOR_YUV2BGR_IYUV: number;
export const COLOR_YUV2BGR_NV12: number;
export const COLOR_YUV2BGR_NV21: number;
export const COLOR_YUV2BGR_UYNV: number;
export const COLOR_YUV2BGR_UYVY: number;
export const COLOR_YUV2BGR_Y422: number;
export const COLOR_YUV2BGR_YUNV: number;
export const COLOR_YUV2BGR_YUY2: number;
export const COLOR_YUV2BGR_YUYV: number;
export const COLOR_YUV2BGR_YV12: number;
export const COLOR_YUV2BGR_YVYU: number;
export const COLOR_YUV2GRAY_420: number;
export const COLOR_YUV2GRAY_I420: number;
export const COLOR_YUV2GRAY_IYUV: number;
export const COLOR_YUV2GRAY_NV12: number;
export const COLOR_YUV2GRAY_NV21: number;
export const COLOR_YUV2GRAY_UYNV: number;
export const COLOR_YUV2GRAY_UYVY: number;
export const COLOR_YUV2GRAY_Y422: number;
export const COLOR_YUV2GRAY_YUNV: number;
export const COLOR_YUV2GRAY_YUY2: number;
export const COLOR_YUV2GRAY_YUYV: number;
export const COLOR_YUV2GRAY_YV12: number;
export const COLOR_YUV2GRAY_YVYU: number;
export const COLOR_YUV2RGB: number;
export const COLOR_YUV2RGBA_I420: number;
export const COLOR_YUV2RGBA_IYUV: number;
export const COLOR_YUV2RGBA_NV12: number;
export const COLOR_YUV2RGBA_NV21: number;
export const COLOR_YUV2RGBA_UYNV: number;
export const COLOR_YUV2RGBA_UYVY: number;
export const COLOR_YUV2RGBA_Y422: number;
export const COLOR_YUV2RGBA_YUNV: number;
export const COLOR_YUV2RGBA_YUY2: number;
export const COLOR_YUV2RGBA_YUYV: number;
export const COLOR_YUV2RGBA_YV12: number;
export const COLOR_YUV2RGBA_YVYU: number;
export const COLOR_YUV2RGB_I420: number;
export const COLOR_YUV2RGB_IYUV: number;
export const COLOR_YUV2RGB_NV12: number;
export const COLOR_YUV2RGB_NV21: number;
export const COLOR_YUV2RGB_UYNV: number;
export const COLOR_YUV2RGB_UYVY: number;
export const COLOR_YUV2RGB_Y422: number;
export const COLOR_YUV2RGB_YUNV: number;
export const COLOR_YUV2RGB_YUY2: number;
export const COLOR_YUV2RGB_YUYV: number;
export const COLOR_YUV2RGB_YV12: number;
export const COLOR_YUV2RGB_YVYU: number;
export const COLOR_YUV420p2BGR: number;
export const COLOR_YUV420p2BGRA: number;
export const COLOR_YUV420p2GRAY: number;
export const COLOR_YUV420p2RGB: number;
export const COLOR_YUV420p2RGBA: number;
export const COLOR_YUV420sp2BGR: number;
export const COLOR_YUV420sp2BGRA: number;
export const COLOR_YUV420sp2GRAY: number;
export const COLOR_YUV420sp2RGB: number;
export const COLOR_YUV420sp2RGBA: number;
export const COLOR_mRGBA2RGBA: number;
export const COLORMAP_AUTUMN: number;
export const COLORMAP_BONE: number;
export const COLORMAP_JET: number;
export const COLORMAP_WINTER: number;
export const COLORMAP_RAINBOW: number;
export const COLORMAP_OCEAN: number;
export const COLORMAP_SUMMER: number;
export const COLORMAP_SPRING: number;
export const COLORMAP_COOL: number;
export const COLORMAP_HSV: number;
export const COLORMAP_PINK: number;
export const COLORMAP_HOT: number;
export const COLORMAP_PARULA: number;
export const CV_CONTOURS_MATCH_I1: number;
export const CV_CONTOURS_MATCH_I2: number;
export const CV_CONTOURS_MATCH_I3: number;
export const DCT_INVERSE: number;
export const DCT_ROWS: number;
export const DFT_COMPLEX_OUTPUT: number;
export const DFT_INVERSE: number;
export const DFT_REAL_OUTPUT: number;
export const DFT_ROWS: number;
export const DFT_SCALE: number;
export const DIST_C: number;
export const DIST_FAIR: number;
export const DIST_HUBER: number;
export const DIST_L1: number;
export const DIST_L12: number;
export const DIST_L2: number;
export const DIST_LABEL_CCOMP: number;
export const DIST_LABEL_PIXEL: number;
export const DIST_MASK_3: number;
export const DIST_MASK_5: number;
export const DIST_MASK_PRECISE: number;
export const DIST_USER: number;
export const DIST_WELSCH: number;
export const FILLED: number;
export const FLOODFILL_FIXED_RANGE: number;
export const FLOODFILL_MASK_ONLY: number;
export const FM_7POINT: number;
export const FM_8POINT: number;
export const FM_LMEDS: number;
export const FM_RANSAC: number;
export const FONT_HERSHEY_COMPLEX: number;
export const FONT_HERSHEY_COMPLEX_SMALL: number;
export const FONT_HERSHEY_DUPLEX: number;
export const FONT_HERSHEY_PLAIN: number;
export const FONT_HERSHEY_SCRIPT_COMPLEX: number;
export const FONT_HERSHEY_SCRIPT_SIMPLEX: number;
export const FONT_HERSHEY_SIMPLEX: number;
export const FONT_HERSHEY_TRIPLEX: number;
export const FONT_ITALIC: number;
export const GC_BGD: number;
export const GC_EVAL: number;
export const GC_FGD: number;
export const GC_INIT_WITH_MASK: number;
export const GC_INIT_WITH_RECT: number;
export const GC_PR_BGD: number;
export const GC_PR_FGD: number;
export const HISTCMP_BHATTACHARYYA: number;
export const HISTCMP_CHISQR: number;
export const HISTCMP_CHISQR_ALT: number;
export const HISTCMP_CORREL: number;
export const HISTCMP_HELLINGER: number;
export const HISTCMP_INTERSECT: number;
export const HISTCMP_KL_DIV: number;
export const HOUGH_GRADIENT: number;
export const HOUGH_MULTI_SCALE: number;
export const HOUGH_PROBABILISTIC: number;
export const HOUGH_STANDARD: number;
export const INTER_AREA: number;
export const INTER_CUBIC: number;
export const INTER_LANCZOS4: number;
export const INTER_LINEAR: number;
export const INTER_MAX: number;
export const INTER_NEAREST: number;
export const KMEANS_PP_CENTERS: number;
export const KMEANS_RANDOM_CENTERS: number;
export const KMEANS_USE_INITIAL_LABELS: number;
export const LINE_4: number;
export const LINE_8: number;
export const LINE_AA: number;
export const LMEDS: number;
export const MIXED_CLONE: number;
export const MONOCHROME_TRANSFER: number;
export const MORPH_BLACKHAT: number;
export const MORPH_CLOSE: number;
export const MORPH_CROSS: number;
export const MORPH_DILATE: number;
export const MORPH_ELLIPSE: number;
export const MORPH_ERODE: number;
export const MORPH_GRADIENT: number;
export const MORPH_HITMISS: number;
export const MORPH_OPEN: number;
export const MORPH_RECT: number;
export const MORPH_TOPHAT: number;
export const NORM_HAMMING: number;
export const NORM_HAMMING2: number;
export const NORM_INF: number;
export const NORM_L1: number;
export const NORM_L2: number;
export const NORM_L2SQR: number;
export const NORM_MINMAX: number;
export const NORM_RELATIVE: number;
export const NORM_const_MASK: number;
export const NORMAL_CLONE: number;
export const RANSAC: number;
export const REGULAR: number;
export const RETR_CCOMP: number;
export const RETR_EXTERNAL: number;
export const RETR_FLOODFILL: number;
export const RETR_LIST: number;
export const RETR_TREE: number;
export const RHO: number;
export const ROTATE_180: number;
export const ROTATE_90_CLOCKWISE: number;
export const ROTATE_90_COUNTERCLOCKWISE: number;
export const SOLVEPNP_AP3P: number;
export const SOLVEPNP_DLS: number;
export const SOLVEPNP_EPNP: number;
export const SOLVEPNP_ITERATIVE: number;
export const SOLVEPNP_MAX_COUNT: number;
export const SOLVEPNP_P3P: number;
export const SOLVEPNP_UPNP: number;
export const THRESH_BINARY: number;
export const THRESH_BINARY_INV: number;
export const THRESH_MASK: number;
export const THRESH_OTSU: number;
export const THRESH_TOZERO: number;
export const THRESH_TOZERO_INV: number;
export const THRESH_TRIANGLE: number;
export const THRESH_TRUNC: number;
export const TM_CCOEFF: number;
export const TM_CCOEFF_NORMED: number;
export const TM_CCORR: number;
export const TM_CCORR_NORMED: number;
export const TM_SQDIFF: number;
export const TM_SQDIFF_NORMED: number;
export const VIDEOWRITER_PROP_FRAMEBYTES: number;
export const VIDEOWRITER_PROP_NSTRIPES: number;
export const VIDEOWRITER_PROP_QUALITY: number;
export const WARP_FILL_OUTLIERS: number;
export const WARP_INVERSE_MAP: number;
export const INPAINT_NS: number;
export const INPAINT_TELEA: number;

export const IMREAD_UNCHANGED: number;
export const IMREAD_GRAYSCALE: number;
export const IMREAD_COLOR: number;
export const IMREAD_ANYDEPTH: number;
export const IMREAD_ANYCOLOR: number;
export const IMREAD_LOAD_GDAL: number;

export const IMWRITE_JPEG_QUALITY: number;
export const IMWRITE_JPEG_PROGRESSIVE: number;
export const IMWRITE_JPEG_OPTIMIZE: number;
export const IMWRITE_JPEG_RST_INTERVAL: number;
export const IMWRITE_JPEG_LUMA_QUALITY: number;
export const IMWRITE_JPEG_CHROMA_QUALITY: number;
export const IMWRITE_PNG_COMPRESSION: number;
export const IMWRITE_PNG_STRATEGY: number;
export const IMWRITE_PNG_BILEVEL: number;
export const IMWRITE_PXM_BINARY: number;
export const IMWRITE_WEBP_QUALITY: number;


export const IMWRITE_PNG_STRATEGY_DEFAULT: number;
export const IMWRITE_PNG_STRATEGY_FILTERED: number;
export const IMWRITE_PNG_STRATEGY_HUFFMAN_ONLY: number;
export const IMWRITE_PNG_STRATEGY_RLE: number;
export const IMWRITE_PNG_STRATEGY_FIXED: number;


export const IMREAD_REDUCED_GRAYSCALE_2: number;
export const IMREAD_REDUCED_COLOR_2: number;
export const IMREAD_REDUCED_GRAYSCALE_4: number;
export const IMREAD_REDUCED_COLOR_4: number;
export const IMREAD_REDUCED_GRAYSCALE_8: number;
export const IMREAD_REDUCED_COLOR_8: number;

export const IMREAD_IGNORE_ORIENTATION: number;
export const IMWRITE_PAM_TUPLETYPE: number;
export const IMWRITE_PAM_FORMAT_NULL: number;

export const IMWRITE_PAM_FORMAT_BLACKANDWHITE: number;
export const IMWRITE_PAM_FORMAT_GRAYSCALE: number;
export const IMWRITE_PAM_FORMAT_GRAYSCALE_ALPHA: number;
export const IMWRITE_PAM_FORMAT_RGB: number;
export const IMWRITE_PAM_FORMAT_RGB_ALPHA: number;

export const HAAR_EYE: string;
export const HAAR_EYE_TREE_EYEGLASSES: string;
export const HAAR_FRONTALCATFACE: string;
export const HAAR_FRONTALCATFACE_EXTENDED: string;
export const HAAR_FRONTALFACE_ALT: string;
export const HAAR_FRONTALFACE_ALT2: string;
export const HAAR_FRONTALFACE_ALT_TREE: string;
export const HAAR_FRONTALFACE_DEFAULT: string;
export const HAAR_FULLBODY: string;
export const HAAR_LEFTEYE_2SPLITS: string;
export const HAAR_LICENCE_PLATE_RUS_16STAGES: string;
export const HAAR_LOWERBODY: string;
export const HAAR_PROFILEFACE: string;
export const HAAR_RIGHTEYE_2SPLITS: string;
export const HAAR_RUSSIAN_PLATE_NUMBER: string;
export const HAAR_SMILE: string;
export const HAAR_UPPERBODY: string;

export const LBP_FRONTALCATFACE: string;
export const LBP_FRONTALFACE: string;
export const LBP_FRONTALFACE_IMPROVED: string;
export const LBP_PROFILEFACE: string;
export const LBP_SILVERWARE: string;

export const WINDOW_NORMAL: number;
export const WINDOW_AUTOSIZE: number;
export const WINDOW_OPENGL: number;
export const WINDOW_FULLSCREEN: number;
export const WINDOW_FREERATIO: number;
export const WINDOW_KEEPRATIO: number;
export const WINDOW_GUI_EXPANDED: number;
export const WINDOW_GUI_NORMAL: number;

//! Flags for cv::setWindowProperty / cv::getWindowProperty
// enum WindowPropertyFlags
export const WND_PROP_FULLSCREEN: number;
export const WND_PROP_AUTOSIZE: number;
export const WND_PROP_ASPECT_RATIO: number;
export const WND_PROP_OPENGL: number;
export const WND_PROP_VISIBLE: number;
export const WND_PROP_TOPMOST: number;
export const WND_PROP_VSYNC: number;

// export type WND_PROP = WND_PROP_FULLSCREEN | WND_PROP_AUTOSIZE | WND_PROP_ASPECT_RATIO | WND_PROP_OPENGL | WND_PROP_VISIBLE | WND_PROP_TOPMOST | WND_PROP_VSYNC;

//! Mouse Events see cv::MouseCallback
// enum MouseEventTypes
export const EVENT_MOUSEMOVE: number;
export const EVENT_LBUTTONDOWN: number;
export const EVENT_RBUTTONDOWN: number;
export const EVENT_MBUTTONDOWN: number;
export const EVENT_LBUTTONUP: number;
export const EVENT_RBUTTONUP: number;
export const EVENT_MBUTTONUP: number;
export const EVENT_LBUTTONDBLCLK: number;
export const EVENT_RBUTTONDBLCLK: number;
export const EVENT_MBUTTONDBLCLK: number;
export const EVENT_MOUSEWHEEL: number;
export const EVENT_MOUSEHWHEEL: number;

//! Mouse Event Flags see cv::MouseCallback
// enum MouseEventFlags
export const EVENT_FLAG_LBUTTON: number;
export const EVENT_FLAG_RBUTTON: number;
export const EVENT_FLAG_MBUTTON: number;
export const EVENT_FLAG_CTRLKEY: number;
export const EVENT_FLAG_SHIFTKEY: number;
export const EVENT_FLAG_ALTKEY: number;

//! Qt font weight
// enum QtFontWeights
export const QT_FONT_LIGHT: number;
export const QT_FONT_NORMAL: number;
export const QT_FONT_DEMIBOLD: number;
export const QT_FONT_BOLD: number;
export const QT_FONT_BLACK: number;

//! Qt font style
// enum QtFontStyles
export const QT_STYLE_NORMAL: number;
export const QT_STYLE_ITALIC: number;
export const QT_STYLE_OBLIQUE: number;

//! Qt "button" type
// enum QtButtonTypes
export const QT_PUSH_BUTTON: number;
export const QT_CHECKBOX: number;
export const QT_RADIOBOX: number;
export const QT_NEW_BUTTONBAR: number;


export const termCriteria: {
  COUNT: number;
  MAX_ITER: number;
  EPS: number;
}

export const ml: {
  COL_SAMPLE: number;
  ROW_SAMPLE: number;
  VAR_CATEGORICAL: number;
  VAR_NUMERICAL: number;
  VAR_ORDERED: number;

  SVM: {
    CUSTOM: number;
    LINEAR: number;
    POLY: number;
    RBF: number;
    SIGMOID: number;
    CHI2: number;
    INTER: number;
    C: number;
    COEF: number;
    DEGREE: number;
    GAMMA: number;
    NU: number;
    P: number;
  }
}

export const statModel: {
  COMPRESSED_INPUT: number;
  PREPROCESSED_INPUT: number;
  RAW_OUTPUT: number;
  UPDATE_MODEL: number;
}
