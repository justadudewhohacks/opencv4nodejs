#include "sfm.h"
#include "../../core/Mat.h"
#include "../../KeyPointMatch.h"
#include <iostream>
#include <opencv2/highgui.hpp>

NAN_MODULE_INIT(Sfm::Init) {
  v8::Local<v8::Object> module = Nan::New<v8::Object>();
	Nan::SetMethod(module, "estimateRelativePose", EstimateRelativePose);
  Nan::SetMethod(module, "theiaReconstruction", TheiaReconstruction);
	RelativePose::Init(module);
	Camera::Init(module);
	WorldPoint::Init(module);
  target->Set(Nan::New("sfm").ToLocalChecked(), module);
};

NAN_METHOD(Sfm::EstimateRelativePose) {
	v8::Local<v8::Array> jsMatches = v8::Local<v8::Array>::Cast(info[0]);
	std::vector<theia::FeatureCorrespondence> featureCorresp;
	if (jsMatches->Length() < 5) {
		std::string err = "EstimateRelativePose not enough matches:" + jsMatches->Length();
		std::cout << err << std::endl;
		info.GetReturnValue().Set(Nan::Error(Nan::New(err).ToLocalChecked()));
		return;
	}

	for (uint i = 0; i < jsMatches->Length(); i++) {
		KeyPointMatch* match = Nan::ObjectWrap::Unwrap<KeyPointMatch>(Nan::To<v8::Object>(jsMatches->Get(i)).ToLocalChecked());
		cv::KeyPoint kpFrom = match->getKpFrom()->keyPoint;
		cv::KeyPoint kpTo = match->getKpTo()->keyPoint;
		featureCorresp.push_back(theia::FeatureCorrespondence(
			theia::Feature(Eigen::Vector2d(kpFrom.pt.x, kpFrom.pt.y)),
			theia::Feature(Eigen::Vector2d(kpTo.pt.x, kpTo.pt.y))
		));
	}

	theia::RelativePose relativePose = estimateRelativePose(featureCorresp);

	v8::Local<v8::Object> jsRelativePose = Nan::NewInstance(Nan::New(RelativePose::constructor)->GetFunction()).ToLocalChecked();
	Nan::ObjectWrap::Unwrap<RelativePose>(jsRelativePose)->setNativeProps(relativePose);
	info.GetReturnValue().Set(jsRelativePose);
}

