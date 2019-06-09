#include "macros.h"
#include "CvBinding.h"
#include "../FeatureDetector.h"

#ifndef __FF_FASTDETECTOR_H__
#define __FF_FASTDETECTOR_H__

class FASTDetector : public FeatureDetector, public FF::ObjectWrapTemplate<FASTDetector, cv::Ptr<cv::FastFeatureDetector>> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "FASTDetector";
	}

	cv::Ptr<cv::FeatureDetector> getDetector() {
		return self;
	}

#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
	class DetectorType : public FF::EnumWrap<DetectorType> {
	public:
		typedef cv::FastFeatureDetector::DetectorType Type;

		static const char* getClassName() {
			return "FASTDetectorType";
		}

		static std::vector<Type> getEnumValues() {
			return { Type::TYPE_5_8, Type::TYPE_7_12, Type::TYPE_9_16 };
		}

		static std::vector<const char*> getEnumMappings() {
			return { "TYPE_5_8", "TYPE_7_12", "TYPE_9_16" };
		}
	};
#endif

	FF_GETTER_CUSTOM(threshold, FF::IntConverter, self->getThreshold());
	FF_GETTER_CUSTOM(nonmaxSuppression, FF::BoolConverter, self->getNonmaxSuppression());
#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
	FF_GETTER_CUSTOM(type, FASTDetector::DetectorType::Converter, self->getType());
#else
	FF_GETTER_CUSTOM(type, FF::IntConverter, self->getType());
#endif

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	class NewBinding : public CvBinding {
	public:
		void construct(Nan::NAN_METHOD_ARGS_TYPE info) {
			FF::TryCatch tryCatch("FASTDetector::New");
			FF_ASSERT_CONSTRUCT_CALL();

			auto threshold = opt<FF::IntConverter>("threshold", 10);
			auto nonmaxSuppression = opt<FF::BoolConverter>("nonmaxSuppression", true);
#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
			auto type = opt<FASTDetector::DetectorType::Converter>("type", cv::FastFeatureDetector::TYPE_9_16);
#else
			auto type = opt<FF::IntConverter>("type", cv::FastFeatureDetector::TYPE_9_16);
#endif
			if (applyUnwrappers(info)) {
				return tryCatch.reThrow();
			}

			FASTDetector* self = new FASTDetector();
			self->setNativeObject(cv::FastFeatureDetector::create(
				threshold->ref(),
				nonmaxSuppression->ref(),
				type->ref()
			));
			self->Wrap(info.Holder());
			info.GetReturnValue().Set(info.Holder());
		};
	};
};

#endif