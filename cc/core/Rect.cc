#include "Rect.h"

Nan::Persistent<v8::FunctionTemplate> Rect::constructor;

NAN_MODULE_INIT(Rect::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Rect::New);
	Rect::constructor.Reset(ctor);
	ctor->InstanceTemplate()->SetInternalFieldCount(1);
	ctor->SetClassName(Nan::New("Rect").ToLocalChecked());
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("x").ToLocalChecked(), Rect::GetX);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("y").ToLocalChecked(), Rect::GetY);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("width").ToLocalChecked(), Rect::GetWidth);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("height").ToLocalChecked(), Rect::GetHeight);

	Nan::SetPrototypeMethod(ctor, "and", And);
	Nan::SetPrototypeMethod(ctor, "or", Or);
	Nan::SetPrototypeMethod(ctor, "toSquare", ToSquare);
	Nan::SetPrototypeMethod(ctor, "toSquareAsync", ToSquareAsync);
	Nan::SetPrototypeMethod(ctor, "rescale", Rescale);
	Nan::SetPrototypeMethod(ctor, "rescaleAsync", RescaleAsync);

  target->Set(Nan::New("Rect").ToLocalChecked(), ctor->GetFunction());
};

NAN_METHOD(Rect::New) {
	Rect* self = new Rect();
	if (info.Length() == 0) {
		self->rect = cv::Rect2d();
	} else {
		if (info.Length() < 4) {
			return Nan::ThrowError("Rect::New - expected arguments x, y, width, height");
		}
		double x = info[0]->NumberValue();
		double y = info[1]->NumberValue();
		double width = info[2]->NumberValue();
		double height = info[3]->NumberValue();
		self->rect = cv::Rect2d(x, y, width, height);
	}
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}

struct Rect::LogicOpWorker : public SimpleWorker {
public:
	cv::Rect2d rect;
	cv::Rect2d rect2;
	cv::Rect2d outRect;

	LogicOpWorker(cv::Rect2d rect) {
		this->rect = rect;
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Rect::Converter::arg(0, &rect2, info)
			);
	}

	FF_VAL getReturnValue() {
		return Rect::Converter::wrap(outRect);
	}
};

struct Rect::AndWorker : public Rect::LogicOpWorker {
public:
	AndWorker(cv::Rect2d rect) : LogicOpWorker(rect) {
	}

	const char* execute() {
		outRect = rect & rect2;
		return "";
	}
};

NAN_METHOD(Rect::And) {
	AndWorker worker(Rect::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Rect::And", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

struct Rect::OrWorker : public Rect::LogicOpWorker {
public:
	OrWorker(cv::Rect2d rect) : LogicOpWorker(rect) {
	}

	const char* execute() {
		outRect = rect | rect2;
		return "";
	}
};

NAN_METHOD(Rect::Or) {
	OrWorker worker(Rect::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Rect::Or", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

struct Rect::ToSquareWorker : SimpleWorker {
public:
	cv::Rect2d rect;
	cv::Rect2d outRect;

	ToSquareWorker(cv::Rect2d rect) {
		this->rect = rect;
	}

	const char* execute() {
		double diff = rect.width - rect.height;
		if (diff < 0) {
			outRect = cv::Rect(rect.x + (diff / 2), rect.y, rect.width - diff, rect.height);
		}
		else {
			outRect = cv::Rect(rect.x, rect.y - (diff / 2), rect.width, rect.height + diff);
		}
		return "";
	}

	FF_VAL getReturnValue() {
		return Rect::Converter::wrap(outRect);
	}
};

NAN_METHOD(Rect::ToSquare) {
	ToSquareWorker worker(Rect::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Rect::ToSquare", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Rect::ToSquareAsync) {
	ToSquareWorker worker(Rect::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Rect::ToSquareAsync", ToSquareWorker, worker);
}


struct Rect::RescaleWorker : SimpleWorker {
public:
	cv::Rect2d rect;
	double f;
	cv::Rect2d outRect;

	RescaleWorker(cv::Rect2d rect) {
		this->rect = rect;
	}

	const char* execute() {
		double newWidth = rect.width * f;
		double newHeight = rect.height * f;
		double offX = (rect.width - newWidth) / 2;
		double offY = (rect.height - newHeight) / 2;
		outRect = cv::Rect(rect.x + offX, rect.y + offY, newWidth, newHeight);
		return "";
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			DoubleConverter::arg(0, &f, info)
		);
	}

	FF_VAL getReturnValue() {
		return Rect::Converter::wrap(outRect);
	}
};

NAN_METHOD(Rect::Rescale) {
	RescaleWorker worker(Rect::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Rect::Rescale", worker);
	info.GetReturnValue().Set(worker.getReturnValue());

}

NAN_METHOD(Rect::RescaleAsync) {
	RescaleWorker worker(Rect::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Rect::RescaleAsync", RescaleWorker, worker);
}
