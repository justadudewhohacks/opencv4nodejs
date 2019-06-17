#include "opencv_modules.h"

#ifdef HAVE_OPENCV_ML

#include "machinelearning.h"
#include "machinelearningConstants.h"
#include "TrainData.h"
#include "ParamGrid.h"
#include "StatModel.h"
#include "SVM.h"

NAN_MODULE_INIT(MachineLearning::Init) {
	MachineLearningConstants::Init(target);
	TrainData::Init(target);
	ParamGrid::Init(target);
	StatModel::Init(target);
	SVM::Init(target);
};

#endif