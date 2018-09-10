#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp>
#include "Mat.h"
#include "Point.h"
#include "CatchCvExceptionWorker.h"
#include "TermCriteria.h"
#include "Rect.h"
#include "macros.h"

#ifndef __FF_CALIB3DBINDINGS_H__
#define __FF_CALIB3DBINDINGS_H__

namespace Calib3dBindings {

  struct ComposeRTWorker : public CatchCvExceptionWorker {
  public:
    cv::Vec3d rvec1;
    cv::Vec3d tvec1;
    cv::Vec3d rvec2;
    cv::Vec3d tvec2;
  
    cv::Vec3d rvec3;
    cv::Vec3d tvec3;
    cv::Mat dr3dr1;
    cv::Mat dr3dt1;
    cv::Mat dr3dr2;
    cv::Mat dr3dt2;
    cv::Mat dt3dr1;
    cv::Mat dt3dt1;
    cv::Mat dt3dr2;
    cv::Mat dt3dt2;
  
    std::string executeCatchCvExceptionWorker() {
      cv::composeRT(rvec1, tvec1, rvec2, tvec2, rvec3, tvec3, dr3dr1, dr3dt1, dr3dr2, dr3dt2, dt3dr1, dt3dt1, dt3dr2, dt3dt2);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("rvec3").ToLocalChecked(), Vec3::Converter::wrap(rvec3));
      Nan::Set(ret, Nan::New("tvec3").ToLocalChecked(), Vec3::Converter::wrap(tvec3));
      Nan::Set(ret, Nan::New("dr3dr1").ToLocalChecked(), Mat::Converter::wrap(dr3dr1));
      Nan::Set(ret, Nan::New("dr3dt1").ToLocalChecked(), Mat::Converter::wrap(dr3dt1));
      Nan::Set(ret, Nan::New("dr3dr2").ToLocalChecked(), Mat::Converter::wrap(dr3dr2));
      Nan::Set(ret, Nan::New("dr3dt2").ToLocalChecked(), Mat::Converter::wrap(dr3dt2));
      Nan::Set(ret, Nan::New("dt3dr1").ToLocalChecked(), Mat::Converter::wrap(dt3dr1));
      Nan::Set(ret, Nan::New("dt3dt1").ToLocalChecked(), Mat::Converter::wrap(dt3dt1));
      Nan::Set(ret, Nan::New("dt3dr2").ToLocalChecked(), Mat::Converter::wrap(dt3dr2));
      Nan::Set(ret, Nan::New("dt3dt2").ToLocalChecked(), Mat::Converter::wrap(dt3dt2));
      return ret;
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Vec3::Converter::arg(0, &rvec1, info) ||
        Vec3::Converter::arg(1, &tvec1, info) ||
        Vec3::Converter::arg(2, &rvec2, info) ||
        Vec3::Converter::arg(3, &tvec2, info)
      );
    }
  };
  
  struct SolvePxPWorker : public CatchCvExceptionWorker {
  public:
    std::vector<cv::Point3d> objectPoints;
    std::vector<cv::Point2d> imagePoints;
    cv::Mat cameraMatrix;
    std::vector<double> distCoeffs;
  
    bool returnValue;
    cv::Vec3d rvec;
    cv::Vec3d tvec;
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("returnValue").ToLocalChecked(), BoolConverter::wrap(returnValue));
      Nan::Set(ret, Nan::New("rvec").ToLocalChecked(), Vec3::Converter::wrap(rvec));
      Nan::Set(ret, Nan::New("tvec").ToLocalChecked(), Vec3::Converter::wrap(tvec));
      return ret;
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        ObjectArrayConverter<Point3, cv::Point3d>::arg(0, &objectPoints, info) ||
        ObjectArrayConverter<Point2, cv::Point2d>::arg(1, &imagePoints, info) ||
        Mat::Converter::arg(2, &cameraMatrix, info) ||
        DoubleArrayConverter::arg(3, &distCoeffs, info)
      );
    }
  };
  
  struct SolvePnPWorker : public SolvePxPWorker {
  public:
    bool useExtrinsicGuess = false;
    int flags = cv::SOLVEPNP_ITERATIVE;
  
    std::string executeCatchCvExceptionWorker() {
      returnValue = cv::solvePnP(objectPoints, imagePoints, cameraMatrix, distCoeffs, rvec, tvec, useExtrinsicGuess, flags);
      return "";
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        BoolConverter::optArg(4, &useExtrinsicGuess, info) ||
        IntConverter::optArg(5, &flags, info)
      );
    }
  
    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF_ARG_IS_OBJECT(4);
    }
  
    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      v8::Local<v8::Object> opts = info[4]->ToObject();
      return (
        BoolConverter::optProp(&useExtrinsicGuess, "useExtrinsicGuess", opts) ||
        IntConverter::optProp(&flags, "flags", opts)
      );
    }
  };
  
  struct SolvePnPRansacWorker : public SolvePxPWorker {
  public:
    bool useExtrinsicGuess = false;
    int iterationsCount = 100;
    float reprojectionError = 8.0;
    double confidence = 0.99;
    int flags = cv::SOLVEPNP_ITERATIVE;
  
    std::vector<int> inliers;
  
    std::string executeCatchCvExceptionWorker() {
      returnValue = cv::solvePnPRansac(objectPoints, imagePoints, cameraMatrix, distCoeffs, rvec, tvec, useExtrinsicGuess, iterationsCount, reprojectionError, confidence, inliers, flags);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = SolvePxPWorker::getReturnValue()->ToObject();
      Nan::Set(ret, Nan::New("inliers").ToLocalChecked(), IntArrayConverter::wrap(inliers));
      return ret;
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        BoolConverter::optArg(4, &useExtrinsicGuess, info) ||
        IntConverter::optArg(5, &iterationsCount, info) ||
        FloatConverter::optArg(6, &reprojectionError, info) ||
        DoubleConverter::optArg(7, &confidence, info) ||
        IntConverter::optArg(8, &flags, info)
      );
    }
  
    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF_ARG_IS_OBJECT(4);
    }
  
    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      v8::Local<v8::Object> opts = info[4]->ToObject();
      return (
        BoolConverter::optProp(&useExtrinsicGuess, "useExtrinsicGuess", opts) ||
        IntConverter::optProp(&iterationsCount, "iterationsCount", opts) ||
        FloatConverter::optProp(&reprojectionError, "reprojectionError", opts) ||
        DoubleConverter::optProp(&confidence, "confidence", opts) ||
        IntConverter::optProp(&flags, "flags", opts)
      );
    }
  };
  
  struct ProjectPointsWorker : public CatchCvExceptionWorker {
  public:
    std::vector<cv::Point3d> objectPoints;
    cv::Vec3d rvec;
    cv::Vec3d tvec;
    cv::Mat cameraMatrix;
    std::vector<double> distCoeffs;
    double aspectRatio = 0;
  
    std::vector<cv::Point2d> imagePoints;
    cv::Mat jacobian;
  
    std::string executeCatchCvExceptionWorker() {
      cv::projectPoints(objectPoints, rvec, tvec, cameraMatrix, distCoeffs, imagePoints, jacobian, aspectRatio);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("imagePoints").ToLocalChecked(), ObjectArrayConverter<Point2, cv::Point2d>::wrap(imagePoints));
      Nan::Set(ret, Nan::New("jacobian").ToLocalChecked(), Mat::Converter::wrap(jacobian));
      return ret;
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        ObjectArrayConverter<Point3, cv::Point3d>::arg(0, &objectPoints, info) ||
        Vec3::Converter::arg(1, &rvec, info) ||
        Vec3::Converter::arg(2, &tvec, info) ||
        Mat::Converter::arg(3, &cameraMatrix, info) ||
        DoubleArrayConverter::arg(4, &distCoeffs, info)
      );
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        DoubleConverter::optArg(5, &aspectRatio, info)
      );
    }
  };
  
  struct InitCameraMatrix2DWorker : public CatchCvExceptionWorker {
  public:
    std::vector<std::vector<cv::Point3f>> objectPoints;
    std::vector<std::vector<cv::Point2f>> imagePoints;
    cv::Size2d imageSize;
    double aspectRatio = 1.0;
  
    cv::Mat returnValue;
  
    std::string executeCatchCvExceptionWorker() {
      returnValue = cv::initCameraMatrix2D(objectPoints, imagePoints, imageSize, aspectRatio);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      return Mat::Converter::wrap(returnValue);
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        ObjectArrayOfArraysConverter<Point3, cv::Point3d, cv::Point3f>::arg(0, &objectPoints, info) ||
        ObjectArrayOfArraysConverter<Point2, cv::Point2d, cv::Point2f>::arg(1, &imagePoints, info) ||
        Size::Converter::arg(2, &imageSize, info)
      );
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        DoubleConverter::optArg(3, &aspectRatio, info)
      );
    }
  };
  
  struct StereoCalibrateWorker : public CatchCvExceptionWorker {
  public:
    std::vector<std::vector<cv::Point3f>> objectPoints;
    std::vector<std::vector<cv::Point2f>> imagePoints1;
    std::vector<std::vector<cv::Point2f>> imagePoints2;
    cv::Mat cameraMatrix1;
    std::vector<double> distCoeffs1;
    cv::Mat cameraMatrix2;
    std::vector<double> distCoeffs2;
    cv::Size2d imageSize;
    int flags = cv::CALIB_FIX_INTRINSIC;
    cv::TermCriteria criteria = cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, 30, 1e-6);
  
    double returnValue;
    cv::Mat R;
    cv::Vec3d T;
    cv::Mat E;
    cv::Mat F;
  
    std::string executeCatchCvExceptionWorker() {
      returnValue = cv::stereoCalibrate(objectPoints, imagePoints1, imagePoints2, cameraMatrix1, distCoeffs1, cameraMatrix2, distCoeffs2, imageSize, R, T, E, F, flags, criteria);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("returnValue").ToLocalChecked(), DoubleConverter::wrap(returnValue));
      Nan::Set(ret, Nan::New("R").ToLocalChecked(), Mat::Converter::wrap(R));
      Nan::Set(ret, Nan::New("T").ToLocalChecked(), Vec3::Converter::wrap(T));
      Nan::Set(ret, Nan::New("E").ToLocalChecked(), Mat::Converter::wrap(E));
      Nan::Set(ret, Nan::New("F").ToLocalChecked(), Mat::Converter::wrap(F));
      Nan::Set(ret, Nan::New("distCoeffs1").ToLocalChecked(), DoubleArrayConverter::wrap(distCoeffs1));
      Nan::Set(ret, Nan::New("distCoeffs2").ToLocalChecked(), DoubleArrayConverter::wrap(distCoeffs2));
      return ret;
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        ObjectArrayOfArraysConverter<Point3, cv::Point3d, cv::Point3f>::arg(0, &objectPoints, info) ||
        ObjectArrayOfArraysConverter<Point2, cv::Point2d, cv::Point2f>::arg(1, &imagePoints1, info) ||
        ObjectArrayOfArraysConverter<Point2, cv::Point2d, cv::Point2f>::arg(2, &imagePoints2, info) ||
        Mat::Converter::arg(3, &cameraMatrix1, info) ||
        DoubleArrayConverter::arg(4, &distCoeffs1, info) ||
        Mat::Converter::arg(5, &cameraMatrix2, info) ||
        DoubleArrayConverter::arg(6, &distCoeffs2, info) ||
        Size::Converter::arg(7, &imageSize, info)
      );
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        IntConverter::optArg(8, &flags, info) ||
        TermCriteria::Converter::optArg(9, &criteria, info)
      );
    }
  
    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF_ARG_IS_OBJECT(8);
    }
  
    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      v8::Local<v8::Object> opts = info[8]->ToObject();
      return (
        IntConverter::optProp(&flags, "flags", opts) ||
        TermCriteria::Converter::optProp(&criteria, "criteria", opts)
        );
    }
  };
  
  struct StereoRectifyUncalibratedWorker : public CatchCvExceptionWorker {
  public:
    std::vector<cv::Point2d> points1;
    std::vector<cv::Point2d> points2;
    cv::Mat F;
    cv::Size2d imgSize;
    double threshold = 5;
  
    bool returnValue;
    cv::Mat H1;
    cv::Mat H2;
  
    std::string executeCatchCvExceptionWorker() {
      returnValue = cv::stereoRectifyUncalibrated(points1, points2, F, imgSize, H1, H2, threshold);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("returnValue").ToLocalChecked(), BoolConverter::wrap(returnValue));
      Nan::Set(ret, Nan::New("H1").ToLocalChecked(), Mat::Converter::wrap(H1));
      Nan::Set(ret, Nan::New("H2").ToLocalChecked(), Mat::Converter::wrap(H2));
      return ret;
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        ObjectArrayConverter<Point2, cv::Point2d>::arg(0, &points1, info) ||
        ObjectArrayConverter<Point2, cv::Point2d>::arg(1, &points2, info) ||
        Mat::Converter::arg(2, &F, info) ||
        Size::Converter::arg(3, &imgSize, info)
      );
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        DoubleConverter::optArg(4, &threshold, info)
      );
    }
  };
  
  struct FindFundamentalMatWorker : public CatchCvExceptionWorker {
  public:
    std::vector<cv::Point2d> points1;
    std::vector<cv::Point2d> points2;
    int method = cv::FM_RANSAC;
    double param1 = 3.0;
    double param2 = 0.99;
  
    cv::Mat F;
    cv::Mat mask;
  
    std::string executeCatchCvExceptionWorker() {
      F = cv::findFundamentalMat(points1, points2, method, param1, param2, mask);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("F").ToLocalChecked(), Mat::Converter::wrap(F));
      Nan::Set(ret, Nan::New("mask").ToLocalChecked(), Mat::Converter::wrap(mask));
      return ret;
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        ObjectArrayConverter<Point2, cv::Point2d>::arg(0, &points1, info) ||
        ObjectArrayConverter<Point2, cv::Point2d>::arg(1, &points2, info)
      );
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        IntConverter::optArg(2, &method, info) ||
        DoubleConverter::optArg(3, &param1, info) ||
        DoubleConverter::optArg(4, &param2, info)
      );
    }
  
    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF_ARG_IS_OBJECT(2);
    }
  
    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      v8::Local<v8::Object> opts = info[2]->ToObject();
      return (
        IntConverter::optProp(&method, "method", opts) ||
        DoubleConverter::optProp(&param1, "param1", opts) ||
        DoubleConverter::optProp(&param2, "param2", opts)
      );
    }
  };
  
  struct FindEssentialMatWorker : public CatchCvExceptionWorker {
  public:
    std::vector<cv::Point2d> points1;
    std::vector<cv::Point2d> points2;
    double focal = 1.0;
    cv::Point2d pp = cv::Point2d(0, 0);
    int method = cv::RANSAC;
    double prob = 0.999;
    double threshold = 1.0;
  
    cv::Mat E;
    cv::Mat mask = cv::noArray().getMat();
  
    std::string executeCatchCvExceptionWorker() {
      E = cv::findEssentialMat(points1, points2, focal, pp, method, prob, threshold, mask);
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
        ObjectArrayConverter<Point2, cv::Point2d>::arg(0, &points1, info) ||
        ObjectArrayConverter<Point2, cv::Point2d>::arg(1, &points2, info)
      );
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        DoubleConverter::optArg(2, &focal, info) ||
        Point2::Converter::optArg(3, &pp, info) ||
        IntConverter::optArg(4, &method, info) ||
        DoubleConverter::optArg(5, &prob, info) ||
        DoubleConverter::optArg(6, &threshold, info)
        );
    }
  
    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF_ARG_IS_OBJECT(2);
    }
  
    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      v8::Local<v8::Object> opts = info[2]->ToObject();
      return (
        DoubleConverter::optProp(&focal, "focal", opts) ||
        Point2::Converter::optProp(&pp, "pp", opts) ||
        IntConverter::optProp(&method, "method", opts) ||
        DoubleConverter::optProp(&prob, "prob", opts) ||
        DoubleConverter::optProp(&threshold, "threshold", opts)
      );
    }
  };
  
  struct RecoverPoseWorker : public CatchCvExceptionWorker {
  public:
    cv::Mat E;
    std::vector<cv::Point2d> points1;
    std::vector<cv::Point2d> points2;
    double focal = 1.0;
    cv::Point2d pp = cv::Point2d(0, 0);
    cv::Mat mask = cv::noArray().getMat();
  
    int returnValue;
    cv::Mat R;
    cv::Vec3d T;
  
    std::string executeCatchCvExceptionWorker() {
      returnValue = cv::recoverPose(E, points1, points2, R, T, focal, pp, mask);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("returnValue").ToLocalChecked(), IntConverter::wrap(returnValue));
      Nan::Set(ret, Nan::New("R").ToLocalChecked(), Mat::Converter::wrap(R));
      Nan::Set(ret, Nan::New("T").ToLocalChecked(), Vec3::Converter::wrap(T));
      return ret;
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Mat::Converter::arg(0, &E, info) ||
        ObjectArrayConverter<Point2, cv::Point2d>::arg(1, &points1, info) ||
        ObjectArrayConverter<Point2, cv::Point2d>::arg(2, &points2, info)
      );
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        DoubleConverter::optArg(3, &focal, info) ||
        Point2::Converter::optArg(4, &pp, info) ||
        Mat::Converter::optArg(5, &mask, info)
      );
    }
  
    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF_ARG_IS_OBJECT(3);
    }
  
    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      v8::Local<v8::Object> opts = info[3]->ToObject();
      return (
        DoubleConverter::optProp(&focal, "focal", opts) ||
        Point2::Converter::optProp(&pp, "pp", opts) ||
        Mat::Converter::optProp(&mask, "mask", opts)
      );
    }
  };
  
  struct ComputeCorrespondEpilinesWorker : public CatchCvExceptionWorker {
  public:
    std::vector<cv::Point2d> points;
    int whichImage;
    cv::Mat F;
  
    std::vector<cv::Point3d> lines;
  
    std::string executeCatchCvExceptionWorker() {
      cv::computeCorrespondEpilines(points, whichImage, F, lines);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      return ObjectArrayConverter<Point3, cv::Point3d>::wrap(lines);
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        ObjectArrayConverter<Point2, cv::Point2d>::arg(0, &points, info) ||
        IntConverter::arg(1, &whichImage, info) ||
        Mat::Converter::arg(2, &F, info)
      );
    }
  };
  
  struct GetValidDisparityROIWorker : public CatchCvExceptionWorker {
  public:
    cv::Rect2d roi1;
    cv::Rect2d roi2;
    int minDisparity;
    int numberOfDisparities;
    int SADWindowSize;
  
    cv::Rect2d returnValue;
  
    std::string executeCatchCvExceptionWorker() {
      returnValue = cv::getValidDisparityROI(roi1, roi2, minDisparity, numberOfDisparities, SADWindowSize);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      return Rect::Converter::wrap(returnValue);
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Rect::Converter::arg(0, &roi1, info) ||
        Rect::Converter::arg(1, &roi2, info) ||
        IntConverter::arg(2, &minDisparity, info) ||
        IntConverter::arg(3, &numberOfDisparities, info) ||
        IntConverter::arg(4, &SADWindowSize, info)
      );
    }
  };
  
  struct EstimateAffine3DWorker : public CatchCvExceptionWorker {
  public:
    std::vector<cv::Point3d> src;
    std::vector<cv::Point3d> dst;
    double ransacThreshold = 3;
    double confidence = 0.99;
  
    int returnValue;
    cv::Mat out;
    cv::Mat inliers;
  
    std::string executeCatchCvExceptionWorker() {
      returnValue = cv::estimateAffine3D(src, dst, out, inliers, ransacThreshold, confidence);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("returnValue").ToLocalChecked(), IntConverter::wrap(returnValue));
      Nan::Set(ret, Nan::New("out").ToLocalChecked(), Mat::Converter::wrap(out));
      Nan::Set(ret, Nan::New("inliers").ToLocalChecked(), Mat::Converter::wrap(inliers));
      return ret;
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        ObjectArrayConverter<Point3, cv::Point3d>::arg(0, &src, info) ||
        ObjectArrayConverter<Point3, cv::Point3d>::arg(1, &dst, info)
      );
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        DoubleConverter::optArg(2, &ransacThreshold, info) ||
        DoubleConverter::optArg(3, &confidence, info)
      );
    }
  
    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF_ARG_IS_OBJECT(2);
    }
  
    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      v8::Local<v8::Object> opts = info[2]->ToObject();
      return (
        DoubleConverter::optProp(&ransacThreshold, "ransacThreshold", opts) ||
        DoubleConverter::optProp(&confidence, "confidence", opts)
      );
    }
  };