NAN_METHOD(Sfm::TheiaReconstruction) {
	
	if (!info[0]->IsArray() || !info[1]->IsArray() || !info[2]->IsNumber()) {
		return Nan::ThrowError("usage: theiaReconstruction(Track[] tracks, RelativePose[] relativePoses), int focalLength");
	}
	
	// TODO
	int numImages = 1068;
	int imageHeight = 800;
	int imageWidth = 450;

	v8::Local<v8::Array> jsTracks = v8::Local<v8::Array>::Cast(info[0]);
	v8::Local<v8::Array> jsRelativePoses = v8::Local<v8::Array>::Cast(info[1]);
	double focalLength = (double)info[2]->NumberValue();

	theia::Reconstruction* pReconst = new theia::Reconstruction();
	theia::ViewGraph* pViewGraph = new theia::ViewGraph();
	
	// add all views to graph and initialize camera intrinsics
	for (int i = 0; i < numImages; ++i) {
		theia::ViewId viewId = pReconst->AddView("view_" + std::to_string(i));
		theia::CameraIntrinsicsPrior* intrinsics = pReconst->MutableView(viewId)->MutableCameraIntrinsicsPrior();
		intrinsics->focal_length.is_set = true;
		intrinsics->focal_length.value[0] = focalLength;
		intrinsics->image_height = imageHeight;
		intrinsics->image_width = imageWidth;
		intrinsics->aspect_ratio.is_set = true;
		intrinsics->aspect_ratio.value[0] = static_cast<double>(imageWidth) / static_cast<double>(imageHeight);
		intrinsics->principal_point.is_set = true;
		intrinsics->principal_point.value[0] = imageWidth / 2.0;
		intrinsics->principal_point.value[1] = imageHeight / 2.0;
		intrinsics->radial_distortion.is_set = true;
		intrinsics->radial_distortion.value[0] = 0;
		intrinsics->radial_distortion.value[1] = 0;
		intrinsics->skew.is_set = true;
		intrinsics->skew.value[0] = 0;
	}
	
	std::cout << "build tracks" << std::endl;
	// add tracks to reconstruction
	for (uint i = 0; i < jsTracks->Length(); ++i) {
		std::vector<std::pair<theia::ViewId, theia::Feature>> track;
		v8::Local<v8::Array> jsTrack = v8::Local<v8::Array>::Cast(jsTracks->Get(i));
		for (uint ti = 0; ti < jsTrack->Length(); ++ti) {
			
			v8::Local<v8::Object> trackNode = Nan::To<v8::Object>(jsTrack->Get(ti)).ToLocalChecked();
			int imgId = (int)Nan::Get(trackNode, Nan::New("imgId").ToLocalChecked()).ToLocalChecked()->NumberValue();
			theia::ViewId viewId = pReconst->ViewIdFromName("view_" + std::to_string(imgId));
			KeyPoint* kp = Nan::ObjectWrap::Unwrap<KeyPoint>(Nan::To<v8::Object>(Nan::Get(trackNode, Nan::New("kp").ToLocalChecked()).ToLocalChecked()).ToLocalChecked());
			track.push_back(std::pair<theia::ViewId, theia::Feature>(
				viewId, theia::Feature(Eigen::Vector2d(kp->keyPoint.pt.x, kp->keyPoint.pt.y)))
			);
		}
		pReconst->AddTrack(track);
	}
	
	std::cout << "build view graph" << std::endl;
	// two view geometry graph from relative poses
	for (uint i = 0; i < jsRelativePoses->Length(); ++i) {
		v8::Local<v8::Object> jsRelativePose = Nan::To<v8::Object>(jsRelativePoses->Get(i)).ToLocalChecked();
		theia::ViewId viewIdFrom = pReconst->ViewIdFromName("view_" + std::to_string(FF_GET_JS_PROP_INT(jsRelativePose, imgFromId)));
		theia::ViewId viewIdTo = pReconst->ViewIdFromName("view_" + std::to_string(FF_GET_JS_PROP_INT(jsRelativePose, imgToId)));
		RelativePose* relativePose = Nan::ObjectWrap::Unwrap<RelativePose>(FF_GET_JS_PROP_OBJECT(jsRelativePose, relativePose));
		theia::TwoViewInfo twoViewInfo;
		twoViewInfo.focal_length_1 = pReconst->MutableView(viewIdFrom)->MutableCamera()->FocalLength();
		twoViewInfo.focal_length_2 = pReconst->MutableView(viewIdTo)->MutableCamera()->FocalLength();
		twoViewInfo.num_verified_matches = FF_GET_JS_PROP_INT(jsRelativePose, numMatches);
		twoViewInfo.position_2 = relativePose->relativePose.position;
		twoViewInfo.rotation_2 = relativePose->rotationAsAngleAxis;
		pViewGraph->AddEdge(viewIdFrom, viewIdTo, twoViewInfo);
	}

	// build reconstruction
	std::cout << std::endl;
	std::cout << "Building Reconstruction" << std::endl;
	std::cout << "--------------------" << std::endl << std::endl;
	std::cout << "Reconstruction - NumViews: " << std::to_string(pReconst->NumViews()) << std::endl;
	std::cout << "Reconstruction - NumTracks: " << std::to_string(pReconst->NumTracks()) << std::endl;
	std::cout << "Graph - NumEdges: " << std::to_string(pViewGraph->NumEdges()) << std::endl;
	std::cout << "Graph - NumViews: " << std::to_string(pViewGraph->NumViews()) << std::endl << std::endl;

	// TODO pass opts as input arg
	theia::ReconstructionBuilderOptions* opts = new theia::ReconstructionBuilderOptions();
	//opts->max_track_length = 100;
	opts->num_threads = 4;
	opts->min_num_inlier_matches = 5;

	theia::ReconstructionEstimatorOptions reconstruction_estimator_options;
	reconstruction_estimator_options.reconstruction_estimator_type = theia::ReconstructionEstimatorType::GLOBAL;
	reconstruction_estimator_options.num_threads = 8;
	reconstruction_estimator_options.filter_relative_translations_with_1dsfm = true;
	reconstruction_estimator_options.refine_relative_translations_after_rotation_estimation = true;
	reconstruction_estimator_options.min_num_absolute_pose_inliers = 5;
	reconstruction_estimator_options.min_num_two_view_inliers = 7;
	reconstruction_estimator_options.bundle_adjust_tracks = true;
	reconstruction_estimator_options.global_position_estimator_type = theia::GlobalPositionEstimatorType::NONLINEAR;

	reconstruction_estimator_options.num_retriangulation_iterations = 1; 
	//reconstruction_estimator_options.min_triangulation_angle_degrees = 5.0;
	//reconstruction_estimator_options.absolute_pose_reprojection_error_threshold = 24.0;
	//reconstruction_estimator_options.triangulation_max_reprojection_error_in_pixels = 50.0;

	opts->reconstruction_estimator_options = reconstruction_estimator_options;

	theia::ReconstructionBuilder* pReconstBuilder = new theia::ReconstructionBuilder(*opts);

	pReconstBuilder->InitializeReconstructionAndViewGraph(pReconst, pViewGraph);
	std::vector<theia::Reconstruction*>* results = new std::vector<theia::Reconstruction*>();
	pReconstBuilder->BuildReconstruction(results);	
	std::cout << "RESULT" << std::endl;
	std::cout << "total iterations: " << results->size() << std::endl;

	int iteration = 0;
	v8::Local<v8::Array> jsResults = Nan::New<v8::Array>(results->size());
	for (auto result : *results) {
		std::cout << "iteration " << iteration << ":" << std::endl;
		std::cout << "estimated views: " << result->NumViews() << std::endl;
		std::cout << "estimated tracks: " << result->NumTracks() << std::endl;

		v8::Local<v8::Array> jsWorldPoints = Nan::New<v8::Array>(result->NumTracks());
		v8::Local<v8::Array> jsCameras = Nan::New<v8::Array>(result->NumViews());
		int t = 0, v = 0;
		for (auto trackId : result->TrackIds()) {
			theia::Track* track = result->MutableTrack(trackId);
			Eigen::Vector3d point = track->Point().hnormalized();
			Eigen::Vector3d color = track->Color().cast<double>();
			int numObservations = track->NumViews();
			bool isEstimated = result->Track(trackId)->IsEstimated();
			v8::Local<v8::Object> jsWorldPoint = Nan::NewInstance(Nan::New(WorldPoint::constructor)->GetFunction()).ToLocalChecked();
			Nan::ObjectWrap::Unwrap<WorldPoint>(jsWorldPoint)->setNativeProps(point, color, numObservations, isEstimated);
			jsWorldPoints->Set(t++, jsWorldPoint);
		}

		for (auto viewId : result->ViewIds()) {
			theia::Camera* cam = result->MutableView(viewId)->MutableCamera();
			Eigen::Vector3d pos = cam->GetPosition();
			Eigen::Matrix3d rot = cam->GetOrientationAsRotationMatrix();
			Eigen::Vector2d principalPoint(cam->PrincipalPointX(), cam->PrincipalPointY());
			double focalLength = cam->FocalLength();
			int imgWidth = cam->ImageWidth();
			int imgHeight = cam->ImageHeight();
			bool isEstimated = result->View(viewId)->IsEstimated();
			v8::Local<v8::Object> jsCamera = Nan::NewInstance(Nan::New(Camera::constructor)->GetFunction()).ToLocalChecked();
			Nan::ObjectWrap::Unwrap<Camera>(jsCamera)->setNativeProps(
				pos, rot, principalPoint, focalLength, imgWidth, imgHeight, isEstimated
			);
			jsCameras->Set(v++, jsCamera);
		}

		v8::Local<v8::Object> jsResult = Nan::New<v8::Object>();
		Nan::Set(jsResult, Nan::New("worldPoints").ToLocalChecked(), jsWorldPoints);
		Nan::Set(jsResult, Nan::New("cameras").ToLocalChecked(), jsCameras);
		jsResults->Set(iteration++, jsResult);
	}
	info.GetReturnValue().Set(jsResults);

}

theia::RelativePose Sfm::estimateRelativePose(std::vector<theia::FeatureCorrespondence> corresp) {
	theia::RelativePose relativePose;
	theia::RansacParameters ransacParams;
	theia::RansacSummary ransacSummary;
	// TODO params
	ransacParams.max_iterations = 2000;
	ransacParams.error_thresh = 0.01;
	ransacParams.use_mle = true;

	theia::EstimateRelativePose(ransacParams, theia::RansacType::RANSAC, corresp, &relativePose, &ransacSummary);
	return relativePose;
}