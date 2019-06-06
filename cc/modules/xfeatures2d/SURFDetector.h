#include "macros.h"
#include "CvBinding.h"
#include <opencv2/xfeatures2d.hpp>
#include "features2d/FeatureDetector.h"

#ifndef __FF_SURFDETECTOR_H__
#define __FF_SURFDETECTOR_H__

class SURFDetector : public FeatureDetector, public FF::ObjectWrapTemplate<SURFDetector, cv::Ptr<cv::xfeatures2d::SURF>> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "SURFDetector";
	}

	cv::Ptr<cv::FeatureDetector> getDetector(void) {
		return self;
	}

	FF_GETTER_CUSTOM(hessianThreshold, FF::DoubleConverter, self->getHessianThreshold());
	FF_GETTER_CUSTOM(nOctaves, FF::IntConverter, self->getNOctaves());
	FF_GETTER_CUSTOM(nOctaveLayers, FF::IntConverter, self->getNOctaveLayers());
	FF_GETTER_CUSTOM(extended, FF::BoolConverter, self->getExtended());
	FF_GETTER_CUSTOM(upright, FF::BoolConverter, self->getUpright());

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	class NewBinding : public CvBinding {
	public:
		void construct(Nan::NAN_METHOD_ARGS_TYPE info) {
			FF::TryCatch tryCatch("SURFDetector::New");
			FF_ASSERT_CONSTRUCT_CALL();

			auto hessianThreshold = opt<FF::DoubleConverter>("hessianThreshold", 100);
			auto nOctaves = opt<FF::IntConverter>("nOctaves", 4);
			auto nOctaveLayers = opt<FF::DoubleConverter>("nOctaveLayers", 3);
			auto extended = opt<FF::BoolConverter>("extended", false);
			auto upright = opt<FF::BoolConverter>("upright", false);

			if (applyUnwrappers(info)) {
				return tryCatch.reThrow();
			}

			SURFDetector* self = new SURFDetector();
			self->setNativeObject(cv::xfeatures2d::SURF::create(
				hessianThreshold->ref(),
				nOctaves->ref(),
				nOctaveLayers->ref(),
				extended->ref(),
				upright->ref()
			));
			self->Wrap(info.Holder());
			info.GetReturnValue().Set(info.Holder());
		};
	};
};

#endif