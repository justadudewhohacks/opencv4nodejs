#include "machinelearning.h"
#include "TrainData.h"
#include "SVM.h"

NAN_MODULE_INIT(MachineLearning::Init) {
	TrainData::Init(target);
	SVM::Init(target);
};
