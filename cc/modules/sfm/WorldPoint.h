#include <nan.h>
#include <Eigen/Core>

class WorldPoint : public Nan::ObjectWrap {
public:
	Eigen::Vector3d point;
  Eigen::Vector3d color;
	int numObservations;
  bool isEstimated;

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);
	static NAN_GETTER(GetPoint);
  static NAN_GETTER(GetColor);
	static NAN_GETTER(GetNumObservations);
	static NAN_GETTER(GetIsEstimated);

  static Nan::Persistent<v8::FunctionTemplate> constructor;

  void setNativeProps(Eigen::Vector3d point, Eigen::Vector3d color, int numObservations, bool isEstimated);
};
