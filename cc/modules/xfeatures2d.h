#include <nan.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>

class XFeatures2d {
public:
  static NAN_MODULE_INIT(Init);
  // xfeatures2d
  static NAN_METHOD(DetectKeypointsSIFT);
  static NAN_METHOD(DetectKeypointsSURF);
  static NAN_METHOD(ComputeDescriptorsSIFT);
  static NAN_METHOD(ComputeDescriptorsSURF);
  static NAN_METHOD(MatchDescriptors);
  // features2d
  static NAN_METHOD(DetectKeypointsORB);
  static NAN_METHOD(ComputeDescriptorsORB);

  static v8::Local<v8::Value> detectKeyPoints(cv::Mat mat, cv::Ptr<cv::FeatureDetector> detector);
  static v8::Local<v8::Value> computeDescriptors(cv::Mat mat, v8::Local<v8::Array> jsKps, cv::Ptr<cv::FeatureDetector> detector);
};
