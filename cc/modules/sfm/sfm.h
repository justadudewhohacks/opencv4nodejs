#define GLOG_NO_ABBREVIATED_SEVERITIES 1

#include <nan.h>
#include <opencv2/imgproc.hpp>

#include <theia/sfm/view.h>
#include <theia/sfm/view_graph/view_graph.h>
#include <theia/sfm/track.h>
#include <theia/sfm/reconstruction.h>
#include <theia/sfm/reconstruction_builder.h>
#include <theia/matching/feature_correspondence.h>
#include <theia/sfm/estimators/estimate_relative_pose.h>

#include "theia/sfm/camera/camera.h"
#include <theia/sfm/global_reconstruction_estimator.h>
#include <theia/sfm/reconstruction_estimator_utils.h>
#include "theia/math/util.h"

#include "RelativePose.h"
#include "Camera.h"
#include "WorldPoint.h"

class Sfm {
public:
  static NAN_MODULE_INIT(Init);
	static NAN_METHOD(EstimateRelativePose);
  static NAN_METHOD(TheiaReconstruction);

	static theia::RelativePose estimateRelativePose(std::vector<theia::FeatureCorrespondence> corresp);
};
