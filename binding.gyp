{
    "targets": [
        {         
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
                "<!(node -e \"require('nan')\")"
            ],
			"libraries": [
				"$(OPENCV_LIB_DIR)/opencv_core320.lib",
				"$(OPENCV_LIB_DIR)/opencv_highgui320.lib",
				"$(OPENCV_LIB_DIR)/opencv_imgcodecs320.lib",
				"$(OPENCV_LIB_DIR)/opencv_imgproc320.lib",
				"$(OPENCV_LIB_DIR)/opencv_features2d320.lib",
				"$(OPENCV_LIB_DIR)/opencv_xfeatures2d320.lib",
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
				"cc/KeyPoint.cc", 
				"cc/KeyPointMatch.cc",
				"cc/modules/io.cc",
				"cc/modules/features2d.cc", 
				"cc/modules/photo.cc", 
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
        }
    ]
}
