#include "NativeNodeUtils.h"
#include "Binding.h"
#include <functional>

#ifndef __FF_CATCHCVEXCEPTIONWORKER_H__
#define __FF_CATCHCVEXCEPTIONWORKER_H__

struct CatchCvExceptionWorker : public FF::SimpleWorker {
public:
	std::string execute() {
		try {
			return executeCatchCvExceptionWorker();
		} catch (std::exception &e) {
			return std::string(e.what());
		}
	}

	virtual std::string executeCatchCvExceptionWorker() = 0;
};

class OpencvBinding : public FF::BindingBase, public CatchCvExceptionWorker {
public:
	//const char*(*executeBinding)(void) = []() { return ""; };
	std::function<const char*(void)> executeBinding = []() { return ""; };

	std::string executeCatchCvExceptionWorker() {
		return executeBinding();
	}
};

#endif