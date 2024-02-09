//
// Created by arthur on 22/05/22.
//

#include <algorithm>

#include "Concerto/Core/Math/Vector.hpp"

namespace Concerto
{
	template<typename T, std::size_t Size>
	constexpr Vector<T, Size> Vector<T, Size>::operator+(const Vector& vector) const noexcept
	{
		auto res = *this;
		res += vector;
		return res;
	}

	template<typename T, std::size_t Size>
	constexpr Vector<T, Size> Vector<T, Size>::operator+(T val) const noexcept
	{
		auto res = *this;
		res += val;
		return res;
	}

	template<typename T, std::size_t Size>
	constexpr Vector<T, Size> Vector<T, Size>::operator-(const Vector& vector) const noexcept
	{
		auto res = *this;
		res -= vector;
		return res;
	}

	template<typename T, std::size_t Size>
	constexpr Vector<T, Size> Vector<T, Size>::operator-(T val) const noexcept
	{
		auto res = *this;
		res -= val;
		return res;
	}

	template<typename T, std::size_t Size>
	constexpr Vector<T, Size> Vector<T, Size>::operator*(const Vector& vector) const noexcept
	{
		auto res = *this;
		res *= vector;
		return res;
	}

	template<typename T, std::size_t Size>
	constexpr Vector<T, Size> Vector<T, Size>::operator*(T val) const noexcept
	{
		auto res = *this;
		res *= val;
		return res;
	}

	template<typename T, std::size_t Size>
	constexpr Vector<T, Size> Vector<T, Size>::operator/(const Vector& vector) const noexcept
	{
		auto res = *this;
		res /= vector;
		return res;
	}

	template<typename T, std::size_t Size>
	constexpr Vector<T, Size> Vector<T, Size>::operator/(T val) const noexcept
	{
		auto res = *this;
		res /= val;
		return res;
	}

	template<typename T, std::size_t Size>
	constexpr Vector<T, Size>& Vector<T, Size>::operator+=(const Vector& vector) noexcept
	{
		for (int i = 0; i < std::min(Size, vector.GetSize()); ++i)
			_data[i] += vector[i];
		return *this;
	}

	template<typename T, std::size_t Size>
	constexpr Vector<T, Size>& Vector<T, Size>::operator+=(T val) noexcept
	{
		for (auto& x: _data)
			x += val;
		return *this;
	}

	template<typename T, std::size_t Size>
	constexpr Vector<T, Size>& Vector<T, Size>::operator-=(const Vector& vector) noexcept
	{
		for (int i = 0; i < std::min(Size, vector.GetSize()); ++i)
			_data[i] -= vector[i];
		return *this;
	}

	template<typename T, std::size_t Size>
	constexpr Vector<T, Size>& Vector<T, Size>::operator-=(T val) noexcept
	{
		for (auto& x: _data)
			x -= val;
		return *this;
	}

	template<typename T, std::size_t Size>
	constexpr Vector<T, Size>& Vector<T, Size>::operator*=(const Vector& vector) noexcept
	{
		for (std::size_t i = 0; i < std::min(Size, vector.GetSize()); ++i)
			_data[i] *= vector[i];
		return *this;
	}

	template<typename T, std::size_t Size>
	constexpr Vector<T, Size>& Vector<T, Size>::operator*=(T val) noexcept
	{
		for (auto& x: _data)
			x *= val;
		return *this;
	}

	template<typename T, std::size_t Size>
	constexpr Vector<T, Size>& Vector<T, Size>::operator/=(const Vector& vector) noexcept
	{
		for (int i = 0; i < std::min(Size, vector.GetSize()); ++i)
			_data[i] /= vector[i];
		return *this;
	}


	template<typename T, std::size_t Size>
	constexpr Vector<T, Size>& Vector<T, Size>::operator/=(T val) noexcept
	{
		for (auto& x: _data)
			x /= val;
		return *this;
	}

	template<typename T, std::size_t Size>
	constexpr bool Vector<T, Size>::operator==(const Vector& other) const noexcept
	{
		return _data == other.GetData();
	}

	template<typename T>
	constexpr Vector3<T> operator*(T scale, const Vector3<T>& vec)
	{
		return Vector3<T>(scale * vec.X(), scale * vec.Y(), scale * vec.Z());
	}

	template<typename T>
	constexpr Vector3<T> operator/(T scale, const Vector3<T>& vec)
	{
		return Vector3<T>(scale / vec.X(), scale / vec.Y(), scale / vec.Z());
	}

	template<typename T, std::size_t Size>
	inline void Vector<T, Size>::Serialize(Stream& stream) const
	{
		for (const T& x : _data)
			Concerto::Serialize(stream, x);
	}

	template<typename T, std::size_t Size>
	inline void Vector<T, Size>::Deserialize(Stream& stream)
	{
		for (T& x : _data)
			Concerto::Deserialize(stream, x);
	}

	template<typename T, std::size_t Size>
	const std::array<T, Size>& Vector<T, Size>::GetData() const
	{
		return _data;
	}
}