#include "Converters.h"
#include "opencv2/dnn.hpp"

#ifndef __FF_DNN_H__
#define __FF_DNN_H__

class Dnn {
public:
  static NAN_MODULE_INIT(Init);

	struct ReadNetFromTensorflowWorker;
	static NAN_METHOD(ReadNetFromTensorflow);
	static NAN_METHOD(ReadNetFromTensorflowAsync);

#if CV_VERSION_MINOR > 2
	struct BlobFromImageWorker;
	static NAN_METHOD(BlobFromImage);
	static NAN_METHOD(BlobFromImageAsync);

	struct BlobFromImagesWorker;
	static NAN_METHOD(BlobFromImages);
	static NAN_METHOD(BlobFromImagesAsync);
#endif
};

#endif