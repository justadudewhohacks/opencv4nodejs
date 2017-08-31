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
			"<!(node -e \"require('nan')\")"
		],
		"libraries": [
			"<!@(node ./lib/libs.js)"
		],
		"sources": [
			"cc/index.cc",
			"cc/cvTypes/cvTypes.cc",
			"cc/cvTypes/imgprocConstants.cc",
			"cc/core/core.cc",
			"cc/core/Mat.cc",
			"cc/core/Point.cc",
			"cc/core/Vec.cc",
			"cc/core/Size.cc",
			"cc/core/Rect.cc",
			"cc/core/RotatedRect.cc",
			"cc/core/Moments.cc",
			"cc/modules/io.cc",
			"cc/modules/VideoCapture.cc",
			"cc/modules/photo.cc",
			"cc/modules/video/video.cc",
			"cc/modules/video/BackgroundSubtractor.cc",
			"cc/modules/video/BackgroundSubtractorMOG2.cc",
			"cc/modules/video/BackgroundSubtractorKNN.cc",
			"cc/modules/calib3d/calib3d.cc",
			"cc/modules/imgproc/imgproc.cc",
			"cc/modules/imgproc/Contour.cc",
			"cc/modules/ximgproc/ximgproc.cc",
			"cc/modules/ximgproc/SuperpixelSEEDS.cc",
			"cc/modules/features2d/features2d.cc",
			"cc/modules/features2d/KeyPoint.cc",
			"cc/modules/features2d/KeyPointMatch.cc",
			"cc/modules/features2d/DescriptorMatch.cc",
			"cc/modules/features2d/FeatureDetector.cc",
			"cc/modules/features2d/descriptorMatching.cc",
			"cc/modules/features2d/detectors/AGASTDetector.cc",
			"cc/modules/features2d/detectors/AKAZEDetector.cc",
			"cc/modules/features2d/detectors/BRISKDetector.cc",
			"cc/modules/features2d/detectors/FASTDetector.cc",
			"cc/modules/features2d/detectors/GFTTDetector.cc",
			"cc/modules/features2d/detectors/KAZEDetector.cc",
			"cc/modules/features2d/detectors/MSERDetector.cc",
			"cc/modules/features2d/detectors/ORBDetector.cc",
			"cc/modules/objdetect/objdetect.cc",
			"cc/modules/objdetect/CascadeClassifier.cc",
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
		"cflags_cc!": [ "-fno-rtti",  "-fno-exceptions"],

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
			}]
		]
	}]
}
