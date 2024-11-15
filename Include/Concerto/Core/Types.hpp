//
// Created by arthur on 22/02/2023.
//

#ifndef CONCERTO_CORE_TYPES_HPP
#define CONCERTO_CORE_TYPES_HPP

#include <cstdint>

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

//from https://sourceforge.net/p/predef/wiki/Architectures/
#if defined(__arm__) || defined(__thumb__) || defined(_M_ARM) || defined(__arm)
	#define CONCERTO_ARCH_ARM
#elif defined(_M_ARM64) || defined(__aarch64__)
	#define CONCERTO_ARCH_ARM64
#elif defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(__x86_64) || defined(_M_AMD64) || defined(_M_X64)
	#define NAZARA_ARCH_X86_64
#elif defined(i386) || defined(__i386) || defined(_M_IX86)
	#define CONCERTO_ARCH_X86
#endif

#if defined(NDEBUG)
	#define CONCERTO_RELEASE
#else
	#define CONCERTO_DEBUG
#endif

#ifndef LIB_STATIC
	#ifdef CONCERTO_PLATFORM_WINDOWS
		#define CONCERTO_EXPORT __declspec(dllexport)
		#define CONCERTO_IMPORT __declspec(dllimport)
	#else
		#define CONCERTO_EXPORT __attribute__((visibility("default")))
		#define CONCERTO_IMPORT __attribute__((visibility("default")))
	#endif
#else
	#define CONCERTO_EXPORT
	#define CONCERTO_IMPORT
#endif

#ifdef CONCERTO_CORE_BUILD
	#define CONCERTO_CORE_PUBLIC_API CONCERTO_EXPORT
#else
	#define CONCERTO_CORE_PUBLIC_API CONCERTO_IMPORT
#endif


#if defined(CONCERTO_PLATFORM_WINDOWS)
	#define CONCERTO_BREAK_IN_DEBUGGER __debugbreak()
#elif defined(CONCERTO_PLATFORM_POSIX)
	#if defined(CONCERTO_ARCH_ARM64) || defined(CONCERTO_ARCH_ARM)
		#define CONCERTO_BREAK_IN_DEBUGGER __builtin_trap();
	#else
		#define CONCERTO_BREAK_IN_DEBUGGER asm("int $3");
	#endif
#else
	#define CONCERTO_BREAK_IN_DEBUGGER {}
#endif


#ifdef CONCERTO_UNITY_BUILD_ID
	#define CONCERTO_ANONYMOUS_NAMESPACE CONCERTO_UNITY_BUILD_ID
#else
	#define CONCERTO_ANONYMOUS_NAMESPACE
#endif

#if defined(__clang__)
	#define CONCERTO_COMPILER_CLANG
	#define CONCERTO_FUNCTION_SIGNATURE __PRETTY_FUNCTION__
#define CONCERTO_FILE
#elif defined(__GNUC__)
	#define CONCERTO_COMPILER_GCC
	#define CONCERTO_FUNCTION_SIGNATURE __PRETTY_FUNCTION__
#elif defined(__MINGW32__)
	#define CONCERTO_COMPILER_MINGW
	#define CONCERTO_FUNCTION_SIGNATURE __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
	#define CONCERTO_COMPILER_MSVC
	#define CONCERTO_FUNCTION_SIGNATURE __FUNCSIG__
#else
	#pragma message("Unsuported compiler")
#endif

namespace cct
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

	CONCERTO_CORE_PUBLIC_API bool IsDebuggerAttached();
}; // namespace cct

#endif //CONCERTO_CORE_TYPES_HPP
