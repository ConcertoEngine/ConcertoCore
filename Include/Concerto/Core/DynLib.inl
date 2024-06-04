//
// Created by arthur on 02/06/2023.
//

#ifndef CONCERTO_CORE_DYNLIB_INL
#define CONCERTO_CORE_DYNLIB_INL

#include "Concerto/Core/DynLib.hpp"

namespace Concerto
{
	template <typename ReturnValue, typename ... Args>
	ReturnValue DynLib::Invoke(const std::string& functionName, Args&&... args)
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
			reinterpret_cast<Func>(symbol)(args...);
			return;
		}
		using Func = ReturnValue(*)(Args...);
		return reinterpret_cast<Func>(symbol)(args...);
	}

	template <typename T>
	T* DynLib::GetValue(const std::string& valueName)
	{
		void* symbol = GetSymbol(valueName);
		if (symbol == nullptr)
		{
			CONCERTO_ASSERT_FALSE("ConcertoCore: Invalid symbol pointer '{}'", valueName);
			return nullptr;
		}
		return static_cast<T*>(symbol);
	}
}// namespace Concerto

#endif//CONCERTO_CORE_DYNLIB_INL