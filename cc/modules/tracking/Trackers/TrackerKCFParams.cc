#ifdef HAVE_TRACKING

#include "TrackerKCFParams.h"

#if CV_MINOR_VERSION > 0

Nan::Persistent<v8::FunctionTemplate> TrackerKCFParams::constructor;

NAN_MODULE_INIT(TrackerKCFParams::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerKCFParams::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	constructor.Reset(ctor);
	ctor->SetClassName(FF::newString("TrackerKCFParams"));
	instanceTemplate->SetInternalFieldCount(1);

	Nan::SetAccessor(instanceTemplate, FF::newString("sigma"), sigmaGet, sigmaSet);
	Nan::SetAccessor(instanceTemplate, FF::newString("lambda"), lambdaGet, lambdaSet);
	Nan::SetAccessor(instanceTemplate, FF::newString("interp_factor"), interp_factorGet, interp_factorSet);
	Nan::SetAccessor(instanceTemplate, FF::newString("output_sigma_factor"), output_sigma_factorGet, output_sigma_factorSet);
	Nan::SetAccessor(instanceTemplate, FF::newString("pca_learning_rate"), pca_learning_rateGet, pca_learning_rateSet);
	Nan::SetAccessor(instanceTemplate, FF::newString("resize"), resizeGet, resizeSet);
	Nan::SetAccessor(instanceTemplate, FF::newString("split_coeff"), split_coeffGet, split_coeffSet);
	Nan::SetAccessor(instanceTemplate, FF::newString("wrap_kernel"), wrap_kernelGet, wrap_kernelSet);
	Nan::SetAccessor(instanceTemplate, FF::newString("compress_feature"), compress_featureGet, compress_featureSet);
	Nan::SetAccessor(instanceTemplate, FF::newString("max_patch_size"), max_patch_sizeGet, max_patch_sizeSet);
	Nan::SetAccessor(instanceTemplate, FF::newString("compressed_size"), compressed_sizeGet, compressed_sizeSet);
	Nan::SetAccessor(instanceTemplate, FF::newString("desc_pca"), desc_pcaGet, desc_pcaSet);
	Nan::SetAccessor(instanceTemplate, FF::newString("desc_npca"), desc_npcaGet, desc_npcaSet);
#if CV_MINOR_VERSION > 2
	Nan::SetAccessor(instanceTemplate, FF::newString("detect_thresh"), detect_threshGet, detect_threshSet);
#endif
	Nan::Set(target,FF::newString("TrackerKCFParams"), FF::getFunction(ctor));
};


NAN_METHOD(TrackerKCFParams::New) {
	FF_ASSERT_CONSTRUCT_CALL(TrackerKCFParams);
	TrackerKCFParams* self = new TrackerKCFParams();
	self->self = cv::TrackerKCF::Params();
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
};

#endif

#endif
