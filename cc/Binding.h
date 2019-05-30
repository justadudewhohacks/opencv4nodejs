#include "NativeNodeUtils.h"

#ifndef __FF_BINDINGBASE_H__
#define __FF_BINDINGBASE_H__

namespace FF {

	class IValue {
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
	class ValueBase {
	public:
		T get() {
			return val;
		}

		void set(T val) {
			this->val = val;
		}
	protected:
		T val;
	};

	template <class Converter, class T>
	class Value : public IValue, public ValueBase<T> {
	public:
		Value(std::string name) : name(name) {}

		v8::Local<v8::Value> wrap() {
			return Converter::wrap(val);
		}

		std::string getName() {
			return name;
		}
	protected:
		std::string name;
	};

	template <class Converter, class T>
	class Arg : public Value<Converter, T>, public IArg {
	public:
		Arg() : Value<Converter, T>("") {}

		bool unwrapArg(int argN, Nan::NAN_METHOD_ARGS_TYPE info) {
			return Converter::arg(argN, &val, info);
		}
	};

	template <class Converter, class T>
	class OptArg : public Value<Converter, T>, public IOptArg {
	public:
		OptArg(std::string name) : Value<Converter, T>(name) {}

		bool unwrapArg(int argN, Nan::NAN_METHOD_ARGS_TYPE info) {
			return Converter::optArg(argN, &val, info);
		}

		bool unwrapProp(v8::Local<v8::Object> opts) {
			return Converter::optProp(&val, name.c_str(), opts);
		}
	};

	template <class Converter, class T>
	class ReturnValue : public Value<Converter, T> {
	public:
		ReturnValue(std::string name) : Value<Converter, T>(name) {}
	};

	typedef ValueBase<int> IntValue;
	typedef ValueBase<uint> UintValue;
	typedef ValueBase<double> DoubleValue;
	typedef ValueBase<float> FloatValue;
	typedef ValueBase<bool> BoolValue;
	typedef ValueBase<std::string> StringValue;
	typedef ValueBase<std::vector<int>> IntArrayValue;
	typedef ValueBase<std::vector<uint>> UintArrayValue;
	typedef ValueBase<std::vector<double>> DoubleArrayValue;
	typedef ValueBase<std::vector<float>> FloatArrayValue;
	typedef ValueBase<std::vector<bool>> BoolArrayValue;
	typedef ValueBase<std::vector<std::string>> StringArrayValue;

	typedef std::shared_ptr<IntValue> Int;
	typedef std::shared_ptr<UintValue> Uint;
	typedef std::shared_ptr<DoubleValue> Double;
	typedef std::shared_ptr<FloatValue> Float;
	typedef std::shared_ptr<BoolValue> Bool;
	typedef std::shared_ptr<StringValue> String;
	typedef std::shared_ptr<IntArrayValue> IntArray;
	typedef std::shared_ptr<UintArrayValue> UintArray;
	typedef std::shared_ptr<DoubleArrayValue> DoubleArray;
	typedef std::shared_ptr<FloatArrayValue> FloatArray;
	typedef std::shared_ptr<BoolArrayValue> BoolArray;
	typedef std::shared_ptr<StringArrayValue> StringArray;

	class BindingBase {
	public:
		Int intRequired() {
			return addRequiredArg<Arg<FF::IntConverter, int>>();
		}

		Int intOptional(int defaultValue, std::string name) {
			return addOptionalArg<OptArg<FF::IntConverter, int>, int>(defaultValue, name);
		}

		Int intReturnValue(std::string name) {
			return addReturnValue<ReturnValue<FF::IntConverter, int>>(name);
		}

		IntArray intArrayRequired() {
			return addRequiredArg<Arg<IntArrayConverter, std::vector<int>>>();
		}

		IntArray intArrayOptional(std::string name) {
			return addOptionalArg<OptArg<IntArrayConverter, std::vector<int>>>(name);
		}

		IntArray intArrayReturnValue(std::string name) {
			return addReturnValue<ReturnValue<IntArrayConverter, std::vector<int>>>(name);
		}


		Uint uintRequired() {
			return addRequiredArg<Arg<UFF::IntConverter, uint>>();
		}

		Uint uintOptional(uint defaultValue, std::string name) {
			return addOptionalArg<OptArg<UFF::IntConverter, uint>, uint>(defaultValue, name);
		}

		Uint uintReturnValue(std::string name) {
			return addReturnValue<ReturnValue<UFF::IntConverter, uint>>(name);
		}

		UintArray uintArrayRequired() {
			return addRequiredArg<Arg<UintArrayConverter, std::vector<uint>>>();
		}

		UintArray uintArrayOptional(std::string name) {
			return addOptionalArg<OptArg<UintArrayConverter, std::vector<uint>>>(name);
		}

		UintArray uintArrayReturnValue(std::string name) {
			return addReturnValue<ReturnValue<UintArrayConverter, std::vector<uint>>>(name);
		}

		Double doubleRequired() {
			return addRequiredArg<Arg<FF::DoubleConverter, double>>();
		}

		Double doubleOptional(double defaultValue, std::string name) {
			return addOptionalArg<OptArg<FF::DoubleConverter, double>, double>(defaultValue, name);
		}

		Double doubleReturnValue(std::string name) {
			return addReturnValue<ReturnValue<FF::DoubleConverter, double>>(name);
		}

