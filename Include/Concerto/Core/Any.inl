//
// Created by arthur on 16/11/2023.
//

#ifndef CONCERTO_CORE_ANY_INL
#define CONCERTO_CORE_ANY_INL

#include <Concerto/Core/TypeInfo.hpp>

#include "Concerto/Core/Assert.hpp"
#include "Concerto/Core/Any.hpp"

namespace Concerto
{
	template<typename T, typename ... Args>
	Any& Any::operator=(Args&&... args)
	{
		return Make<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	Any& Any::operator=(const T& data)
	{
		return Make<T>(data);
	}

	template<typename T>
	Any& Any::operator=(T&& data)
	{
		return Make<T>(std::move(data));
	}

	template<typename T>
	bool Any::Is() const
	{
		return _id == TypeId<T>();
	}

	template<typename T>
	T Any::As()
	{
		using RawType = std::remove_reference_t<std::remove_pointer_t<T>>;
		if (_id != TypeId<std::remove_const_t<RawType>>())
		{
			CONCERTO_ASSERT_FALSE; // Trying to cast to a wrong type
			throw std::bad_cast();
		}
		auto* any = static_cast<AnyImpl<RawType>*>(*_data);
		RawType* data = any->operator->();
		return static_cast<T>(*data);
	}

	template<typename T, class ... Args>
	Any Any::Make(Args&&... args)
	{
		using RawType = std::remove_reference_t<std::remove_pointer_t<T>>;
		auto data = std::make_unique<void*>(new AnyImpl<T>(std::forward<Args>(args)...));
		return Any(TypeId<RawType>(), std::move(data));
	}

	template<typename T>
	template<typename... Args>
	Any::AnyImpl<T>::AnyImpl(Args&&... args) :
		_data(std::forward<Args>(args)...)
	{
	}

	template<typename T>
	Any::AnyImpl<T>::AnyImpl(T& data) :
		_data(data)
	{
	}

	template<typename T>
	Any::AnyImpl<T>::AnyImpl(T&& data) :
		_data(std::move(data))
	{
	}

	template<typename T>
	Any::AnyImpl<T>& Any::AnyImpl<T>::operator=(const AnyImpl& other)
	{
		_data = other._data;
		return *this;
	}

	template<typename T>
	Any::AnyImpl<T>& Any::AnyImpl<T>::operator=(AnyImpl&& other) noexcept
	{
		_data = std::move(other._data);
		return *this;
	}

	template<typename T>
	T* Any::AnyImpl<T>::operator->()
	{
		return &_data;
	}
}

#endif //CONCERTO_CORE_ANY_INL
