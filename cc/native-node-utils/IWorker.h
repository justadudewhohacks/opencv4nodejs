#include <nan.h>
#include <iostream>

#ifndef __FF_IWORKER_H__
#define __FF_IWORKER_H__

namespace FF {

	class IWorker {
	public:
		virtual std::string execute() = 0;
		virtual bool applyUnwrappers(Nan::NAN_METHOD_ARGS_TYPE info) = 0;
	};

	class ISyncWorker : public IWorker {
	public:
		virtual v8::Local<v8::Value> getReturnValue(Nan::NAN_METHOD_ARGS_TYPE info) = 0;
	};

	class IAsyncWorker : public IWorker {
	public:
		virtual v8::Local<v8::Value> getReturnValue() = 0;
	};
}

#endif