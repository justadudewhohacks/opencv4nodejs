#include "IWorker.h"
#include "TryCatch.h"
#include "utils.h"

#ifndef __FF_BINDING_H__
#define __FF_BINDING_H__

namespace FF {

	static void executeSyncBinding(std::shared_ptr<ISyncWorker> worker, std::string methodName, Nan::NAN_METHOD_ARGS_TYPE info) {
		FF::TryCatch tryCatch(methodName);
		if (worker->applyUnwrappers(info)) {
			return tryCatch.reThrow();
		}

		std::string err = worker->execute();
		if (!err.empty()) {
			tryCatch.throwError(err);
			return;
		}

		info.GetReturnValue().Set(worker->getReturnValue(info));
	}

	static void executeAsyncBinding(std::shared_ptr<IAsyncWorker> worker, std::string methodName, Nan::NAN_METHOD_ARGS_TYPE info) {
		FF::TryCatch tryCatch(methodName);
		if (!hasArg(info, info.Length() - 1) || !info[info.Length() - 1]->IsFunction()) {
			tryCatch.throwError("callback function required");
			return;
		}
		Nan::Callback *callback = new Nan::Callback(info[info.Length() - 1].As<v8::Function>());
		if (worker->applyUnwrappers(info)) {
			v8::Local<v8::Value> argv[] = {
				Nan::Error(tryCatch.extendWithPrefix(tryCatch.getCaughtErrorMessageUnchecked()).c_str()),
				Nan::Null()
			};
			tryCatch.Reset();
			Nan::AsyncResource resource("native-node-utils:AsyncBindingBase::run");
			resource.runInAsyncScope(Nan::GetCurrentContext()->Global(), **callback, 2, argv);
			return;
		}
		Nan::AsyncQueueWorker(new FF::AsyncWorker(callback, worker));
	}

	template<class WorkerImpl>
	static void syncBinding(std::string methodNamespace, std::string methodName, Nan::NAN_METHOD_ARGS_TYPE info) {
		auto worker = std::make_shared<WorkerImpl>();
		worker->setup();
		executeSyncBinding(
			worker,
			methodNamespace + "::" + methodName,
			info
		);
	}

	template<class WorkerImpl>
	static void asyncBinding(std::string methodNamespace, std::string methodName, Nan::NAN_METHOD_ARGS_TYPE info) {
		auto worker = std::make_shared<WorkerImpl>();
		worker->setup();
		executeAsyncBinding(
			worker,
			methodNamespace + "::" + methodName + "Async",
			info
		);
	}
}

#endif
