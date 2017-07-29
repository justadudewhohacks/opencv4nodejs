#include <node.h>
#include "Mat.h"
#include "Point.h"
#include "Size.h"

#include "modules/io.h"
#include "modules/photo.h"
#include "modules/calib3d/calib3d.h"
#include "modules/imgproc/imgproc.h"
#include "modules/ximgproc/ximgproc.h"
#include "modules/features2d/features2d.h"
#include "modules/xfeatures2d/xfeatures2d.h"
#include "modules/sfm/sfm.h"

// TODO core index
void init(v8::Local<v8::Object> target) {
  Mat::Init(target);
	Point::Init(target);
	Size::Init(target);
  Io::Init(target);
  Photo::Init(target);
  Calib3d::Init(target);
  Imgproc::Init(target);
	XImgproc::Init(target);
  Features2d::Init(target);
	XFeatures2d::Init(target);
  Sfm::Init(target);

};

NODE_MODULE(tutorial, init)
