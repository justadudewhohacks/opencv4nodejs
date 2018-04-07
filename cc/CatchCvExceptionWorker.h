#include "Workers.h"

#ifndef __FF_CATCHCVEXCEPTIONWORKER_H__
#define __FF_CATCHCVEXCEPTIONWORKER_H__

struct CatchCvExceptionWorker : public SimpleWorker {
public:
	const char* execute() {
		try {
			return executeCatchCvExceptionWorker();
		} catch (std::exception e) {
			return e.what();
		}
	}

	virtual const char* executeCatchCvExceptionWorker() = 0;
};

#endif