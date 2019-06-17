#include "opencv_modules.h"

#ifdef HAVE_OPENCV_FEATURES2D

#include "BFMatcher.h"
#include "BFMatcherBindings.h"

Nan::Persistent<v8::FunctionTemplate> BFMatcher::constructor;

NAN_MODULE_INIT(BFMatcher::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(BFMatcher::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

  constructor.Reset(ctor);
  instanceTemplate->SetInternalFieldCount(1);

   ctor->SetClassName(Nan::New("BFMatcher").ToLocalChecked());

	Nan::SetAccessor(instanceTemplate, Nan::New("normType").ToLocalChecked(), normType_getter);
	Nan::SetAccessor(instanceTemplate, Nan::New("crossCheck").ToLocalChecked(), crossCheck_getter);

    Nan::SetPrototypeMethod(ctor, "match", match);
    Nan::SetPrototypeMethod(ctor, "matchAsync", matchAsync);
    Nan::SetPrototypeMethod(ctor, "knnMatch", knnMatch);
    Nan::SetPrototypeMethod(ctor, "knnMatchAsync", knnMatchAsync);

    Nan::Set(target,Nan::New("BFMatcher").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(BFMatcher::New) {
	FF::TryCatch tryCatch("BFMatcher::New");
	FF_ASSERT_CONSTRUCT_CALL();
	BFMatcher::NewWorker worker;

	if (worker.applyUnwrappers(info)) {
		return tryCatch.reThrow();
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
  FF::executeSyncBinding(
    std::make_shared<BFMatcherBindings::MatchWorker>(BFMatcher::unwrapSelf(info)),
    "BFMatcher::match",
    info
  );
}

NAN_METHOD(BFMatcher::matchAsync) {
  FF::executeAsyncBinding(
    std::make_shared<BFMatcherBindings::MatchWorker>(BFMatcher::unwrapSelf(info)),
    "BFMatcher::matchAsync",
    info
  );
}

NAN_METHOD(BFMatcher::knnMatch) {
  FF::executeSyncBinding(
    std::make_shared<BFMatcherBindings::MatchKnnWorker>(BFMatcher::unwrapSelf(info)),
    "BFMatcher::knnMatch",
    info
  );
}


NAN_METHOD(BFMatcher::knnMatchAsync) {
  FF::executeAsyncBinding(
    std::make_shared<BFMatcherBindings::MatchKnnWorker>(BFMatcher::unwrapSelf(info)),
    "BFMatcher::knnMatchAsync",
    info
  );
}

#endif