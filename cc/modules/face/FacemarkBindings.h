#include "Facemark.h"
#include "FacemarkAAMData.h"

#if CV_VERSION_MINOR >= 4

#ifndef __FF_FACEMARKBINDINGS_H_
#define __FF_FACEMARKBINDINGS_H_

namespace FacemarkBindings {

  struct LoadModelWorker : public CatchCvExceptionWorker {
  public:
    cv::Ptr<cv::face::Facemark> self;
    LoadModelWorker(cv::Ptr<cv::face::Facemark> self) { this->self = self; }

    std::string model;

    std::string executeCatchCvExceptionWorker() {
      self->loadModel(model);
      return "";
    }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (StringConverter::arg(0, &model, info));
    }
  };

  struct FitWorker : public CatchCvExceptionWorker {
  public:
	  cv::Ptr<cv::face::Facemark> self;
	  FitWorker(cv::Ptr<cv::face::Facemark> self) { this->self = self; }

	  cv::Mat image;
	  std::vector<cv::Rect> faces;
	  std::vector<std::vector<cv::Point2f>> landmarks;

	  std::string executeCatchCvExceptionWorker() {
		  self->fit(image, faces, landmarks);
		  return "";
	  }

	  v8::Local<v8::Value> getReturnValue() {
		  v8::Local<v8::Value> ret =
			  ObjectArrayOfArraysConverter<Point2, cv::Point2d, cv::Point2f>::wrap(
				  landmarks);
		  return ret;
	  }

	  bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		  return (Mat::Converter::arg(0, &image, info) ||
			  ObjectArrayConverter<Rect, cv::Rect>::arg(1, &faces, info));
	  }
  };

#if CV_MINOR_VERSION < 2
  struct AddTrainingSampleWorker : public CatchCvExceptionWorker {
  public:
	  cv::Ptr<cv::face::Facemark> self;
	  AddTrainingSampleWorker(cv::Ptr<cv::face::Facemark> self) {
		  this->self = self;
	  }

	  bool results;
	  cv::Mat image;
	  std::vector<cv::Point2f> landmarks;

	  std::string executeCatchCvExceptionWorker() {
		  results = self->addTrainingSample(image, landmarks);
		  return "";
	  }

	  v8::Local<v8::Value> getReturnValue() {
		  v8::Local<v8::Value> ret = Nan::New<v8::Boolean>(results);
		  return ret;
	  }

	  bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		  return (Mat::Converter::arg(0, &image, info) ||
			  ObjectArrayConverter<Point2, cv::Point2d, cv::Point2f>::arg(
				  1, &landmarks, info));
	  }
  };

  struct GetDataWorker : public CatchCvExceptionWorker {
  public:
    cv::Ptr<cv::face::Facemark> self;
    GetDataWorker(cv::Ptr<cv::face::Facemark> self) { this->self = self; }

    cv::face::FacemarkAAM::Data data;

    std::string executeCatchCvExceptionWorker() {
      self->getData(&data);
      return "";
    }

    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Value> ret = InstanceConverter<FacemarkAAMData, cv::face::FacemarkAAM::Data>::wrap(data);
      return ret;
    }
  };

  struct GetFacesWorker : public CatchCvExceptionWorker {
  public:
    cv::Ptr<cv::face::Facemark> self;
    GetFacesWorker(cv::Ptr<cv::face::Facemark> self) { this->self = self; }

    cv::Mat image;
    std::vector<cv::Rect> faces;

    std::string executeCatchCvExceptionWorker() {
      self->getFaces(image, faces);
      return "";
    }

    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Value> ret =
          ObjectArrayConverter<Rect, cv::Rect>::wrap(faces);
      return ret;
    }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (Mat::Converter::arg(0, &image, info));
    }
  };

  struct TrainingWorker : public CatchCvExceptionWorker {
  public:
    cv::Ptr<cv::face::Facemark> self;
    TrainingWorker(cv::Ptr<cv::face::Facemark> self) { this->self = self; }

    std::string executeCatchCvExceptionWorker() {
      self->training();
      return "";
    }
  };
#endif
}

#endif

#endif
