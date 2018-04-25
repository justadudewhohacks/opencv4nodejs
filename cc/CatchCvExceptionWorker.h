#include "NativeNodeUtils.h"

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

#endif