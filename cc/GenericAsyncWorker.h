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

#endif