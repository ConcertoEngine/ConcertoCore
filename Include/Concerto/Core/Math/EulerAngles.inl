//
// Created by arthur on 14/03/2023.
//

#include "EulerAngles.hpp"
#include "Quaternion.hpp"
#include "Serializer.hpp"

namespace Concerto::Math
{
	template<typename T>
	EulerAngles<T>::EulerAngles(T pitch, T yaw, T roll) : _pitch(pitch), _yaw(yaw), _roll(roll)
	{

	}

	template<typename T>
	T& EulerAngles<T>::Pitch()
	{
		return _pitch;
	}

	template<typename T>
	T& EulerAngles<T>::Yaw()
	{
		return _yaw;
	}

	template<typename T>
	T& EulerAngles<T>::Roll()
	{
		return _roll;
	}

	template<typename T>
	T EulerAngles<T>::Pitch() const
	{
		return _pitch;
	}

	template<typename T>
	T EulerAngles<T>::Yaw() const
	{
		return _yaw;
	}

	template<typename T>
	T EulerAngles<T>::Roll() const
	{
		return _roll;
	}

	template<typename T>
	Quaternion<T> EulerAngles<T>::ToQuaternion() const
	{
		return Quaternion<T>(*this);
	}

	template<typename T>
	EulerAngles<T> EulerAngles<T>::operator+(const EulerAngles<T>& other) const
	{
		return EulerAngles<T>(
			_pitch + other._pitch,
			_yaw + other._yaw,
			_roll + other._roll
		);
	}

	template<typename T>
	EulerAngles<T> EulerAngles<T>::operator-(const EulerAngles<T>& other) const
	{
		return EulerAngles<T>(
			_pitch - other._pitch,
			_yaw - other._yaw,
			_roll - other._roll
		);
	}

	template<typename T>
	EulerAngles<T> EulerAngles<T>::operator*(const EulerAngles<T>& other) const
	{
		return EulerAngles<T>(
			_pitch * other._pitch,
			_yaw * other._yaw,
			_roll * other._roll
		);
	}

	template<typename T>
	EulerAngles<T> EulerAngles<T>::operator/(const EulerAngles<T>& other) const
	{
		return EulerAngles<T>(
			_pitch / other._pitch,
			_yaw / other._yaw,
			_roll / other._roll
		);
	}

	template<typename T>
	EulerAngles<T>& EulerAngles<T>::operator+=(const EulerAngles<T>& other)
	{
		_pitch += other._pitch;
		_yaw += other._yaw;
		_roll += other._roll;
		return *this;
	}

	template<typename T>
	EulerAngles<T>& EulerAngles<T>::operator-=(const EulerAngles<T>& other)
	{
		_pitch -= other._pitch;
		_yaw -= other._yaw;
		_roll -= other._roll;
		return *this;
	}

	template<typename T>
	EulerAngles<T>& EulerAngles<T>::operator*=(const EulerAngles<T>& other)
	{
		_pitch *= other._pitch;
		_yaw *= other._yaw;
		_roll *= other._roll;
		return *this;
	}

	template<typename T>
	EulerAngles<T>& EulerAngles<T>::operator/=(const EulerAngles<T>& other)
	{
		_pitch /= other._pitch;
		_yaw /= other._yaw;
		_roll /= other._roll;
		return *this;
	}

	template<typename T>
	EulerAngles<T> EulerAngles<T>::operator+(const Vector<T, 3>& other) const
	{
		EulerAngles<T> result(*this);
		result += other;
		return result;
	}

	template<typename T>
	EulerAngles<T> EulerAngles<T>::operator-(const Vector<T, 3>& other) const
	{
		EulerAngles<T> result(*this);
		result -= other;
		return result;
	}

	template<typename T>
	EulerAngles<T> EulerAngles<T>::operator*(const Vector<T, 3>& other) const
	{
		EulerAngles<T> result(*this);
		result *= other;
		return result;
	}

	template<typename T>
	EulerAngles<T> EulerAngles<T>::operator/(const Vector<T, 3>& other) const
	{
		EulerAngles<T> result(*this);
		result /= other;
		return result;
	}

	template<typename T>
	EulerAngles<T>& EulerAngles<T>::operator+=(const Vector<T, 3>& other)
	{
		_pitch += other.X();
		_yaw += other.Y();
		_roll += other.Z();
		return *this;
	}

	template<typename T>
	EulerAngles<T>& EulerAngles<T>::operator-=(const Vector<T, 3>& other)
	{
		_pitch -= other.X();
		_yaw -= other.Y();
		_roll -= other.Z();
		return *this;
	}

	template<typename T>
	EulerAngles<T>& EulerAngles<T>::operator*=(const Vector<T, 3>& other)
	{
		_pitch *= other.X();
		_yaw *= other.Y();
		_roll *= other.Z();
		return *this;
	}

	template<typename T>
	EulerAngles<T>& EulerAngles<T>::operator/=(const Vector<T, 3>& other)
	{
		_pitch /= other.X();
		_yaw /= other.Y();
		_roll /= other.Z();
		return *this;
	}

	template<typename T>
	EulerAngles<T> EulerAngles<T>::Zero()
	{
		return EulerAngles<T>(0, 0, 0);
	}

	template<typename T>
	void EulerAngles<T>::Serialize(Stream& stream) const
	{
		Concerto::Serialize(stream, _pitch);
		Concerto::Serialize(stream, _yaw);
		Concerto::Serialize(stream, _roll);
	}

	template<typename T>
	void EulerAngles<T>::Deserialize(Stream& stream)
	{
		Concerto::Deserialize(stream, _pitch);
		Concerto::Deserialize(stream, _yaw);
		Concerto::Deserialize(stream, _roll);
	}
}
