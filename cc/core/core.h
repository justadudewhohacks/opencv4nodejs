#include "Mat.h"
#include "Point.h"
#include "Vec.h"
#include "Size.h"
#include "Rect.h"
#include "RotatedRect.h"
#include "TermCriteria.h"
#include "HistAxes.h"
#include "macros.h"
#include <opencv2/core.hpp>

#ifndef __FF_CORE_H__
#define __FF_CORE_H__

class Core : public Nan::ObjectWrap {
public:
	static NAN_MODULE_INIT(Init);

	static NAN_METHOD(GetBuildInformation);
	static NAN_METHOD(Partition);
	static NAN_METHOD(Kmeans);
	static NAN_METHOD(CartToPolar);
	static NAN_METHOD(CartToPolarAsync);
	static NAN_METHOD(PolarToCart);
	static NAN_METHOD(PolarToCartAsync);
	static NAN_METHOD(GetNumThreads);
	static NAN_METHOD(SetNumThreads);
	static NAN_METHOD(GetThreadNum);

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
