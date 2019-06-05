#include "NativeNodeUtils.h"

#ifndef __FF_BINDINGBASE_H__
#define __FF_BINDINGBASE_H__

namespace FF {

	class INamedValue {
	public:
		virtual std::string getName() = 0;
		virtual v8::Local<v8::Value> wrap() = 0;
	};

	class IArg {
	public:
		virtual bool unwrapArg(int argN, Nan::NAN_METHOD_ARGS_TYPE info) = 0;
	};

	class IOptArg: public IArg {
	public:
		virtual bool unwrapProp(v8::Local<v8::Object> opts) = 0;
	};

	template <class T>
	class Value {
	public:
		Value() {};
		Value(T val) : val(val) {};

		T& ref() {
			return val;
		}

		T* ptr() {
			return &val;
		}
	private:
		T val;
	};

	template <class Converter>
	class NamedValue : public INamedValue, public Value<typename Converter::Type> {
	public:
		typedef Value<typename Converter::Type> super;

		NamedValue(std::string name) : name(name) {};
		NamedValue(std::string name, typename Converter::Type defaultValue) : super(defaultValue), name(name) {};

		v8::Local<v8::Value> wrap() {
			return Converter::wrap(super::ref());
		}

		std::string getName() {
			return name;
		}

	private:
		std::string name;
	};

	template <class Converter>
	class Arg : public NamedValue<Converter>, public IArg {
	public:
		typedef NamedValue<Converter> super;

		Arg() : super("") {};

		bool unwrapArg(int argN, Nan::NAN_METHOD_ARGS_TYPE info) {
			return Converter::arg(argN, super::super::ptr(), info);
		}
	};

	template <class Converter>
	class OptArg : public NamedValue<Converter>, public IOptArg {
	public:
		typedef NamedValue<Converter> super;

		OptArg(std::string name) : super(name) {};
		OptArg(std::string name, typename Converter::Type defaultValue) : super(name, defaultValue) {};

		bool unwrapArg(int argN, Nan::NAN_METHOD_ARGS_TYPE info) {
			return Converter::optArg(argN, super::super::ptr(), info);
		}

		bool unwrapProp(v8::Local<v8::Object> opts) {
			return Converter::optProp(super::super::ptr(), super::getName().c_str(), opts);
		}
	};

	class BindingBase {
	public:
		template <class Converter>
		std::shared_ptr<Value<typename Converter::Type>> req() {
			std::shared_ptr<Arg<Converter>> val = std::make_shared<Arg<Converter>>();
			requiredArgs.push_back(val);
			return val;
		}

		template <class Converter>
		std::shared_ptr<Value<typename Converter::Type>> opt(std::string name, typename Converter::Type defaultValue) {
			std::shared_ptr<OptArg<Converter>> val = std::make_shared<OptArg<Converter>>(name, defaultValue);
			optionalArgs.push_back(val);
			return val;
		}

		template <class Converter>
		std::shared_ptr<Value<typename Converter::Type>> ret(std::string name) {
			std::shared_ptr<NamedValue<Converter>> val = std::make_shared<NamedValue<Converter>>(name);
			returnValues.push_back(val);
			return val;
		}

		template <class Converter>
		std::shared_ptr<Value<typename Converter::Type>> ret(std::string name, typename Converter::Type defaultValue) {
			std::shared_ptr<NamedValue<Converter>> val = std::make_shared<NamedValue<Converter>>(name, defaultValue);
			returnValues.push_back(val);
			return val;
		}

		bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			for (uint idx = 0; idx < requiredArgs.size(); idx++) {
				if (requiredArgs[idx]->unwrapArg(idx, info)) {
					return true;
				}
			}
			return false;
		}

		bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			uint optArgsIdx = requiredArgs.size();
			for (uint idx = 0; idx < optionalArgs.size(); idx++) {
				if (optionalArgs[idx]->unwrapArg(optArgsIdx + idx, info)) {
					return true;
				}
			}
			return false;
		}

		bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
			int optArgsIdx = requiredArgs.size();
			return optionalArgs.size() > 1 && FF::isArgObject(info, optArgsIdx);
		}

		bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
			int optArgsIdx = requiredArgs.size();
			v8::Local<v8::Object> opts = info[optArgsIdx]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
			for (uint idx = 0; idx < optionalArgs.size(); idx++) {
				if (optionalArgs[idx]->unwrapProp(opts)) {
					return true;
				}
			}
			return false;
		}

		v8::Local<v8::Value> getReturnValue() {
			if (returnValues.size() == 0) {
				return Nan::Undefined();
			}
			if (returnValues.size() == 1) {
				return returnValues[0]->wrap();
			}
			v8::Local<v8::Object> ret = Nan::New<v8::Object>();
			for (std::shared_ptr<INamedValue> val : returnValues) {
				Nan::Set(ret, Nan::New(val->getName()).ToLocalChecked(), val->wrap());
			}
			return ret;
		}

	protected:
		std::vector<std::shared_ptr<IArg>> requiredArgs;
		std::vector<std::shared_ptr<IOptArg>> optionalArgs;
		std::vector<std::shared_ptr<INamedValue>> returnValues;
	};


}
#endif