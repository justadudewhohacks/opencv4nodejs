#include "macros.h"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "Mat.h"

class Io {
public:
  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(Imshow);
	static NAN_METHOD(ImshowWait);
	static NAN_METHOD(WaitKey);
	static NAN_METHOD(MoveWindow);
	static NAN_METHOD(DestroyWindow);
	static NAN_METHOD(DestroyAllWindows);

	struct ImreadWorker;
  static NAN_METHOD(Imread);
	static NAN_METHOD(ImreadAsync);

	struct ImwriteWorker;
  static NAN_METHOD(Imwrite);
	static NAN_METHOD(ImwriteAsync);

	struct ImencodeWorker;
	static NAN_METHOD(Imencode);
	static NAN_METHOD(ImencodeAsync);

	struct ImdecodeWorker;
	static NAN_METHOD(Imdecode);
	static NAN_METHOD(ImdecodeAsync);
};
