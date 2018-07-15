#include "Mat.h"
#include "MatImgproc.h"
#include "MatCalib3d.h"
#include "MatBindings.h"

Nan::Persistent<v8::FunctionTemplate> Mat::constructor;

NAN_MODULE_INIT(Mat::Init) {

  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Mat::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("Mat").ToLocalChecked());
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("rows").ToLocalChecked(), Mat::GetRows);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("cols").ToLocalChecked(), Mat::GetCols);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("type").ToLocalChecked(), Mat::GetType);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("channels").ToLocalChecked(), Mat::GetChannels);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("dims").ToLocalChecked(), Mat::GetDims);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("depth").ToLocalChecked(), Mat::GetDepth);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("empty").ToLocalChecked(), Mat::GetIsEmpty);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("sizes").ToLocalChecked(), Mat::GetSizes);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("elemSize").ToLocalChecked(), Mat::GetElemSize);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("step").ToLocalChecked(), Mat::GetStep);

  Nan::SetMethod(ctor, "eye", Eye);
  Nan::SetPrototypeMethod(ctor, "flattenFloat", FlattenFloat);

  Nan::SetPrototypeMethod(ctor, "at", At);
  Nan::SetPrototypeMethod(ctor, "atRaw", AtRaw);
  Nan::SetPrototypeMethod(ctor, "set", Set);
  Nan::SetPrototypeMethod(ctor, "setTo", SetTo);
  Nan::SetPrototypeMethod(ctor, "setToAsync", SetToAsync);
  Nan::SetPrototypeMethod(ctor, "push_back", PushBack);
  Nan::SetPrototypeMethod(ctor, "push_backAsync", PushBackAsync);
  Nan::SetPrototypeMethod(ctor, "pushBack", PushBack);
  Nan::SetPrototypeMethod(ctor, "pushBackAsync", PushBackAsync);
  Nan::SetPrototypeMethod(ctor, "pop_back", PopBack);
  Nan::SetPrototypeMethod(ctor, "pop_backAsync", PopBackAsync);
  Nan::SetPrototypeMethod(ctor, "popBack", PopBack);
  Nan::SetPrototypeMethod(ctor, "popBackAsync", PopBackAsync);
  Nan::SetPrototypeMethod(ctor, "getData", GetData);
  Nan::SetPrototypeMethod(ctor, "getDataAsync", GetDataAsync);
  Nan::SetPrototypeMethod(ctor, "getDataAsArray", GetDataAsArray);
  Nan::SetPrototypeMethod(ctor, "getRegion", GetRegion);
  Nan::SetPrototypeMethod(ctor, "row", Row);
  Nan::SetPrototypeMethod(ctor, "copy", Copy);
  Nan::SetPrototypeMethod(ctor, "copyAsync", CopyAsync);
  Nan::SetPrototypeMethod(ctor, "copyTo", CopyTo);
  Nan::SetPrototypeMethod(ctor, "copyToAsync", CopyToAsync);
  Nan::SetPrototypeMethod(ctor, "convertTo", ConvertTo);
  Nan::SetPrototypeMethod(ctor, "convertToAsync", ConvertToAsync);
  Nan::SetPrototypeMethod(ctor, "norm", Norm);
  Nan::SetPrototypeMethod(ctor, "normalize", Normalize);
  Nan::SetPrototypeMethod(ctor, "split", SplitChannels);
  Nan::SetPrototypeMethod(ctor, "splitAsync", SplitChannelsAsync);
  Nan::SetPrototypeMethod(ctor, "splitChannels", SplitChannels);
  Nan::SetPrototypeMethod(ctor, "splitChannelsAsync", SplitChannelsAsync);
  Nan::SetPrototypeMethod(ctor, "addWeighted", AddWeighted);
  Nan::SetPrototypeMethod(ctor, "addWeightedAsync", AddWeightedAsync);
  Nan::SetPrototypeMethod(ctor, "minMaxLoc", MinMaxLoc);
  Nan::SetPrototypeMethod(ctor, "minMaxLocAsync", MinMaxLocAsync);
  Nan::SetPrototypeMethod(ctor, "findNonZero", FindNonZero);
  Nan::SetPrototypeMethod(ctor, "findNonZeroAsync", FindNonZeroAsync);
  Nan::SetPrototypeMethod(ctor, "countNonZero", CountNonZero);
  Nan::SetPrototypeMethod(ctor, "countNonZeroAsync", CountNonZeroAsync);
  Nan::SetPrototypeMethod(ctor, "padToSquare", PadToSquare);
  Nan::SetPrototypeMethod(ctor, "padToSquareAsync", PadToSquareAsync);
  Nan::SetPrototypeMethod(ctor, "dct", Dct);
  Nan::SetPrototypeMethod(ctor, "dctAsync", DctAsync);
  Nan::SetPrototypeMethod(ctor, "idct", Idct);
  Nan::SetPrototypeMethod(ctor, "idctAsync", IdctAsync);
  Nan::SetPrototypeMethod(ctor, "dft", Dft);
  Nan::SetPrototypeMethod(ctor, "dftAsync", DftAsync);
  Nan::SetPrototypeMethod(ctor, "idft", Idft);
  Nan::SetPrototypeMethod(ctor, "idftAsync", IdftAsync);
  Nan::SetPrototypeMethod(ctor, "mulSpectrums", MulSpectrums);
  Nan::SetPrototypeMethod(ctor, "mulSpectrumsAsync", MulSpectrumsAsync);
  Nan::SetPrototypeMethod(ctor, "transform", Transform);
  Nan::SetPrototypeMethod(ctor, "transformAsync", TransformAsync);
  Nan::SetPrototypeMethod(ctor, "perspectiveTransform", PerspectiveTransform);
  Nan::SetPrototypeMethod(ctor, "perspectiveTransformAsync", PerspectiveTransformAsync);
  Nan::SetPrototypeMethod(ctor, "flip", Flip);
  Nan::SetPrototypeMethod(ctor, "flipAsync", FlipAsync);
  Nan::SetPrototypeMethod(ctor, "convertScaleAbs", ConvertScaleAbs);
  Nan::SetPrototypeMethod(ctor, "convertScaleAbsAsync", ConvertScaleAbsAsync);
  Nan::SetPrototypeMethod(ctor, "sum", Sum);
  Nan::SetPrototypeMethod(ctor, "sumAsync", SumAsync);
  Nan::SetPrototypeMethod(ctor, "goodFeaturesToTrack", GoodFeaturesToTrack);
  Nan::SetPrototypeMethod(ctor, "goodFeaturesToTrackAsync", GoodFeaturesToTrackAsync);
  Nan::SetPrototypeMethod(ctor, "mean", Mean);
  Nan::SetPrototypeMethod(ctor, "meanAsync", MeanAsync);
  Nan::SetPrototypeMethod(ctor, "meanStdDev", MeanStdDev);
  Nan::SetPrototypeMethod(ctor, "meanStdDevAsync", MeanStdDevAsync);
  Nan::SetPrototypeMethod(ctor, "copyMakeBorder", CopyMakeBorder);
  Nan::SetPrototypeMethod(ctor, "copyMakeBorderAsync", CopyMakeBorderAsync);
  Nan::SetPrototypeMethod(ctor, "reduce", Reduce);
  Nan::SetPrototypeMethod(ctor, "reduceAsync", ReduceAsync);
