#include "Converters.h"
#include <opencv2/imgproc.hpp>
#include "Size.h"
#include "coreUtils.h"
#include "matUtils.h"
#include "Vec.h"

#ifndef __FF_MAT_H__
#define __FF_MAT_H__

class Mat : public Nan::ObjectWrap {
public:
  cv::Mat mat;

  static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);

	static NAN_METHOD(Eye);

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

	struct GetDataWorker;
	static NAN_METHOD(GetData);
	static NAN_METHOD(GetDataAsync);

	static NAN_METHOD(GetDataAsArray);
	static NAN_METHOD(GetRegion);
	static NAN_METHOD(Row);
	static NAN_METHOD(Copy);
	static NAN_METHOD(CopyTo);
	static NAN_METHOD(ConvertTo);
	static NAN_METHOD(Norm);
	static NAN_METHOD(Normalize);
	static NAN_METHOD(SplitChannels);
	static NAN_METHOD(AddWeighted);
	static NAN_METHOD(MinMaxLoc);

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

	/* imgproc */

  static NAN_METHOD(Rescale);
  static NAN_METHOD(Resize);
  static NAN_METHOD(ResizeToMax);


	struct ThresholdWorker;
	static NAN_METHOD(Threshold);
	static NAN_METHOD(ThresholdAsync);

	struct AdaptiveThresholdWorker;
	static NAN_METHOD(AdaptiveThreshold);
	static NAN_METHOD(AdaptiveThresholdAsync);

	struct InRangeWorker;
	static NAN_METHOD(InRange);
	static NAN_METHOD(InRangeAsync);

	static NAN_METHOD(CvtColor);
	static NAN_METHOD(BgrToGray);

	struct WarpWorker;
	struct WarpAffineWorker;
	struct WarpPerspectiveWorker;
	static NAN_METHOD(WarpAffine);
	static NAN_METHOD(WarpAffineAsync);
	static NAN_METHOD(WarpPerspective);
	static NAN_METHOD(WarpPerspectiveAsync);

	struct MorphWorker;
	struct DilateWorker;
	struct ErodeWorker;
	struct MorphologyExWorker;
	static NAN_METHOD(Dilate);
	static NAN_METHOD(DilateAsync);
	static NAN_METHOD(Erode);
	static NAN_METHOD(ErodeAsync);
	static NAN_METHOD(MorphologyEx);
	static NAN_METHOD(MorphologyExAsync);

	static NAN_METHOD(DistanceTransform);
	static NAN_METHOD(DistanceTransformWithLabels);

	struct BlurWorker;
	static NAN_METHOD(Blur);
	static NAN_METHOD(BlurAsync);

	struct GaussianBlurWorker;
	static NAN_METHOD(GaussianBlur);
	static NAN_METHOD(GaussianBlurAsync);

	struct MedianBlurWorker;
	static NAN_METHOD(MedianBlur);
	static NAN_METHOD(MedianBlurAsync);
	static NAN_METHOD(ConnectedComponents);
	static NAN_METHOD(ConnectedComponentsWithStats);
	static NAN_METHOD(GrabCut);
	static NAN_METHOD(_Moments);
	static NAN_METHOD(FindContours);
	static NAN_METHOD(DrawContours);
	static NAN_METHOD(DrawLine);
	static NAN_METHOD(DrawCircle);
	static NAN_METHOD(DrawRectangle);
	static NAN_METHOD(DrawEllipse);
	static NAN_METHOD(PutText);

	struct MatchTemplateWorker;
	static NAN_METHOD(MatchTemplate);
	static NAN_METHOD(MatchTemplateAsync);

	struct CannyWorker;
	static NAN_METHOD(Canny);
	static NAN_METHOD(CannyAsync);

	struct SobelScharrWorker;
	struct SobelWorker;
	struct ScharrWorker;
	static NAN_METHOD(Sobel);
	static NAN_METHOD(SobelAsync);
	static NAN_METHOD(Scharr);
	static NAN_METHOD(ScharrAsync);

	struct LaplacianWorker;
	static NAN_METHOD(Laplacian);
	static NAN_METHOD(LaplacianAsync);

	struct PyrWorker;
	static NAN_METHOD(PyrDown);
	static NAN_METHOD(PyrDownAsync);
	static NAN_METHOD(PyrUp);
	static NAN_METHOD(PyrUpAsync);

	struct BuildPyramidWorker;
	static NAN_METHOD(BuildPyramid);
	static NAN_METHOD(BuildPyramidAsync);

	struct HoughLinesWorker;
	static NAN_METHOD(HoughLines);
	static NAN_METHOD(HoughLinesAsync);

	struct HoughLinesPWorker;
	static NAN_METHOD(HoughLinesP);
	static NAN_METHOD(HoughLinesPAsync);

	struct HoughCirclesWorker;
	static NAN_METHOD(HoughCircles);
	static NAN_METHOD(HoughCirclesAsync);

	/* end imgproc */

	static void morph(Nan::NAN_METHOD_ARGS_TYPE, const char*, void(*)(cv::InputArray, cv::OutputArray, cv::InputArray, cv::Point, int, int, const cv::Scalar&));
	
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