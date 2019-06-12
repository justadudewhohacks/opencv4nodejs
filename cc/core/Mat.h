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

class Mat : public FF::ObjectWrap<Mat, cv::Mat> {
public:
	static Nan::Persistent<v8::FunctionTemplate> constructor;

	static const char* getClassName() {
		return "Mat";
	}

	static NAN_MODULE_INIT(Init);

	FF_GETTER(rows, FF::IntConverter);
	FF_GETTER(cols, FF::IntConverter);
	FF_GETTER_CUSTOM(type, FF::IntConverter, self.type());
	FF_GETTER_CUSTOM(channels, FF::IntConverter, self.channels());
	FF_GETTER_CUSTOM(dims, FF::IntConverter, self.dims);
	FF_GETTER_CUSTOM(depth, FF::IntConverter, self.depth());
	FF_GETTER_CUSTOM(empty, FF::IntConverter, self.empty());

	static NAN_GETTER(GetElemSize) {
		info.GetReturnValue().Set((int)Mat::unwrapSelf(info).elemSize());
	};
	static NAN_GETTER(GetStep) {
		info.GetReturnValue().Set((int)Mat::unwrapSelf(info).step.operator size_t());
	};
	static NAN_GETTER(GetSizes) {
		cv::Mat m = Mat::unwrapSelf(info);
		std::vector<int> sizes;
		for (int s = 0; s < m.dims; s++) {
			sizes.push_back(m.size[s]);
		}
		info.GetReturnValue().Set(FF::IntArrayConverter::wrap(sizes));
	};

	FF_INIT_MAT_OPERATIONS();
	static NAN_METHOD(Dot) {
		FF_OPERATOR_RET_SCALAR(&cv::Mat::dot, FF_APPLY_CLASS_FUNC, Mat, "Dot");
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
  static NAN_METHOD(Flip);
  static NAN_METHOD(FlipAsync);
  static NAN_METHOD(CopyMakeBorder);
  static NAN_METHOD(CopyMakeBorderAsync);

#if CV_VERSION_GREATER_EQUAL(3, 2, 0)
  static NAN_METHOD(Rotate);
  static NAN_METHOD(RotateAsync);
#endif

  static NAN_METHOD(AddWeighted);
  static NAN_METHOD(AddWeightedAsync);
  static NAN_METHOD(MinMaxLoc);
  static NAN_METHOD(MinMaxLocAsync);
  static NAN_METHOD(FindNonZero);
  static NAN_METHOD(FindNonZeroAsync);
  static NAN_METHOD(CountNonZero);
  static NAN_METHOD(CountNonZeroAsync);
  static NAN_METHOD(Normalize);
  static NAN_METHOD(NormalizeAsync);
  static NAN_METHOD(Split);
  static NAN_METHOD(SplitAsync);
  static NAN_METHOD(MulSpectrums);
  static NAN_METHOD(MulSpectrumsAsync);
  static NAN_METHOD(Transform);
  static NAN_METHOD(TransformAsync);
  static NAN_METHOD(PerspectiveTransform);
  static NAN_METHOD(PerspectiveTransformAsync);
  static NAN_METHOD(Sum);
  static NAN_METHOD(SumAsync);
  static NAN_METHOD(ConvertScaleAbs);
  static NAN_METHOD(ConvertScaleAbsAsync);
  static NAN_METHOD(Mean);
  static NAN_METHOD(MeanAsync);
  static NAN_METHOD(MeanStdDev);
  static NAN_METHOD(MeanStdDevAsync);
  static NAN_METHOD(Reduce);
  static NAN_METHOD(ReduceAsync);
  static NAN_METHOD(Eigen);
  static NAN_METHOD(EigenAsync);
  static NAN_METHOD(Solve);
  static NAN_METHOD(SolveAsync);

};

#endif
