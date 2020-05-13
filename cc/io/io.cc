#include "opencv_modules.h"

#ifdef HAVE_IO

#include "io.h"
#include "ioBindings.h"
#include "ioConstants.h"

NAN_MODULE_INIT(Io::Init) {
  IoConstants::Init(target);
  VideoCapture::Init(target);
  VideoWriter::Init(target);

  Nan::SetMethod(target, "imread", Imread);
  Nan::SetMethod(target, "imshow", Imshow);
  Nan::SetMethod(target, "imshowWait", ImshowWait);
  Nan::SetMethod(target, "imwrite", Imwrite);
  Nan::SetMethod(target, "waitKey", WaitKey);
#if CV_VERSION_GREATER_EQUAL(3, 2, 0)
  Nan::SetMethod(target, "waitKeyEx", WaitKeyEx);
#endif
  Nan::SetMethod(target, "imencode", Imencode);
  Nan::SetMethod(target, "imdecode", Imdecode);
  Nan::SetMethod(target, "moveWindow", MoveWindow);
  Nan::SetMethod(target, "destroyWindow", DestroyWindow);
  Nan::SetMethod(target, "destroyAllWindows", DestroyAllWindows);

  Nan::SetMethod(target, "imreadAsync", ImreadAsync);
  Nan::SetMethod(target, "imwriteAsync", ImwriteAsync);
  Nan::SetMethod(target, "imencodeAsync", ImencodeAsync);
  Nan::SetMethod(target, "imdecodeAsync", ImdecodeAsync);

  FF_SET_JS_PROP(target, IMREAD_UNCHANGED, Nan::New<v8::Integer>(cv::IMREAD_UNCHANGED));
  FF_SET_JS_PROP(target, IMREAD_GRAYSCALE, Nan::New<v8::Integer>(cv::IMREAD_GRAYSCALE));
  FF_SET_JS_PROP(target, IMREAD_COLOR, Nan::New<v8::Integer>(cv::IMREAD_COLOR));
  FF_SET_JS_PROP(target, IMREAD_ANYDEPTH, Nan::New<v8::Integer>(cv::IMREAD_ANYDEPTH));
  FF_SET_JS_PROP(target, IMREAD_ANYCOLOR, Nan::New<v8::Integer>(cv::IMREAD_ANYCOLOR));
  FF_SET_JS_PROP(target, IMREAD_LOAD_GDAL, Nan::New<v8::Integer>(cv::IMREAD_LOAD_GDAL));

  FF_SET_JS_PROP(target, IMWRITE_JPEG_QUALITY, Nan::New<v8::Integer>(cv::IMWRITE_JPEG_QUALITY));
  FF_SET_JS_PROP(target, IMWRITE_JPEG_PROGRESSIVE, Nan::New<v8::Integer>(cv::IMWRITE_JPEG_PROGRESSIVE));
  FF_SET_JS_PROP(target, IMWRITE_JPEG_OPTIMIZE, Nan::New<v8::Integer>(cv::IMWRITE_JPEG_OPTIMIZE));
  FF_SET_JS_PROP(target, IMWRITE_JPEG_RST_INTERVAL, Nan::New<v8::Integer>(cv::IMWRITE_JPEG_RST_INTERVAL));
  FF_SET_JS_PROP(target, IMWRITE_JPEG_LUMA_QUALITY, Nan::New<v8::Integer>(cv::IMWRITE_JPEG_LUMA_QUALITY));
  FF_SET_JS_PROP(target, IMWRITE_JPEG_CHROMA_QUALITY, Nan::New<v8::Integer>(cv::IMWRITE_JPEG_CHROMA_QUALITY));
  FF_SET_JS_PROP(target, IMWRITE_PNG_COMPRESSION, Nan::New<v8::Integer>(cv::IMWRITE_PNG_COMPRESSION));
  FF_SET_JS_PROP(target, IMWRITE_PNG_STRATEGY, Nan::New<v8::Integer>(cv::IMWRITE_PNG_STRATEGY));
  FF_SET_JS_PROP(target, IMWRITE_PNG_BILEVEL, Nan::New<v8::Integer>(cv::IMWRITE_PNG_BILEVEL));
  FF_SET_JS_PROP(target, IMWRITE_PXM_BINARY, Nan::New<v8::Integer>(cv::IMWRITE_PXM_BINARY));
  FF_SET_JS_PROP(target, IMWRITE_WEBP_QUALITY, Nan::New<v8::Integer>(cv::IMWRITE_WEBP_QUALITY));

#if CV_VERSION_GREATER_EQUAL(3, 1, 0)
  FF_SET_JS_PROP(target, IMREAD_REDUCED_GRAYSCALE_2, Nan::New<v8::Integer>(cv::IMREAD_REDUCED_GRAYSCALE_2));
  FF_SET_JS_PROP(target, IMREAD_REDUCED_COLOR_2, Nan::New<v8::Integer>(cv::IMREAD_REDUCED_COLOR_2));
  FF_SET_JS_PROP(target, IMREAD_REDUCED_GRAYSCALE_4, Nan::New<v8::Integer>(cv::IMREAD_REDUCED_GRAYSCALE_4));
  FF_SET_JS_PROP(target, IMREAD_REDUCED_COLOR_4, Nan::New<v8::Integer>(cv::IMREAD_REDUCED_COLOR_4));
  FF_SET_JS_PROP(target, IMREAD_REDUCED_GRAYSCALE_8, Nan::New<v8::Integer>(cv::IMREAD_REDUCED_GRAYSCALE_8));
  FF_SET_JS_PROP(target, IMREAD_REDUCED_COLOR_8, Nan::New<v8::Integer>(cv::IMREAD_REDUCED_COLOR_8));
#endif
#if CV_VERSION_GREATER_EQUAL(3, 2, 0)
  FF_SET_JS_PROP(target, IMREAD_IGNORE_ORIENTATION, Nan::New<v8::Integer>(cv::IMREAD_IGNORE_ORIENTATION));
  FF_SET_JS_PROP(target, IMWRITE_PAM_TUPLETYPE, Nan::New<v8::Integer>(cv::IMWRITE_PAM_TUPLETYPE));

  FF_SET_JS_PROP(target, IMWRITE_PAM_FORMAT_NULL, Nan::New<v8::Integer>(cv::IMWRITE_PAM_FORMAT_NULL));
  FF_SET_JS_PROP(target, IMWRITE_PAM_FORMAT_BLACKANDWHITE, Nan::New<v8::Integer>(cv::IMWRITE_PAM_FORMAT_BLACKANDWHITE));
  FF_SET_JS_PROP(target, IMWRITE_PAM_FORMAT_GRAYSCALE, Nan::New<v8::Integer>(cv::IMWRITE_PAM_FORMAT_GRAYSCALE));
  FF_SET_JS_PROP(target, IMWRITE_PAM_FORMAT_GRAYSCALE_ALPHA, Nan::New<v8::Integer>(cv::IMWRITE_PAM_FORMAT_GRAYSCALE_ALPHA));
  FF_SET_JS_PROP(target, IMWRITE_PAM_FORMAT_RGB, Nan::New<v8::Integer>(cv::IMWRITE_PAM_FORMAT_RGB));
  FF_SET_JS_PROP(target, IMWRITE_PAM_FORMAT_RGB_ALPHA, Nan::New<v8::Integer>(cv::IMWRITE_PAM_FORMAT_RGB_ALPHA));
#endif
  FF_SET_JS_PROP(target, IMWRITE_PNG_STRATEGY_DEFAULT, Nan::New<v8::Integer>(cv::IMWRITE_PNG_STRATEGY_DEFAULT));
  FF_SET_JS_PROP(target, IMWRITE_PNG_STRATEGY_FILTERED, Nan::New<v8::Integer>(cv::IMWRITE_PNG_STRATEGY_FILTERED));
  FF_SET_JS_PROP(target, IMWRITE_PNG_STRATEGY_HUFFMAN_ONLY, Nan::New<v8::Integer>(cv::IMWRITE_PNG_STRATEGY_HUFFMAN_ONLY));
  FF_SET_JS_PROP(target, IMWRITE_PNG_STRATEGY_RLE, Nan::New<v8::Integer>(cv::IMWRITE_PNG_STRATEGY_RLE));
  FF_SET_JS_PROP(target, IMWRITE_PNG_STRATEGY_FIXED, Nan::New<v8::Integer>(cv::IMWRITE_PNG_STRATEGY_FIXED));
};

