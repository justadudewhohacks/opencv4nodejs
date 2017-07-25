#define GLOG_NO_ABBREVIATED_SEVERITIES 1

#include <nan.h>
#include <opencv2/imgproc.hpp>
#include <theia/sfm/estimators/estimate_relative_pose.h>
#include <theia/sfm/camera/camera.h>

class RelativePose : public Nan::ObjectWrap {
public:
  theia::RelativePose relativePose;
	Eigen::Vector3d rotationAsAngleAxis;

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);
	static NAN_GETTER(GetPosition);
  static NAN_GETTER(GetRotation);
	static NAN_GETTER(GetRotationAsAngleAxis);
	static NAN_GETTER(GetEssentialMatrix);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

  void setNativeProps(theia::RelativePose);
};
