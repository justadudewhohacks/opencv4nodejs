#include "coreUtils.h"
#include "matUtils.h"
#include "Vec.h"
#include "Point2.h"
#include "Rect.h"
#include "RotatedRect.h"
#include "CatchCvExceptionWorker.h"
#include "macros.h"
#include "NativeNodeUtils.h"
#include "ExternalMemTracking.h"

#ifndef __FF_MAT_H__
#define __FF_MAT_H__

class Mat : public Nan::ObjectWrap {
public:
	cv::Mat mat;

  static Nan::Persistent<v8::FunctionTemplate> constructor;

	void setNativeProps(cv::Mat);

	cv::Mat* getNativeObjectPtr() { return &mat; }
	cv::Mat getNativeObject() { return mat; }

	typedef InstanceConverter<Mat, cv::Mat> Converter;

	static const char* getClassName() {
		return "Mat";
	}

	static NAN_MODULE_INIT(Init);

	static FF_GETTER(Mat, GetRows, mat.rows);
	static FF_GETTER(Mat, GetCols, mat.cols);
	static FF_GETTER(Mat, GetType, mat.type());
	static FF_GETTER(Mat, GetChannels, mat.channels());
	static FF_GETTER(Mat, GetDims, mat.dims);
	static FF_GETTER(Mat, GetDepth, mat.depth());
	static FF_GETTER(Mat, GetIsEmpty, mat.empty());
	static NAN_GETTER(GetElemSize) {
		info.GetReturnValue().Set((int)Converter::unwrap(info.This()).elemSize());
	};
	static NAN_GETTER(GetStep) {
		info.GetReturnValue().Set((int)Converter::unwrap(info.This()).step.operator size_t());
	};
	static NAN_GETTER(GetSizes) {
		cv::Mat m = Converter::unwrap(info.This());
		std::vector<int> sizes;
		for (int s = 0; s < m.dims; s++) {
			sizes.push_back(m.size[s]);
		}
		info.GetReturnValue().Set(IntArrayConverter::wrap(sizes));
	};

	FF_INIT_MAT_OPERATIONS();
	static NAN_METHOD(Dot) {
		FF_OPERATOR_RET_SCALAR(&cv::Mat::dot, FF_APPLY_CLASS_FUNC, FF_UNWRAP_MAT_AND_GET, Mat);
	}

  static NAN_METHOD(New);
  static NAN_METHOD(Eye);
  static NAN_METHOD(FlattenFloat);
  static NAN_METHOD(At);
  static NAN_METHOD(AtRaw);
  static NAN_METHOD(Set);
  static NAN_METHOD(SetTo);
  static NAN_METHOD(SetToAsync);
  static NAN_METHOD(GetDataAsArray);
  static NAN_METHOD(GetRegion);
  static NAN_METHOD(Norm);
  static NAN_METHOD(Normalize);
  static NAN_METHOD(Row);
  static NAN_METHOD(Release);
  static NAN_METHOD(PushBack);
  static NAN_METHOD(PushBackAsync);
  static NAN_METHOD(PopBack);
  static NAN_METHOD(PopBackAsync);
  static NAN_METHOD(GetData);
  static NAN_METHOD(GetDataAsync);
  static NAN_METHOD(Copy);
  static NAN_METHOD(CopyAsync);
  static NAN_METHOD(CopyTo);
  static NAN_METHOD(CopyToAsync);
  static NAN_METHOD(ConvertTo);
  static NAN_METHOD(ConvertToAsync);
  static NAN_METHOD(SplitChannels);
  static NAN_METHOD(SplitChannelsAsync);
  static NAN_METHOD(AddWeighted);
  static NAN_METHOD(AddWeightedAsync);
  static NAN_METHOD(MinMaxLoc);
  static NAN_METHOD(MinMaxLocAsync);
  static NAN_METHOD(FindNonZero);
  static NAN_METHOD(FindNonZeroAsync);
  static NAN_METHOD(CountNonZero);
  static NAN_METHOD(CountNonZeroAsync);
  static NAN_METHOD(PadToSquare);
  static NAN_METHOD(PadToSquareAsync);
  static NAN_METHOD(Dct);
  static NAN_METHOD(DctAsync);
  static NAN_METHOD(Idct);
  static NAN_METHOD(IdctAsync);
  static NAN_METHOD(Dft);
  static NAN_METHOD(DftAsync);
  static NAN_METHOD(Idft);
  static NAN_METHOD(IdftAsync);
  static NAN_METHOD(MulSpectrums);
  static NAN_METHOD(MulSpectrumsAsync);
  static NAN_METHOD(Transform);
  static NAN_METHOD(TransformAsync);
  static NAN_METHOD(PerspectiveTransform);
  static NAN_METHOD(PerspectiveTransformAsync);
  static NAN_METHOD(Flip);
  static NAN_METHOD(FlipAsync);
  static NAN_METHOD(Sum);
  static NAN_METHOD(SumAsync);
  static NAN_METHOD(ConvertScaleAbs);
  static NAN_METHOD(ConvertScaleAbsAsync);
  static NAN_METHOD(GoodFeaturesToTrack);
  static NAN_METHOD(GoodFeaturesToTrackAsync);
  static NAN_METHOD(Mean);
  static NAN_METHOD(MeanAsync);
  static NAN_METHOD(MeanStdDev);
  static NAN_METHOD(MeanStdDevAsync);
  static NAN_METHOD(CopyMakeBorder);
  static NAN_METHOD(CopyMakeBorderAsync);
  static NAN_METHOD(Reduce);
  static NAN_METHOD(ReduceAsync);
#if CV_VERSION_MINOR > 1
  static NAN_METHOD(Rotate);
  static NAN_METHOD(RotateAsync);
#endif

};

#endif
