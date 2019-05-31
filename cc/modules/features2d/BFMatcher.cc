#include "BFMatcher.h"
#include "BFMatcherBindings.h"

Nan::Persistent<v8::FunctionTemplate> BFMatcher::constructor;

NAN_MODULE_INIT(BFMatcher::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(BFMatcher::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  instanceTemplate->SetInternalFieldCount(1);

   ctor->SetClassName(Nan::New("BFMatcher").ToLocalChecked());

	Nan::SetAccessor(instanceTemplate, Nan::New("normType").ToLocalChecked(), BFMatcher::GetNormType);
  Nan::SetAccessor(instanceTemplate, Nan::New("crossCheck").ToLocalChecked(), BFMatcher::GetCrossCheck);

    Nan::SetPrototypeMethod(ctor, "match", match);
    Nan::SetPrototypeMethod(ctor, "matchAsync", matchAsync);
    Nan::SetPrototypeMethod(ctor, "knnMatch", knnMatch);
    Nan::SetPrototypeMethod(ctor, "knnMatchAsync", knnMatchAsync);

    Nan::Set(target,Nan::New("BFMatcher").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(BFMatcher::New) {
	FF_ASSERT_CONSTRUCT_CALL(BFMatcher);
	FF::TryCatch tryCatch;
	BFMatcher::NewWorker worker;

	if (worker.applyUnwrappers(info)) {
		v8::Local<v8::Value> err = tryCatch.formatCatchedError("BFMatcher::New");
		tryCatch.throwNew(err);
		return;
	}

	BFMatcher* self = new BFMatcher();
	self->normType = worker.normType;
	self->crossCheck = worker.crossCheck;
	self->self = cv::BFMatcher(
		worker.normType,
		worker.crossCheck
	);
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(BFMatcher::match) {
  FF::SyncBinding(
    std::make_shared<BFMatcherBindings::MatchWorker>(BFMatcher::unwrapSelf(info)),
    "BFMatcher::match",
    info
  );
}

NAN_METHOD(BFMatcher::matchAsync) {
  FF::AsyncBinding(
    std::make_shared<BFMatcherBindings::MatchWorker>(BFMatcher::unwrapSelf(info)),
    "BFMatcher::matchAsync",
    info
  );
}

NAN_METHOD(BFMatcher::knnMatch) {
  FF::SyncBinding(
    std::make_shared<BFMatcherBindings::MatchKnnWorker>(BFMatcher::unwrapSelf(info)),
    "BFMatcher::knnMatch",
    info
  );
}


NAN_METHOD(BFMatcher::knnMatchAsync) {
  FF::AsyncBinding(
    std::make_shared<BFMatcherBindings::MatchKnnWorker>(BFMatcher::unwrapSelf(info)),
    "BFMatcher::knnMatchAsync",
    info
  );
}
