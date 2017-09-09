#include <opencv2/imgproc.hpp>
#include "Size.h"
#include "macros.h"
#include "coreUtils.h"
#include "Vec.h"

#ifndef FF_MAT_H_
#define FF_MAT_H_

class Mat : public Nan::ObjectWrap {
public:
  cv::Mat mat;

  static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	static FF_GETTER(Mat, GetRows, mat.rows);
	static FF_GETTER(Mat, GetCols, mat.cols);
	static FF_GETTER(Mat, GetType, mat.type());
	static FF_GETTER(Mat, GetChannels, mat.channels());
	static FF_GETTER(Mat, GetDims, mat.dims);
	static FF_GETTER(Mat, GetDepth, mat.depth());
	static FF_GETTER(Mat, GetIsEmpty, mat.empty());

	static NAN_METHOD(At);
	static NAN_METHOD(AtRaw);
	static NAN_METHOD(Set);
	static NAN_METHOD(GetData);
	static NAN_METHOD(GetDataAsArray);
	static NAN_METHOD(GetRegion);
	static NAN_METHOD(Row);
	static NAN_METHOD(Copy);
	static NAN_METHOD(CopyTo);
	static NAN_METHOD(ConvertTo);
	static NAN_METHOD(Norm);
	static NAN_METHOD(Normalize);
	static NAN_METHOD(SplitChannels);

	FF_INIT_MAT_OPERATIONS();
	static NAN_METHOD(Dot) {
		FF_OPERATOR_RET_SCALAR(&cv::Mat::dot, FF_APPLY_CLASS_FUNC, FF_UNWRAP_MAT_AND_GET, Mat);
	}

	/* #IFDEF IMGPROC */
  static NAN_METHOD(Rescale);
  static NAN_METHOD(Resize);
  static NAN_METHOD(ResizeToMax);
	static NAN_METHOD(Threshold);
	static NAN_METHOD(InRange);
	static NAN_METHOD(CvtColor);
	static NAN_METHOD(BgrToGray);
	static NAN_METHOD(WarpPerspective);
	static NAN_METHOD(Dilate);
	static NAN_METHOD(Erode);
	static NAN_METHOD(DistanceTransform);
	static NAN_METHOD(DistanceTransformWithLabels);
	static NAN_METHOD(Blur);
	static NAN_METHOD(GaussianBlur);
	static NAN_METHOD(MedianBlur);
	static NAN_METHOD(ConnectedComponents);
	static NAN_METHOD(ConnectedComponentsWithStats);
	static NAN_METHOD(FindContours);
	static NAN_METHOD(DrawContours);
	static NAN_METHOD(DrawLine);
	static NAN_METHOD(DrawCircle);
	static NAN_METHOD(DrawRectangle);
	static NAN_METHOD(DrawEllipse);
	static NAN_METHOD(PutText);

	/* #ENDIF IMGPROC */

	static void dilateOrErode(Nan::NAN_METHOD_ARGS_TYPE, char*, bool);
	
  static Nan::Persistent<v8::FunctionTemplate> constructor;

  void setNativeProps(cv::Mat);
};

#endif