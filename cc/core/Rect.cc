#include "Rect.h"
#include "Size.h"

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
	Nan::SetPrototypeMethod(ctor, "pad", Pad);
	Nan::SetPrototypeMethod(ctor, "padAsync", PadAsync);
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


struct Rect::PadWorker : SimpleWorker {
public:
	cv::Rect2d rect;
	cv::Size2d newSize = cv::Size2d();
	cv::Rect2d outRect;

	PadWorker(cv::Rect2d rect) {
		this->rect = rect;
	}

	const char* execute() {
		double offX = (rect.width - newSize.width) / 2;
		double offY = (rect.height - newSize.height) / 2;
		outRect = cv::Rect(rect.x + offX, rect.y + offY, newSize.width, newSize.height);
		return "";
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		bool isSizeArg = Size::Converter::hasInstance(info[0]);
		double f = 1;
		bool didThrow = 
			(!isSizeArg && DoubleConverter::arg(0, &f, info))
			|| (isSizeArg && Size::Converter::arg(0, &newSize, info));

		if (!isSizeArg) {
			newSize = cv::Size2d(rect.width * f, rect.height * f);
		}
		return didThrow;
	}

	FF_VAL getReturnValue() {
		return Rect::Converter::wrap(outRect);
	}
};

NAN_METHOD(Rect::Pad) {
	PadWorker worker(Rect::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Rect::Pad", worker);
	info.GetReturnValue().Set(worker.getReturnValue());

}

NAN_METHOD(Rect::PadAsync) {
	PadWorker worker(Rect::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Rect::PadAsync", PadWorker, worker);
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
		outRect = cv::Rect(f * rect.x, f * rect.y, f * rect.width, f * rect.height);
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