#if CV_VERSION_MINOR > 1
  Nan::SetPrototypeMethod(ctor, "rotate", Rotate);
  Nan::SetPrototypeMethod(ctor, "rotateAsync", RotateAsync);
#endif

  Nan::SetPrototypeMethod(ctor, "release", Release);

  FF_PROTO_SET_MAT_OPERATIONS(ctor);

  MatImgproc::Init(ctor);
  MatCalib3d::Init(ctor);

  target->Set(Nan::New("Mat").ToLocalChecked(), ctor->GetFunction());
};

void Mat::setNativeProps(cv::Mat mat) {
  this->mat = mat;
};

NAN_METHOD(Mat::New) {
  Mat* self = new Mat();
  /* from channels */
  if (info.Length() == 1 && info[0]->IsArray()) {
    FF_ARR jsChannelMats = FF_ARR::Cast(info[0]);
    std::vector<cv::Mat> channels;
    for (int i = 0; i < jsChannelMats->Length(); i++) {
      FF_OBJ jsChannelMat = FF_CAST_OBJ(jsChannelMats->Get(i));
      FF_REQUIRE_INSTANCE(constructor, jsChannelMat,
        FF_NEW_STRING("expected channel " + std::to_string(i) + " to be an instance of Mat"));
      cv::Mat channelMat = FF_UNWRAP_MAT_AND_GET(jsChannelMat);
      channels.push_back(channelMat);
      if (i > 0) {
		if (channels.at(i - 1).rows != channelMat.rows) {
			return Nan::ThrowError(FF_NEW_STRING("Mat::New - rows mismatch "
				+ std::to_string(channels.at(i - 1).rows) + ", have " + std::to_string(channelMat.rows)
				+ " at channel " + std::to_string(i)));
		}
		if (channels.at(i - 1).cols != channelMat.cols) {
			return Nan::ThrowError(FF_NEW_STRING("Mat::New - cols mismatch "
				+ std::to_string(channels.at(i - 1).cols) + ", have " + std::to_string(channelMat.rows)
				+ " at channel " + std::to_string(i)));
		}
      }
    }
    cv::Mat mat;
    cv::merge(channels, mat);
    self->setNativeProps(mat);
  }
  /* data array, type */
  else if (info.Length() == 2 && info[0]->IsArray() && info[1]->IsInt32()) {
    FF_ARR rowArray = FF_ARR::Cast(info[0]);
    int type = info[1]->Int32Value();

    int numCols = -1;
    for (uint i = 0; i < rowArray->Length(); i++) {
      if (!rowArray->Get(i)->IsArray()) {
        return Nan::ThrowError(Nan::New("Mat::New - Column should be an array, at column: " + std::to_string(i)).ToLocalChecked());
      }
      FF_ARR colArray = FF_ARR::Cast(rowArray->Get(i));
      if (numCols != -1 && numCols != colArray->Length()) {
        return Nan::ThrowError(Nan::New("Mat::New - Mat cols must be of uniform length, at column: " + std::to_string(i)).ToLocalChecked());
      }
      numCols = colArray->Length();
    }

    cv::Mat mat = cv::Mat(rowArray->Length(), numCols, type);
    FF_MAT_APPLY_TYPED_OPERATOR(mat, rowArray, type, FF_MAT_FROM_JS_ARRAY, FF::matPut);
    self->setNativeProps(mat);
  }
  /* row, col, type */
  else if (info[0]->IsNumber() && info[1]->IsNumber() && info[2]->IsInt32()) {
    int type = info[2]->Int32Value();
    cv::Mat mat(info[0]->Int32Value(), info[1]->Int32Value(), type);
    /* fill vector */
    // TODO by Vec
    if (info[3]->IsArray()) {
      FF_ARR vec = FF_ARR::Cast(info[3]);
      if (mat.channels() != vec->Length()) {
        return Nan::ThrowError(FF_NEW_STRING(
          std::string("Mat::New - number of channels (") + std::to_string(mat.channels())
          + std::string(") do not match fill vector length ") + std::to_string(vec->Length()))
        );
      }
      FF_MAT_APPLY_TYPED_OPERATOR(mat, vec, type, FF_MAT_FILL, FF::matPut);
    }
    if (info[3]->IsNumber()) {
      FF_MAT_APPLY_TYPED_OPERATOR(mat, info[3], type, FF_MAT_FILL, FF::matPut);
    }
    self->setNativeProps(mat);
  }
  /* raw data, row, col, type */
  else if (info.Length() == 4 && info[1]->IsNumber() && info[2]->IsNumber() && info[3]->IsInt32()) {
    int type = info[3]->Int32Value();
    char *data = static_cast<char *>(node::Buffer::Data(info[0]->ToObject()));
    cv::Mat mat(info[1]->Int32Value(), info[2]->Int32Value(), type);
    size_t size = mat.rows * mat.cols * mat.elemSize();
    memcpy(mat.data, data, size);
    self->setNativeProps(mat);
  }
  self->Wrap(info.Holder());

  // if ExternalMemTracking is disabled, the following instruction will be a no op
    // notes: I *think* New should be called in JS thread where cv::mat has been created async,
    // so a good place to rationalise memory
  ExternalMemTracking::onMatAllocated();

  FF_RETURN(info.Holder());
}

