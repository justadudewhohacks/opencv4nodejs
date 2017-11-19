#include "MatCalib3d.h"

void MatCalib3d::Init(v8::Local<v8::FunctionTemplate> ctor) {
	Nan::SetPrototypeMethod(ctor, "rodrigues", Rodrigues);
	Nan::SetPrototypeMethod(ctor, "rodriguesAsync", RodriguesAsync);
	Nan::SetPrototypeMethod(ctor, "rqDecomp3x3", RQDecomp3x3);
	Nan::SetPrototypeMethod(ctor, "rqDecomp3x3Async", RQDecomp3x3Async);
	Nan::SetPrototypeMethod(ctor, "decomposeProjectionMatrix", DecomposeProjectionMatrix);
	Nan::SetPrototypeMethod(ctor, "decomposeProjectionMatrixAsync", DecomposeProjectionMatrixAsync);
	Nan::SetPrototypeMethod(ctor, "matMulDeriv", MatMulDeriv);
	Nan::SetPrototypeMethod(ctor, "matMulDerivAsync", MatMulDerivAsync);
	Nan::SetPrototypeMethod(ctor, "findChessboardCorners", FindChessboardCorners);
	Nan::SetPrototypeMethod(ctor, "findChessboardCornersAsync", FindChessboardCornersAsync);
	Nan::SetPrototypeMethod(ctor, "drawChessboardCorners", DrawChessboardCorners);
	Nan::SetPrototypeMethod(ctor, "drawChessboardCornersAsync", DrawChessboardCornersAsync);
	Nan::SetPrototypeMethod(ctor, "find4QuadCornerSubpix", Find4QuadCornerSubpix);
	Nan::SetPrototypeMethod(ctor, "find4QuadCornerSubpixAsync", Find4QuadCornerSubpixAsync);
	Nan::SetPrototypeMethod(ctor, "calibrationMatrixValues", CalibrationMatrixValues);
	Nan::SetPrototypeMethod(ctor, "calibrationMatrixValuesAsync", CalibrationMatrixValuesAsync);
	Nan::SetPrototypeMethod(ctor, "stereoRectify", StereoRectify);
	Nan::SetPrototypeMethod(ctor, "stereoRectifyAsync", StereoRectifyAsync);
	Nan::SetPrototypeMethod(ctor, "rectify3Collinear", Rectify3Collinear);
	Nan::SetPrototypeMethod(ctor, "rectify3CollinearAsync", Rectify3CollinearAsync);
	Nan::SetPrototypeMethod(ctor, "getOptimalNewCameraMatrix", GetOptimalNewCameraMatrix);
	Nan::SetPrototypeMethod(ctor, "getOptimalNewCameraMatrixAsync", GetOptimalNewCameraMatrixAsync);
	Nan::SetPrototypeMethod(ctor, "decomposeEssentialMat", DecomposeEssentialMat);
	Nan::SetPrototypeMethod(ctor, "decomposeEssentialMatAsync", DecomposeEssentialMatAsync);
	Nan::SetPrototypeMethod(ctor, "triangulatePoints", TriangulatePoints);
	Nan::SetPrototypeMethod(ctor, "triangulatePointsAsync", TriangulatePointsAsync);
	Nan::SetPrototypeMethod(ctor, "correctMatches", CorrectMatches);
	Nan::SetPrototypeMethod(ctor, "correctMatchesAsync", CorrectMatchesAsync);
	Nan::SetPrototypeMethod(ctor, "filterSpeckles", FilterSpeckles);
	Nan::SetPrototypeMethod(ctor, "filterSpecklesAsync", FilterSpecklesAsync);
	Nan::SetPrototypeMethod(ctor, "validateDisparity", ValidateDisparity);
	Nan::SetPrototypeMethod(ctor, "validateDisparityAsync", ValidateDisparityAsync);
	Nan::SetPrototypeMethod(ctor, "reprojectImageTo3D", ReprojectImageTo3D);
	Nan::SetPrototypeMethod(ctor, "reprojectImageTo3DAsync", ReprojectImageTo3DAsync);
	Nan::SetPrototypeMethod(ctor, "decomposeHomographyMat", DecomposeHomographyMat);
	Nan::SetPrototypeMethod(ctor, "decomposeHomographyMatAsync", DecomposeHomographyMatAsync);
#if CV_VERSION_MINOR > 0
	Nan::SetPrototypeMethod(ctor, "findEssentialMat", FindEssentialMat);
	Nan::SetPrototypeMethod(ctor, "findEssentialMatAsync", FindEssentialMatAsync);
	Nan::SetPrototypeMethod(ctor, "recoverPose", RecoverPose);
	Nan::SetPrototypeMethod(ctor, "recoverPoseAsync", RecoverPoseAsync);
#endif
};

