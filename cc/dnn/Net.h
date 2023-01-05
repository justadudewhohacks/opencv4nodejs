#include "NativeNodeUtils.h"
#include "opencv2/dnn.hpp"
#include "CatchCvExceptionWorker.h"
#include "Mat.h"

#ifndef __FF_NET_H__
#define __FF_NET_H__

class Net : public FF::ObjectWrap<Net, cv::dnn::Net> {
public:
  static Nan::Persistent<v8::FunctionTemplate> constructor;

  static const char* getClassName() {
    return "Net";
  }

  static NAN_MODULE_INIT(Init);

  static NAN_METHOD(New);
  // setInput(blob: Mat, name?: string, scalefactor?: number, mean?: number): void;
  // setInput(blob: Mat, inputName?: string): void;
  static NAN_METHOD(SetInput);
  static NAN_METHOD(SetInputAsync);
  // forward(inputName?: string): Mat;
  static NAN_METHOD(Forward);
  static NAN_METHOD(ForwardAsync);
  // getLayerNames(): string[];
  static NAN_METHOD(GetLayerNames);
  static NAN_METHOD(GetLayerNamesAsync);
  // getUnconnectedOutLayers(): number[];
  static NAN_METHOD(GetUnconnectedOutLayers);
  static NAN_METHOD(GetUnconnectedOutLayersAsync);
  // dump(): string;
  static NAN_METHOD(Dump);
  // setPreferableBackend(backendId: number): void;
  static NAN_METHOD(SetPreferableBackend);
  // setPreferableTarget(targetId: number): void;
  static NAN_METHOD(SetPreferableTarget);
  // getPerfProfile(): {	retval: number, timings: number[] };
  static NAN_METHOD(GetPerfProfile);
};

#endif