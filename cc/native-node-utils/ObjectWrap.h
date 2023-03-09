#include "utils.h"
#include "ArrayConverter.h"
#include "ArrayOfArraysConverter.h"
#include "InstanceConverter.h"
#include "TryCatch.h"
#include <functional>

#ifndef __FF_OBJECT_WRAP_H__
#define __FF_OBJECT_WRAP_H__

namespace FF {

	template<class TClass>
	class ObjectWrapBase {
	public:
		static TClass* unwrapClassPtrUnchecked(v8::Local<v8::Value> jsVal) {
			return unwrapNanObjectWrap<TClass>(jsVal);
		}

		static TClass* unwrapThis(Nan::NAN_METHOD_ARGS_TYPE info) {
			return unwrapClassPtrUnchecked(info.This());
		}

		static TClass* unwrapThis(Nan::NAN_GETTER_ARGS_TYPE info) {
			return unwrapClassPtrUnchecked(info.This());
		}

		static TClass* unwrapThis(Nan::NAN_SETTER_ARGS_TYPE info) {
			return unwrapClassPtrUnchecked(info.This());
		}
	};

	template<class TClass, class T>
	class ObjectWrapTemplate : public ObjectWrapBase<TClass> {
	public:
		typedef ObjectWrapBase<TClass> super;

		T self;

		void setNativeObject(T obj) { self = obj; }

		typedef InstanceConverterImpl<TClass, T> ConverterImpl;
		typedef AbstractConverter<ConverterImpl> Converter;

		template<class CastType>
		class WithCastConverter : public AbstractConverter<InstanceConverterImpl<TClass, CastType>> {};

		template<class ElementCastType>
		class ArrayWithCastConverter : public ArrayConverterTemplate<ConverterImpl, ElementCastType> {};

		template<class ElementCastType>
		class ArrayOfArraysWithCastConverter : public ArrayOfArraysConverterTemplate<ConverterImpl, ElementCastType> {};

		typedef ArrayWithCastConverter<T> ArrayConverter;
		typedef ArrayOfArraysWithCastConverter<T> ArrayOfArraysConverter;

		template<class WorkerImpl>
		static void syncBinding(std::string name, Nan::NAN_METHOD_ARGS_TYPE info) {
			auto worker = std::make_shared<WorkerImpl>();
			worker->setup(unwrapSelf(info));
			FF::executeSyncBinding(
				worker,
				std::string(TClass::getClassName()) + "::" + name,
				info
			);
		}

		template<class WorkerImpl>
		static void asyncBinding(std::string name, Nan::NAN_METHOD_ARGS_TYPE info) {
			auto worker = std::make_shared<WorkerImpl>();
			worker->setup(unwrapSelf(info));
			FF::executeAsyncBinding(
				worker,
				std::string(TClass::getClassName()) + "::" + name + "Async",
				info
			);
		}

		static bool hasInstance(v8::Local<v8::Value> jsVal) {
			return TClass::ConverterImpl::assertType(jsVal);
		}

		static T unwrapSelf(Nan::NAN_METHOD_ARGS_TYPE info) {
			return unwrapSelf(info.This());
		}

		static T unwrapSelf(Nan::NAN_GETTER_ARGS_TYPE info) {
			return unwrapSelf(info.This());
		}

		static T unwrapSelf(Nan::NAN_SETTER_ARGS_TYPE info) {
			return unwrapSelf(info.This());
		}

	protected:
		typedef TClass ClassType;

		template<class TPropertyConverter>
		static void setter(
			const char* setterName,
			Nan::NAN_SETTER_ARGS_TYPE info,
			v8::Local<v8::Value> value,
			void(*setProperty)(TClass*, typename TPropertyConverter::Type)
		) {
			FF::TryCatch tryCatch(setterName);
			typename TPropertyConverter::Type val;
			if (TPropertyConverter::unwrapTo(&val, value)) {
				return tryCatch.reThrow();
			}
			setProperty(super::unwrapThis(info), val);
		}

		template<class TPropertyConverter>
		static void getter(
			Nan::NAN_GETTER_ARGS_TYPE info,
			typename TPropertyConverter::Type(*getProperty)(TClass*)
		) {
			info.GetReturnValue().Set(TPropertyConverter::wrap(getProperty(super::unwrapThis(info))));
		}

		template<class ConstructorImpl>
		static void constructorBinding(Nan::NAN_METHOD_ARGS_TYPE info) {
			FF::executeSyncBinding(
				std::make_shared<ConstructorImpl>(info),
				std::string(TClass::getClassName()) + "::Constructor",
				info
			);
		};

		class ConstructorBase : public BindingBase, public ISyncWorker {
		public:
			bool applyUnwrappers(Nan::NAN_METHOD_ARGS_TYPE info) {
				if (!info.IsConstructCall()) {
					Nan::ThrowError("constructor has to be called with \"new\" keyword");
					return true;
				}
				return BindingBase::applyUnwrappers(info);
			}

			v8::Local<v8::Value> getReturnValue(Nan::NAN_METHOD_ARGS_TYPE info) {
				TClass* self = new TClass();
				self->Wrap(info.Holder());
				self->setNativeObject(nativeObject);
				modifySelf(self);
				return info.Holder();
			}

			std::string execute() {
				try {
					nativeObject = executeBinding();
					return "";
				}
				catch (std::exception &e) {
					return std::string(e.what());
				}
			}

		protected:
			T nativeObject;
			std::function<T(void)> executeBinding;
			std::function<void(TClass* self)> modifySelf = [](TClass*) {};
		};

	private:
		static T unwrapSelf(v8::Local<v8::Object> thisObj) {
			return super::unwrapClassPtrUnchecked(thisObj)->self;
		}
	};

	template<class TClass, class T>
	class ObjectWrap : public ObjectWrapTemplate<TClass, T>, public Nan::ObjectWrap {
	public:
		void Wrap(v8::Local<v8::Object> object) {
			Nan::ObjectWrap::Wrap(object);
		}
	};

}

#endif