NAN_METHOD(Mat::Eye) {
  FF_METHOD_CONTEXT("Mat::Eye");
  FF_ARG_INT(0, int rows);
  FF_ARG_INT(1, int cols);
  FF_ARG_INT(2, int type);
  FF_OBJ jsEyeMat = FF_NEW_INSTANCE(Mat::constructor);
  FF_UNWRAP_MAT_AND_GET(jsEyeMat) = cv::Mat::eye(cv::Size(cols, rows), type);
  FF_RETURN(jsEyeMat);
}

NAN_METHOD(Mat::FlattenFloat) {
  FF_METHOD_CONTEXT("Mat::To2DFloat");
  FF_ARG_INT(0, int rows);
  FF_ARG_INT(1, int cols);

  cv::Mat matSelf = FF_UNWRAP_MAT_AND_GET(info.This());
  cv::Mat mat2D(rows, cols, CV_32F, matSelf.ptr<float>());
  FF_RETURN(Mat::Converter::wrap(mat2D));
}

NAN_METHOD(Mat::At) {
  FF_METHOD_CONTEXT("Mat::At");
  cv::Mat matSelf = FF_UNWRAP_MAT_AND_GET(info.This());
  FF_ASSERT_INDEX_RANGE(info[0]->Int32Value(), matSelf.size[0] - 1, "Mat::At row");
  FF_ASSERT_INDEX_RANGE(info[1]->Int32Value(), matSelf.size[1] - 1, "Mat::At col");
  v8::Local<v8::Value> val;
  FF_MAT_APPLY_TYPED_OPERATOR(matSelf, val, matSelf.type(), FF_MAT_AT, FF::matGet);
  v8::Local<v8::Value> jsVal;
  if (val->IsArray()) {
    FF_ARR vec = FF_ARR::Cast(val);
    FF_OBJ jsVec;
    if (vec->Length() == 2) {
      jsVec = FF_NEW_INSTANCE(Vec2::constructor);
      FF_UNWRAP_VEC2(jsVec)->vec = cv::Vec2d(vec->Get(0)->NumberValue(), vec->Get(1)->NumberValue());
    }
    else if (vec->Length() == 3) {
      jsVec = FF_NEW_INSTANCE(Vec3::constructor);
      FF_UNWRAP_VEC3(jsVec)->vec = cv::Vec3d(vec->Get(0)->NumberValue(), vec->Get(1)->NumberValue(), vec->Get(2)->NumberValue());
    }
    else {
      jsVec = FF_NEW_INSTANCE(Vec4::constructor);
      FF_UNWRAP_VEC4(jsVec)->vec = cv::Vec4d(vec->Get(0)->NumberValue(), vec->Get(1)->NumberValue(), vec->Get(2)->NumberValue(), vec->Get(3)->NumberValue());
    }
    jsVal = jsVec;
  }
  else {
    jsVal = v8::Local<v8::Value>::Cast(val);
  }
  FF_RETURN(jsVal);
}

