//
// Created by arthur on 16/11/2023.
//

#ifndef CONCERTO_CORE_ANY_INL
#define CONCERTO_CORE_ANY_INL

#include <Concerto/Core/TypeInfo.hpp>

#include "Concerto/Core/Assert.hpp"
#include "Concerto/Core/Any.hpp"

namespace cct
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

	inline void Any::Reset()
	{
		_data = nullptr;
		_id = 0;
	}

	inline bool Any::HasValue() const
	{
		return _data != nullptr && _id != 0;
	}

	template<typename T>
	T Any::As()
	{
		using RawType = std::remove_reference_t<T>;
		using RealType = std::conditional_t<std::is_pointer_v<T>,
				std::add_pointer_t<std::remove_const_t<std::remove_pointer_t<RawType>>>,
				std::remove_const_t<std::remove_pointer_t<RawType>>>;

		constexpr auto type = TypeName<RealType>();
		if (_id != TypeId<RealType>())
		{
			CCT_ASSERT_FALSE("Trying to cast to a wrong type");
			throw std::bad_cast();
		}
		auto* any = static_cast<AnyImpl<RawType>*>(*_data);
		RawType* data = any->operator->();
		return static_cast<T>(*data);
	}

	template<typename T, class ... Args>
	requires(!std::is_reference_v<T> && !std::is_const_v<T>)
	Any Any::Make(Args&&... args)
	{
		auto data = std::make_unique<void*>(new AnyImpl<T>(std::forward<Args>(args)...));
		return Any(TypeId<T>(), std::move(data));
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
