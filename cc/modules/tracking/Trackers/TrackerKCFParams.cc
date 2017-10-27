#ifdef HAVE_TRACKING

#include "TrackerKCFParams.h"

#if CV_MINOR_VERSION > 0

Nan::Persistent<v8::FunctionTemplate> TrackerKCFParams::constructor;

NAN_MODULE_INIT(TrackerKCFParams::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TrackerKCFParams::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	constructor.Reset(ctor);
	ctor->SetClassName(FF_NEW_STRING("TrackerKCFParams"));
	instanceTemplate->SetInternalFieldCount(1);

	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("sigma"), sigmaGet, sigmaSet);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("lambda"), lambdaGet, lambdaSet);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("interp_factor"), interp_factorGet, interp_factorSet);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("output_sigma_factor"), output_sigma_factorGet, output_sigma_factorSet);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("pca_learning_rate"), pca_learning_rateGet, pca_learning_rateSet);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("resize"), resizeGet, resizeSet);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("split_coeff"), split_coeffGet, split_coeffSet);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("wrap_kernel"), wrap_kernelGet, wrap_kernelSet);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("compress_feature"), compress_featureGet, compress_featureSet);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("max_patch_size"), max_patch_sizeGet, max_patch_sizeSet);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("compressed_size"), compressed_sizeGet, compressed_sizeSet);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("desc_pca"), desc_pcaGet, desc_pcaSet);
	Nan::SetAccessor(instanceTemplate, FF_NEW_STRING("desc_npca"), desc_npcaGet, desc_npcaSet);

	target->Set(FF_NEW_STRING("TrackerKCFParams"), ctor->GetFunction());
};


NAN_METHOD(TrackerKCFParams::New) {
	FF_METHOD_CONTEXT("TrackerKCFParams::New");
	TrackerKCFParams* self = new TrackerKCFParams();
	self->params = cv::TrackerKCF::Params();
	self->Wrap(info.Holder());
	FF_RETURN(info.Holder());
};

#endif

#endif