NAN_METHOD(Mat::AtRaw) {
  FF_METHOD_CONTEXT("Mat::AtRaw");
  cv::Mat matSelf = FF_UNWRAP_MAT_AND_GET(info.This());
  FF_ASSERT_INDEX_RANGE(info[0]->Int32Value(), matSelf.size[0] - 1, "Mat::At row");
  FF_ASSERT_INDEX_RANGE(info[1]->Int32Value(), matSelf.size[1] - 1, "Mat::At col");
  v8::Local<v8::Value> val;
  FF_MAT_APPLY_TYPED_OPERATOR(matSelf, val, matSelf.type(), FF_MAT_AT, FF::matGet);
  FF_RETURN(val);
}

NAN_METHOD(Mat::Set) {
  FF_METHOD_CONTEXT("Mat::Set");
  cv::Mat matSelf = FF_UNWRAP_MAT_AND_GET(info.This());
  FF_ASSERT_INDEX_RANGE(info[0]->Int32Value(), matSelf.size[0] - 1, "Mat::At row");
  FF_ASSERT_INDEX_RANGE(info[1]->Int32Value(), matSelf.size[1] - 1, "Mat::At col");

  int cn = matSelf.channels();
  if (info[2]->IsArray()) {
    FF_ARR vec = FF_ARR::Cast(info[2]);
    FF_ASSERT_CHANNELS(cn, vec->Length(), "Mat::Set");
    FF_MAT_APPLY_TYPED_OPERATOR(matSelf, vec, matSelf.type(), FF_MAT_SET, FF::matPut);
  }
  else if (FF_IS_INSTANCE(Vec2::constructor, info[2])) {
    FF_ASSERT_CHANNELS(cn, 2, "Mat::Set");
    FF_MAT_APPLY_TYPED_OPERATOR(matSelf, FF::vecToJsArr<2>(FF_UNWRAP_VEC2_AND_GET(info[2]->ToObject())), matSelf.type(), FF_MAT_SET, FF::matPut);
  }
  else if (FF_IS_INSTANCE(Vec3::constructor, info[2])) {
    FF_ASSERT_CHANNELS(cn, 3, "Mat::Set");
    FF_MAT_APPLY_TYPED_OPERATOR(matSelf, FF::vecToJsArr<3>(FF_UNWRAP_VEC3_AND_GET(info[2]->ToObject())), matSelf.type(), FF_MAT_SET, FF::matPut);
  }
  else if (FF_IS_INSTANCE(Vec4::constructor, info[2])) {
    FF_ASSERT_CHANNELS(cn, 4, "Mat::Set");
    FF_MAT_APPLY_TYPED_OPERATOR(matSelf, FF::vecToJsArr<4>(FF_UNWRAP_VEC4_AND_GET(info[2]->ToObject())), matSelf.type(), FF_MAT_SET, FF::matPut);
  }
  else if (info[2]->IsNumber()) {
    FF_MAT_APPLY_TYPED_OPERATOR(matSelf, info[2], matSelf.type(), FF_MAT_SET, FF::matPut);
  }
  else {
    return Nan::ThrowError(FF_NEW_STRING("Mat::Set - unexpected argument 2"));
  }
}

