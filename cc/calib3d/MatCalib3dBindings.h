#include "MatCalib3d.h"
#include "CvBinding.h"

#ifndef __FF_MATCALIB3DBINDINGS_H__
#define __FF_MATCALIB3DBINDINGS_H__

namespace MatCalib3dBindings {

  struct RodriguesWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    RodriguesWorker(cv::Mat self) {
      this->self = self;
    }
  
    cv::Mat dst;
    cv::Mat jacobian;
  
    std::string executeCatchCvExceptionWorker() {
      cv::Rodrigues(self, dst, jacobian);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("dst").ToLocalChecked(), Mat::Converter::wrap(dst));
      Nan::Set(ret, Nan::New("jacobian").ToLocalChecked(), Mat::Converter::wrap(jacobian));
      return ret;
    }
  };
  
  struct RQDecomp3x3Worker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    RQDecomp3x3Worker(cv::Mat self) {
      this->self = self;
    }
  
    cv::Vec3d returnValue;
    cv::Mat mtxR;
    cv::Mat mtxQ;
    cv::Mat Qx;
    cv::Mat Qy;
    cv::Mat Qz;
  
    std::string executeCatchCvExceptionWorker() {
      returnValue = cv::RQDecomp3x3(self, mtxR, mtxQ, Qx, Qy, Qz);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("returnValue").ToLocalChecked(), Vec3::Converter::wrap(returnValue));
      Nan::Set(ret, Nan::New("mtxR").ToLocalChecked(), Mat::Converter::wrap(mtxR));
      Nan::Set(ret, Nan::New("mtxQ").ToLocalChecked(), Mat::Converter::wrap(mtxQ));
      Nan::Set(ret, Nan::New("Qx").ToLocalChecked(), Mat::Converter::wrap(Qx));
      Nan::Set(ret, Nan::New("Qy").ToLocalChecked(), Mat::Converter::wrap(Qy));
      Nan::Set(ret, Nan::New("Qz").ToLocalChecked(), Mat::Converter::wrap(Qz));
      return ret;
    }
  };
  
  struct DecomposeProjectionMatrixWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    DecomposeProjectionMatrixWorker(cv::Mat self) {
      this->self = self;
    }
  
    cv::Mat cameraMatrix;
    cv::Mat rotMatrix;
    cv::Vec4d transVect;
    cv::Mat rotMatrixX;
    cv::Mat rotMatrixY;
    cv::Mat rotMatrixZ;
    cv::Mat eulerAngles;
  
    std::string executeCatchCvExceptionWorker() {
      cv::decomposeProjectionMatrix(self, cameraMatrix, rotMatrix, transVect, rotMatrixX, rotMatrixY, rotMatrixZ, eulerAngles);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("cameraMatrix").ToLocalChecked(), Mat::Converter::wrap(cameraMatrix));
      Nan::Set(ret, Nan::New("rotMatrix").ToLocalChecked(), Mat::Converter::wrap(rotMatrix));
      Nan::Set(ret, Nan::New("transVect").ToLocalChecked(), Vec4::Converter::wrap(transVect));
      Nan::Set(ret, Nan::New("rotMatrixX").ToLocalChecked(), Mat::Converter::wrap(rotMatrixX));
      Nan::Set(ret, Nan::New("rotMatrixY").ToLocalChecked(), Mat::Converter::wrap(rotMatrixY));
      Nan::Set(ret, Nan::New("rotMatrixZ").ToLocalChecked(), Mat::Converter::wrap(rotMatrixZ));
      return ret;
    }
  };
  
  struct MatMulDerivWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    MatMulDerivWorker(cv::Mat self) {
      this->self = self;
    }
  
    cv::Mat B;
  
    cv::Mat dABdA;
    cv::Mat dABdB;
  
    std::string executeCatchCvExceptionWorker() {
      cv::matMulDeriv(self, B, dABdA, dABdB);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("dABdA").ToLocalChecked(), Mat::Converter::wrap(dABdA));
      Nan::Set(ret, Nan::New("dABdB").ToLocalChecked(), Mat::Converter::wrap(dABdB));
      return ret;
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::arg(0, &B, info)
      );
    }
  };
  
  struct FindChessboardCornersWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    FindChessboardCornersWorker(cv::Mat self) {
      this->self = self;
    }
  
    cv::Size2d patternSize;
    int flags = cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE;
  
    bool returnValue;
    std::vector<cv::Point2d> corners;
  
    std::string executeCatchCvExceptionWorker() {
      returnValue = cv::findChessboardCorners(self, patternSize, corners, flags);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("returnValue").ToLocalChecked(), FF::BoolConverter::wrap(returnValue));
      Nan::Set(ret, Nan::New("corners").ToLocalChecked(), Point2::ArrayConverter::wrap(corners));
      return ret;
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Size::Converter::arg(0, &patternSize, info)
      );
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        FF::IntConverter::optArg(1, &flags, info)
      );
    }
  };
  
  struct DrawChessboardCornersWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    DrawChessboardCornersWorker(cv::Mat self) {
      this->self = self;
    }
  
    cv::Size2d patternSize;
    std::vector<cv::Point2f> corners;
    bool patternWasFound;
  
  
    std::string executeCatchCvExceptionWorker() {
      cv::drawChessboardCorners(self, patternSize, corners, patternWasFound);
      return "";
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Size::Converter::arg(0, &patternSize, info) ||
        Point2::ArrayWithCastConverter<cv::Point2f>::arg(1, &corners, info) ||
        FF::BoolConverter::arg(2, &patternWasFound, info)
      );
    }
  };
  
  struct Find4QuadCornerSubpixWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    Find4QuadCornerSubpixWorker(cv::Mat self) {
      this->self = self;
    }
  
    std::vector<cv::Point2f> corners;
    cv::Size2d region_size;
  
    bool returnValue;
  
    std::string executeCatchCvExceptionWorker() {
      returnValue = cv::find4QuadCornerSubpix(self, corners, region_size);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      return FF::BoolConverter::wrap(returnValue);
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Point2::ArrayWithCastConverter<cv::Point2f>::arg(0, &corners, info) ||
        Size::Converter::arg(1, &region_size, info)
      );
    }
  };
  
  struct CalibrationMatrixValuesWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    CalibrationMatrixValuesWorker(cv::Mat self) {
      this->self = self;
    }
  
    cv::Size2d imageSize;
    double apertureWidth;
    double apertureHeight;
  
    double fovx;
    double fovy;
    double focalLength;
    cv::Point2d principalPoint;
    double aspectRatio;
  
    std::string executeCatchCvExceptionWorker() {
      cv::calibrationMatrixValues(self, imageSize, apertureWidth, apertureHeight, fovx, fovy, focalLength, principalPoint, aspectRatio);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("fovx").ToLocalChecked(), FF::DoubleConverter::wrap(fovx));
      Nan::Set(ret, Nan::New("fovy").ToLocalChecked(), FF::DoubleConverter::wrap(fovy));
      Nan::Set(ret, Nan::New("focalLength").ToLocalChecked(), FF::DoubleConverter::wrap(focalLength));
      Nan::Set(ret, Nan::New("principalPoint").ToLocalChecked(), Point2::Converter::wrap(principalPoint));
      Nan::Set(ret, Nan::New("aspectRatio").ToLocalChecked(), FF::DoubleConverter::wrap(aspectRatio));
      return ret;
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Size::Converter::arg(0, &imageSize, info) ||
        FF::DoubleConverter::arg(1, &apertureWidth, info) ||
        FF::DoubleConverter::arg(2, &apertureHeight, info)
      );
    }
  };
  
  struct StereoRectifyWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    StereoRectifyWorker(cv::Mat self) {
      this->self = self;
    }
  
    std::vector<double> distCoeffs1;
    cv::Mat cameraMatrix2;
    std::vector<double> distCoeffs2;
    cv::Size2d imageSize;
    cv::Mat R;
    cv::Vec3d T;
    int flags = cv::CALIB_ZERO_DISPARITY;
    double alpha = -1;
    cv::Size2d newImageSize = cv::Size2d();
  
    cv::Mat R1;
    cv::Mat R2;
    cv::Mat P1;
    cv::Mat P2;
    cv::Mat Q;
    cv::Rect roi1;
    cv::Rect roi2;
  
    std::string executeCatchCvExceptionWorker() {
      cv::stereoRectify(self, distCoeffs1, cameraMatrix2, distCoeffs2, imageSize, R, T, R1, R2, P1, P2, Q, flags, alpha, newImageSize, &roi1, &roi2);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("R1").ToLocalChecked(), Mat::Converter::wrap(R1));
      Nan::Set(ret, Nan::New("R2").ToLocalChecked(), Mat::Converter::wrap(R2));
      Nan::Set(ret, Nan::New("P1").ToLocalChecked(), Mat::Converter::wrap(P1));
      Nan::Set(ret, Nan::New("P2").ToLocalChecked(), Mat::Converter::wrap(P2));
      Nan::Set(ret, Nan::New("Q").ToLocalChecked(), Mat::Converter::wrap(Q));
      Nan::Set(ret, Nan::New("roi1").ToLocalChecked(), Rect::Converter::wrap(roi1));
      Nan::Set(ret, Nan::New("roi2").ToLocalChecked(), Rect::Converter::wrap(roi2));
      return ret;
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        FF::DoubleArrayConverter::arg(0, &distCoeffs1, info) ||
        Mat::Converter::arg(1, &cameraMatrix2, info) ||
        FF::DoubleArrayConverter::arg(2, &distCoeffs2, info) ||
        Size::Converter::arg(3, &imageSize, info) ||
        Mat::Converter::arg(4, &R, info) ||
        Vec3::Converter::arg(5, &T, info)
      );
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        FF::IntConverter::optArg(6, &flags, info) ||
        FF::DoubleConverter::optArg(7, &alpha, info) ||
        Size::Converter::optArg(8, &newImageSize, info)
      );
    }
  
    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF::isArgObject(info, 6);
    }
  
    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      v8::Local<v8::Object> opts = info[6]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
      return (
        FF::IntConverter::optProp(&flags, "flags", opts) ||
        FF::DoubleConverter::optProp(&alpha, "alpha", opts) ||
        Size::Converter::optProp(&newImageSize, "newImageSize", opts)
      );
    }
  };
  
  struct Rectify3CollinearWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    Rectify3CollinearWorker(cv::Mat self) {
      this->self = self;
    }
  
    std::vector<double> distCoeffs1;
    cv::Mat cameraMatrix2;
    std::vector<double> distCoeffs2;
    cv::Mat cameraMatrix3;
    std::vector<double> distCoeffs3;
    std::vector<cv::Point2f> imgpt1;
    std::vector<cv::Point2f> imgpt3;
    cv::Size2d imageSize;
    cv::Mat R12;
    cv::Vec3d T12;
    cv::Mat R13;
    cv::Vec3d T13;
    double alpha;
    cv::Size2d newImgSize;
    int flags;
  
  
    float returnValue;
    cv::Mat R1;
    cv::Mat R2;
    cv::Mat R3;
    cv::Mat P1;
    cv::Mat P2;
    cv::Mat P3;
    cv::Mat Q;
    cv::Rect roi1;
    cv::Rect roi2;
  
    std::string executeCatchCvExceptionWorker() {
      returnValue = cv::rectify3Collinear(self, distCoeffs1, cameraMatrix2, distCoeffs2, cameraMatrix3, distCoeffs3, imgpt1, imgpt3, imageSize, R12, T12, R13, T13, R1, R2, R3, P1, P2, P3, Q, alpha, newImgSize, &roi1, &roi2, flags);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("returnValue").ToLocalChecked(), FF::FloatConverter::wrap(returnValue));
      Nan::Set(ret, Nan::New("R1").ToLocalChecked(), Mat::Converter::wrap(R1));
      Nan::Set(ret, Nan::New("R2").ToLocalChecked(), Mat::Converter::wrap(R2));
      Nan::Set(ret, Nan::New("R3").ToLocalChecked(), Mat::Converter::wrap(R3));
      Nan::Set(ret, Nan::New("P1").ToLocalChecked(), Mat::Converter::wrap(P1));
      Nan::Set(ret, Nan::New("P2").ToLocalChecked(), Mat::Converter::wrap(P2));
      Nan::Set(ret, Nan::New("P3").ToLocalChecked(), Mat::Converter::wrap(P3));
      Nan::Set(ret, Nan::New("Q").ToLocalChecked(), Mat::Converter::wrap(Q));
      Nan::Set(ret, Nan::New("roi1").ToLocalChecked(), Rect::Converter::wrap(roi1));
      Nan::Set(ret, Nan::New("roi2").ToLocalChecked(), Rect::Converter::wrap(roi2));
      return ret;
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        FF::DoubleArrayConverter::arg(0, &distCoeffs1, info) ||
        Mat::Converter::arg(1, &cameraMatrix2, info) ||
        FF::DoubleArrayConverter::arg(2, &distCoeffs2, info) ||
        Mat::Converter::arg(3, &cameraMatrix3, info) ||
        FF::DoubleArrayConverter::arg(4, &distCoeffs3, info) ||
        Point2::ArrayWithCastConverter<cv::Point2f>::arg(5, &imgpt1, info) ||
        Point2::ArrayWithCastConverter<cv::Point2f>::arg(6, &imgpt3, info) ||
        Size::Converter::arg(7, &imageSize, info) ||
        Mat::Converter::arg(8, &R12, info) ||
        Vec3::Converter::arg(9, &T12, info) ||
        Mat::Converter::arg(10, &R13, info) ||
        Vec3::Converter::arg(11, &T13, info) ||
        FF::DoubleConverter::arg(12, &alpha, info) ||
        Size::Converter::arg(13, &newImgSize, info) ||
        FF::IntConverter::arg(14, &flags, info)
      );
    }
  };
  
  struct GetOptimalNewCameraMatrixWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    GetOptimalNewCameraMatrixWorker(cv::Mat self) {
      this->self = self;
    }
  
    std::vector<double> distCoeffs;
    cv::Size2d imageSize;
    double alpha;
    cv::Size2d newImgSize = cv::Size2d();
    bool centerPrincipalPoint = false;
  
    cv::Mat out;
    cv::Rect validPixROI;
  
    std::string executeCatchCvExceptionWorker() {
      out = cv::getOptimalNewCameraMatrix(self, distCoeffs, imageSize, alpha, newImgSize, &validPixROI, centerPrincipalPoint);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("out").ToLocalChecked(), Mat::Converter::wrap(out));
      Nan::Set(ret, Nan::New("validPixROI").ToLocalChecked(), Rect::Converter::wrap(validPixROI));
      return ret;
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        FF::DoubleArrayConverter::arg(0, &distCoeffs, info) ||
        Size::Converter::arg(1, &imageSize, info) ||
        FF::DoubleConverter::arg(2, &alpha, info)
      );
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Size::Converter::optArg(3, &newImgSize, info) ||
        FF::BoolConverter::optArg(4, &centerPrincipalPoint, info)
      );
    }
  
    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF::isArgObject(info, 3);
    }
  
    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      v8::Local<v8::Object> opts = info[3]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
      return (
        Size::Converter::optProp(&newImgSize, "newImgSize", opts) ||
        FF::BoolConverter::optProp(&centerPrincipalPoint, "centerPrincipalPoint", opts)
      );
    }
  };;
  
  struct DecomposeEssentialMatWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    DecomposeEssentialMatWorker(cv::Mat self) {
      this->self = self;
    }
  
    cv::Mat R1;
    cv::Mat R2;
    cv::Vec3d T;
  
    std::string executeCatchCvExceptionWorker() {
      cv::decomposeEssentialMat(self, R1, R2, T);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("R1").ToLocalChecked(), Mat::Converter::wrap(R1));
      Nan::Set(ret, Nan::New("R2").ToLocalChecked(), Mat::Converter::wrap(R2));
      Nan::Set(ret, Nan::New("T").ToLocalChecked(), Vec3::Converter::wrap(T));
      return ret;
    }
  };
  
  struct TriangulatePointsWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    TriangulatePointsWorker(cv::Mat self) {
      this->self = self;
    }
  
    cv::Mat projMatr2;
    std::vector<cv::Point2d> projPoints1;
    std::vector<cv::Point2d> projPoints2;
  
    cv::Mat points4D;
  
    std::string executeCatchCvExceptionWorker() {
      cv::triangulatePoints(self, projMatr2, projPoints1, projPoints2, points4D);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      return Mat::Converter::wrap(points4D);
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::arg(0, &projMatr2, info) ||
        Point2::ArrayConverter::arg(1, &projPoints1, info) ||
        Point2::ArrayConverter::arg(2, &projPoints2, info)
      );
    }
  };
  
  struct CorrectMatchesWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    CorrectMatchesWorker(cv::Mat self) {
      this->self = self;
    }
  
    std::vector<cv::Point2f> points1;
    std::vector<cv::Point2f> points2;
  
    std::vector<cv::Point2f> newPoints1;
    std::vector<cv::Point2f> newPoints2;
  
    std::string executeCatchCvExceptionWorker() {
      cv::correctMatches(self, points1, points2, newPoints1, newPoints2);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("newPoints1").ToLocalChecked(), Point2::ArrayWithCastConverter<cv::Point2f>::wrap(newPoints1));
      Nan::Set(ret, Nan::New("newPoints2").ToLocalChecked(), Point2::ArrayWithCastConverter<cv::Point2f>::wrap(newPoints2));
      return ret;
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Point2::ArrayWithCastConverter<cv::Point2f>::arg(0, &points1, info) ||
        Point2::ArrayWithCastConverter<cv::Point2f>::arg(1, &points2, info)
      );
    }
  };
  
  struct FilterSpecklesWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    FilterSpecklesWorker(cv::Mat self) {
      this->self = self;
    }
  
    double newVal;
    int maxSpeckleSize;
    double maxDiff;
  
    std::string executeCatchCvExceptionWorker() {
      cv::filterSpeckles(self, newVal, maxSpeckleSize, maxDiff, cv::noArray());
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      return ret;
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        FF::DoubleConverter::arg(0, &newVal, info) ||
        FF::IntConverter::arg(1, &maxSpeckleSize, info) ||
        FF::DoubleConverter::arg(2, &maxDiff, info)
      );
    }
  };
  
  struct ValidateDisparityWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    ValidateDisparityWorker(cv::Mat self) {
      this->self = self;
    }
  
    cv::Mat cost;
    int minDisparity;
    int numberOfDisparities;
    int disp12MaxDisp = 1;
  
  
    std::string executeCatchCvExceptionWorker() {
      cv::validateDisparity(self, cost, minDisparity, numberOfDisparities, disp12MaxDisp);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      return ret;
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::arg(0, &cost, info) ||
        FF::IntConverter::arg(1, &minDisparity, info) ||
        FF::IntConverter::arg(2, &numberOfDisparities, info)
      );
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        FF::IntConverter::optArg(3, &disp12MaxDisp, info)
      );
    }
  };
  
  struct ReprojectImageTo3DWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    ReprojectImageTo3DWorker(cv::Mat self) {
      this->self = self;
    }
  
    cv::Mat Q;
    bool handleMissingValues = false;
    int ddepth = -1;
  
    cv::Mat _3dImage;
  
    std::string executeCatchCvExceptionWorker() {
      cv::reprojectImageTo3D(self, _3dImage, Q, handleMissingValues, ddepth);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      return Mat::Converter::wrap(_3dImage);
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::arg(0, &Q, info)
      );
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        FF::BoolConverter::optArg(1, &handleMissingValues, info) ||
        FF::IntConverter::optArg(2, &ddepth, info)
      );
    }
  
    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF::isArgObject(info, 1);
    }
  
    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      v8::Local<v8::Object> opts = info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
      return (
        FF::BoolConverter::optProp(&handleMissingValues, "handleMissingValues", opts) ||
        FF::IntConverter::optProp(&ddepth, "ddepth", opts)
      );
    }
  };
  
  struct DecomposeHomographyMatWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    DecomposeHomographyMatWorker(cv::Mat self) {
      this->self = self;
    }
  
    cv::Mat K;
  
    int returnValue;
    std::vector<cv::Mat> rotations;
    std::vector<cv::Mat> translations;
    std::vector<cv::Mat> normals;
  
    std::string executeCatchCvExceptionWorker() {
      returnValue = cv::decomposeHomographyMat(self, K, rotations, translations, normals);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("returnValue").ToLocalChecked(), FF::IntConverter::wrap(returnValue));
      Nan::Set(ret, Nan::New("rotations").ToLocalChecked(), Mat::ArrayConverter::wrap(rotations));
      Nan::Set(ret, Nan::New("translations").ToLocalChecked(), Mat::ArrayConverter::wrap(translations));
      Nan::Set(ret, Nan::New("normals").ToLocalChecked(), Mat::ArrayConverter::wrap(normals));
      return ret;
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::arg(0, &K, info)
      );
    }
  };

