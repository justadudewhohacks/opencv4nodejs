{
	"targets": [{
		"target_name": "opencv4nodejs",
		"defines": [
			"<!@(node ./install/parseEnv.js OPENCV4NODEJS_DEFINES)",
		],
		"include_dirs" : [
			"<!@(node ./install/parseEnv.js OPENCV4NODEJS_INCLUDES)",
			"cc",
			"cc/core",
			"<!(node -e \"require('nan')\")",
			"<!(node -e \"require('native-node-utils')\")"
		],
		"libraries": [
			"<!@(node ./install/parseEnv.js OPENCV4NODEJS_LIBRARIES)",
		],
		"sources": [
			"cc/opencv4nodejs.cc",
			"cc/CustomMatAllocator.cc",
			"cc/ExternalMemTracking.cc",
			"cc/core/core.cc",
			"cc/core/coreConstants.cc",
			"cc/core/HistAxes.cc",
			"cc/core/Mat.cc",
			"cc/core/Point.cc",
			"cc/core/Vec.cc",
			"cc/core/Size.cc",
			"cc/core/Rect.cc",
			"cc/core/RotatedRect.cc",
			"cc/core/TermCriteria.cc",
			"cc/imgproc/imgproc.cc",
			"cc/imgproc/imgprocConstants.cc",
			"cc/imgproc/MatImgproc.cc",
			"cc/imgproc/Contour.cc",
			"cc/imgproc/Moments.cc",
			"cc/calib3d/calib3d.cc",
			"cc/calib3d/calib3dConstants.cc",
			"cc/calib3d/MatCalib3d.cc",
			"cc/io/io.cc",
			"cc/io/ioConstants.cc",
			"cc/io/VideoCapture.cc",
			"cc/io/VideoWriter.cc",
			"cc/photo/photo.cc",
			"cc/photo/photoConstants.cc",
			"cc/photo/MatPhoto.cc",
			"cc/video/video.cc",
			"cc/video/BackgroundSubtractor.cc",
			"cc/video/BackgroundSubtractorMOG2.cc",
			"cc/video/BackgroundSubtractorKNN.cc",
			"cc/ximgproc/ximgproc.cc",
			"cc/ximgproc/MatXimgproc.cc",
			"cc/ximgproc/SuperpixelSEEDS.cc",
			"cc/ximgproc/SuperpixelSLIC.cc",
			"cc/ximgproc/SuperpixelLSC.cc",
			"cc/objdetect/objdetect.cc",
			"cc/objdetect/CascadeClassifier.cc",
			"cc/objdetect/HOGDescriptor.cc",
			"cc/objdetect/DetectionROI.cc",
			"cc/machinelearning/machinelearning.cc",
			"cc/machinelearning/machinelearningConstants.cc",
			"cc/machinelearning/ParamGrid.cc",
			"cc/machinelearning/StatModel.cc",
			"cc/machinelearning/SVM.cc",
			"cc/machinelearning/TrainData.cc",
			"cc/dnn/dnn.cc",
			"cc/dnn/Net.cc",
			"cc/face/face.cc",
			"cc/face/FaceRecognizer.cc",
			"cc/face/EigenFaceRecognizer.cc",
			"cc/face/FisherFaceRecognizer.cc",
			"cc/face/LBPHFaceRecognizer.cc",
			"cc/face/Facemark.cc",
			"cc/face/FacemarkAAM.cc",
			"cc/face/FacemarkAAMData.cc",
			"cc/face/FacemarkAAMParams.cc",
			"cc/face/FacemarkLBF.cc",
			"cc/face/FacemarkLBFParams.cc",
			"cc/text/text.cc",
			"cc/text/OCRHMMClassifier.cc",
			"cc/text/OCRHMMDecoder.cc",
			"cc/tracking/tracking.cc",
			"cc/tracking/Tracker.cc",
			"cc/tracking/MultiTracker.cc",
			"cc/tracking/Trackers/TrackerBoosting.cc",
			"cc/tracking/Trackers/TrackerBoostingParams.cc",
			"cc/tracking/Trackers/TrackerKCF.cc",
			"cc/tracking/Trackers/TrackerKCFParams.cc",
			"cc/tracking/Trackers/TrackerMIL.cc",
			"cc/tracking/Trackers/TrackerMILParams.cc",
			"cc/tracking/Trackers/TrackerMedianFlow.cc",
			"cc/tracking/Trackers/TrackerTLD.cc",
			"cc/tracking/Trackers/TrackerGOTURN.cc",
			"cc/tracking/Trackers/TrackerCSRT.cc",
			"cc/tracking/Trackers/TrackerCSRTParams.cc",
			"cc/tracking/Trackers/TrackerMOSSE.cc",
			"cc/features2d/features2d.cc",
			"cc/features2d/KeyPoint.cc",
			"cc/features2d/KeyPointMatch.cc",
			"cc/features2d/DescriptorMatch.cc",
			"cc/features2d/BFMatcher.cc",
			"cc/features2d/FeatureDetector.cc",
			"cc/features2d/descriptorMatching.cc",
			"cc/features2d/descriptorMatchingKnn.cc",
			"cc/features2d/detectors/AGASTDetector.cc",
			"cc/features2d/detectors/AKAZEDetector.cc",
			"cc/features2d/detectors/BRISKDetector.cc",
			"cc/features2d/detectors/FASTDetector.cc",
			"cc/features2d/detectors/GFTTDetector.cc",
			"cc/features2d/detectors/KAZEDetector.cc",
			"cc/features2d/detectors/MSERDetector.cc",
			"cc/features2d/detectors/ORBDetector.cc",
			"cc/features2d/detectors/SimpleBlobDetector.cc",
			"cc/features2d/detectors/SimpleBlobDetectorParams.cc",
			"cc/xfeatures2d/xfeatures2d.cc",
			"cc/xfeatures2d/SIFTDetector.cc",
			"cc/xfeatures2d/SURFDetector.cc"
		],

		"cflags" : [
			"-std=c++11"
		],
		"cflags!" : [
			"-fno-exceptions"
		],
		"cflags_cc!": [
			"-fno-rtti",
			"-fno-exceptions"
		],
		"ldflags" : [
			"-Wl,-rpath,'$$ORIGIN'"
		],
		"xcode_settings": {
			"OTHER_CFLAGS": [
				"-std=c++11",
				"-stdlib=libc++"
			],
			"GCC_ENABLE_CPP_EXCEPTIONS": "YES",
			"MACOSX_DEPLOYMENT_TARGET": "10.9"
		},

		"conditions": [
			[ "OS==\"win\"", {
				"cflags": [
					"-Wall"
				],
				"defines": [
					"WIN",
					"_HAS_EXCEPTIONS=1"
				],
				"msvs_settings": {
					"VCCLCompilerTool": {
						"ExceptionHandling": "2",
						"RuntimeLibrary": "2"
					},
				}
			}],
	        ["OS==\"mac\"",
	          {
	            "link_settings": {
	              "libraries": [
					"-Wl,-rpath,@loader_path/../../../opencv-build/opencv/build/lib"
	              ],
	            }
	          }
	        ]
		],

		"configurations": {
			"Debug": {
				"cflags": ["--coverage"],
				"ldflags": ["--coverage"]
			},
    }

	}]
}