NAN_METHOD(Mat::SetTo) {
  FF::SyncBinding(
    std::make_shared<MatBindings::SetToWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::SetTo",
    info
  );
}

NAN_METHOD(Mat::SetToAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::SetToWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::SetToAsync",
    info
  );
}

NAN_METHOD(Mat::GetDataAsArray) {
  cv::Mat mat = FF_UNWRAP_MAT_AND_GET(info.This());
  FF_ARR rowArray = FF_NEW_ARRAY(mat.size[0]);
  if (mat.dims > 2) { // 3D
    FF_MAT_APPLY_TYPED_OPERATOR(mat, rowArray, mat.type(), FF_JS_ARRAY_FROM_MAT_3D, FF::matGet);
  } else { // 2D
    FF_MAT_APPLY_TYPED_OPERATOR(mat, rowArray, mat.type(), FF_JS_ARRAY_FROM_MAT, FF::matGet);
  }
  FF_RETURN(rowArray);
}

NAN_METHOD(Mat::GetRegion) {
  if (!FF_IS_INSTANCE(Rect::constructor, info[0])) {
    Nan::ThrowError("Mat::GetRegion expected arg0 to be an instance of Rect");
  }
  cv::Rect2d rect = FF_UNWRAP(info[0]->ToObject(), Rect)->rect;
  FF_OBJ jsRegion = FF_NEW_INSTANCE(constructor);
  FF_UNWRAP_MAT_AND_GET(jsRegion) = FF_UNWRAP_MAT_AND_GET(info.This())(rect);
  FF_RETURN(jsRegion);
}

