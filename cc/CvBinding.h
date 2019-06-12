#include "NativeNodeUtils.h"
#include <functional>

#ifndef __FF_CV_BINDING_H__
#define __FF_CV_BINDING_H__

class CvBinding : public FF::BindingBase, public FF::ISyncWorker, public FF::IAsyncWorker {
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

	bool applyUnwrappers(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF::BindingBase::applyUnwrappers(info);
	}

	v8::Local<v8::Value> getReturnValue() {
		return FF::BindingBase::getReturnValue();
	}

	v8::Local<v8::Value> getReturnValue(Nan::NAN_METHOD_ARGS_TYPE info) {
		return getReturnValue();
	}

protected:
	std::function<void(void)> executeBinding = [](){};
};

template<class TClass>
class CvClassMethodBinding : public CvBinding {
public:
	void setup() {
		createBinding(req<typename TClass::Converter>());
	}

	void setup(typename TClass::Converter::Type self) {
		createBinding(std::make_shared<FF::Value<typename TClass::Converter::Type>>(self));
	}

	virtual void createBinding(std::shared_ptr<FF::Value<typename TClass::Converter::Type>> self) = 0;
};

#endif