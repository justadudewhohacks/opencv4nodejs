#include "NativeNodeUtils.h"
#include <opencv2/core.hpp>

#ifndef __FF_MACROS_H__
#define __FF_MACROS_H__

#define CV_VERSION_GREATER_EQUAL(major, minor, revision) \
	(	\
		CV_VERSION_MAJOR > major  \
		|| (CV_VERSION_MAJOR == major && CV_VERSION_MINOR > minor) \
		|| (CV_VERSION_MAJOR == major && CV_VERSION_MINOR == minor && CV_VERSION_REVISION >= revision) \
	)

#define CV_VERSION_LOWER_THAN(major, minor, revision) \
	!(CV_VERSION_GREATER_EQUAL(major, minor, revision))

/* define getters, custom expression for accessing properties of "self" */
#define FF_GETTER_CUSTOM(ff_property_name, ff_property_converter, ff_access_property_expr) \
	static ff_property_converter::Type getProperty_##ff_property_name(ClassType* self) { \
		return self->ff_access_property_expr; \
	} \
	static NAN_GETTER(ff_property_name##_getter) { \
		getter<ff_property_converter>(info, getProperty_##ff_property_name); \
	}

/* define getters */
#define FF_GETTER(ff_property_name, ff_property_converter) \
	FF_GETTER_CUSTOM(ff_property_name, ff_property_converter, self.ff_property_name)

/* define accessors, custom expression for accessing properties of "self" */
#define FF_ACCESSORS_CUSTOM(ff_property_name, ff_property_converter, ff_access_property_expr) \
	FF_GETTER_CUSTOM(ff_property_name, ff_property_converter, ff_access_property_expr); \
	static void setProperty_##ff_property_name(ClassType* self, ff_property_converter::Type val) { \
		self->ff_access_property_expr = val; \
	} \
	static NAN_SETTER(ff_property_name##_setter) { \
		setter<ff_property_converter>(#ff_property_name, info, value, setProperty_##ff_property_name); \
	}

/* define accessors */
#define FF_ACCESSORS(ff_property_name, ff_property_converter) \
	FF_ACCESSORS_CUSTOM(ff_property_name, ff_property_converter, self.ff_property_name)

/* define accessors, self is pointer type */
#define FF_ACCESSORS_PTR(ff_property_name, ff_property_converter) \
	FF_ACCESSORS_CUSTOM(ff_property_name, ff_property_converter, self->ff_property_name)

#define FF_SET_JS_PROP(obj, prop, val) Nan::Set(obj, FF::newString(#prop), val)

#define FF_SET_CV_CONSTANT(obj, cvConstant) \
	FF_SET_JS_PROP(obj, cvConstant, Nan::New<v8::Integer>(cvConstant));

#define FF_ASSERT_CONSTRUCT_CALL() \
  if (!info.IsConstructCall()) { \
    return tryCatch.throwError("constructor has to be called with \"new\" keyword"); \
  }

/* TODO: move this to native-node-utils */
namespace FF {
	template<class TEnum>
	class EnumConverterImpl : public FF::UnwrapperBase<EnumConverterImpl<TEnum>, typename TEnum::Type> {
	public:
		typedef typename TEnum::Type Type;

		static std::string getTypeName() {
			std::vector<const char*> mappings = TEnum::getEnumMappings();
			std::string typeName = "";
			for (uint i = 0; i < mappings.size(); i++) {
				typeName += mappings[i];
				if (i < (mappings.size() - 1)) {
					typeName += " | ";
				}
			}
			return typeName;
		}

		static bool assertType(v8::Local<v8::Value> jsVal) {
			return getMappingIndex(jsVal) != -1;
		}

		static Type unwrapUnchecked(v8::Local<v8::Value> jsVal) {
			int idx = getMappingIndex(jsVal);
			if (idx == -1) {
				idx = 0;
			}
			return TEnum::getEnumValues()[idx];
		}

		static v8::Local<v8::Value> wrap(Type val) {
			std::vector<const char*> mappings = TEnum::getEnumMappings();
			return StringConverter::wrap(mappings[getValueIndex(val)]);
		}

	private:
		static int getMappingIndex(v8::Local<v8::Value> jsVal) {
			std::string val;
			std::vector<const char*> mappings = TEnum::getEnumMappings();
			if (!StringConverter::unwrapTo(&val, jsVal)) {
				for (uint idx = 0; idx < mappings.size(); idx++) {
					if (val.compare(mappings[idx]) == 0) {
						return (int)idx;
					}
				}
			}
			return -1;
		}

		static int getValueIndex(Type val) {
			std::vector<Type> enumValues = TEnum::getEnumValues();
			for (uint idx = 0; idx < enumValues.size(); idx++) {
				if (enumValues[idx] == val) {
					return (int)idx;
				}
			}
			return -1;
		}
	};

	template<class TEnum>
	class EnumWrap {
	public:
		typedef AbstractConverter<EnumConverterImpl<TEnum>> Converter;

		static void init(Nan::ADDON_REGISTER_FUNCTION_ARGS_TYPE target) {
			v8::Local<v8::Object> scoreTypes = Nan::New<v8::Object>();
			for (const char* e : TEnum::getEnumMappings()) {
				Nan::Set(scoreTypes, newString(e), newString(e));
			}
			Nan::Set(target, newString(TEnum::getClassName()), scoreTypes);
		}
	};
}

#endif