NAN_METHOD(Io::Imshow) {
  FF::TryCatch tryCatch("Io::Imshow");
  if (!info[0]->IsString()) {
    return tryCatch.throwError("expected arg0 to be the window name");
  }
  if (!Mat::hasInstance(info[1])) {
    return tryCatch.throwError("expected arg1 to be an instance of Mat");
  }
  cv::imshow(FF::StringConverter::unwrapUnchecked(info[0]), Mat::Converter::unwrapUnchecked(info[1]));
}

NAN_METHOD(Io::ImshowWait) {
	FF::TryCatch tryCatch("Io::ImshowWait");
  if (!info[0]->IsString()) {
    return tryCatch.throwError("expected arg0 to be the window name");
  }
  if (!Mat::hasInstance(info[1])) {
    return tryCatch.throwError("expected arg1 to be an instance of Mat");
  }
  cv::imshow(FF::StringConverter::unwrapUnchecked(info[0]), Mat::Converter::unwrapUnchecked(info[1]));
  cv::waitKey();
}

NAN_METHOD(Io::WaitKey) {
  int key;
  if (info[0]->IsNumber()) {
    key = cv::waitKey(info[0]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value());
  } else{
    key = cv::waitKey();
  }
  info.GetReturnValue().Set(Nan::New(key));
}

