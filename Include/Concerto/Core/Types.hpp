//
// Created by arthur on 22/02/2023.
//

#ifndef CONCERTOCORE_INCLUDE_TYPES_HPP_
#define CONCERTOCORE_INCLUDE_TYPES_HPP_

#include <cstdint>

namespace Concerto
{
#ifndef LIB_STATIC
	#ifdef _WIN32
		#define CONCERTO_EXPORT __declspec(dllexport)
		#define CONCERTO_IMPORT __declspec(dllimport)
	#else
		#define CONCERTO_EXPORT [[gnu::visibility("default")]]
		#define CONCERTO_IMPORT [[gnu::visibility("default")]]
	#endif
#else
	#define CONCERTO_EXPORT
	#define CONCERTO_IMPORT
#endif

#ifdef CONCERTO_BUILD
	#define CONCERTO_PUBLIC_API CONCERTO_EXPORT
#else
	#define CONCERTO_PUBLIC_API CONCERTO_IMPORT
#endif

	using Int8 = std::int8_t;
	using Int16 = std::int16_t;
	using Int32 = std::int32_t;
	using Int64 = std::int64_t;

	using UInt8 = std::uint8_t;
	using UInt16 = std::uint16_t;
	using UInt32 = std::uint32_t;
	using UInt64 = std::uint64_t;

	using Byte = std::int8_t;
	using UByte = std::uint8_t;
}

#endif //CONCERTOCORE_INCLUDE_TYPES_HPP_
