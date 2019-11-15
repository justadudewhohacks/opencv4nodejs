//
// Created by stefan on 11/4/19.
//
#include "macros.h"

#ifndef __FF_HISTAXES_H__
#define __FF_HISTAXES_H__

namespace internal {
  class HistAxes {
  public:
    std::vector<double> range = {};
    int channel = 0;
    int bins = 0;
  };
}

class HistAxes: public FF::ObjectWrap<HistAxes, internal::HistAxes> {
public:
  static Nan::Persistent<v8::FunctionTemplate> constructor;

  static const char* getClassName() {
    return "HistAxes";
  }

  static NAN_METHOD(New);

  static NAN_MODULE_INIT(Init);

  FF_GETTER_CUSTOM(bins, FF::IntConverter, self.bins);
  FF_GETTER_CUSTOM(channel, FF::IntConverter, self.channel);
  FF_GETTER_CUSTOM(ranges, FF::DoubleArrayConverter, self.range);

};

#endif //__FF_HISTAXES_H__
