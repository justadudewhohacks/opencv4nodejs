#include "core.h"

#ifndef __FF_COREBINDINGS_H__
#define __FF_COREBINDINGS_H__

namespace CoreBindings {

	struct CartToPolarWorker : public CatchCvExceptionWorker {
	public:
		cv::Mat x;
		cv::Mat y;
		bool angleInDegrees = false;

		cv::Mat magnitude;
		cv::Mat angle;

		std::string executeCatchCvExceptionWorker() {
			cv::cartToPolar(x, y, magnitude, angle, angleInDegrees);
			return "";
		}

		v8::Local<v8::Value> getReturnValue() {
			v8::Local<v8::Object> ret = Nan::New<v8::Object>();
			Nan::Set(ret, Nan::New("magnitude").ToLocalChecked(), Mat::Converter::wrap(magnitude));
			Nan::Set(ret, Nan::New("angle").ToLocalChecked(), Mat::Converter::wrap(angle));
			return ret;
		}

		bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			return (
				Mat::Converter::arg(0, &x, info) ||
				Mat::Converter::arg(1, &y, info)
				);
		}

		bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			return (
				BoolConverter::optArg(2, &angleInDegrees, info)
				);
		}
	};

	struct PolarToCartWorker : public CatchCvExceptionWorker {
	public:
		cv::Mat magnitude;
		cv::Mat angle;
		bool angleInDegrees = false;

		cv::Mat x;
		cv::Mat y;

		std::string executeCatchCvExceptionWorker() {
			cv::polarToCart(magnitude, angle, x, y, angleInDegrees);
			return "";
		}

		v8::Local<v8::Value> getReturnValue() {
			v8::Local<v8::Object> ret = Nan::New<v8::Object>();
			Nan::Set(ret, Nan::New("x").ToLocalChecked(), Mat::Converter::wrap(x));
			Nan::Set(ret, Nan::New("y").ToLocalChecked(), Mat::Converter::wrap(y));
			return ret;
		}

		bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			return (
				Mat::Converter::arg(0, &magnitude, info) ||
				Mat::Converter::arg(1, &angle, info)
				);
		}

		bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			return (
				BoolConverter::optArg(2, &angleInDegrees, info)
				);
		}
	};

}

#endif