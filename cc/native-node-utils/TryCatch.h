#include "utils.h"
#include "Converters.h"

#ifndef __FF_TRY_CATCH_H__
#define __FF_TRY_CATCH_H__

namespace FF {

	class TryCatch : public Nan::TryCatch {
	public:
		// errorPrefix can be used to prefix errors in a method binding with the method name
		std::string errorPrefix;
		TryCatch(std::string errorPrefix) : errorPrefix(errorPrefix) {};

		std::string getCaughtErrorMessageUnchecked() {
			return *Nan::Utf8String(Exception()->ToString(Nan::GetCurrentContext()).ToLocalChecked());
		}

		std::string extendWithPrefix(std::string errorMessage) {
			if (!errorPrefix.empty()) {
				return errorPrefix + std::string(" - ") + errorMessage;
			}
			return errorMessage;
		}

		void throwError(v8::Local<v8::Value> message) {
			Nan::ThrowError(message);
			// need to call ReThrow to prevent this try catch to catch the error thrown by itself
			ReThrow();
		}

		void throwError(std::string errorMessage) {
			throwError(StringConverter::wrap(extendWithPrefix(errorMessage)));
		}

		void reThrow() {
			throwError(StringConverter::wrap(extendWithPrefix(getCaughtErrorMessageUnchecked())));
		}
	};

}

#endif
