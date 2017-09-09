#include "machinelearning.h"
#include "TrainData.h"
#include "ParamGrid.h"
#include "StatModel.h"
#include "SVM.h"

NAN_MODULE_INIT(MachineLearning::Init) {
	TrainData::Init(target);
	ParamGrid::Init(target);
	StatModel::Init(target);
	SVM::Init(target);
};
