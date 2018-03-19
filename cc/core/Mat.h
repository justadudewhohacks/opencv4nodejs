#include "Converters.h"
#include "Size.h"
#include "coreUtils.h"
#include "matUtils.h"
#include "Vec.h"
#include "Point2.h"
#include "Rect.h"
#include "RotatedRect.h"
#include "Workers.h"
#include "CustomAllocator.h"


#ifndef __FF_MAT_H__
#define __FF_MAT_H__

class Mat : public Nan::ObjectWrap {
public:
  cv::Mat mat;
  
  static CustomMatAllocator *custommatallocator;

  static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	static NAN_METHOD(Eye);
	static NAN_METHOD(FlattenFloat);

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

	static NAN_METHOD(At);
	static NAN_METHOD(AtRaw);
	static NAN_METHOD(Set);

	struct PushBackWorker;
	static NAN_METHOD(PushBack);
	static NAN_METHOD(PushBackAsync);
	struct PopBackWorker;
	static NAN_METHOD(PopBack);
	static NAN_METHOD(PopBackAsync);

	struct GetDataWorker;
	static NAN_METHOD(GetData);
	static NAN_METHOD(GetDataAsync);

	static NAN_METHOD(GetDataAsArray);
	static NAN_METHOD(GetRegion);
	static NAN_METHOD(Row);

	struct CopyWorker;
	static NAN_METHOD(Copy);
	static NAN_METHOD(CopyAsync);

	struct CopyToWorker;
	static NAN_METHOD(CopyTo);
	static NAN_METHOD(CopyToAsync);

	struct ConvertToWorker;
	static NAN_METHOD(ConvertTo);
	static NAN_METHOD(ConvertToAsync);

	static NAN_METHOD(Norm);
	static NAN_METHOD(Normalize);

	struct SplitChannelsWorker;
	static NAN_METHOD(SplitChannels);
	static NAN_METHOD(SplitChannelsAsync);

	struct AddWeightedWorker;
	static NAN_METHOD(AddWeighted);
	static NAN_METHOD(AddWeightedAsync);

	struct MinMaxLocWorker;
	static NAN_METHOD(MinMaxLoc);
	static NAN_METHOD(MinMaxLocAsync);

	struct FindNonZeroWorker;
	static NAN_METHOD(FindNonZero);
	static NAN_METHOD(FindNonZeroAsync);

	struct CountNonZeroWorker;
	static NAN_METHOD(CountNonZero);
	static NAN_METHOD(CountNonZeroAsync);

	struct PadToSquareWorker;
	static NAN_METHOD(PadToSquare);
	static NAN_METHOD(PadToSquareAsync);

	struct SumWorker;
	static NAN_METHOD(Sum);
	static NAN_METHOD(SumAsync);

	struct ConvertScaleAbsWorker;
	static NAN_METHOD(ConvertScaleAbs);
	static NAN_METHOD(ConvertScaleAbsAsync);


	FF_INIT_MAT_OPERATIONS();
	static NAN_METHOD(Dot) {
		FF_OPERATOR_RET_SCALAR(&cv::Mat::dot, FF_APPLY_CLASS_FUNC, FF_UNWRAP_MAT_AND_GET, Mat);
	}

	struct DTWorker;
	struct DCTWorker;
	struct DFTWorker;
	static NAN_METHOD(Dct);
	static NAN_METHOD(DctAsync);
	static NAN_METHOD(Idct);
	static NAN_METHOD(IdctAsync);
	static NAN_METHOD(Dft);
	static NAN_METHOD(DftAsync);
	static NAN_METHOD(Idft);
	static NAN_METHOD(IdftAsync);

	struct MulSpectrumsWorker;
	static NAN_METHOD(MulSpectrums);
	static NAN_METHOD(MulSpectrumsAsync);

	struct TransformWorker;
	struct PerspectiveTransformWorker;
	static NAN_METHOD(Transform);
	static NAN_METHOD(TransformAsync);
	static NAN_METHOD(PerspectiveTransform);
	static NAN_METHOD(PerspectiveTransformAsync);

	struct OpWithCodeWorker;
	struct FlipWorker;
	static NAN_METHOD(Flip);
	static NAN_METHOD(FlipAsync);

#if CV_VERSION_MINOR > 1
	struct RotateWorker;
	static NAN_METHOD(Rotate);
	static NAN_METHOD(RotateAsync);
#endif

    static NAN_METHOD(GetMemMetrics);


  static Nan::Persistent<v8::FunctionTemplate> constructor;

	void setNativeProps(cv::Mat);

	cv::Mat* getNativeObjectPtr() { return &mat; }
	cv::Mat getNativeObject() { return mat; }

	typedef InstanceConverter<Mat, cv::Mat> Converter;

	static const char* getClassName() {
		return "Mat";
	}
};

#endif