#if CV_VERSION_GREATER_EQUAL(3, 2, 0)
NAN_METHOD(Io::WaitKeyEx) {
  int key;
  if (info[0]->IsNumber()) {
    key = cv::waitKeyEx(info[0]->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value());
  } else{
    key = cv::waitKeyEx();
  }
  info.GetReturnValue().Set(Nan::New(key));
}
#endif

NAN_METHOD(Io::MoveWindow) {
	FF::TryCatch tryCatch("Io::MoveWindow");
	std::string winName;
	int x, y;
	if (FF::StringConverter::arg(0, &winName, info) || FF::IntConverter::arg(1, &x, info) || FF::IntConverter::arg(2, &y, info)) {
		return tryCatch.reThrow();
	}
	cv::moveWindow(winName, x, y);
}

NAN_METHOD(Io::DestroyWindow) {
	FF::TryCatch tryCatch("Io::DestroyWindow");
	std::string winName;
	if (FF::StringConverter::arg(0, &winName, info)) {
		return tryCatch.reThrow();
	}
  cv::destroyWindow(winName);
}

NAN_METHOD(Io::DestroyAllWindows) {
  cv::destroyAllWindows();
}

NAN_METHOD(Io::Imdecode) {
	FF::TryCatch tryCatch("Io::Imdecode");

  if (!info[0]->IsUint8Array()) {
	return tryCatch.throwError("expected arg 0 to be a Buffer of Uint8 Values");
  }

  int flags = cv::IMREAD_ANYCOLOR;
  if (FF::IntConverter::optArg(1, &flags, info)) {
	  return tryCatch.reThrow();
  }

  char *data = static_cast<char *>(node::Buffer::Data(info[0]->ToObject(Nan::GetCurrentContext()).ToLocalChecked()));
  size_t size = node::Buffer::Length(info[0]->ToObject(Nan::GetCurrentContext()).ToLocalChecked());
  std::vector<uchar> vec(size);
  memcpy(vec.data(), data, size);

  info.GetReturnValue().Set(Mat::Converter::wrap(cv::imdecode(vec, flags)));
}

NAN_METHOD(Io::ImdecodeAsync) {
	FF::TryCatch tryCatch("Io::ImdecodeAsync");

  if (!info[0]->IsUint8Array()) {
    return tryCatch.throwError("expected arg 0 to be a Buffer of Uint8 Values");
  }

  std::shared_ptr<IoBindings::ImdecodeWorker> worker = std::make_shared<IoBindings::ImdecodeWorker>();

  v8::Local<v8::Function> cbFunc;
  if (FF::hasArg(info, 1) && FF::IntConverterImpl::assertType(info[1])) {
	worker->flags = info[1]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value();
	if (!info[2]->IsFunction()) {
		return tryCatch.throwError("expected argument 2 to be of type Function");
	}
	cbFunc = v8::Local<v8::Function>::Cast(info[2]);
  }
  else {
	if (!info[1]->IsFunction()) {
		return tryCatch.throwError("expected argument 1 to be of type Function");
	}
	cbFunc = v8::Local<v8::Function>::Cast(info[1]);
    worker->flags = cv::IMREAD_ANYCOLOR;
  }

  v8::Local<v8::Object> jsBuf = info[0]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
  worker->data = static_cast<char *>(node::Buffer::Data(jsBuf));
  worker->dataSize = node::Buffer::Length(jsBuf);

  Nan::AsyncQueueWorker(new FF::AsyncWorker(
    new Nan::Callback(cbFunc),
    worker
  ));
}

NAN_METHOD(Io::Imread) {
  FF::executeSyncBinding(
    std::make_shared<IoBindings::ImreadWorker>(),
    "Io::Imread",
    info
  );
}

NAN_METHOD(Io::ImreadAsync) {
  FF::executeAsyncBinding(
    std::make_shared<IoBindings::ImreadWorker>(),
    "Io::ImreadAsync",
    info
  );
}

NAN_METHOD(Io::Imwrite) {
  FF::executeSyncBinding(
    std::make_shared<IoBindings::ImwriteWorker>(),
    "Io::Imwrite",
    info
  );
}

NAN_METHOD(Io::ImwriteAsync) {
  FF::executeAsyncBinding(
    std::make_shared<IoBindings::ImwriteWorker>(),
    "Io::ImwriteAsync",
    info
  );
}

NAN_METHOD(Io::Imencode) {
  FF::executeSyncBinding(
    std::make_shared<IoBindings::ImencodeWorker>(),
    "Io::Imencode",
    info
  );
}

NAN_METHOD(Io::ImencodeAsync) {
  FF::executeAsyncBinding(
    std::make_shared<IoBindings::ImencodeWorker>(),
    "Io::ImencodeAsync",
    info
  );
}

#endif
