#include "macros.h"
#include "CvBinding.h"
#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>
#include "Size.h"
#include "Mat.h"
#include "Rect.h"
#include "Point.h"
#include "DetectionROI.h"
#include "CatchCvExceptionWorker.h"

#ifndef __FF_HOGDESCRIPTOR_H__
#define __FF_HOGDESCRIPTOR_H__

class HOGDescriptor : public FF::ObjectWrap<HOGDescriptor, std::shared_ptr<cv::HOGDescriptor>> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "HOGDescriptor";
	}

#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
	class HistogramNormType : public FF::EnumWrap<HistogramNormType> {
	public:
		typedef cv::HOGDescriptor::HistogramNormType Type;

		static const char* getClassName() {
			return "HOGHistogramNormType";
		}

		static std::vector<Type> getEnumValues() {
			return { Type::L2Hys };
		}

		static std::vector<const char*> getEnumMappings() {
			return { "L2Hys" };
		}
	};
#endif

	FF_ACCESSORS_PTR(winSize, Size::Converter);
	FF_ACCESSORS_PTR(blockSize, Size::Converter);
	FF_ACCESSORS_PTR(blockStride, Size::Converter);
	FF_ACCESSORS_PTR(cellSize, Size::Converter);
	FF_ACCESSORS_PTR(nbins, FF::IntConverter);
	FF_ACCESSORS_PTR(derivAperture, FF::IntConverter);
	FF_ACCESSORS_PTR(winSigma, FF::DoubleConverter);
#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
	FF_ACCESSORS_PTR(histogramNormType, HistogramNormType::Converter);
#else
	FF_ACCESSORS_PTR(histogramNormType, FF::IntConverter);
#endif
	FF_ACCESSORS_PTR(L2HysThreshold, FF::DoubleConverter);
	FF_ACCESSORS_PTR(gammaCorrection, FF::BoolConverter);
	FF_ACCESSORS_PTR(nlevels, FF::IntConverter);
	FF_ACCESSORS_PTR(signedGradient, FF::BoolConverter);

	static NAN_MODULE_INIT(Init);

	static NAN_METHOD(New);
	static NAN_METHOD(GetDaimlerPeopleDetector);
	static NAN_METHOD(GetDefaultPeopleDetector);
	static NAN_METHOD(CheckDetectorSize);
	static NAN_METHOD(SetSVMDetector);
	static NAN_METHOD(Save);
	static NAN_METHOD(Load);
	static NAN_METHOD(Compute);
	static NAN_METHOD(ComputeAsync);
	static NAN_METHOD(ComputeGradient);
	static NAN_METHOD(ComputeGradientAsync);
	static NAN_METHOD(Detect);
	static NAN_METHOD(DetectAsync);
	static NAN_METHOD(DetectROI);
	static NAN_METHOD(DetectROIAsync);
	static NAN_METHOD(DetectMultiScale);
	static NAN_METHOD(DetectMultiScaleAsync);
	static NAN_METHOD(DetectMultiScaleROI);
	static NAN_METHOD(DetectMultiScaleROIAsync);
	static NAN_METHOD(GroupRectangles);
	static NAN_METHOD(GroupRectanglesAsync);

	class Constructor : public ConstructorBase {
	public:
		Constructor(Nan::NAN_METHOD_ARGS_TYPE info) {
			auto winSize = opt<Size::Converter>("winSize", cv::Size2d(64, 128));
			auto blockSize = opt<Size::Converter>("blockSize", cv::Size2d(16, 16));
			auto blockStride = opt<Size::Converter>("blockStride", cv::Size2d(8, 8));
			auto cellSize = opt<Size::Converter>("cellSize", cv::Size2d(8, 8));
			auto nbins = opt<FF::IntConverter>("nbins", 9);
			auto derivAperture = opt<FF::IntConverter>("derivAperture", 1);
			auto winSigma = opt<FF::DoubleConverter>("winSigma", -1);
#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
			auto histogramNormType = opt<HOGDescriptor::HistogramNormType::Converter>("histogramNormType", cv::HOGDescriptor::L2Hys);
#else
			auto histogramNormType = opt<FF::IntConverter>("histogramNormType", cv::HOGDescriptor::L2Hys);
#endif
			auto L2HysThreshold = opt<FF::DoubleConverter>("L2HysThreshold", 0.2);
			auto gammaCorrection = opt<FF::BoolConverter>("gammaCorrection", false);
			auto nlevels = opt<FF::IntConverter>("nlevels", cv::HOGDescriptor::DEFAULT_NLEVELS);
			auto signedGradient = opt<FF::BoolConverter>("signedGradient", false);

			executeBinding = [=]() {
				return std::make_shared<cv::HOGDescriptor>(
					winSize->ref(),
					blockSize->ref(),
					blockStride->ref(),
					cellSize->ref(),
					nbins->ref(),
					derivAperture->ref(),
					winSigma->ref(),
					histogramNormType->ref(),
					L2HysThreshold->ref(),
					gammaCorrection->ref(),
					nlevels->ref(),
					signedGradient->ref()
				);
			};
		};
	};
};

#endif