NAN_METHOD(Mat::Norm) {
  FF_METHOD_CONTEXT("Mat::Norm");

  bool withSrc2 = FF_HAS_ARG(0) && FF_IS_INSTANCE(Mat::constructor, info[0]);
  uint i = withSrc2 ? 1 : 0;
  double norm;

  // optional args
  bool hasOptArgsObj = FF_HAS_ARG(i) && info[i]->IsObject();
  FF_OBJ optArgs = hasOptArgsObj ? info[i]->ToObject() : FF_NEW_OBJ();
  FF_GET_UINT_IFDEF(optArgs, uint normType, "normType", cv::NORM_L2);
  FF_GET_INSTANCE_IFDEF(optArgs, cv::Mat mask, "mask", Mat::constructor, FF_UNWRAP_MAT_AND_GET, Mat, cv::noArray().getMat());
  if (!hasOptArgsObj) {
    FF_ARG_UINT_IFDEF(i, normType, normType);
    FF_ARG_INSTANCE_IFDEF(i + 1, mask, Mat::constructor, FF_UNWRAP_MAT_AND_GET, mask);
  }

  if (withSrc2) {
    FF_ARG_INSTANCE(0, cv::Mat src2, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
    norm = cv::norm(FF_UNWRAP_MAT_AND_GET(info.This()), src2, (int)normType, mask);
  }
  else {
    norm = cv::norm(FF_UNWRAP_MAT_AND_GET(info.This()), (int)normType, mask);
  }
  FF_RETURN(norm);
}

NAN_METHOD(Mat::Normalize) {
  FF_METHOD_CONTEXT("Mat::Normalize");

  // optional args
  bool hasOptArgsObj = FF_HAS_ARG(0) && info[0]->IsObject();
  FF_OBJ optArgs = hasOptArgsObj ? info[0]->ToObject() : FF_NEW_OBJ();
  FF_GET_NUMBER_IFDEF(optArgs, double alpha, "alpha", 1.0);
  FF_GET_NUMBER_IFDEF(optArgs, double beta, "beta", 0.0);
  FF_GET_UINT_IFDEF(optArgs, uint normType, "normType", cv::NORM_L2);
  FF_GET_UINT_IFDEF(optArgs, int dtype, "dtype", -1);
  FF_GET_INSTANCE_IFDEF(optArgs, cv::Mat mask, "mask", Mat::constructor, FF_UNWRAP_MAT_AND_GET, Mat, cv::noArray().getMat());
  if (!hasOptArgsObj) {
    FF_ARG_NUMBER_IFDEF(0, alpha, 1.0);
    FF_ARG_NUMBER_IFDEF(1, beta, 0.0);
    FF_ARG_UINT_IFDEF(2, normType, normType);
    FF_ARG_INT_IFDEF(3, dtype, dtype);
    FF_ARG_INSTANCE_IFDEF(4, mask, Mat::constructor, FF_UNWRAP_MAT_AND_GET, mask);
  }

  FF_OBJ jsMat = FF_NEW_INSTANCE(constructor);
  cv::normalize(FF_UNWRAP_MAT_AND_GET(info.This()), FF_UNWRAP_MAT_AND_GET(jsMat), alpha, beta, normType, dtype, mask);
  FF_RETURN(jsMat);
}

NAN_METHOD(Mat::Row) {
  if (!info[0]->IsNumber()) {
    return Nan::ThrowError("usage: row(int r)");
  }
  int r = (int)info[0]->NumberValue();
  cv::Mat mat = Nan::ObjectWrap::Unwrap<Mat>(info.This())->mat;
  FF_ARR row = FF_NEW_ARRAY(mat.cols);
  try {
    if (mat.type() == CV_32FC1) {
      for (int c = 0;  c < mat.cols; c++) {
        row->Set(c, Nan::New(mat.at<float>(r, c)));
      }
    } else if (mat.type() == CV_8UC1) {
      for (int c = 0;  c < mat.cols; c++) {
        row->Set(c, Nan::New((uint)mat.at<uchar>(r, c)));
      }
    } else if (mat.type() == CV_8UC3) {
      for (int c = 0;  c < mat.cols; c++) {
        cv::Vec3b vec = mat.at<cv::Vec3b>(r, c);
        FF_ARR jsVec = FF_NEW_ARRAY(3);
        for (int i = 0; i < 3; i++) {
          jsVec->Set(i, Nan::New(vec[i]));
        }
        row->Set(c, jsVec);
      }
    } else {
      return Nan::ThrowError(Nan::New("not implemented yet - mat type:" + mat.type()).ToLocalChecked());
    }
  } catch(std::exception &e) {
    return Nan::ThrowError(e.what());
  } catch(...) {
    return Nan::ThrowError("... Exception");
  }
  FF_RETURN(row);
}

NAN_METHOD(Mat::Release) {
    // must get pointer to the original; else we are just getting a COPY and then releasing that!
    cv::Mat *mat = &(Nan::ObjectWrap::Unwrap<Mat>(info.This())->mat);
    mat->release();
}

NAN_METHOD(Mat::PushBack) {
  FF::SyncBinding(
    std::make_shared<MatBindings::PushBackWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::PushBack",
    info
  );
}

NAN_METHOD(Mat::PushBackAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::PushBackWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::PushBackAsync",
    info
  );
}

NAN_METHOD(Mat::PopBack) {
  FF::SyncBinding(
    std::make_shared<MatBindings::PopBackWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::PopBack",
    info
  );
}

NAN_METHOD(Mat::PopBackAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::PopBackWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::PopBackAsync",
    info
  );
}

