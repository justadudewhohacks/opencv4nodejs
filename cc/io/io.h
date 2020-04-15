#include "macros.h"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "Mat.h"
#include "VideoCapture.h"
#include "VideoWriter.h"
#include "CatchCvExceptionWorker.h"

#ifndef __FF_IO_H_
#define __FF_IO_H_

class Io {
public:
	static NAN_MODULE_INIT(Init);

	static NAN_METHOD(Imshow);
	static NAN_METHOD(ImshowWait);
	static NAN_METHOD(WaitKey);
#if CV_VERSION_GREATER_EQUAL(3, 2, 0)
	static NAN_METHOD(WaitKeyEx);
#endif
	static NAN_METHOD(MoveWindow);
	static NAN_METHOD(DestroyWindow);
	static NAN_METHOD(DestroyAllWindows);
	static NAN_METHOD(Imread);
	static NAN_METHOD(ImreadAsync);
	static NAN_METHOD(Imwrite);
	static NAN_METHOD(ImwriteAsync);
	static NAN_METHOD(Imencode);
	static NAN_METHOD(ImencodeAsync);
	static NAN_METHOD(Imdecode);
	static NAN_METHOD(ImdecodeAsync);
};

#endif
