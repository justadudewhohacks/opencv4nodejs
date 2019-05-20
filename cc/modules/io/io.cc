#include "io.h"
#include "ioBindings.h"

NAN_MODULE_INIT(Io::Init) {
  VideoCapture::Init(target);
  VideoWriter::Init(target);

  Nan::SetMethod(target, "imread", Imread);
  Nan::SetMethod(target, "imshow", Imshow);
  Nan::SetMethod(target, "imshowWait", ImshowWait);
  Nan::SetMethod(target, "imwrite", Imwrite);
  Nan::SetMethod(target, "waitKey", WaitKey);
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

#if CV_VERSION_MINOR >= 1
  FF_SET_JS_PROP(target, IMREAD_REDUCED_GRAYSCALE_2, Nan::New<v8::Integer>(cv::IMREAD_REDUCED_GRAYSCALE_2));
  FF_SET_JS_PROP(target, IMREAD_REDUCED_COLOR_2, Nan::New<v8::Integer>(cv::IMREAD_REDUCED_COLOR_2));
  FF_SET_JS_PROP(target, IMREAD_REDUCED_GRAYSCALE_4, Nan::New<v8::Integer>(cv::IMREAD_REDUCED_GRAYSCALE_4));
  FF_SET_JS_PROP(target, IMREAD_REDUCED_COLOR_4, Nan::New<v8::Integer>(cv::IMREAD_REDUCED_COLOR_4));
  FF_SET_JS_PROP(target, IMREAD_REDUCED_GRAYSCALE_8, Nan::New<v8::Integer>(cv::IMREAD_REDUCED_GRAYSCALE_8));
  FF_SET_JS_PROP(target, IMREAD_REDUCED_COLOR_8, Nan::New<v8::Integer>(cv::IMREAD_REDUCED_COLOR_8));
#endif
#if CV_VERSION_MINOR >= 2
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
  FF_METHOD_CONTEXT("Imshow");
  if (!info[0]->IsString()) {
    FF_THROW("expected arg0 to be the window name");
  }
  if (!FF_IS_INSTANCE(Mat::constructor, info[1])) {
    FF_THROW("expected arg1 to be an instance of Mat");
  }
  cv::imshow(FF_CAST_STRING(info[0]), FF_UNWRAP_MAT_AND_GET(info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked()));
}

NAN_METHOD(Io::ImshowWait) {
  FF_METHOD_CONTEXT("ImshowWait");
  if (!info[0]->IsString()) {
    FF_THROW("expected arg0 to be the window name");
  }
  if (!FF_IS_INSTANCE(Mat::constructor, info[1])) {
    FF_THROW("expected arg1 to be an instance of Mat");
  }
  cv::imshow(FF_CAST_STRING(info[0]), FF_UNWRAP_MAT_AND_GET(info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked()));
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

NAN_METHOD(Io::MoveWindow) {
	FF::TryCatch tryCatch;
	std::string winName;
	int x, y;
	if (StringConverter::arg(0, &winName, info) || IntConverter::arg(1, &x, info) || IntConverter::arg(2, &y, info)) {
		v8::Local<v8::Value> err = tryCatch.formatCatchedError("Io::MoveWindow");
		tryCatch.throwNew(err);
		return;
	}
	cv::moveWindow(winName, x, y);
}

NAN_METHOD(Io::DestroyWindow) {
	FF::TryCatch tryCatch;
	std::string winName;
	if (StringConverter::arg(0, &winName, info)) {
		v8::Local<v8::Value> err = tryCatch.formatCatchedError("Io::DestroyWindow");
		tryCatch.throwNew(err);
		return;
	}
  cv::destroyWindow(winName);
}

NAN_METHOD(Io::DestroyAllWindows) {
  cv::destroyAllWindows();
}

NAN_METHOD(Io::Imdecode) {
	FF::TryCatch tryCatch;

  if (!info[0]->IsUint8Array()) {
	tryCatch.throwNew(FF_NEW_STRING("Io::Imdecode - expected arg 0 to be a Buffer of Uint8 Values"));
	return;
  }

  int flags = cv::IMREAD_ANYCOLOR;
  if (IntConverter::optArg(1, &flags, info)) {
	  v8::Local<v8::Value> err = tryCatch.formatCatchedError("Io::Imdecode");
	  tryCatch.throwNew(err);
	  return;
  }

  char *data = static_cast<char *>(node::Buffer::Data(info[0]->ToObject(Nan::GetCurrentContext()).ToLocalChecked()));
  size_t size = node::Buffer::Length(info[0]->ToObject(Nan::GetCurrentContext()).ToLocalChecked());
  std::vector<uchar> vec(size);
  memcpy(vec.data(), data, size);

  v8::Local<v8::Object> jsDecodedMat = FF::newInstance(Nan::New(Mat::constructor));
  FF_UNWRAP_MAT_AND_GET(jsDecodedMat) = cv::imdecode(vec, flags);
  info.GetReturnValue().Set(jsDecodedMat);
}

NAN_METHOD(Io::ImdecodeAsync) {
  FF_METHOD_CONTEXT("ImdecodeAsync");

  if (!info[0]->IsUint8Array()) {
    FF_THROW("expected arg 0 to be a Buffer of Uint8 Values");
  }

  std::shared_ptr<IoBindings::ImdecodeWorker> worker = std::make_shared<IoBindings::ImdecodeWorker>();

  v8::Local<v8::Function> cbFunc;
  if (FF_HAS_ARG(1) && FF_IS_INT(info[1])) {
	worker->flags = info[1]->ToInt32(Nan::GetCurrentContext()).ToLocalChecked()->Value();
	if (!info[2]->IsFunction()) {
		return Nan::ThrowError(Nan::New("Io::ImdecodeAsync - Error: "
			"expected argument 2 to be of type Function")
			.ToLocalChecked());
	}
	cbFunc = v8::Local<v8::Function>::Cast(info[2]);
  }
  else {
	if (!info[1]->IsFunction()) {
		return Nan::ThrowError(Nan::New("Io::ImdecodeAsync - Error: "
			"expected argument 1 to be of type Function")
			.ToLocalChecked());
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
  FF::SyncBinding(
    std::make_shared<IoBindings::ImreadWorker>(),
    "Io::Imread",
    info
  );
}

NAN_METHOD(Io::ImreadAsync) {
  FF::AsyncBinding(
    std::make_shared<IoBindings::ImreadWorker>(),
    "Io::ImreadAsync",
    info
  );
}

NAN_METHOD(Io::Imwrite) {
  FF::SyncBinding(
    std::make_shared<IoBindings::ImwriteWorker>(),
    "Io::Imwrite",
    info
  );
}

NAN_METHOD(Io::ImwriteAsync) {
  FF::AsyncBinding(
    std::make_shared<IoBindings::ImwriteWorker>(),
    "Io::ImwriteAsync",
    info
  );
}

NAN_METHOD(Io::Imencode) {
  FF::SyncBinding(
    std::make_shared<IoBindings::ImencodeWorker>(),
    "Io::Imencode",
    info
  );
}

NAN_METHOD(Io::ImencodeAsync) {
  FF::AsyncBinding(
    std::make_shared<IoBindings::ImencodeWorker>(),
    "Io::ImencodeAsync",
    info
  );
}