NAN_METHOD(Mat::GetData) {
  FF::SyncBinding(
    std::make_shared<MatBindings::GetDataWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::GetData",
    info
  );
}

NAN_METHOD(Mat::GetDataAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::GetDataWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::GetDataAsync",
    info
  );
}

NAN_METHOD(Mat::Copy) {
  FF::SyncBinding(
    std::make_shared<MatBindings::CopyWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::Copy",
    info
  );
}

NAN_METHOD(Mat::CopyAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::CopyWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::CopyAsync",
    info
  );
}

NAN_METHOD(Mat::CopyTo) {
  FF::SyncBinding(
    std::make_shared<MatBindings::CopyToWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::CopyTo",
    info
  );
}

NAN_METHOD(Mat::CopyToAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::CopyToWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::CopyToAsync",
    info
  );
}

NAN_METHOD(Mat::ConvertTo) {
  FF::SyncBinding(
    std::make_shared<MatBindings::ConvertToWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::ConvertTo",
    info
  );
}

NAN_METHOD(Mat::ConvertToAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::ConvertToWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::ConvertToAsync",
    info
  );
}

NAN_METHOD(Mat::SplitChannels) {
  FF::SyncBinding(
    std::make_shared<MatBindings::SplitChannelsWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::SplitChannels",
    info
  );
}

NAN_METHOD(Mat::SplitChannelsAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::SplitChannelsWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::SplitChannelsAsync",
    info
  );
}

NAN_METHOD(Mat::AddWeighted) {
  FF::SyncBinding(
    std::make_shared<MatBindings::AddWeightedWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::AddWeighted",
    info
  );
}

NAN_METHOD(Mat::AddWeightedAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::AddWeightedWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::AddWeightedAsync",
    info
  );
}

NAN_METHOD(Mat::MinMaxLoc) {
  FF::SyncBinding(
    std::make_shared<MatBindings::MinMaxLocWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::MinMaxLoc",
    info
  );
}

NAN_METHOD(Mat::MinMaxLocAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::MinMaxLocWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::MinMaxLocAsync",
    info
  );
}

NAN_METHOD(Mat::FindNonZero) {
  FF::SyncBinding(
    std::make_shared<MatBindings::FindNonZeroWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::FindNonZero",
    info
  );
}

NAN_METHOD(Mat::FindNonZeroAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::FindNonZeroWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::FindNonZeroAsync",
    info
  );
}

NAN_METHOD(Mat::CountNonZero) {
  FF::SyncBinding(
    std::make_shared<MatBindings::CountNonZeroWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::CountNonZero",
    info
  );
}

NAN_METHOD(Mat::CountNonZeroAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::CountNonZeroWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::CountNonZeroAsync",
    info
  );
}

NAN_METHOD(Mat::PadToSquare) {
  FF::SyncBinding(
    std::make_shared<MatBindings::PadToSquareWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::PadToSquare",
    info
  );
}

NAN_METHOD(Mat::PadToSquareAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::PadToSquareWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::PadToSquareAsync",
    info
  );
}

NAN_METHOD(Mat::Dct) {
  FF::SyncBinding(
    std::make_shared<MatBindings::DCTWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::Dct",
    info
  );
}

NAN_METHOD(Mat::DctAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::DCTWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::DctAsync",
    info
  );
}

NAN_METHOD(Mat::Idct) {
  FF::SyncBinding(
    std::make_shared<MatBindings::DCTWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::Idct",
    info
  );
}

NAN_METHOD(Mat::IdctAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::DCTWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::IdctAsync",
    info
  );
}

NAN_METHOD(Mat::Dft) {
  FF::SyncBinding(
    std::make_shared<MatBindings::DFTWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::Dft",
    info
  );
}

NAN_METHOD(Mat::DftAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::DFTWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::DftAsync",
    info
  );
}

NAN_METHOD(Mat::Idft) {
  FF::SyncBinding(
    std::make_shared<MatBindings::DFTWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::Idft",
    info
  );
}

NAN_METHOD(Mat::IdftAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::DFTWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::IdftAsync",
    info
  );
}

NAN_METHOD(Mat::MulSpectrums) {
  FF::SyncBinding(
    std::make_shared<MatBindings::MulSpectrumsWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::MulSpectrums",
    info
  );
}

