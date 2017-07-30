{
	"targets": [{
		"target_name": "opencv4nodejs",
		"include_dirs" : [
			"$(OPENCV_DIR)/include",
			"$(EIGEN_DIR)",
			"C:/Users/user/Documents/dev/cpp/installs/TheiaSfM-0.7/include",
			"C:/Users/user/Documents/dev/cpp/installs/TheiaSfM-0.7/src",
			"C:/Users/user/Documents/dev/cpp/installs/sfm/glog-0.3.5/build/include",
			"C:/Users/user/Documents/dev/cpp/installs/TheiaSfM-0.7/libraries/cereal/include",
			"C:/Users/user/Documents/dev/cpp/installs/sfm/ceres-solver-1.13.0rc1/include",
			"C:/Users/user/Documents/dev/cpp/installs/GL/freeglut-3.0.0/include",
			"C:/Users/user/Documents/dev/cpp/installs/GL/glew-1.13.0/include",
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
			"$(OPENCV_LIB_DIR)/opencv_videostab320.lib",
			"C:/Users/user/Documents/dev/cpp/installs/sfm/glog-0.3.5/build/Release/glog.lib",
			"C:/Users/user/Documents/dev/cpp/installs/sfm/gflags-2.2.1/build-x64/lib/Release/gflags_static.lib",
			"C:/Users/user/Documents/dev/cpp/installs/sfm/ceres-solver-1.13.0rc1/build/lib/Release/ceres.lib",
			"C:/Users/user/Documents/dev/cpp/installs/sfm/suitesparse-win/build/lib/Release/libspqr.lib",
			"C:/Users/user/Documents/dev/cpp/installs/sfm/suitesparse-win/build/lib/Release/libcholmod.lib",
			"C:/Users/user/Documents/dev/cpp/installs/sfm/suitesparse-win/build/lib/Release/libccolamd.lib",
			"C:/Users/user/Documents/dev/cpp/installs/sfm/suitesparse-win/build/lib/Release/libcamd.lib",
			"C:/Users/user/Documents/dev/cpp/installs/sfm/suitesparse-win/build/lib/Release/libcolamd.lib",
			"C:/Users/user/Documents/dev/cpp/installs/sfm/suitesparse-win/build/lib/Release/libamd.lib",
			"C:/Users/user/Documents/dev/cpp/installs/sfm/suitesparse-win/lapack_windows/x64/liblapack.lib",
			"C:/Users/user/Documents/dev/cpp/installs/sfm/suitesparse-win/lapack_windows/x64/libblas.lib",
			"C:/Users/user/Documents/dev/cpp/installs/sfm/suitesparse-win/build/lib/Release/suitesparseconfig.lib",
			"C:/Users/user/Documents/dev/cpp/installs/sfm/suitesparse-win/build/lib/Release/metis.lib",
			"$(THEIA_LIB_DIR)/akaze.lib",
			"$(THEIA_LIB_DIR)/build_reconstruction.lib",
			"$(THEIA_LIB_DIR)/build_1dsfm_reconstruction.lib",
			"$(THEIA_LIB_DIR)/compute_two_view_geometry.lib",
			"$(THEIA_LIB_DIR)/flann_cpp.lib",
			"$(THEIA_LIB_DIR)/flann_cpp_s.lib",
			"$(THEIA_LIB_DIR)/statx.lib",
			"$(THEIA_LIB_DIR)/stlplus3.lib",
			"$(THEIA_LIB_DIR)/visual_sfm.lib",
			"$(THEIA_LIB_DIR)/vlfeat.lib",
			"$(THEIA_LIB_DIR)/theia.lib",
			"C:/Users/user/Documents/dev/cpp/installs/GL/freeglut-3.0.0/lib/x64/freeglut.lib",
			"C:/Users/user/Documents/dev/cpp/installs/GL/glew-1.13.0/lib/Release/x64/glew32.lib"
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
			"cc/modules/xfeatures2d/SURFDetector.cc",
			"cc/modules/sfm/sfm.cc",
			"cc/modules/sfm/RelativePose.cc",
			"cc/modules/sfm/Camera.cc",
			"cc/modules/sfm/WorldPoint.cc"
		],

		"cflags!" : [ "-fno-exceptions"],
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
						"RuntimeLibrary": "2",
						'AdditionalOptions': [
							'/GR',
							'/MD',
							'/EHsc'
						]
					},
				}
			}]
		]
	}]
}
