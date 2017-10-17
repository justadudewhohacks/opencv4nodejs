#include <macros.h>

#ifndef __FF_GENERICASYNCWORKER_H__
#define __FF_GENERICASYNCWORKER_H__

template<class Context>
class GenericAsyncWorker : public Nan::AsyncWorker {
public:
	Context ctx;

	GenericAsyncWorker(
		Nan::Callback *callback,
		Context ctx
	) : Nan::AsyncWorker(callback), ctx(ctx) {}
	~GenericAsyncWorker() {}

	void Execute() {
		const char* err = ctx.execute();
		if (!std::string(err).empty()) {
			this->SetErrorMessage(err);
		}
	}

	void HandleOKCallback() {
		Nan::HandleScope scope;
		FF_VAL argv[] = { Nan::Null(), ctx.getReturnValue() };
		callback->Call(2, argv);
	}

	void HandleErrorCallback() {
		Nan::HandleScope scope;
		FF_VAL argv[] = { FF_NEW_STRING(this->ErrorMessage()), Nan::Null() };
		callback->Call(2, argv);
	}
};

#define FF_TRY_UNWRAP_ARGS(ff_methodName, ff_worker)\
	Nan::TryCatch tryCatch;\
	if (\
		ff_worker.unwrapRequiredArgs(info) ||\
		(ff_worker.hasOptArgsObject(info) && ff_worker.unwrapOptionalArgsFromOpts(info)) ||\
		(!ff_worker.hasOptArgsObject(info) && ff_worker.unwrapOptionalArgs(info))\
	) {\
		std::string err = std::string(*Nan::Utf8String(tryCatch.Exception()->ToString()));\
		tryCatch.Reset();\
		Nan::ThrowError(\
			Nan::New(\
				std::string(ff_methodName)\
				+ std::string(" - ")\
				+ err\
			).ToLocalChecked()\
		);\
		tryCatch.ReThrow();\
		return;\
	}

#define FF_WORKER_SYNC(ff_methodName, ff_worker)\
	FF_TRY_UNWRAP_ARGS(ff_methodName, ff_worker);\
	const char* err = ff_worker.execute();\
	if (!std::string(err).empty()) {\
		tryCatch.Reset();\
		Nan::ThrowError(\
			Nan::New(\
				std::string(ff_methodName)\
				+ std::string(err)\
			).ToLocalChecked()\
		);\
		tryCatch.ReThrow();\
		return;\
	}

#define FF_WORKER_ASYNC(ff_methodName, ff_Worker, ff_worker)\
	FF_TRY_UNWRAP_ARGS(ff_methodName, ff_worker);\
	if (!hasArg(info.Length() - 1, info) || !info[info.Length() - 1]->IsFunction()) {\
		tryCatch.Reset();\
		Nan::ThrowError(\
			Nan::New(\
				std::string(ff_methodName)\
				+ std::string(" - ")\
				+ std::string(" callback function required")\
			).ToLocalChecked()\
		);\
		tryCatch.ReThrow();\
		return;\
	}\
	Nan::AsyncQueueWorker(new GenericAsyncWorker<ff_Worker>(\
		new Nan::Callback(info[info.Length() - 1].As<v8::Function>()),\
		ff_worker\
	));

#endif