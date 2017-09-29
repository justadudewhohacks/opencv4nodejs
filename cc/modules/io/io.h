#include "macros.h"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class Io {
public:
  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(Imread);
  static NAN_METHOD(Imwrite);
  static NAN_METHOD(Imshow);
	static NAN_METHOD(ImshowWait);
	static NAN_METHOD(WaitKey);
	static NAN_METHOD(Imencode);
	static NAN_METHOD(Imdecode);
};
