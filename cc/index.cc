#include <node.h>
#include "Mat.h"
#include "Point.h"
#include "Vec.h"
#include "Size.h"
#include "cvTypes/cvTypes.h"

#include "modules/io.h"
#include "modules/VideoCapture.h"
#include "modules/photo.h"
#include "modules/calib3d/calib3d.h"
#include "modules/imgproc/imgproc.h"
#include "modules/ximgproc/ximgproc.h"
#include "modules/features2d/features2d.h"
#include "modules/xfeatures2d/xfeatures2d.h"

void init(v8::Local<v8::Object> target) {
  CvTypes::Init(target);
  Mat::Init(target);
	Point::Init(target);
	Vec::Init(target);
	Size::Init(target);
  Io::Init(target);
	VideoCapture::Init(target);
  Photo::Init(target);
  Calib3d::Init(target);
  Imgproc::Init(target);
	XImgproc::Init(target);
  Features2d::Init(target);
	XFeatures2d::Init(target);
};

NODE_MODULE(opencv4nodejs, init)
