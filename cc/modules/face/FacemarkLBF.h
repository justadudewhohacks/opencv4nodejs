#include "Facemark.h"

#if CV_VERSION_MINOR >= 4

#ifndef __FF_FACEMARKLBF_H__
#define __FF_FACEMARKLBF_H__

class FacemarkLBF : public Facemark {
public:
  cv::Ptr<cv::face::Facemark> facemark;

  void save(std::string path) { facemark->save(path); }

  void load(std::string path) {
    cv::Algorithm::load<cv::face::FacemarkLBF>(path);
  }

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);

  static Nan::Persistent<v8::FunctionTemplate> constructor;
  cv::Ptr<cv::face::Facemark> getFacemark() { return facemark; }
};

#endif

#endif
