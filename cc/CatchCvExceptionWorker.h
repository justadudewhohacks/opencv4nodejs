#include "NativeNodeUtils.h"

#ifndef __FF_CATCHCVEXCEPTIONWORKER_H__
#define __FF_CATCHCVEXCEPTIONWORKER_H__

// TODO remove this one
namespace FF {

	class SimpleWorkerBase : public ISyncWorker, public IAsyncWorker {
	public:
		virtual bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) = 0;
		virtual bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) = 0;
		virtual bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) = 0;
		virtual bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) = 0;

		std::string execute() {
			return "";
		}

		v8::Local<v8::Value> getReturnValue() {
			return Nan::Undefined();
		}

		v8::Local<v8::Value> getReturnValue(Nan::NAN_METHOD_ARGS_TYPE info) {
			return getReturnValue();
		}

		bool applyUnwrappers(Nan::NAN_METHOD_ARGS_TYPE info) {
			return unwrapRequiredArgs(info)
				|| (!hasOptArgsObject(info) && unwrapOptionalArgs(info))
				|| (hasOptArgsObject(info) && unwrapOptionalArgsFromOpts(info));
		}
	};

	class SimpleWorker : public SimpleWorkerBase {
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