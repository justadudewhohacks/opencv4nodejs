#include "CascadeClassifier.h"
#include "Workers.h"

Nan::Persistent<v8::FunctionTemplate> CascadeClassifier::constructor;

NAN_MODULE_INIT(CascadeClassifier::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(CascadeClassifier::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	constructor.Reset(ctor);
	ctor->SetClassName(FF_NEW_STRING("CascadeClassifier"));
	instanceTemplate->SetInternalFieldCount(1);

	Nan::SetPrototypeMethod(ctor, "detectMultiScale", DetectMultiScale);
	Nan::SetPrototypeMethod(ctor, "detectMultiScaleWithRejectLevels", DetectMultiScaleWithRejectLevels);

	Nan::SetPrototypeMethod(ctor, "detectMultiScaleAsync", DetectMultiScaleAsync);
	Nan::SetPrototypeMethod(ctor, "detectMultiScaleWithRejectLevelsAsync", DetectMultiScaleWithRejectLevelsAsync);

	target->Set(FF_NEW_STRING("CascadeClassifier"), ctor->GetFunction());
};

NAN_METHOD(CascadeClassifier::New) {
	FF_METHOD_CONTEXT("CascadeClassifier::New");

	FF_ARG_STRING(0, std::string xmlFilePath);

	CascadeClassifier* self = new CascadeClassifier();
	self->classifier = cv::CascadeClassifier(xmlFilePath);
	if (self->classifier.empty()) {
		FF_THROW("failed to load cascade.xml file: " + xmlFilePath);
	}
	self->Wrap(info.Holder());
	FF_RETURN(info.Holder());
};

NAN_METHOD(CascadeClassifier::DetectMultiScale) {
	FF_METHOD_CONTEXT("CascadeClassifier::DetectMultiScale");

	FF_ARG_INSTANCE(0, cv::Mat img, Mat::constructor, FF_UNWRAP_MAT_AND_GET);

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(1) && info[1]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[1]->ToObject() : FF_NEW_OBJ();

	FF_GET_NUMBER_IFDEF(optArgs, double scaleFactor, "scaleFactor", 1.1);
	FF_GET_UINT_IFDEF(optArgs, uint minNeighbors, "minNeighbors", 3);
	FF_GET_UINT_IFDEF(optArgs, uint flags, "flags", 0);
	FF_GET_INSTANCE_IFDEF(optArgs, cv::Size2d minSize, "minSize", Size::constructor, FF_UNWRAP_SIZE_AND_GET, Size, cv::Size2d());
	FF_GET_INSTANCE_IFDEF(optArgs, cv::Size2d maxSize, "maxSize", Size::constructor, FF_UNWRAP_SIZE_AND_GET, Size, cv::Size2d());
	if (!hasOptArgsObj) {
		FF_ARG_NUMBER_IFDEF(1, scaleFactor, scaleFactor);
		FF_ARG_UINT_IFDEF(2, minNeighbors, minNeighbors);
		FF_ARG_UINT_IFDEF(3, flags, flags);
		FF_ARG_INSTANCE_IFDEF(4, minSize, Size::constructor, FF_UNWRAP_SIZE_AND_GET, minSize);
		FF_ARG_INSTANCE_IFDEF(5, maxSize, Size::constructor, FF_UNWRAP_SIZE_AND_GET, maxSize);
	}

	std::vector<cv::Rect> objectRects;
	std::vector<int> numDetections;
	FF_UNWRAP(info.This(), CascadeClassifier)->classifier.detectMultiScale(
		img,
		objectRects,
		numDetections,
		scaleFactor,
		(int)minNeighbors,
		(int)flags,
		minSize,
		maxSize
	);

	FF_OBJ ret = FF_NEW_OBJ();
	FF_PACK_ARRAY(jsNumDetections, numDetections);
	FF_ARR jsObjectRects = FF_NEW_ARRAY(objectRects.size());
	for (int i = 0; i < objectRects.size(); i++) {
		FF_OBJ jsObjectRect = FF_NEW_INSTANCE(Rect::constructor);
		FF_UNWRAP(jsObjectRect, Rect)->rect = objectRects.at(i);
		jsObjectRects->Set(i, jsObjectRect);
	}
	Nan::Set(ret, FF_NEW_STRING("numDetections"), jsNumDetections);
	Nan::Set(ret, FF_NEW_STRING("objects"), jsObjectRects);
	FF_RETURN(ret);
}

NAN_METHOD(CascadeClassifier::DetectMultiScaleWithRejectLevels) {
	FF_METHOD_CONTEXT("CascadeClassifier::DetectMultiScaleWithRejectLevels");

	FF_ARG_INSTANCE(0, cv::Mat img, Mat::constructor, FF_UNWRAP_MAT_AND_GET);

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(1) && info[1]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[1]->ToObject() : FF_NEW_OBJ();

	FF_GET_NUMBER_IFDEF(optArgs, double scaleFactor, "scaleFactor", 1.1);
	FF_GET_UINT_IFDEF(optArgs, uint minNeighbors, "minNeighbors", 3);
	FF_GET_UINT_IFDEF(optArgs, uint flags, "flags", 0);
	FF_GET_INSTANCE_IFDEF(optArgs, cv::Size2d minSize, "minSize", Size::constructor, FF_UNWRAP_SIZE_AND_GET, Size, cv::Size2d());
	FF_GET_INSTANCE_IFDEF(optArgs, cv::Size2d maxSize, "maxSize", Size::constructor, FF_UNWRAP_SIZE_AND_GET, Size, cv::Size2d());
	if (!hasOptArgsObj) {
		FF_ARG_NUMBER_IFDEF(1, scaleFactor, scaleFactor);
		FF_ARG_UINT_IFDEF(2, minNeighbors, minNeighbors);
		FF_ARG_UINT_IFDEF(3, flags, flags);
		FF_ARG_INSTANCE_IFDEF(4, minSize, Size::constructor, FF_UNWRAP_SIZE_AND_GET, minSize);
		FF_ARG_INSTANCE_IFDEF(5, maxSize, Size::constructor, FF_UNWRAP_SIZE_AND_GET, maxSize);
	}

	std::vector<cv::Rect> objectRects;
	std::vector<int> rejectLevels;
	std::vector<double> levelWeights;
	FF_UNWRAP(info.This(), CascadeClassifier)->classifier.detectMultiScale(
		img,
		objectRects,
		rejectLevels,
		levelWeights,
		scaleFactor,
		(int)minNeighbors,
		(int)flags,
		minSize,
		maxSize,
		true
	);

	FF_OBJ ret = FF_NEW_OBJ();
	FF_PACK_ARRAY(jsRejectLevels, rejectLevels);
	FF_PACK_ARRAY(jsLevelWeights, levelWeights);
	FF_ARR jsObjectRects = FF_NEW_ARRAY(objectRects.size());
	for (int i = 0; i < objectRects.size(); i++) {
		FF_OBJ jsObjectRect = FF_NEW_INSTANCE(Rect::constructor);
		FF_UNWRAP(jsObjectRect, Rect)->rect = objectRects.at(i);
		jsObjectRects->Set(i, jsObjectRect);
	}
	Nan::Set(ret, FF_NEW_STRING("rejectLevels"), jsRejectLevels);
	Nan::Set(ret, FF_NEW_STRING("levelWeights"), jsLevelWeights);
	Nan::Set(ret, FF_NEW_STRING("objects"), jsObjectRects);
	FF_RETURN(ret);
}

NAN_METHOD(CascadeClassifier::DetectMultiScaleAsync) {
	FF_METHOD_CONTEXT("CascadeClassifier::DetectMultiScaleAsync");

	DetectMultiScaleContext ctx;
	FF_ARG_INSTANCE(0, ctx.img, Mat::constructor, FF_UNWRAP_MAT_AND_GET);

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(1) && info[1]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[1]->ToObject() : FF_NEW_OBJ();

	FF_GET_NUMBER_IFDEF(optArgs, ctx.scaleFactor, "scaleFactor", 1.1);
	FF_GET_UINT_IFDEF(optArgs, ctx.minNeighbors, "minNeighbors", 3);
	FF_GET_UINT_IFDEF(optArgs, ctx.flags, "flags", 0);
	FF_GET_INSTANCE_IFDEF(optArgs, ctx.minSize, "minSize", Size::constructor, FF_UNWRAP_SIZE_AND_GET, Size, cv::Size2d());
	FF_GET_INSTANCE_IFDEF(optArgs, ctx.maxSize, "maxSize", Size::constructor, FF_UNWRAP_SIZE_AND_GET, Size, cv::Size2d());
	if (!hasOptArgsObj) {
		FF_ARG_NUMBER_IFDEF(1, ctx.scaleFactor, ctx.scaleFactor);
		FF_ARG_UINT_IFDEF(2, ctx.minNeighbors, ctx.minNeighbors);
		FF_ARG_UINT_IFDEF(3, ctx.flags, ctx.flags);
		FF_ARG_INSTANCE_IFDEF(4, ctx.minSize, Size::constructor, FF_UNWRAP_SIZE_AND_GET, ctx.minSize);
		FF_ARG_INSTANCE_IFDEF(5, ctx.maxSize, Size::constructor, FF_UNWRAP_SIZE_AND_GET, ctx.maxSize);
	}

	ctx.classifier = FF_UNWRAP(info.This(), CascadeClassifier)->classifier;
	FF_ARG_FUNC(info.Length() - 1, v8::Local<v8::Function> cbFunc);

	Nan::AsyncQueueWorker(new GenericAsyncWorker<DetectMultiScaleContext>(
		new Nan::Callback(cbFunc),
		ctx
	));
}

NAN_METHOD(CascadeClassifier::DetectMultiScaleWithRejectLevelsAsync) {
	FF_METHOD_CONTEXT("CascadeClassifier:: DetectMultiScaleWithRejectLevelsAsync");

	DetectMultiScaleWithRejectLevelsContext ctx;
	FF_ARG_INSTANCE(0, ctx.img, Mat::constructor, FF_UNWRAP_MAT_AND_GET);

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(1) && info[1]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[1]->ToObject() : FF_NEW_OBJ();

	FF_GET_NUMBER_IFDEF(optArgs, ctx.scaleFactor, "scaleFactor", 1.1);
	FF_GET_UINT_IFDEF(optArgs, ctx.minNeighbors, "minNeighbors", 3);
	FF_GET_UINT_IFDEF(optArgs, ctx.flags, "flags", 0);
	FF_GET_INSTANCE_IFDEF(optArgs, ctx.minSize, "minSize", Size::constructor, FF_UNWRAP_SIZE_AND_GET, Size, cv::Size2d());
	FF_GET_INSTANCE_IFDEF(optArgs, ctx.maxSize, "maxSize", Size::constructor, FF_UNWRAP_SIZE_AND_GET, Size, cv::Size2d());
	if (!hasOptArgsObj) {
		FF_ARG_NUMBER_IFDEF(1, ctx.scaleFactor, ctx.scaleFactor);
		FF_ARG_UINT_IFDEF(2, ctx.minNeighbors, ctx.minNeighbors);
		FF_ARG_UINT_IFDEF(3, ctx.flags, ctx.flags);
		FF_ARG_INSTANCE_IFDEF(4, ctx.minSize, Size::constructor, FF_UNWRAP_SIZE_AND_GET, ctx.minSize);
		FF_ARG_INSTANCE_IFDEF(5, ctx.maxSize, Size::constructor, FF_UNWRAP_SIZE_AND_GET, ctx.maxSize);
	}

	ctx.classifier = FF_UNWRAP(info.This(), CascadeClassifier)->classifier;
	FF_ARG_FUNC(info.Length() - 1, v8::Local<v8::Function> cbFunc);

	Nan::AsyncQueueWorker(new GenericAsyncWorker< DetectMultiScaleWithRejectLevelsContext>(
		new Nan::Callback(cbFunc),
		ctx
	));
}