		DoubleArray doubleArrayRequired() {
			return addRequiredArg<Arg<DoubleArrayConverter, std::vector<double>>>();
		}

		DoubleArray doubleArrayOptional(std::string name) {
			return addOptionalArg<OptArg<DoubleArrayConverter, std::vector<double>>>(name);
		}

		DoubleArray doubleArrayReturnValue(std::string name) {
			return addReturnValue<ReturnValue<DoubleArrayConverter, std::vector<double>>>(name);
		}

		Float floatRequired() {
			return addRequiredArg<Arg<FF::FloatConverter, float>>();
		}

		Float floatOptional(float defaultValue, std::string name) {
			return addOptionalArg<OptArg<FF::FloatConverter, float>, float>(defaultValue, name);
		}

		Float floatReturnValue(std::string name) {
			return addReturnValue<ReturnValue<FF::FloatConverter, float>>(name);
		}

		FloatArray floatArrayRequired() {
			return addRequiredArg<Arg<FloatArrayConverter, std::vector<float>>>();
		}

		FloatArray floatArrayOptional(std::string name) {
			return addOptionalArg<OptArg<FloatArrayConverter, std::vector<float>>>(name);
		}

		FloatArray floatArrayReturnValue(std::string name) {
			return addReturnValue<ReturnValue<FloatArrayConverter, std::vector<float>>>(name);
		}

		Bool boolRequired() {
			return addRequiredArg<Arg<FF::BoolConverter, bool>>();
		}

		Bool boolOptional(bool defaultValue, std::string name) {
			return addOptionalArg<OptArg<FF::BoolConverter, bool>, bool>(defaultValue, name);
		}

		Bool boolReturnValue(std::string name) {
			return addReturnValue<ReturnValue<FF::BoolConverter, bool>>(name);
		}

		BoolArray boolArrayRequired() {
			return addRequiredArg<Arg<BoolArrayConverter, std::vector<bool>>>();
		}

		BoolArray boolArrayOptional(std::string name) {
			return addOptionalArg<OptArg<BoolArrayConverter, std::vector<bool>>>(name);
		}

		BoolArray boolArrayReturnValue(std::string name) {
			return addReturnValue<ReturnValue<BoolArrayConverter, std::vector<bool>>>(name);
		}
		String stringRequired() {
			return addRequiredArg<Arg<FF::StringConverter, std::string>>();
		}

		String stringOptional(std::string defaultValue, std::string name) {
			return addOptionalArg<OptArg<FF::StringConverter, std::string>, std::string>(defaultValue, name);
		}

		String stringReturnValue(std::string name) {
			return addReturnValue<ReturnValue<FF::StringConverter, std::string>>(name);
		}

		StringArray stringArrayRequired() {
			return addRequiredArg<Arg<StringArrayConverter, std::vector<std::string>>>();
		}

		StringArray stringArrayOptional(std::string name) {
			return addOptionalArg<OptArg<StringArrayConverter, std::vector<std::string>>>(name);
		}

		StringArray stringArrayReturnValue(std::string name) {
			return addReturnValue<ReturnValue<StringArrayConverter, std::vector<std::string>>>(name);
		}

		template <class ValueType>
		std::shared_ptr<ValueType> addRequiredArg() {
			std::shared_ptr<ValueType> val = std::make_shared<ValueType>();
			requiredArgs.push_back(val);
			return val;
		}

		template <class ValueType>
		std::shared_ptr<ValueType> addOptionalArg(std::string name) {
			std::shared_ptr<ValueType> val = std::make_shared<ValueType>(name);
			optionalArgs.push_back(val);
			return val;
		}

		template <class ValueType, class T>
		std::shared_ptr<ValueType> addOptionalArg(T defaultValue, std::string name) {
			std::shared_ptr<ValueType> val = std::make_shared<ValueType>(name);
			val->set(defaultValue);
			optionalArgs.push_back(val);
			return val;
		}

		template <class ValueType>
		std::shared_ptr<ValueType> addReturnValue(std::string name) {
			std::shared_ptr<ValueType> val = std::make_shared<ValueType>(name);
			returnValues.push_back(val);
			return val;
		}

		bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			for (int idx = 0; idx < requiredArgs.size(); idx++) {
				if (requiredArgs[idx]->unwrapArg(idx, info)) {
					return true;
				}
			}
			return false;
		}

		bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			for (int idx = 0; idx < optionalArgs.size(); idx++) {
				if (optionalArgs[idx]->unwrapArg(idx, info)) {
					return true;
				}
			}
			return false;
		}

		bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
			return optionalArgs.size() > 1;
		}

		bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
			int optArgsIdx = requiredArgs.size();
			v8::Local<v8::Object> opts = info[optArgsIdx]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
			for (int idx = 0; idx < optionalArgs.size(); idx++) {
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
			for (std::shared_ptr<IValue> val : returnValues) {
				Nan::Set(ret, Nan::New(val->getName()).ToLocalChecked(), val->wrap());
				;
			}
			return ret;
		}

	protected:
		std::vector<std::shared_ptr<IArg>> requiredArgs;
		std::vector<std::shared_ptr<IOptArg>> optionalArgs;
		std::vector<std::shared_ptr<IValue>> returnValues;
	};


}
#endif