#include <nan.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/photo.hpp>

class Photo {
public:
  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(FastNlMeansDenoisingColored);

};
