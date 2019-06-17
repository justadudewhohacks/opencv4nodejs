#include "NativeNodeUtils.h"
#include "Mat.h"
#include "Point.h"
#include "Rect.h"
#include "macros.h"
#include <iostream>
#include <opencv2/face.hpp>

#if CV_VERSION_GREATER_EQUAL(3, 4, 0)

#ifndef __FF_FACEMARK_H__
#define __FF_FACEMARK_H__

class Facemark : public FF::ObjectWrapBase<Facemark>, public Nan::ObjectWrap {
public:
  virtual cv::Ptr<cv::face::Facemark> getFacemark() = 0;
  virtual void save(std::string) = 0;
  virtual void load(std::string) = 0;

  static void Init(v8::Local<v8::FunctionTemplate>);

  static NAN_METHOD(AddTrainingSample);
  static NAN_METHOD(AddTrainingSampleAsync);
  static NAN_METHOD(LoadModel);
  static NAN_METHOD(LoadModelAsync);
  static NAN_METHOD(GetData);
  static NAN_METHOD(GetDataAsync);
  static NAN_METHOD(GetFaces);
  static NAN_METHOD(GetFacesAsync);
  static NAN_METHOD(SetFaceDetector);
  static NAN_METHOD(Training);
  static NAN_METHOD(TrainingAsync);
  static NAN_METHOD(Fit);
  static NAN_METHOD(FitAsync);
  static NAN_METHOD(Save);
  static NAN_METHOD(Load);

  static bool detector(cv::InputArray image, cv::OutputArray faces,
                       Nan::Callback *callback);
};

#endif

#endif
