#include "macros.h"
#include "CvBinding.h"
#include "../FeatureDetector.h"

#ifndef __FF_KAZEDETECTOR_H__
#define __FF_KAZEDETECTOR_H__

class KAZEDetector : public FeatureDetector, public FF::ObjectWrapTemplate<KAZEDetector, cv::Ptr<cv::KAZE>> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "KAZEDetector";
	}

	cv::Ptr<cv::FeatureDetector> getDetector() {
		return self;
	}

#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
	class DiffusivityType : public FF::EnumWrap<DiffusivityType> {
	public:
		typedef cv::KAZE::DiffusivityType Type;

		static const char* getClassName() {
			return "KAZEDiffusivityType";
		}

		static std::vector<Type> getEnumValues() {
			return { Type::DIFF_CHARBONNIER, Type::DIFF_PM_G1, Type::DIFF_PM_G2, Type::DIFF_WEICKERT };
		}

		static std::vector<const char*> getEnumMappings() {
			return { "DIFF_CHARBONNIER", "DIFF_PM_G1", "DIFF_PM_G2", "DIFF_WEICKERT" };
		}
	};
#endif

	FF_GETTER_CUSTOM(extended, FF::BoolConverter, self->getExtended());
	FF_GETTER_CUSTOM(upright, FF::BoolConverter, self->getUpright());
	FF_GETTER_CUSTOM(threshold, FF::FloatConverter, self->getThreshold());
	FF_GETTER_CUSTOM(nOctaves, FF::IntConverter, self->getNOctaves());
	FF_GETTER_CUSTOM(nOctaveLayers, FF::IntConverter, self->getNOctaveLayers());
#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
	FF_GETTER_CUSTOM(diffusivity, KAZEDetector::DiffusivityType::Converter, self->getDiffusivity());
#else
	FF_GETTER_CUSTOM(diffusivity, FF::IntConverter, self->getDiffusivity());
#endif

	static NAN_MODULE_INIT(Init); 
	static NAN_METHOD(New);

	class NewBinding : public CvBinding {
	public:
		void construct(Nan::NAN_METHOD_ARGS_TYPE info) {
			FF::TryCatch tryCatch("KAZEDetector::New");
			FF_ASSERT_CONSTRUCT_CALL();
			auto extended = opt<FF::BoolConverter>("extended", false);
			auto upright = opt<FF::BoolConverter>("upright", false);
			auto threshold = opt<FF::DoubleConverter>("threshold", (double)0.001f);
			auto nOctaves = opt<FF::IntConverter>("nOctaves", 4);
			auto nOctaveLayers = opt<FF::IntConverter>("nOctaveLayers", 4);
#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
			auto diffusivity = opt<KAZEDetector::DiffusivityType::Converter>("diffusivity", cv::KAZE::DIFF_PM_G2);
#else
			auto diffusivity = opt<FF::IntConverter>("diffusivity", cv::KAZE::DIFF_PM_G2);
#endif

			if (applyUnwrappers(info)) {
				return tryCatch.reThrow();
			}

			KAZEDetector* self = new KAZEDetector();
			self->setNativeObject(cv::KAZE::create(
				extended->ref(), 
				upright->ref(),
				threshold->ref(),
				nOctaves->ref(),
				nOctaveLayers->ref(),
				diffusivity->ref()
			));
			self->Wrap(info.Holder());
			info.GetReturnValue().Set(info.Holder());
		};
	};
};

#endif