#if CV_VERSION_GREATER_EQUAL(3, 1, 0)
  struct FindEssentialMatWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    FindEssentialMatWorker(cv::Mat self) {
      this->self = self;
    }
  
    std::vector<cv::Point2f> points1;
    std::vector<cv::Point2f> points2;
    int method = cv::RANSAC;
    double prob = 0.999;
    double threshold = 1.0;
  
    cv::Mat E;
    cv::Mat mask = cv::noArray().getMat();
  
    std::string executeCatchCvExceptionWorker() {
      E = cv::findEssentialMat(points1, points2, self, method, prob, threshold, mask);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("E").ToLocalChecked(), Mat::Converter::wrap(E));
      Nan::Set(ret, Nan::New("mask").ToLocalChecked(), Mat::Converter::wrap(mask));
      return ret;
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Point2::ArrayWithCastConverter<cv::Point2f>::arg(0, &points1, info) ||
        Point2::ArrayWithCastConverter<cv::Point2f>::arg(1, &points2, info)
        );
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        FF::IntConverter::optArg(2, &method, info) ||
        FF::DoubleConverter::optArg(3, &prob, info) ||
        FF::DoubleConverter::optArg(4, &threshold, info)
        );
    }
  
    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF::isArgObject(info, 2);
    }
  
    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      v8::Local<v8::Object> opts = info[2]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
      return (
        FF::IntConverter::optProp(&method, "method", opts) ||
        FF::DoubleConverter::optProp(&prob, "prob", opts) ||
        FF::DoubleConverter::optProp(&threshold, "threshold", opts)
      );
    }
  };
  
  struct RecoverPoseWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat self;
    RecoverPoseWorker(cv::Mat self) {
      this->self = self;
    }
  
    cv::Mat E;
    std::vector<cv::Point2f> points1;
    std::vector<cv::Point2f> points2;
    cv::Mat mask = cv::noArray().getMat();
  
    int returnValue;
    cv::Mat R;
    cv::Vec3d T;
  
    std::string executeCatchCvExceptionWorker() {
      returnValue = cv::recoverPose(E, points1, points2, self, R, T, mask);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("returnValue").ToLocalChecked(), FF::IntConverter::wrap(returnValue));
      Nan::Set(ret, Nan::New("R").ToLocalChecked(), Mat::Converter::wrap(R));
      Nan::Set(ret, Nan::New("T").ToLocalChecked(), Vec3::Converter::wrap(T));
      return ret;
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::arg(0, &E, info) ||
        Point2::ArrayWithCastConverter<cv::Point2f>::arg(1, &points1, info) ||
        Point2::ArrayWithCastConverter<cv::Point2f>::arg(2, &points2, info)
      );
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::optArg(3, &mask, info)
      );
    }
  };

#endif

#if CV_VERSION_GREATER_EQUAL(4, 0, 0)
  // since 4.0.0 cv::undistort has been moved from imgproc to calib3d
  class Undistort : public CvBinding {
  public:
	  void setup(cv::Mat self) {
		  auto cameraMatrix = req<Mat::Converter>();
		  auto distCoeffs = req<Mat::Converter>();
		  auto undistortedMat = ret<Mat::Converter>("undistortedMat");

		  executeBinding = [=]() {
			  cv::undistort(self, undistortedMat->ref(), cameraMatrix->ref(), distCoeffs->ref());
		  };
	  };
  };
#endif
  

}

#endif