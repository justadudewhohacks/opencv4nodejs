#include "NativeNodeUtils.h"
#include <functional>

#ifndef __FF_CV_BINDING_H__
#define __FF_CV_BINDING_H__

class CvBinding : public FF::BindingBase, public FF::IWorker {
public:
	std::string execute() {
		try {
			executeBinding();
			return "";
		}
		catch (std::exception &e) {
			return std::string(e.what());
		}
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF::BindingBase::unwrapOptionalArgs(info);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF::BindingBase::hasOptArgsObject(info);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF::BindingBase::unwrapOptionalArgsFromOpts(info);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF::BindingBase::unwrapRequiredArgs(info);
	}

	v8::Local<v8::Value> getReturnValue() {
		return FF::BindingBase::getReturnValue();
	}

protected:
	std::function<void(void)> executeBinding = [] {};
};

#endif