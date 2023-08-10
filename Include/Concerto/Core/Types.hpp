//
// Created by arthur on 22/02/2023.
//

#ifndef CONCERTOCORE_INCLUDE_TYPES_HPP_
#define CONCERTOCORE_INCLUDE_TYPES_HPP_

#include <cstdint>

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

#if defined(_WIN32)
#define CONCERTO_PLATFORM_WINDOWS
#elif defined(__linux__)
#define CONCERTO_PLATFORM_LINUX
#define CONCERTO_PLATFORM_POSIX
#elif defined(__FreeBSD__)
#define CONCERTO_PLATFORM_FREEBSD
#define CONCERTO_PLATFORM_POSIX
#elif defined(__APPLE__)
#define CONCERTO_PLATFORM_MACOS
#define CONCERTO_PLATFORM_POSIX
#endif

#if defined(NDEBUG)
#define CONCERTO_RELEASE
#else
#define CONCERTO_DEBUG
#endif

#if defined(CONCERTO_PLATFORM_WINDOWS)
#define CONCERTO_BREAK_IN_DEBUGGER __debugbreak();
#elif defined(CONCERTO_PLATFORM_POSIX)
#define CONCERTO_BREAK_IN_DEBUGGER asm ("int $3");
#else
#define CONCERTO_BREAK_IN_DEBUGGER {}
#endif

#if defined(CONCERTO_DEBUG)
#define CONCERTO_ASSERT(expression)  { if (Concerto::IsDebuggerAttached() && !(expression)) { CONCERTO_BREAK_IN_DEBUGGER; } }
#else
#define CONCERTO_ASSERT(expression) {}
#endif

#define CONCERTO_ASSERT_FALSE CONCERTO_ASSERT(false)

#ifdef CONCERTO_UNITY_BUILD_ID
#define CONCERTO_ANONYMOUS_NAMESPACE CONCERTO_UNITY_BUILD_ID
#else
#define CONCERTO_ANONYMOUS_NAMESPACE
#endif

namespace Concerto
{
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

	CONCERTO_PUBLIC_API bool IsDebuggerAttached();
}; // namespace Concerto

#endif //CONCERTOCORE_INCLUDE_TYPES_HPP_