#if CV_VERSION_MINOR > 0
  struct SampsonDistanceWorker : public CatchCvExceptionWorker {
  public:
    cv::Vec2d pt1;
    cv::Vec2d pt2;
    cv::Mat F;
  
    double returnValue;
  
    std::string executeCatchCvExceptionWorker() {
      returnValue = cv::sampsonDistance(pt1, pt2, F);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      return DoubleConverter::wrap(returnValue);
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        Vec2::Converter::arg(0, &pt1, info) ||
        Vec2::Converter::arg(1, &pt2, info) ||
        Mat::Converter::arg(2, &F, info)
      );
    }
  };
  
  struct CalibrateCameraWorker : public CatchCvExceptionWorker {
  public:
    std::vector<std::vector<cv::Point3f>> objectPoints;
    std::vector<std::vector<cv::Point2f>> imagePoints;
    cv::Size2d imageSize;
    cv::Mat cameraMatrix;
    std::vector<double> distCoeffs;
    int flags = 0;
    cv::TermCriteria criteria = cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, 30, DBL_EPSILON);
  
    double returnValue;
    std::vector<cv::Vec3d> rvecs;
    std::vector<cv::Vec3d> tvecs;
  
    cv::Mat _rvecs;
    cv::Mat _tvecs;
  
    std::string executeCatchCvExceptionWorker() {
      returnValue = cv::calibrateCamera(objectPoints, imagePoints, imageSize, cameraMatrix, distCoeffs, rvecs, tvecs, flags, criteria);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("returnValue").ToLocalChecked(), DoubleConverter::wrap(returnValue));
      Nan::Set(ret, Nan::New("rvecs").ToLocalChecked(), ObjectArrayConverter<Vec3, cv::Vec3d>::wrap(rvecs));
      Nan::Set(ret, Nan::New("tvecs").ToLocalChecked(), ObjectArrayConverter<Vec3, cv::Vec3d>::wrap(tvecs));
      Nan::Set(ret, Nan::New("distCoeffs").ToLocalChecked(), DoubleArrayConverter::wrap(distCoeffs));
      return ret;
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        ObjectArrayOfArraysConverter<Point3, cv::Point3d, cv::Point3f>::arg(0, &objectPoints, info) ||
        ObjectArrayOfArraysConverter<Point2, cv::Point2d, cv::Point2f>::arg(1, &imagePoints, info) ||
        Size::Converter::arg(2, &imageSize, info) ||
        Mat::Converter::arg(3, &cameraMatrix, info) ||
        DoubleArrayConverter::arg(4, &distCoeffs, info)
        );
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        IntConverter::optArg(5, &flags, info) ||
        TermCriteria::Converter::optArg(6, &criteria, info)
        );
    }
  
    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF_ARG_IS_OBJECT(5);
    }
  
    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      v8::Local<v8::Object> opts = info[5]->ToObject();
      return (
        IntConverter::optProp(&flags, "flags", opts) ||
        TermCriteria::Converter::optProp(&criteria, "criteria", opts)
        );
    }
  };
