#include "macros.h"
#include "CvBinding.h"
#include "../FeatureDetector.h"

#ifndef __FF_AGASTDETECTOR_H__
#define __FF_AGASTDETECTOR_H__

class AGASTDetector : public FeatureDetector, public FF::ObjectWrapTemplate<AGASTDetector, cv::Ptr<cv::AgastFeatureDetector>> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "AGASTDetector";
	}

	cv::Ptr<cv::FeatureDetector> getDetector() {
		return self;
	}

#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
	class DetectorType : public FF::EnumWrap<DetectorType> {
	public:
		typedef cv::AgastFeatureDetector::DetectorType Type;

		static const char* getClassName() {
			return "AGASTDetectorType";
		}

		static std::vector<Type> getEnumValues() {
			return { Type::AGAST_5_8, Type::AGAST_7_12d, Type::AGAST_7_12s, Type::OAST_9_16 };
		}

		static std::vector<const char*> getEnumMappings() {
			return { "AGAST_5_8", "AGAST_7_12d", "AGAST_7_12s", "OAST_9_16" };
		}
	};
#endif

	FF_GETTER_CUSTOM(threshold, FF::DoubleConverter, self->getThreshold());
	FF_GETTER_CUSTOM(nonmaxSuppression, FF::BoolConverter, self->getNonmaxSuppression());
#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
	FF_GETTER_CUSTOM(type, AGASTDetector::DetectorType::Converter, self->getType());
#else
	FF_GETTER_CUSTOM(type, FF::IntConverter, self->getType());
#endif

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	class NewBinding : public CvBinding {
	public:
		void construct(Nan::NAN_METHOD_ARGS_TYPE info) {
			FF::TryCatch tryCatch("AGASTDetector::New");
			FF_ASSERT_CONSTRUCT_CALL();

			auto threshold = opt<FF::IntConverter>("threshold", 10);
			auto nonmaxSuppression = opt<FF::BoolConverter>("nonmaxSuppression", true);
#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
			auto type = opt<AGASTDetector::DetectorType::Converter>("type", cv::AgastFeatureDetector::OAST_9_16);
#else
			auto type = opt<FF::IntConverter>("type", cv::AgastFeatureDetector::OAST_9_16);
#endif
			if (applyUnwrappers(info)) {
				return tryCatch.reThrow();
			}

			AGASTDetector* self = new AGASTDetector();
			self->setNativeObject(cv::AgastFeatureDetector::create(
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