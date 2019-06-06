#include "macros.h"
#include "CvBinding.h"
#include <opencv2/xfeatures2d.hpp>
#include "features2d/FeatureDetector.h"

#ifndef __FF_SIFTDETECTOR_H__
#define __FF_SIFTDETECTOR_H__

class SIFTDetector : public FeatureDetector, public FF::ObjectWrapTemplate<SIFTDetector, cv::Ptr<cv::xfeatures2d::SIFT>> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "SIFTDetector";
	}

	cv::Ptr<cv::FeatureDetector> getDetector(void) {
		return self;
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

	class NewBinding : public CvBinding {
	public:
		void construct(Nan::NAN_METHOD_ARGS_TYPE info) {
			FF::TryCatch tryCatch("SIFTDetector::New");
			FF_ASSERT_CONSTRUCT_CALL();

			auto nFeatures = opt<FF::IntConverter>("nFeatures", 0);
			auto nOctaveLayers = opt<FF::IntConverter>("nOctaveLayers", 3);
			auto contrastThreshold = opt<FF::DoubleConverter>("contrastThreshold", 0.04);
			auto edgeThreshold = opt<FF::DoubleConverter>("edgeThreshold", 10);
			auto sigma = opt<FF::DoubleConverter>("sigma", 1.6);

			if (applyUnwrappers(info)) {
				return tryCatch.reThrow();
			}

			SIFTDetector* self = new SIFTDetector();
			self->nFeatures = nFeatures->ref();
			self->nOctaveLayers = nOctaveLayers->ref();
			self->contrastThreshold = contrastThreshold->ref();
			self->edgeThreshold = edgeThreshold->ref();
			self->sigma = sigma->ref();
			self->setNativeObject(cv::xfeatures2d::SIFT::create(
				self->nFeatures,
				self->nOctaveLayers,
				self->contrastThreshold,
				self->edgeThreshold,
				self->sigma
			));
			self->Wrap(info.Holder());
			info.GetReturnValue().Set(info.Holder());
		};
	};
};

#endif