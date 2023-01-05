#include "macros.h"
#include "CvBinding.h"
#include <opencv2/xfeatures2d.hpp>
#include "features2d/FeatureDetector.h"

#ifndef __FF_SIFTDETECTOR_H__
#define __FF_SIFTDETECTOR_H__

#if CV_VERSION_GREATER_EQUAL(4, 4, 0)
class SIFTDetector : public FeatureDetector, public FF::ObjectWrapTemplate<SIFTDetector, cv::Ptr<cv::SIFT>> {
#else
class SIFTDetector : public FeatureDetector, public FF::ObjectWrapTemplate<SIFTDetector, cv::Ptr<cv::xfeatures2d::SIFT>> {
#endif
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "SIFTDetector";
	}

	cv::Ptr<cv::FeatureDetector> getDetector(void) {
		return self;
	}

	void Wrap(v8::Local<v8::Object> object) {
		FeatureDetector::Wrap(object);
	}

	int nFeatures;
	int nOctaveLayers;
	double contrastThreshold;
	double edgeThreshold;
	double sigma;

	FF_GETTER_CUSTOM(nFeatures, FF::IntConverter, nFeatures);
	FF_GETTER_CUSTOM(nOctaveLayers, FF::IntConverter, nOctaveLayers);
	FF_GETTER_CUSTOM(contrastThreshold, FF::DoubleConverter, contrastThreshold);
	FF_GETTER_CUSTOM(edgeThreshold, FF::DoubleConverter, edgeThreshold);
	FF_GETTER_CUSTOM(sigma, FF::DoubleConverter, sigma);

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	class Constructor : public ConstructorBase {
	public:
		Constructor(Nan::NAN_METHOD_ARGS_TYPE info) {
			auto nFeatures = opt<FF::IntConverter>("nFeatures", 0);
			auto nOctaveLayers = opt<FF::IntConverter>("nOctaveLayers", 3);
			auto contrastThreshold = opt<FF::DoubleConverter>("contrastThreshold", 0.04);
			auto edgeThreshold = opt<FF::DoubleConverter>("edgeThreshold", 10);
			auto sigma = opt<FF::DoubleConverter>("sigma", 1.6);

			executeBinding = [=]() {
			#if CV_VERSION_GREATER_EQUAL(4, 4, 0)
				return cv::SIFT::create(
			#else
				return cv::xfeatures2d::SIFT::create(
			#endif
					nFeatures->ref(),
					nOctaveLayers->ref(),
					contrastThreshold->ref(),
					edgeThreshold->ref(),
					sigma->ref()
				);
			};

			modifySelf = [=](SIFTDetector* self) {
				self->nFeatures = nFeatures->ref();
				self->nOctaveLayers = nOctaveLayers->ref();
				self->contrastThreshold = contrastThreshold->ref();
				self->edgeThreshold = edgeThreshold->ref();
				self->sigma = sigma->ref();
			};
		};
	};
};

#endif
