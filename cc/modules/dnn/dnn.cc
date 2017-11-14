#include "opencv2/core.hpp"

#if CV_VERSION_MINOR > 2

// cv 3.3+ should have dnn by default
//#ifdef HAVE_DNN

#include "dnn.h"
#include "Workers.h"
#include "Net.h"
#include "Mat.h"


NAN_MODULE_INIT(Dnn::Init) {
	Net::Init(target);

	Nan::SetMethod(target, "readNetFromTensorflow", ReadNetFromTensorflow);
	Nan::SetMethod(target, "readNetFromTensorflowAsync", ReadNetFromTensorflowAsync);
	Nan::SetMethod(target, "readNetFromCaffe", ReadNetFromCaffe);
	Nan::SetMethod(target, "readNetFromCaffeAsync", ReadNetFromCaffeAsync);
	Nan::SetMethod(target, "blobFromImage", BlobFromImage);
	Nan::SetMethod(target, "blobFromImageAsync", BlobFromImageAsync);
	Nan::SetMethod(target, "blobFromImages", BlobFromImages);
	Nan::SetMethod(target, "blobFromImagesAsync", BlobFromImagesAsync);
};

struct Dnn::ReadNetFromTensorflowWorker : public SimpleWorker {
public:
	std::string modelFile;

	cv::dnn::Net net;

	const char* execute() {
		net = cv::dnn::readNetFromTensorflow(modelFile);
		if (net.empty()) {
			return std::string("failed to load net: " + modelFile).data();
		}
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		return Net::Converter::wrap(net);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			StringConverter::arg(0, &modelFile, info)
		);
	}
};

NAN_METHOD(Dnn::ReadNetFromTensorflow) {
	ReadNetFromTensorflowWorker worker;
	FF_WORKER_SYNC("Dnn::ReadNetFromTensorflow", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Dnn::ReadNetFromTensorflowAsync) {
	ReadNetFromTensorflowWorker worker;
	FF_WORKER_ASYNC("Dnn::ReadNetFromTensorflowAsync", ReadNetFromTensorflowWorker, worker);
}


struct Dnn::ReadNetFromCaffeWorker : public SimpleWorker {
public:
	std::string prototxt;
	std::string modelFile = "";

	cv::dnn::Net net;

	const char* execute() {
		net = cv::dnn::readNetFromCaffe(prototxt, modelFile);
		if (net.empty()) {
			return std::string("failed to prototxt: " + prototxt + ", modelFile: " + modelFile).data();
		}
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		return Net::Converter::wrap(net);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			StringConverter::arg(0, &prototxt, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			StringConverter::optArg(1, &modelFile, info)
		);
	}
};

NAN_METHOD(Dnn::ReadNetFromCaffe) {
	ReadNetFromCaffeWorker worker;
	FF_WORKER_SYNC("Dnn::ReadNetFromCaffe", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Dnn::ReadNetFromCaffeAsync) {
	ReadNetFromCaffeWorker worker;
	FF_WORKER_ASYNC("Dnn::ReadNetFromCaffeAsync", ReadNetFromCaffeWorker, worker);
}


struct Dnn::BlobFromImageWorker : public SimpleWorker {
public:
	bool isSingleImage;
	BlobFromImageWorker(bool isSingleImage = true) {
		this->isSingleImage = isSingleImage;
	}

	cv::Mat image;
	std::vector<cv::Mat> images;
	double scalefactor = 1.0;
	cv::Size2d size = cv::Size2d();
	cv::Vec3d mean = cv::Vec3d();
	bool swapRB = true;

	cv::Mat returnValue;

	const char* execute() {
		if (isSingleImage) {
			returnValue = cv::dnn::blobFromImage(image, scalefactor, size, mean, swapRB);
		}
		else {
			returnValue = cv::dnn::blobFromImages(images, scalefactor, size, mean, swapRB);
		}
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		return Mat::Converter::wrap(returnValue);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			isSingleImage && Mat::Converter::arg(0, &image, info) ||
			!isSingleImage && ObjectArrayConverter<Mat, cv::Mat>::arg(0, &images, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			DoubleConverter::optArg(1, &scalefactor, info) ||
			Size::Converter::optArg(2, &size, info) ||
			Vec3::Converter::optArg(3, &mean, info) ||
			BoolConverter::optArg(4, &swapRB, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(1);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		v8::Local<v8::Object> opts = info[1]->ToObject();
		return (
			DoubleConverter::optProp(&scalefactor, "scalefactor", opts) ||
			BoolConverter::optProp(&swapRB, "swapRB", opts) ||
			Size::Converter::optProp(&size, "size", opts) ||
			Vec3::Converter::optProp(&mean, "mean", opts)
		);
	}
};

NAN_METHOD(Dnn::BlobFromImage) {
	BlobFromImageWorker worker;
	FF_WORKER_SYNC("Dnn::BlobFromImage", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Dnn::BlobFromImageAsync) {
	BlobFromImageWorker worker;
	FF_WORKER_ASYNC("Dnn::BlobFromImageAsync", BlobFromImageWorker, worker);
}

NAN_METHOD(Dnn::BlobFromImages) {
	BlobFromImageWorker worker(false);
	FF_WORKER_SYNC("Dnn::BlobFromImages", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Dnn::BlobFromImagesAsync) {
	BlobFromImageWorker worker(false);
	FF_WORKER_ASYNC("Dnn::BlobFromImagesAsync", BlobFromImageWorker, worker);
}

//#endif

#endif