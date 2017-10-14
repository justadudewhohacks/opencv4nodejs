#include "macros.h"
#include <opencv2/core.hpp>
#include <opencv2/objdetect.hpp>
#include "Mat.h"
#include "Rect.h"

#ifndef __FF_CASCADECLASSIFIER_H__
#define __FF_CASCADECLASSIFIER_H__

class CascadeClassifier : public Nan::ObjectWrap {
public:
	cv::CascadeClassifier classifier;

	static NAN_MODULE_INIT(Init);
	static NAN_METHOD(New);
	static NAN_METHOD(DetectMultiScale);
	static NAN_METHOD(DetectMultiScaleWithRejectLevels);
	static NAN_METHOD(DetectMultiScaleAsync);
	static NAN_METHOD(DetectMultiScaleWithRejectLevelsAsync);

	static Nan::Persistent<v8::FunctionTemplate> constructor;

	struct DetectMultiScaleContext {
	public:
		cv::CascadeClassifier classifier;
		cv::Mat img;
		double scaleFactor;
		uint minNeighbors;
		uint flags;
		cv::Size2d minSize;
		cv::Size2d maxSize;

		std::vector<cv::Rect> objectRects;
		std::vector<int> numDetections;

		const char* execute() {
			classifier.detectMultiScale(
				img,
				objectRects,
				numDetections,
				scaleFactor,
				(int)minNeighbors,
				(int)flags,
				minSize,
				maxSize
			);
			return "";
		}

		FF_VAL getReturnValue() {
			FF_OBJ ret = FF_NEW_OBJ();
			FF_PACK_ARRAY(jsNumDetections, numDetections);
			FF_ARR jsObjectRects = FF_NEW_ARRAY(objectRects.size());
			for (int i = 0; i < objectRects.size(); i++) {
				FF_OBJ jsObjectRect = FF_NEW_INSTANCE(Rect::constructor);
				FF_UNWRAP(jsObjectRect, Rect)->rect = objectRects.at(i);
				jsObjectRects->Set(i, jsObjectRect);
			}
			Nan::Set(ret, FF_NEW_STRING("numDetections"), jsNumDetections);
			Nan::Set(ret, FF_NEW_STRING("objects"), jsObjectRects);
			return ret;
		}
	};

	struct DetectMultiScaleWithRejectLevelsContext : DetectMultiScaleContext {
	public:
		std::vector<int> rejectLevels;
		std::vector<double> levelWeights;

		const char* execute() {
			classifier.detectMultiScale(
				img,
				objectRects,
				rejectLevels,
				levelWeights,
				scaleFactor,
				(int)minNeighbors,
				(int)flags,
				minSize,
				maxSize,
				true
			);
			return "";
		}

		FF_VAL getReturnValue() {
			FF_OBJ ret = FF_NEW_OBJ();
			FF_PACK_ARRAY(jsRejectLevels, rejectLevels);
			FF_PACK_ARRAY(jsLevelWeights, levelWeights);
			FF_ARR jsObjectRects = FF_NEW_ARRAY(objectRects.size());
			for (int i = 0; i < objectRects.size(); i++) {
				FF_OBJ jsObjectRect = FF_NEW_INSTANCE(Rect::constructor);
				FF_UNWRAP(jsObjectRect, Rect)->rect = objectRects.at(i);
				jsObjectRects->Set(i, jsObjectRect);
			}
			Nan::Set(ret, FF_NEW_STRING("rejectLevels"), jsRejectLevels);
			Nan::Set(ret, FF_NEW_STRING("levelWeights"), jsLevelWeights);
			Nan::Set(ret, FF_NEW_STRING("objects"), jsObjectRects);
			return ret;
		}
	};
};

#endif