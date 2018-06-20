

#ifndef __FF__BOWTRAINER_H__
#define __FF__BOWTRAINER_H__

class BOWTrainer : public Nan::ObjectWrap {
public:
  cv::BOWTrainer bowTrainer;

  static NAN_MODULE_
};

#endif
