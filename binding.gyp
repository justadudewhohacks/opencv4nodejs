{
	"targets": [{
		"target_name": "opencv4nodejs",
		"include_dirs" : [
			"$(OPENCV_DIR)/include",
			"cc",
			"cc/core",
			"cc/modules",
			"<!(node -e \"require('nan')\")"
		],
		"libraries": [
			"$(OPENCV_LIB_DIR)/opencv_core320.lib",
			"$(OPENCV_LIB_DIR)/opencv_highgui320.lib",
			"$(OPENCV_LIB_DIR)/opencv_imgcodecs320.lib",
			"$(OPENCV_LIB_DIR)/opencv_imgproc320.lib",
			"$(OPENCV_LIB_DIR)/opencv_ximgproc320.lib",
			"$(OPENCV_LIB_DIR)/opencv_features2d320.lib",
			"$(OPENCV_LIB_DIR)/opencv_xfeatures2d320.lib",
			"$(OPENCV_LIB_DIR)/opencv_calib3d320.lib",
			"$(OPENCV_LIB_DIR)/opencv_photo320.lib",
			"$(OPENCV_LIB_DIR)/opencv_videostab320.lib"
		],
		"sources": [
			"cc/index.cc",
			"cc/core/Mat.cc",
			"cc/core/Point.cc",
			"cc/core/Size.cc",
			"cc/modules/io.cc",
			"cc/modules/photo.cc",
			"cc/modules/calib3d/calib3d.cc",
			"cc/modules/imgproc/imgproc.cc",
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
			"cc/modules/xfeatures2d/xfeatures2d.cc",
			"cc/modules/xfeatures2d/SIFTDetector.cc",
			"cc/modules/xfeatures2d/SURFDetector.cc"
		],

		"cflags" : [
			"-std=c++11",
  		"-stdlib=libc++"
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
