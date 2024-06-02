//
// Created by arthur on 02/06/2023.
//

#ifndef CONCERTO_CORE_DYNLIB_HPP
#define CONCERTO_CORE_DYNLIB_HPP

#include "Assert.hpp"

#include <filesystem>
#include <memory>
#include <type_traits>

#include "Concerto/Core/Types.hpp"

#ifdef CONCERTO_PLATFORM_WINDOWS
#define CONCERTO_DYNLIB_EXTENSION ".dll"
#elif defined(CONCERTO_PLATFORM_LINUX)
#define CONCERTO_DYNLIB_EXTENSION ".so"
#elif defined(CONCERTO_PLATFORM_MACOS)
#define CONCERTO_DYNLIB_EXTENSION ".dylib"
#endif

namespace Concerto
{
	class DynLibImpl;

	class CONCERTO_CORE_PUBLIC_API DynLib
	{
	 public:
		DynLib() = default;
		DynLib(DynLib&&) = default;
		DynLib(const DynLib&) = delete;
		~DynLib();

		DynLib& operator=(const DynLib&) = delete;
		DynLib& operator=(DynLib&&) = default;

		inline bool IsLoaded() const;
		bool Load(const std::filesystem::path& path);
		bool Unload();
		void* GetSymbol(const std::string& symbol) const;

		template<typename ReturnValue, typename... Args>
		ReturnValue Invoke(const std::string& functionName, Args&&... args)
			requires(std::is_invocable_v<ReturnValue (*)(Args...)>)
		{
			void* symbol = GetSymbol(functionName);
			if (symbol == nullptr)
			{
				CONCERTO_ASSERT_FALSE("ConcertoCore: Invalid symbol pointer '{}'", functionName);
				if constexpr (std::is_void_v<ReturnValue>)
					return;
				else return ReturnValue();
			}
			if constexpr (std::is_void_v<ReturnValue>)
			{
				using Func = void (*)(Args...);
				static_cast<Func>(symbol)(args...);
				return;
			}
			using Func = ReturnValue (*)(Args...);
			return static_cast<Func>(symbol)(args...);
		}


		template<typename T>
		T* GetValue(const std::string& valueName)
		{
			void* symbol = GetSymbol(valueName);
			if (symbol == nullptr)
			{
				CONCERTO_ASSERT_FALSE("ConcertoCore: Invalid symbol pointer '{}'", valueName);
				return nullptr;
			}
			return static_cast<T*>(symbol);
		}

		template<typename ReturnValue, typename... Args>
		ReturnValue operator()(std::string_view functionName, Args&& ...args)
			requires(std::is_invocable_v<ReturnValue (*)(Args...)>)
		{
			if constexpr (std::is_void_v<ReturnValue>)
				Invoke<ReturnValue, Args...>(functionName, args);
			return Invoke<ReturnValue, Args...>(functionName, args);
		}

	 private:
		struct ImplDeleter {
			void operator()(void* b) const;
		};
		std::unique_ptr<void, ImplDeleter> _impl;
		mutable std::string _lastError;
	};
}// namespace Concerto

#endif//CONCERTO_CORE_DYNLIB_HPP