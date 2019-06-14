#include "macros.h"
#include "CvBinding.h"
#include "KAZEDetector.h"
#include "../FeatureDetector.h"

#ifndef __FF_AKAZEDETECTOR_H__
#define __FF_AKAZEDETECTOR_H__

class AKAZEDetector : public FeatureDetector, public FF::ObjectWrapTemplate<AKAZEDetector, cv::Ptr<cv::AKAZE>> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "AKAZEDetector";
	}

	cv::Ptr<cv::FeatureDetector> getDetector() {
		return self;
	}

#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
	class DescriptorType : public FF::EnumWrap<DescriptorType> {
	public:
		typedef cv::AKAZE::DescriptorType Type;

		static const char* getClassName() {
			return "AKAZEDescriptorType";
		}

		static std::vector<Type> getEnumValues() {
			return { Type::DESCRIPTOR_KAZE, Type::DESCRIPTOR_KAZE_UPRIGHT, Type::DESCRIPTOR_MLDB, Type::DESCRIPTOR_MLDB_UPRIGHT };
		}

		static std::vector<const char*> getEnumMappings() {
			return { "DESCRIPTOR_KAZE", "DESCRIPTOR_KAZE_UPRIGHT", "DESCRIPTOR_MLDB", "DESCRIPTOR_MLDB_UPRIGHT" };
		}
	};
#endif

#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
	FF_GETTER_CUSTOM(descriptorType, AKAZEDetector::DescriptorType::Converter, self->getDescriptorType());
#else
	FF_GETTER_CUSTOM(descriptorType, FF::IntConverter, self->getDescriptorType());
#endif
	FF_GETTER_CUSTOM(descriptorSize, FF::IntConverter, self->getDescriptorSize());
	FF_GETTER_CUSTOM(descriptorChannels, FF::IntConverter, self->getDescriptorChannels());
	FF_GETTER_CUSTOM(threshold, FF::DoubleConverter, self->getThreshold());
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
			FF::TryCatch tryCatch("AKAZEDetector::New");
			FF_ASSERT_CONSTRUCT_CALL();

#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
			auto descriptorType = opt<AKAZEDetector::DescriptorType::Converter>("descriptorType", cv::AKAZE::DESCRIPTOR_MLDB);
#else
			auto descriptorType = opt<FF::IntConverter>("descriptorType", cv::AKAZE::DESCRIPTOR_MLDB);
#endif
			auto descriptorSize = opt<FF::IntConverter>("descriptorSize", 0);
			auto descriptorChannels = opt<FF::IntConverter>("descriptorChannels", 3);
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

			AKAZEDetector* self = new AKAZEDetector();
			self->setNativeObject(cv::AKAZE::create(
				descriptorType->ref(), 
				descriptorSize->ref(),
				descriptorChannels->ref(),
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