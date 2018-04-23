#include "Converters.h"
#include "Mat.h"
#include "Point.h"
#include "Rect.h"
#include "Workers.h"
#include "macros.h"
#include <iostream>
#include <opencv2/face.hpp>

#ifndef __FF_FACEMARK_H__
#define __FF_FACEMARK_H__

class Facemark : public Nan::ObjectWrap {
public:
  virtual cv::Ptr<cv::face::Facemark> getFacemark() = 0;
  virtual void save(std::string) = 0;
  virtual void load(std::string) = 0;

  static void Init(v8::Local<v8::FunctionTemplate>);

  struct AddTrainingSampleWorker;
  static NAN_METHOD(AddTrainingSample);
  static NAN_METHOD(AddTrainingSampleAsync);

  struct LoadModelWorker;
  static NAN_METHOD(LoadModel);
  static NAN_METHOD(LoadModelAsync);

  struct GetDataWorker;
  static NAN_METHOD(GetData);
  static NAN_METHOD(GetDataAsync);

  struct GetFacesWorker;
  static NAN_METHOD(GetFaces);
  static NAN_METHOD(GetFacesAsync);

  static bool detector(cv::InputArray image, cv::OutputArray faces,
                       Nan::Callback *callback);

  struct SetFaceDetectorWorker;
  static NAN_METHOD(SetFaceDetector);

  struct TrainingWorker;
  static NAN_METHOD(Training);
  static NAN_METHOD(TrainingAsync);

  struct FitWorker;
  static NAN_METHOD(Fit);
  static NAN_METHOD(FitAsync);

  static NAN_METHOD(Save);
  static NAN_METHOD(Load);
};

#endif
