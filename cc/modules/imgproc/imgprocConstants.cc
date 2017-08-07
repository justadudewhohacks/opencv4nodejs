#include "imgprocConstants.h"

using namespace cv;

void ImgprocConstants::init(v8::Local<v8::Object> module) {
	v8::Local<v8::Object> morphShapes = Nan::New<v8::Object>();
	FF_SET_CV_CONSTANT(morphShapes, MORPH_RECT);
	FF_SET_CV_CONSTANT(morphShapes, MORPH_CROSS);
	FF_SET_CV_CONSTANT(morphShapes, MORPH_ELLIPSE);
	module->Set(FF_V8STRING("morphShapes"), morphShapes);
	
	v8::Local<v8::Object> borderTypes = Nan::New<v8::Object>();
	FF_SET_CV_CONSTANT(borderTypes, BORDER_CONSTANT);
	FF_SET_CV_CONSTANT(borderTypes, BORDER_REPLICATE);
	FF_SET_CV_CONSTANT(borderTypes, BORDER_REFLECT);
	FF_SET_CV_CONSTANT(borderTypes, BORDER_WRAP);
	FF_SET_CV_CONSTANT(borderTypes, BORDER_REFLECT_101);
	FF_SET_CV_CONSTANT(borderTypes, BORDER_TRANSPARENT);
	FF_SET_CV_CONSTANT(borderTypes, BORDER_ISOLATED);
	FF_SET_CV_CONSTANT(borderTypes, BORDER_DEFAULT);
	module->Set(FF_V8STRING("borderTypes"), borderTypes);

	v8::Local<v8::Object> interpolationFlags = Nan::New<v8::Object>();
	FF_SET_CV_CONSTANT(interpolationFlags, INTER_NEAREST);
	FF_SET_CV_CONSTANT(interpolationFlags, INTER_LINEAR);
	FF_SET_CV_CONSTANT(interpolationFlags, INTER_CUBIC);
	FF_SET_CV_CONSTANT(interpolationFlags, INTER_AREA);
	FF_SET_CV_CONSTANT(interpolationFlags, INTER_LANCZOS4);
	FF_SET_CV_CONSTANT(interpolationFlags, INTER_MAX);
	FF_SET_CV_CONSTANT(interpolationFlags, WARP_FILL_OUTLIERS);
	FF_SET_CV_CONSTANT(interpolationFlags, WARP_INVERSE_MAP);
	module->Set(FF_V8STRING("interpolationFlags"), interpolationFlags);

	v8::Local<v8::Object> thresholdTypes = Nan::New<v8::Object>();
	FF_SET_CV_CONSTANT(thresholdTypes, THRESH_BINARY);
	FF_SET_CV_CONSTANT(thresholdTypes, THRESH_BINARY_INV);
	FF_SET_CV_CONSTANT(thresholdTypes, THRESH_TRUNC);
	FF_SET_CV_CONSTANT(thresholdTypes, THRESH_TOZERO);
	FF_SET_CV_CONSTANT(thresholdTypes, THRESH_TOZERO_INV);
	FF_SET_CV_CONSTANT(thresholdTypes, THRESH_MASK);
	FF_SET_CV_CONSTANT(thresholdTypes, THRESH_OTSU);
	FF_SET_CV_CONSTANT(thresholdTypes, THRESH_TRIANGLE);
	module->Set(FF_V8STRING("thresholdTypes"), thresholdTypes);

	v8::Local<v8::Object> colorConversionCodes = Nan::New<v8::Object>();
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGR2BGRA);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_RGB2RGBA);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGRA2BGR);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_RGBA2RGB);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGR2RGBA);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_RGB2BGRA);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_RGBA2BGR);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGRA2RGB);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGR2RGB);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_RGB2BGR);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGRA2RGBA);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_RGBA2BGRA);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGR2GRAY);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_RGB2GRAY);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_GRAY2BGR);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_GRAY2RGB);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_GRAY2BGRA);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_GRAY2RGBA);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGRA2GRAY);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_RGBA2GRAY);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGR2BGR565);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_RGB2BGR565);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGR5652BGR);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGR5652RGB);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGRA2BGR565);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_RGBA2BGR565);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGR5652BGRA);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGR5652RGBA);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_GRAY2BGR565);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGR5652GRAY);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGR2BGR555);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_RGB2BGR555);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGR5552BGR);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGR5552RGB);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGRA2BGR555);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_RGBA2BGR555);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGR5552BGRA);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGR5552RGBA);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_GRAY2BGR555);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGR5552GRAY);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGR2XYZ);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_RGB2XYZ);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_XYZ2BGR);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_XYZ2RGB);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGR2YCrCb);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_RGB2YCrCb);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YCrCb2BGR);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YCrCb2RGB);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGR2HSV);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_RGB2HSV);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGR2Lab);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_RGB2Lab);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGR2Luv);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_RGB2Luv);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGR2HLS);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_RGB2HLS);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_HSV2BGR);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_HSV2RGB);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_Lab2BGR);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_Lab2RGB);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_Luv2BGR);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_Luv2RGB);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_HLS2BGR);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_HLS2RGB);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGR2HSV_FULL);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_RGB2HSV_FULL);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGR2HLS_FULL);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_RGB2HLS_FULL);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_HSV2BGR_FULL);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_HSV2RGB_FULL);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_HLS2BGR_FULL);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_HLS2RGB_FULL);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_LBGR2Lab);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_LRGB2Lab);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_LBGR2Luv);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_LRGB2Luv);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_Lab2LBGR);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_Lab2LRGB);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_Luv2LBGR);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_Luv2LRGB);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGR2YUV);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_RGB2YUV);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2BGR);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2RGB);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2RGB_NV12);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2BGR_NV12);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2RGB_NV21);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2BGR_NV21);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV420sp2RGB);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV420sp2BGR);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2RGBA_NV12);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2BGRA_NV12);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2RGBA_NV21);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2BGRA_NV21);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV420sp2RGBA);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV420sp2BGRA);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2RGB_YV12);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2BGR_YV12);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2RGB_IYUV);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2BGR_IYUV);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2RGB_I420);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2BGR_I420);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV420p2RGB);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV420p2BGR);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2RGBA_YV12);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2BGRA_YV12);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2RGBA_IYUV);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2BGRA_IYUV);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2RGBA_I420);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2BGRA_I420);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV420p2RGBA);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV420p2BGRA);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2GRAY_420);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2GRAY_NV21);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2GRAY_NV12);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2GRAY_YV12);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2GRAY_IYUV);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2GRAY_I420);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV420sp2GRAY);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV420p2GRAY);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2RGB_UYVY);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2BGR_UYVY);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2RGB_Y422);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2BGR_Y422);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2RGB_UYNV);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2BGR_UYNV);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2RGBA_UYVY);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2BGRA_UYVY);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2RGBA_Y422);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2BGRA_Y422);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2RGBA_UYNV);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2BGRA_UYNV);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2RGB_YUY2);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2BGR_YUY2);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2RGB_YVYU);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2BGR_YVYU);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2RGB_YUYV);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2BGR_YUYV);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2RGB_YUNV);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2BGR_YUNV);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2RGBA_YUY2);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2BGRA_YUY2);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2RGBA_YVYU);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2BGRA_YVYU);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2RGBA_YUYV);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2BGRA_YUYV);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2RGBA_YUNV);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2BGRA_YUNV);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2GRAY_UYVY);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2GRAY_YUY2);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2GRAY_Y422);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2GRAY_UYNV);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2GRAY_YVYU);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2GRAY_YUYV);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_YUV2GRAY_YUNV);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_RGBA2mRGBA);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_mRGBA2RGBA);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_RGB2YUV_I420);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGR2YUV_I420);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_RGB2YUV_IYUV);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGR2YUV_IYUV);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_RGBA2YUV_I420);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGRA2YUV_I420);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_RGBA2YUV_IYUV);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGRA2YUV_IYUV);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_RGB2YUV_YV12);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGR2YUV_YV12);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_RGBA2YUV_YV12);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BGRA2YUV_YV12);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BayerBG2BGR);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BayerGB2BGR);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BayerRG2BGR);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BayerGR2BGR);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BayerBG2RGB);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BayerGB2RGB);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BayerRG2RGB);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BayerGR2RGB);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BayerBG2GRAY);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BayerGB2GRAY);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BayerRG2GRAY);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BayerGR2GRAY);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BayerBG2BGR_VNG);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BayerGB2BGR_VNG);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BayerRG2BGR_VNG);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BayerGR2BGR_VNG);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BayerBG2RGB_VNG);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BayerGB2RGB_VNG);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BayerRG2RGB_VNG);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BayerGR2RGB_VNG);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BayerBG2BGR_EA);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BayerGB2BGR_EA);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BayerRG2BGR_EA);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BayerGR2BGR_EA);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BayerBG2RGB_EA);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BayerGB2RGB_EA);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BayerRG2RGB_EA);
	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_BayerGR2RGB_EA);

	FF_SET_CV_CONSTANT(colorConversionCodes, COLOR_COLORCVT_MAX);
	module->Set(FF_V8STRING("colorConversionCodes"), colorConversionCodes);
}