struct MatCalib3d::RodriguesWorker : public SimpleWorker {
public:
	cv::Mat self;
	RodriguesWorker(cv::Mat self) {
		this->self = self;
	}

	cv::Mat dst;
	cv::Mat jacobian;

	const char* execute() {
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

NAN_METHOD(MatCalib3d::Rodrigues) {
	RodriguesWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::Rodrigues", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatCalib3d::RodriguesAsync) {
	RodriguesWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::RodriguesAsync", RodriguesWorker, worker);
}


struct MatCalib3d::RQDecomp3x3Worker : public SimpleWorker {
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

	const char* execute() {
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

NAN_METHOD(MatCalib3d::RQDecomp3x3) {
	RQDecomp3x3Worker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::RQDecomp3x3", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatCalib3d::RQDecomp3x3Async) {
	RQDecomp3x3Worker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::RQDecomp3x3Async", RQDecomp3x3Worker, worker);
}


struct MatCalib3d::DecomposeProjectionMatrixWorker : public SimpleWorker {
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

	const char* execute() {
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

NAN_METHOD(MatCalib3d::DecomposeProjectionMatrix) {
	DecomposeProjectionMatrixWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::DecomposeProjectionMatrix", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatCalib3d::DecomposeProjectionMatrixAsync) {
	DecomposeProjectionMatrixWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::DecomposeProjectionMatrixAsync", DecomposeProjectionMatrixWorker, worker);
}


struct MatCalib3d::MatMulDerivWorker : public SimpleWorker {
public:
	cv::Mat self;
	MatMulDerivWorker(cv::Mat self) {
		this->self = self;
	}

	cv::Mat B;

	cv::Mat dABdA;
	cv::Mat dABdB;

	const char* execute() {
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

NAN_METHOD(MatCalib3d::MatMulDeriv) {
	MatMulDerivWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::MatMulDeriv", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatCalib3d::MatMulDerivAsync) {
	MatMulDerivWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::MatMulDerivAsync", MatMulDerivWorker, worker);
}


struct MatCalib3d::FindChessboardCornersWorker : public SimpleWorker {
public:
	cv::Mat self;
	FindChessboardCornersWorker(cv::Mat self) {
		this->self = self;
	}

	cv::Size2d patternSize;
	int flags = cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE;

	bool returnValue;
	std::vector<cv::Point2d> corners;

	const char* execute() {
		returnValue = cv::findChessboardCorners(self, patternSize, corners, flags);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		v8::Local<v8::Object> ret = Nan::New<v8::Object>();
		Nan::Set(ret, Nan::New("returnValue").ToLocalChecked(), BoolConverter::wrap(returnValue));
		Nan::Set(ret, Nan::New("corners").ToLocalChecked(), ObjectArrayConverter<Point2, cv::Point2d>::wrap(corners));
		return ret;
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Size::Converter::arg(0, &patternSize, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::optArg(1, &flags, info)
		);
	}
};

NAN_METHOD(MatCalib3d::FindChessboardCorners) {
	FindChessboardCornersWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::FindChessboardCorners", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatCalib3d::FindChessboardCornersAsync) {
	FindChessboardCornersWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::FindChessboardCornersAsync", FindChessboardCornersWorker, worker);
}


struct MatCalib3d::DrawChessboardCornersWorker : public SimpleWorker {
public:
	cv::Mat self;
	DrawChessboardCornersWorker(cv::Mat self) {
		this->self = self;
	}

	cv::Size2d patternSize;
	std::vector<cv::Point2f> corners;
	bool patternWasFound;


	const char* execute() {
		cv::drawChessboardCorners(self, patternSize, corners, patternWasFound);
		return "";
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Size::Converter::arg(0, &patternSize, info) ||
			ObjectArrayConverter<Point2, cv::Point2d, cv::Point2f>::arg(1, &corners, info) ||
			BoolConverter::arg(2, &patternWasFound, info)
		);
	}
};

NAN_METHOD(MatCalib3d::DrawChessboardCorners) {
	DrawChessboardCornersWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::DrawChessboardCorners", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatCalib3d::DrawChessboardCornersAsync) {
	DrawChessboardCornersWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::DrawChessboardCornersAsync", DrawChessboardCornersWorker, worker);
}


struct MatCalib3d::Find4QuadCornerSubpixWorker : public SimpleWorker {
public:
	cv::Mat self;
	Find4QuadCornerSubpixWorker(cv::Mat self) {
		this->self = self;
	}

	std::vector<cv::Point2f> corners;
	cv::Size2d region_size;

	bool returnValue;

	const char* execute() {
		returnValue = cv::find4QuadCornerSubpix(self, corners, region_size);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		return BoolConverter::wrap(returnValue);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			ObjectArrayConverter<Point2, cv::Point2d, cv::Point2f>::arg(0, &corners, info) ||
			Size::Converter::arg(1, &region_size, info)
		);
	}
};

NAN_METHOD(MatCalib3d::Find4QuadCornerSubpix) {
	Find4QuadCornerSubpixWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::Find4QuadCornerSubpix", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatCalib3d::Find4QuadCornerSubpixAsync) {
	Find4QuadCornerSubpixWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::Find4QuadCornerSubpixAsync", Find4QuadCornerSubpixWorker, worker);
}


struct MatCalib3d::CalibrationMatrixValuesWorker : public SimpleWorker {
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

	const char* execute() {
		cv::calibrationMatrixValues(self, imageSize, apertureWidth, apertureHeight, fovx, fovy, focalLength, principalPoint, aspectRatio);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		v8::Local<v8::Object> ret = Nan::New<v8::Object>();
		Nan::Set(ret, Nan::New("fovx").ToLocalChecked(), DoubleConverter::wrap(fovx));
		Nan::Set(ret, Nan::New("fovy").ToLocalChecked(), DoubleConverter::wrap(fovy));
		Nan::Set(ret, Nan::New("focalLength").ToLocalChecked(), DoubleConverter::wrap(focalLength));
		Nan::Set(ret, Nan::New("principalPoint").ToLocalChecked(), Point2::Converter::wrap(principalPoint));
		Nan::Set(ret, Nan::New("aspectRatio").ToLocalChecked(), DoubleConverter::wrap(aspectRatio));
		return ret;
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Size::Converter::arg(0, &imageSize, info) ||
			DoubleConverter::arg(1, &apertureWidth, info) ||
			DoubleConverter::arg(2, &apertureHeight, info)
		);
	}
};

NAN_METHOD(MatCalib3d::CalibrationMatrixValues) {
	CalibrationMatrixValuesWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::CalibrationMatrixValues", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatCalib3d::CalibrationMatrixValuesAsync) {
	CalibrationMatrixValuesWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::CalibrationMatrixValuesAsync", CalibrationMatrixValuesWorker, worker);
}


struct MatCalib3d::StereoRectifyWorker : public SimpleWorker {
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

	const char* execute() {
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
			DoubleArrayConverter::arg(0, &distCoeffs1, info) ||
			Mat::Converter::arg(1, &cameraMatrix2, info) ||
			DoubleArrayConverter::arg(2, &distCoeffs2, info) ||
			Size::Converter::arg(3, &imageSize, info) ||
			Mat::Converter::arg(4, &R, info) ||
			Vec3::Converter::arg(5, &T, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::optArg(6, &flags, info) ||
			DoubleConverter::optArg(7, &alpha, info) ||
			Size::Converter::optArg(8, &newImageSize, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(6);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		v8::Local<v8::Object> opts = info[6]->ToObject();
		return (
			IntConverter::optProp(&flags, "flags", opts) ||
			DoubleConverter::optProp(&alpha, "alpha", opts) ||
			Size::Converter::optProp(&newImageSize, "newImageSize", opts)
		);
	}
};

NAN_METHOD(MatCalib3d::StereoRectify) {
	StereoRectifyWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::StereoRectify", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatCalib3d::StereoRectifyAsync) {
	StereoRectifyWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::StereoRectifyAsync", StereoRectifyWorker, worker);
}

struct MatCalib3d::Rectify3CollinearWorker : public SimpleWorker {
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

	const char* execute() {
		returnValue = cv::rectify3Collinear(self, distCoeffs1, cameraMatrix2, distCoeffs2, cameraMatrix3, distCoeffs3, imgpt1, imgpt3, imageSize, R12, T12, R13, T13, R1, R2, R3, P1, P2, P3, Q, alpha, newImgSize, &roi1, &roi2, flags);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		v8::Local<v8::Object> ret = Nan::New<v8::Object>();
		Nan::Set(ret, Nan::New("returnValue").ToLocalChecked(), FloatConverter::wrap(returnValue));
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
			DoubleArrayConverter::arg(0, &distCoeffs1, info) ||
			Mat::Converter::arg(1, &cameraMatrix2, info) ||
			DoubleArrayConverter::arg(2, &distCoeffs2, info) ||
			Mat::Converter::arg(3, &cameraMatrix3, info) ||
			DoubleArrayConverter::arg(4, &distCoeffs3, info) ||
			ObjectArrayConverter<Point2, cv::Point2d, cv::Point2f>::arg(5, &imgpt1, info) ||
			ObjectArrayConverter<Point2, cv::Point2d, cv::Point2f>::arg(6, &imgpt3, info) ||
			Size::Converter::arg(7, &imageSize, info) ||
			Mat::Converter::arg(8, &R12, info) ||
			Vec3::Converter::arg(9, &T12, info) ||
			Mat::Converter::arg(10, &R13, info) ||
			Vec3::Converter::arg(11, &T13, info) ||
			DoubleConverter::arg(12, &alpha, info) ||
			Size::Converter::arg(13, &newImgSize, info) ||
			IntConverter::arg(14, &flags, info)
		);
	}
};

NAN_METHOD(MatCalib3d::Rectify3Collinear) {
	Rectify3CollinearWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::Rectify3Collinear", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatCalib3d::Rectify3CollinearAsync) {
	Rectify3CollinearWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::Rectify3CollinearAsync", Rectify3CollinearWorker, worker);
}


struct MatCalib3d::GetOptimalNewCameraMatrixWorker : public SimpleWorker {
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

	const char* execute() {
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
			DoubleArrayConverter::arg(0, &distCoeffs, info) ||
			Size::Converter::arg(1, &imageSize, info) ||
			DoubleConverter::arg(2, &alpha, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Size::Converter::optArg(3, &newImgSize, info) ||
			BoolConverter::optArg(4, &centerPrincipalPoint, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(3);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		v8::Local<v8::Object> opts = info[3]->ToObject();
		return (
			Size::Converter::optProp(&newImgSize, "newImgSize", opts) ||
			BoolConverter::optProp(&centerPrincipalPoint, "centerPrincipalPoint", opts)
		);
	}
};;

NAN_METHOD(MatCalib3d::GetOptimalNewCameraMatrix) {
	GetOptimalNewCameraMatrixWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::GetOptimalNewCameraMatrix", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatCalib3d::GetOptimalNewCameraMatrixAsync) {
	GetOptimalNewCameraMatrixWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::GetOptimalNewCameraMatrixAsync", GetOptimalNewCameraMatrixWorker, worker);
}


struct MatCalib3d::DecomposeEssentialMatWorker : public SimpleWorker {
public:
	cv::Mat self;
	DecomposeEssentialMatWorker(cv::Mat self) {
		this->self = self;
	}

	cv::Mat R1;
	cv::Mat R2;
	cv::Vec3d T;

	const char* execute() {
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

NAN_METHOD(MatCalib3d::DecomposeEssentialMat) {
	DecomposeEssentialMatWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::DecomposeEssentialMat", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatCalib3d::DecomposeEssentialMatAsync) {
	DecomposeEssentialMatWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::DecomposeEssentialMatAsync", DecomposeEssentialMatWorker, worker);
}


struct MatCalib3d::TriangulatePointsWorker : public SimpleWorker {
public:
	cv::Mat self;
	TriangulatePointsWorker(cv::Mat self) {
		this->self = self;
	}

	cv::Mat projMatr2;
	std::vector<cv::Point2d> projPoints1;
	std::vector<cv::Point2d> projPoints2;

	cv::Mat points4D;

	const char* execute() {
		cv::triangulatePoints(self, projMatr2, projPoints1, projPoints2, points4D);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		return Mat::Converter::wrap(points4D);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Mat::Converter::arg(0, &projMatr2, info) ||
			ObjectArrayConverter<Point2, cv::Point2d>::arg(1, &projPoints1, info) ||
			ObjectArrayConverter<Point2, cv::Point2d>::arg(2, &projPoints2, info)
		);
	}
};

NAN_METHOD(MatCalib3d::TriangulatePoints) {
	TriangulatePointsWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::TriangulatePoints", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatCalib3d::TriangulatePointsAsync) {
	TriangulatePointsWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::TriangulatePointsAsync", TriangulatePointsWorker, worker);
}


struct MatCalib3d::CorrectMatchesWorker : public SimpleWorker {
public:
	cv::Mat self;
	CorrectMatchesWorker(cv::Mat self) {
		this->self = self;
	}

	std::vector<cv::Point2f> points1;
	std::vector<cv::Point2f> points2;

	std::vector<cv::Point2f> newPoints1;
	std::vector<cv::Point2f> newPoints2;

	const char* execute() {
		cv::correctMatches(self, points1, points2, newPoints1, newPoints2);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		v8::Local<v8::Object> ret = Nan::New<v8::Object>();
		Nan::Set(ret, Nan::New("newPoints1").ToLocalChecked(), ObjectArrayConverter<Point2, cv::Point2d, cv::Point2f>::wrap(newPoints1));
		Nan::Set(ret, Nan::New("newPoints2").ToLocalChecked(), ObjectArrayConverter<Point2, cv::Point2d, cv::Point2f>::wrap(newPoints2));
		return ret;
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			ObjectArrayConverter<Point2, cv::Point2d, cv::Point2f>::arg(0, &points1, info) ||
			ObjectArrayConverter<Point2, cv::Point2d, cv::Point2f>::arg(1, &points2, info)
		);
	}
};

NAN_METHOD(MatCalib3d::CorrectMatches) {
	CorrectMatchesWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::CorrectMatches", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatCalib3d::CorrectMatchesAsync) {
	CorrectMatchesWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::CorrectMatchesAsync", CorrectMatchesWorker, worker);
}


struct MatCalib3d::FilterSpecklesWorker : public SimpleWorker {
public:
	cv::Mat self;
	FilterSpecklesWorker(cv::Mat self) {
		this->self = self;
	}

	double newVal;
	int maxSpeckleSize;
	double maxDiff;

	const char* execute() {
		cv::filterSpeckles(self, newVal, maxSpeckleSize, maxDiff, cv::noArray());
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		v8::Local<v8::Object> ret = Nan::New<v8::Object>();
		return ret;
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			DoubleConverter::arg(0, &newVal, info) ||
			IntConverter::arg(1, &maxSpeckleSize, info) ||
			DoubleConverter::arg(2, &maxDiff, info)
		);
	}
};

NAN_METHOD(MatCalib3d::FilterSpeckles) {
	FilterSpecklesWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::FilterSpeckles", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatCalib3d::FilterSpecklesAsync) {
	FilterSpecklesWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::FilterSpecklesAsync", FilterSpecklesWorker, worker);
}

struct MatCalib3d::ValidateDisparityWorker : public SimpleWorker {
public:
	cv::Mat self;
	ValidateDisparityWorker(cv::Mat self) {
		this->self = self;
	}

	cv::Mat cost;
	int minDisparity;
	int numberOfDisparities;
	int disp12MaxDisp = 1;


	const char* execute() {
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
			IntConverter::arg(1, &minDisparity, info) ||
			IntConverter::arg(2, &numberOfDisparities, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::optArg(3, &disp12MaxDisp, info)
		);
	}
};

NAN_METHOD(MatCalib3d::ValidateDisparity) {
	ValidateDisparityWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::ValidateDisparity", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatCalib3d::ValidateDisparityAsync) {
	ValidateDisparityWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::ValidateDisparityAsync", ValidateDisparityWorker, worker);
}


struct MatCalib3d::ReprojectImageTo3DWorker : public SimpleWorker {
public:
	cv::Mat self;
	ReprojectImageTo3DWorker(cv::Mat self) {
		this->self = self;
	}

	cv::Mat Q;
	bool handleMissingValues = false;
	int ddepth = -1;

	cv::Mat _3dImage;

	const char* execute() {
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
			BoolConverter::optArg(1, &handleMissingValues, info) ||
			IntConverter::optArg(2, &ddepth, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(1);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		v8::Local<v8::Object> opts = info[1]->ToObject();
		return (
			BoolConverter::optProp(&handleMissingValues, "handleMissingValues", opts) ||
			IntConverter::optProp(&ddepth, "ddepth", opts)
		);
	}
};

NAN_METHOD(MatCalib3d::ReprojectImageTo3D) {
	ReprojectImageTo3DWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::ReprojectImageTo3D", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatCalib3d::ReprojectImageTo3DAsync) {
	ReprojectImageTo3DWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::ReprojectImageTo3DAsync", ReprojectImageTo3DWorker, worker);
}


struct MatCalib3d::DecomposeHomographyMatWorker : public SimpleWorker {
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

	const char* execute() {
		returnValue = cv::decomposeHomographyMat(self, K, rotations, translations, normals);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		v8::Local<v8::Object> ret = Nan::New<v8::Object>();
		Nan::Set(ret, Nan::New("returnValue").ToLocalChecked(), IntConverter::wrap(returnValue));
		Nan::Set(ret, Nan::New("rotations").ToLocalChecked(), ObjectArrayConverter<Mat, cv::Mat>::wrap(rotations));
		Nan::Set(ret, Nan::New("translations").ToLocalChecked(), ObjectArrayConverter<Mat, cv::Mat>::wrap(translations));
		Nan::Set(ret, Nan::New("normals").ToLocalChecked(), ObjectArrayConverter<Mat, cv::Mat>::wrap(normals));
		return ret;
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Mat::Converter::arg(0, &K, info)
		);
	}
};

NAN_METHOD(MatCalib3d::DecomposeHomographyMat) {
	DecomposeHomographyMatWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::DecomposeHomographyMat", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatCalib3d::DecomposeHomographyMatAsync) {
	DecomposeHomographyMatWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::DecomposeHomographyMatAsync", DecomposeHomographyMatWorker, worker);
}


#if CV_VERSION_MINOR > 0

struct MatCalib3d::FindEssentialMatWorker : public SimpleWorker {
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

	cv::Mat returnValue;
	cv::Mat mask = cv::noArray().getMat();

	const char* execute() {
		returnValue = cv::findEssentialMat(points1, points2, self, method, prob, threshold, mask);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		v8::Local<v8::Object> ret = Nan::New<v8::Object>();
		Nan::Set(ret, Nan::New("returnValue").ToLocalChecked(), Mat::Converter::wrap(returnValue));
		Nan::Set(ret, Nan::New("mask").ToLocalChecked(), Mat::Converter::wrap(mask));
		return ret;
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			ObjectArrayConverter<Point2, cv::Point2d, cv::Point2f>::arg(0, &points1, info) ||
			ObjectArrayConverter<Point2, cv::Point2d, cv::Point2f>::arg(1, &points2, info)
			);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::optArg(2, &method, info) ||
			DoubleConverter::optArg(3, &prob, info) ||
			DoubleConverter::optArg(4, &threshold, info)
			);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(2);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		v8::Local<v8::Object> opts = info[2]->ToObject();
		return (
			IntConverter::optProp(&method, "method", opts) ||
			DoubleConverter::optProp(&prob, "prob", opts) ||
			DoubleConverter::optProp(&threshold, "threshold", opts)
			);
	}
};

NAN_METHOD(MatCalib3d::FindEssentialMat) {
	FindEssentialMatWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::FindEssentialMat", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatCalib3d::FindEssentialMatAsync) {
	FindEssentialMatWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::FindEssentialMatAsync", FindEssentialMatWorker, worker);
}


struct MatCalib3d::RecoverPoseWorker : public SimpleWorker {
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
	cv::Vec3f t;

	const char* execute() {
		returnValue = cv::recoverPose(E, points1, points2, self, R, t, mask);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		v8::Local<v8::Object> ret = Nan::New<v8::Object>();
		Nan::Set(ret, Nan::New("returnValue").ToLocalChecked(), IntConverter::wrap(returnValue));
		Nan::Set(ret, Nan::New("R").ToLocalChecked(), Mat::Converter::wrap(R));
		Nan::Set(ret, Nan::New("t").ToLocalChecked(), Vec3::Converter::wrap(t));
		return ret;
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Mat::Converter::arg(0, &E, info) ||
			ObjectArrayConverter<Point2, cv::Point2d, cv::Point2f>::arg(1, &points1, info) ||
			ObjectArrayConverter<Point2, cv::Point2d, cv::Point2f>::arg(2, &points2, info)
			);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Mat::Converter::optArg(3, &mask, info)
			);
	}
};

NAN_METHOD(MatCalib3d::RecoverPose) {
	RecoverPoseWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::RecoverPose", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(MatCalib3d::RecoverPoseAsync) {
	RecoverPoseWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::RecoverPoseAsync", RecoverPoseWorker, worker);
}

#endif