NAN_METHOD(Mat::MulSpectrumsAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::MulSpectrumsWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::MulSpectrumsAsync",
    info
  );
}

NAN_METHOD(Mat::Transform) {
  FF::SyncBinding(
    std::make_shared<MatBindings::TransformWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::Transform",
    info
  );
}

NAN_METHOD(Mat::TransformAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::TransformWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::TransformAsync",
    info
  );
}

NAN_METHOD(Mat::PerspectiveTransform) {
  FF::SyncBinding(
    std::make_shared<MatBindings::PerspectiveTransformWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::PerspectiveTransform",
    info
  );
}

NAN_METHOD(Mat::PerspectiveTransformAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::PerspectiveTransformWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::PerspectiveTransformAsync",
    info
  );
}

NAN_METHOD(Mat::Flip) {
  FF::SyncBinding(
    std::make_shared<MatBindings::FlipWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::Flip",
    info
  );
}

NAN_METHOD(Mat::FlipAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::FlipWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::FlipAsync",
    info
  );
}

NAN_METHOD(Mat::Sum) {
  FF::SyncBinding(
    std::make_shared<MatBindings::SumWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::Sum",
    info
  );
}

NAN_METHOD(Mat::SumAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::SumWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::SumAsync",
    info
  );
}

NAN_METHOD(Mat::ConvertScaleAbs) {
  FF::SyncBinding(
    std::make_shared<MatBindings::ConvertScaleAbsWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::ConvertScaleAbs",
    info
  );
}

NAN_METHOD(Mat::ConvertScaleAbsAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::ConvertScaleAbsWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::ConvertScaleAbsAsync",
    info
  );
}

NAN_METHOD(Mat::GoodFeaturesToTrack) {
  FF::SyncBinding(
    std::make_shared<MatBindings::GoodFeaturesToTrackWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::GoodFeaturesToTrack",
    info
  );
}

NAN_METHOD(Mat::GoodFeaturesToTrackAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::GoodFeaturesToTrackWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::GoodFeaturesToTrackAsync",
    info
  );
}

NAN_METHOD(Mat::Mean) {
	FF::SyncBinding(
		std::make_shared<MatBindings::MeanWorker>(Mat::Converter::unwrap(info.This())),
		"Mat::Mean",
		info
	);
}

NAN_METHOD(Mat::MeanAsync) {
	FF::AsyncBinding(
		std::make_shared<MatBindings::MeanWorker>(Mat::Converter::unwrap(info.This())),
		"Mat::MeanAsync",
		info
	);
}

NAN_METHOD(Mat::MeanStdDev) {
  FF::SyncBinding(
    std::make_shared<MatBindings::MeanStdDevWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::MeanStdDev",
    info
  );
}

NAN_METHOD(Mat::MeanStdDevAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::MeanStdDevWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::MeanStdDevAsync",
    info
  );
}

NAN_METHOD(Mat::CopyMakeBorder) {
	FF::SyncBinding(
		std::make_shared<MatBindings::CopyMakeBorderWorker>(Mat::Converter::unwrap(info.This())),
		"Mat::CopyMakeBorder",
		info
	);
}

NAN_METHOD(Mat::CopyMakeBorderAsync) {
	FF::AsyncBinding(
		std::make_shared<MatBindings::CopyMakeBorderWorker>(Mat::Converter::unwrap(info.This())),
		"Mat::CopyMakeBorderAsync",
		info
	);
}

NAN_METHOD(Mat::Reduce) {
	FF::SyncBinding(
		std::make_shared<MatBindings::ReduceWorker>(Mat::Converter::unwrap(info.This())),
		"Mat::Reduce",
		info
	);
}

NAN_METHOD(Mat::ReduceAsync) {
	FF::AsyncBinding(
		std::make_shared<MatBindings::ReduceWorker>(Mat::Converter::unwrap(info.This())),
		"Mat::ReduceAsync",
		info
	);
}

#if CV_VERSION_MINOR > 1
NAN_METHOD(Mat::Rotate) {
  FF::SyncBinding(
    std::make_shared<MatBindings::RotateWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::Rotate",
    info
  );
}

NAN_METHOD(Mat::RotateAsync) {
  FF::AsyncBinding(
    std::make_shared<MatBindings::RotateWorker>(Mat::Converter::unwrap(info.This())),
    "Mat::RotateAsync",
    info
  );
}
#endif
