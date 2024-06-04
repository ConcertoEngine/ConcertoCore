//
// Created by arthur on 03/06/2023.
//

#ifndef CONCERTO_CORE_FUNCTIONREF_HPP
#define CONCERTO_CORE_FUNCTIONREF_HPP

#include <concepts>
#include <functional>

#include "Concerto/Core/Assert.hpp"

namespace Concerto
{
	template<typename T>
	class FunctionRef;

	template<typename ReturnValue, typename... Args>
	class FunctionRef<ReturnValue(Args...)>
	{
	public:
		FunctionRef() = default;
		FunctionRef(const FunctionRef&) = default;
		FunctionRef(FunctionRef&&) = default;
		~FunctionRef() = default;

		FunctionRef& operator=(const FunctionRef&) = default;
		FunctionRef& operator=(FunctionRef&&) = default;

		explicit operator bool() const noexcept;

		template<typename Functor>
			requires(std::invocable<Functor, Args...>&& std::is_same_v<ReturnValue, std::invoke_result_t<Functor>>)
		FunctionRef& operator=(Functor&& f);

		ReturnValue operator()(Args... args) const;

	private:
		using CallBack = ReturnValue(*)(Args...);
		CallBack _function;
		void* _functionPointer;
	};

	template<typename ReturnValue, typename... Args>
	FunctionRef(ReturnValue(*)(Args...)) -> FunctionRef<ReturnValue(Args...)>;

	template <typename ReturnValue, typename ... Args>
	FunctionRef<ReturnValue(Args...)>::operator bool() const noexcept
	{
		return _functionPointer != nullptr;
	}

	template <typename ReturnValue, typename ... Args>
	ReturnValue FunctionRef<ReturnValue(Args...)>::operator()(Args... args) const
	{
		if (this->operator bool() == false)
		{
			CONCERTO_ASSERT_FALSE("ConcertoCore: Invalid function pointer");
			throw std::bad_function_call();
		}
		return std::invoke(*reinterpret_cast<CallBack>(_functionPointer), std::forward<Args>(args)...);
	}

	template <typename ReturnValue, typename ... Args>
	template <typename Functor> requires (std::invocable<Functor, Args...> && std::is_same_v<ReturnValue, std::invoke_result_t<Functor>>)
	FunctionRef<ReturnValue(Args...)>& FunctionRef<ReturnValue(Args...)>::operator=(Functor&& f)
	{
		_functionPointer = std::addressof(std::forward<Functor>(f));
		return *this;
	}

#include "Concerto/Core/FunctionRef.inl"
}

#endif // CONCERTO_CORE_FUNCTIONREF_HPP
