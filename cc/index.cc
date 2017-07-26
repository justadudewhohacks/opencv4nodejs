#include <node.h>
#include "Mat.h"
#include "modules/io.h"
#include "modules/xfeatures2d.h"
#include "modules/photo.h"
#include "modules/features2d/features2d.h"
#include "modules/sfm/sfm.h"

void init(v8::Local<v8::Object> target) {
  Mat::Init(target);
  Io::Init(target);
  XFeatures2d::Init(target);
  Photo::Init(target);
  Features2d::Init(target);
  Sfm::Init(target);

};

NODE_MODULE(tutorial, init)
