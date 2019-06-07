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

	class DetectorType : public FF::EnumWrap<DetectorType> {
	public:
		typedef cv::FastFeatureDetector::DetectorType Type;

		static const char* getClassName() {
			return "DetectorType";
		}

		static std::vector<Type> getEnumValues() {
			return { Type::TYPE_5_8, Type::TYPE_7_12, Type::TYPE_9_16 };
		}

		static std::vector<char*> getEnumMappings() {
			return { "TYPE_5_8", "TYPE_7_12", "TYPE_9_16" };
		}
	};

	FF_GETTER_CUSTOM(threshold, FF::IntConverter, self->getThreshold());
	FF_GETTER_CUSTOM(nonmaxSuppression, FF::BoolConverter, self->getNonmaxSuppression());
	FF_GETTER_CUSTOM(type, FF::IntConverter, self->getType());

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

	struct NewWorker : public CatchCvExceptionWorker {
	public:

		int threshold = 10;
		bool nonmaxSuppression = true;
		int type = cv::FastFeatureDetector::TYPE_9_16;

		std::string executeCatchCvExceptionWorker() {
			return "";
		}

		bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			return (
				FF::IntConverter::optArg(0, &threshold, info) ||
				FF::BoolConverter::optArg(1, &nonmaxSuppression, info) ||
				FF::IntConverter::optArg(2, &type, info)
				);
		}

		bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
			return FF::isArgObject(info, 0);
		}

		bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
			v8::Local<v8::Object> opts = info[0]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
			return (
				FF::IntConverter::optProp(&threshold, "threshold", opts) ||
				FF::BoolConverter::optProp(&nonmaxSuppression, "nonmaxSuppression", opts) ||
				FF::IntConverter::optProp(&type, "type", opts)
				);
		}
	};
};

#endif