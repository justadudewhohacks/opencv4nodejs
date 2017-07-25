#include <nan.h>
#include <Eigen/Core>

class Camera : public Nan::ObjectWrap {
public:
	Eigen::Vector3d pos;
  Eigen::Matrix3d rot;
	Eigen::Vector2d principalPoint;
	double focalLength;
  int imgWidth;
  int imgHeight;
  bool isEstimated;

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);
	static NAN_GETTER(GetPosition);
  static NAN_GETTER(GetRotation);
	static NAN_GETTER(GetPrincipalPoint);
	static NAN_GETTER(GetFocalLength);
  static NAN_GETTER(GetImgWidth);
  static NAN_GETTER(GetImgHeight);
	static NAN_GETTER(GetIsEstimated);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

  void setNativeProps(Eigen::Vector3d pos, Eigen::Matrix3d rot, Eigen::Vector2d principalPoint, 
		double focalLength, int imgWidth, int imgHeight, bool isEstimated);
};
