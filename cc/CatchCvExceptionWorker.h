#include "NativeNodeUtils.h"

#ifndef __FF_CATCHCVEXCEPTIONWORKER_H__
#define __FF_CATCHCVEXCEPTIONWORKER_H__

// TODO remove this one
namespace FF {

	struct SimpleWorker : public IWorker {
	public:
		std::string execute() {
			return "";
		}

		v8::Local<v8::Value> getReturnValue() {
			return Nan::Undefined();
		}

		bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			return false;
		}

		bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
			return false;
		}

		bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
			return false;
		}

		bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			return false;
		}
	};

}

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