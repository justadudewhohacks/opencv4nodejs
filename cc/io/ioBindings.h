#include "io.h"

#ifndef __FF_IOBINDINGS_H_
#define __FF_IOBINDINGS_H_

namespace IoBindings {

  struct ImreadWorker : CatchCvExceptionWorker {
  public:
    std::string path;
    int flags = cv::IMREAD_COLOR;
    cv::Mat img;

    std::string executeCatchCvExceptionWorker() {
      img = cv::imread(path, flags);
      if (img.rows == 0 && img.cols == 0) {
        return "empty Mat";
      }
      return "";
    }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF::StringConverter::arg(0, &path, info);
    }

    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF::IntConverter::optArg(1, &flags, info);
    }

    v8::Local<v8::Value> getReturnValue() {
      return Mat::Converter::wrap(img);
    }
  };

  struct ImwriteWorker : CatchCvExceptionWorker {
  public:
    std::string path;
    cv::Mat img;
    std::vector<int> flags;

    std::string executeCatchCvExceptionWorker() {
      cv::imwrite(path, img);
      return "";
    }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF::StringConverter::arg(0, &path, info)
        || Mat::Converter::arg(1, &img, info);
    }

    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF::IntArrayConverter::optArg(2, &flags, info);
    }
  };

  struct ImencodeWorker : CatchCvExceptionWorker {
  public:
    std::string ext;
    cv::Mat img;
    std::vector<int> flags;
    char *data;
    size_t dataSize;

    std::string executeCatchCvExceptionWorker() {
      std::vector<uchar> dataVec;
      cv::imencode(ext, img, dataVec, flags);
      dataSize = dataVec.size() * sizeof(char);
      data = static_cast<char *>(malloc(dataSize));
      memcpy(data, reinterpret_cast<char*>(dataVec.data()), dataSize);
      return "";
    }

    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF::StringConverter::arg(0, &ext, info)
        || Mat::Converter::arg(1, &img, info);
    }

    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF::IntArrayConverter::optArg(2, &flags, info);
    }

    static void freeBufferCallback(char* data, void* hint) {
      free(data);
    }

    v8::Local<v8::Value> getReturnValue() {
      return Nan::NewBuffer(data, dataSize, freeBufferCallback, 0).ToLocalChecked();
    }
  };

  struct ImdecodeWorker : CatchCvExceptionWorker {
  public:
    int flags;
    cv::Mat img;
    char *data;
    size_t dataSize;

    std::string executeCatchCvExceptionWorker() {
      std::vector<uchar> vec(dataSize);
      memcpy(vec.data(), data, dataSize);
      img = cv::imdecode(vec, flags);
      return "";
    }

    v8::Local<v8::Value> getReturnValue() {
      return Mat::Converter::wrap(img);
    }
  };


}

#endif