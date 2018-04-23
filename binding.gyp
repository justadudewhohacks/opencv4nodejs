{
	"targets": [{
		"target_name": "opencv4nodejs",
		"defines": [
			"<!@(node ./lib/defines.js)",
		],
		"include_dirs" : [
			"<!@(node ./lib/includes.js)",
			"cc",
			"cc/core",
			"cc/modules",
			"<!(node -e \"require('nan')\")",
			"<!(node -e \"require('macro-inferno')\")",
			"<!(node -e \"require('native-node-utils')\")"
		],
		"libraries": [
			"<!@(node ./lib/libs.js)"
		],
		"sources": [
			"cc/opencv4nodejs.cc",
			"cc/CustomMatAllocator.cc",
			"cc/ExternalMemTracking.cc",
			"cc/cvTypes/cvTypes.cc",
			"cc/cvTypes/imgprocConstants.cc",
			"cc/cvTypes/photoConstants.cc",
			"cc/cvTypes/videoCaptureProps.cc",
			"cc/core/core.cc",
			"cc/core/Mat.cc",
			"cc/core/MatImgproc.cc",
			"cc/core/MatCalib3d.cc",
			"cc/core/Point.cc",
			"cc/core/Vec.cc",
			"cc/core/Size.cc",
			"cc/core/Rect.cc",
			"cc/core/RotatedRect.cc",
			"cc/core/TermCriteria.cc",
			"cc/modules/io/io.cc",
			"cc/modules/io/VideoCapture.cc",
			"cc/modules/io/VideoWriter.cc",
			"cc/modules/photo/photo.cc",
			"cc/modules/video/video.cc",
			"cc/modules/video/BackgroundSubtractor.cc",
			"cc/modules/video/BackgroundSubtractorMOG2.cc",
			"cc/modules/video/BackgroundSubtractorKNN.cc",
			"cc/modules/calib3d/calib3d.cc",
			"cc/modules/imgproc/imgproc.cc",
			"cc/modules/imgproc/Contour.cc",
			"cc/modules/imgproc/Moments.cc",
			"cc/modules/ximgproc/ximgproc.cc",
			"cc/modules/ximgproc/SuperpixelSEEDS.cc",
			"cc/modules/ximgproc/SuperpixelSLIC.cc",
			"cc/modules/ximgproc/SuperpixelLSC.cc",
			"cc/modules/objdetect/objdetect.cc",
			"cc/modules/objdetect/CascadeClassifier.cc",
			"cc/modules/objdetect/HOGDescriptor.cc",
			"cc/modules/objdetect/DetectionROI.cc",
			"cc/modules/machinelearning/machinelearning.cc",
			"cc/modules/machinelearning/ParamGrid.cc",
			"cc/modules/machinelearning/StatModel.cc",
			"cc/modules/machinelearning/SVM.cc",
			"cc/modules/machinelearning/TrainData.cc",
			"cc/modules/dnn/dnn.cc",
			"cc/modules/dnn/Net.cc",
			"cc/modules/face/face.cc",
			"cc/modules/face/FaceRecognizer.cc",
			"cc/modules/face/EigenFaceRecognizer.cc",
			"cc/modules/face/FisherFaceRecognizer.cc",
			"cc/modules/face/LBPHFaceRecognizer.cc",
			"cc/modules/face/Facemark.cc",
			"cc/modules/face/FacemarkAAM.cc",
			"cc/modules/face/FacemarkAAMData.cc",
			"cc/modules/face/FacemarkAAMParams.cc",
			"cc/modules/face/FacemarkLBF.cc",
			"cc/modules/face/FacemarkLBFParams.cc",
			"cc/modules/text/text.cc",
			"cc/modules/text/OCRHMMClassifier.cc",
			"cc/modules/text/OCRHMMDecoder.cc",
			"cc/modules/tracking/tracking.cc",
			"cc/modules/tracking/Tracker.cc",
			"cc/modules/tracking/MultiTracker.cc",
			"cc/modules/tracking/Trackers/TrackerBoosting.cc",
			"cc/modules/tracking/Trackers/TrackerBoostingParams.cc",
			"cc/modules/tracking/Trackers/TrackerKCF.cc",
			"cc/modules/tracking/Trackers/TrackerKCFParams.cc",
			"cc/modules/tracking/Trackers/TrackerMIL.cc",
			"cc/modules/tracking/Trackers/TrackerMILParams.cc",
			"cc/modules/tracking/Trackers/TrackerMedianFlow.cc",
			"cc/modules/tracking/Trackers/TrackerTLD.cc",
			"cc/modules/tracking/Trackers/TrackerGOTURN.cc",
			"cc/modules/features2d/features2d.cc",
			"cc/modules/features2d/KeyPoint.cc",
			"cc/modules/features2d/KeyPointMatch.cc",
			"cc/modules/features2d/DescriptorMatch.cc",
			"cc/modules/features2d/FeatureDetector.cc",
			"cc/modules/features2d/descriptorMatching.cc",
			"cc/modules/features2d/descriptorMatchingKnn.cc",
			"cc/modules/features2d/detectors/AGASTDetector.cc",
			"cc/modules/features2d/detectors/AKAZEDetector.cc",
			"cc/modules/features2d/detectors/BRISKDetector.cc",
			"cc/modules/features2d/detectors/FASTDetector.cc",
			"cc/modules/features2d/detectors/GFTTDetector.cc",
			"cc/modules/features2d/detectors/KAZEDetector.cc",
			"cc/modules/features2d/detectors/MSERDetector.cc",
			"cc/modules/features2d/detectors/ORBDetector.cc",
			"cc/modules/features2d/detectors/SimpleBlobDetector.cc",
			"cc/modules/features2d/detectors/SimpleBlobDetectorParams.cc",
			"cc/modules/xfeatures2d/xfeatures2d.cc",
			"cc/modules/xfeatures2d/SIFTDetector.cc",
			"cc/modules/xfeatures2d/SURFDetector.cc"
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
			"GCC_ENABLE_CPP_EXCEPTIONS": "YES"
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