#endif

#if CV_VERSION_MINOR > 1 
  struct CalibrateCameraExtendedWorker : public CalibrateCameraWorker {
  public:
    cv::Mat stdDeviationsIntrinsics;
    cv::Mat stdDeviationsExtrinsics;
    std::vector<double> perViewErrors;
  
    std::string executeCatchCvExceptionWorker() {
      returnValue = cv::calibrateCamera(objectPoints, imagePoints, imageSize, cameraMatrix, distCoeffs, rvecs, tvecs, stdDeviationsIntrinsics, stdDeviationsExtrinsics, perViewErrors, flags, criteria);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = CalibrateCameraWorker::getReturnValue()->ToObject();
      Nan::Set(ret, Nan::New("stdDeviationsIntrinsics").ToLocalChecked(), Mat::Converter::wrap(stdDeviationsIntrinsics));
      Nan::Set(ret, Nan::New("stdDeviationsExtrinsics").ToLocalChecked(), Mat::Converter::wrap(stdDeviationsExtrinsics));
      Nan::Set(ret, Nan::New("perViewErrors").ToLocalChecked(), DoubleArrayConverter::wrap(perViewErrors));
      return ret;
    }
  };
  
  struct EstimateAffine2DWorker : public CatchCvExceptionWorker {
  public:
    std::vector<cv::Point2d> from;
    std::vector<cv::Point2d> to;
    int method = cv::RANSAC;
    double ransacReprojThreshold = 3;
    int maxIters = 2000;
    double confidence = 0.99;
    int refineIters = 10;
  
    cv::Mat out;
    cv::Mat inliers;
  
    std::string executeCatchCvExceptionWorker() {
      out = cv::estimateAffine2D(from, to, inliers, method, ransacReprojThreshold, maxIters, confidence, refineIters);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("out").ToLocalChecked(), Mat::Converter::wrap(out));
      Nan::Set(ret, Nan::New("inliers").ToLocalChecked(), Mat::Converter::wrap(inliers));
      return ret;
    }
  
    bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        ObjectArrayConverter<Point2, cv::Point2d>::arg(0, &from, info) ||
        ObjectArrayConverter<Point2, cv::Point2d>::arg(1, &to, info)
      );
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        IntConverter::optArg(2, &method, info) ||
        DoubleConverter::optArg(3, &ransacReprojThreshold, info) ||
        IntConverter::optArg(4, &maxIters, info) ||
        DoubleConverter::optArg(5, &confidence, info) ||
        IntConverter::optArg(6, &refineIters, info)
      );
    }
  
    bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
      return FF_ARG_IS_OBJECT(2);
    }
  
    bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
      v8::Local<v8::Object> opts = info[2]->ToObject();
      return (
        IntConverter::optProp(&method, "method", opts) ||
        DoubleConverter::optProp(&ransacReprojThreshold, "ransacReprojThreshold", opts) ||
        IntConverter::optProp(&maxIters, "maxIters", opts) ||
        DoubleConverter::optProp(&confidence, "confidence", opts) ||
        IntConverter::optProp(&refineIters, "refineIters", opts)
      );
    }
  };
  
  struct EstimateAffinePartial2DWorker : public EstimateAffine2DWorker {
    std::string executeCatchCvExceptionWorker() {
      out = cv::estimateAffinePartial2D(from, to, inliers, method, ransacReprojThreshold, maxIters, confidence, refineIters);
      return "";
    }
  };
#endif

#if CV_VERSION_MINOR > 2
  struct SolveP3PWorker : public SolvePxPWorker {
  public:
    int flags = cv::SOLVEPNP_P3P;
  
    bool returnValue;
    std::vector<cv::Mat> rvecs;
    std::vector<cv::Mat> tvecs;
  
    std::string executeCatchCvExceptionWorker() {
      returnValue = cv::solveP3P(objectPoints, imagePoints, cameraMatrix, distCoeffs, rvecs, tvecs, flags);
      return "";
    }
  
    v8::Local<v8::Value> getReturnValue() {
      v8::Local<v8::Object> ret = Nan::New<v8::Object>();
      Nan::Set(ret, Nan::New("returnValue").ToLocalChecked(), BoolConverter::wrap(returnValue));
      Nan::Set(ret, Nan::New("rvecs").ToLocalChecked(), ObjectArrayConverter<Mat, cv::Mat>::wrap(rvecs));
      Nan::Set(ret, Nan::New("tvecs").ToLocalChecked(), ObjectArrayConverter<Mat, cv::Mat>::wrap(tvecs));
      return ret;
    }
  
    bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
      return (
        IntConverter::optArg(4, &flags, info)
      );
    }
  };
#endif
  

}

#endif
