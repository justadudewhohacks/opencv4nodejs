#include "PrimitiveTypeConverters.h"
#include "ArrayConverter.h"

#ifndef __FF_CONVERTERS_H__
#define __FF_CONVERTERS_H__

namespace FF {
	template<class ConverterImpl, class ElementType = typename ConverterImpl::Type>
	class ArrayConverterTemplate : public AbstractConverter<ArrayConverterImpl<ConverterImpl, ElementType>> {};
	
	template<class ConverterImpl, class ElementType = typename ConverterImpl::Type>
	class ArrayOfArraysConverterTemplate : public AbstractConverter<ArrayOfArraysConverterImpl<ConverterImpl, ElementType>> {};

	typedef AbstractConverter<IntConverterImpl> IntConverter;
	typedef AbstractConverter<UintConverterImpl> UintConverter;
	typedef AbstractConverter<LongConverterImpl> LongConverter;
	typedef AbstractConverter<UlongConverterImpl> UlongConverter;
	typedef AbstractConverter<CharConverterImpl> CharConverter;
	typedef AbstractConverter<UcharConverterImpl> UcharConverter;
	typedef AbstractConverter<BoolConverterImpl> BoolConverter;
	typedef AbstractConverter<DoubleConverterImpl> DoubleConverter;
	typedef AbstractConverter<FloatConverterImpl> FloatConverter;
	typedef AbstractConverter<StringConverterImpl> StringConverter;

	typedef ArrayConverterTemplate<IntConverterImpl> IntArrayConverter;
	typedef ArrayConverterTemplate<UintConverterImpl> UintArrayConverter;
	typedef ArrayConverterTemplate<LongConverterImpl> LongArrayConverter;
	typedef ArrayConverterTemplate<UlongConverterImpl> UlongArrayConverter;
	typedef ArrayConverterTemplate<CharConverterImpl> CharArrayConverter;
	typedef ArrayConverterTemplate<UcharConverterImpl> UcharArrayConverter;
	typedef ArrayConverterTemplate<BoolConverterImpl> BoolArrayConverter;
	typedef ArrayConverterTemplate<DoubleConverterImpl> DoubleArrayConverter;
	typedef ArrayConverterTemplate<FloatConverterImpl> FloatArrayConverter;
	typedef ArrayConverterTemplate<StringConverterImpl> StringArrayConverter;

	typedef ArrayOfArraysConverterTemplate<IntConverterImpl> IntArrayOfArraysConverter;
	typedef ArrayOfArraysConverterTemplate<UintConverterImpl> UintArrayOfArraysConverter;
	typedef ArrayOfArraysConverterTemplate<LongConverterImpl> LongArrayOfArraysConverter;
	typedef ArrayOfArraysConverterTemplate<UlongConverterImpl> UlongArrayOfArraysConverter;
	typedef ArrayOfArraysConverterTemplate<CharConverterImpl> CharArrayOfArraysConverter;
	typedef ArrayOfArraysConverterTemplate<UcharConverterImpl> UcharArrayOfArraysConverter;
	typedef ArrayOfArraysConverterTemplate<BoolConverterImpl> BoolArrayOfArraysConverter;
	typedef ArrayOfArraysConverterTemplate<DoubleConverterImpl> DoubleArrayOfArraysConverter;
	typedef ArrayOfArraysConverterTemplate<FloatConverterImpl> FloatArrayOfArraysConverter;
	typedef ArrayOfArraysConverterTemplate<StringConverterImpl> StringArrayOfArraysConverter;
}

#endif