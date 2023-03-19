//
// Created by arthur on 03/09/2022.
//

#ifndef CONCERTO_QUATERNION_H
#define CONCERTO_QUATERNION_H

#include <iostream>
#include <cmath>

#include "Concerto/Core/Math/Algorithm.hpp"
#include "Concerto/Core/Math/Vector.hpp"
#include "Concerto/Core/Math/EulerAngles.hpp"

namespace Concerto::Math
{
	template<typename T>
	class Quaternion
	{
	 public:
		Quaternion() = default;

		/**
		 * @brief Construct a new Quaternion object
		 *
		 * @param x The x axis
		 * @param y The y axis
		 * @param z The z axis
		 * @param w The w scalar
		 */
		constexpr Quaternion(T x, T y, T z, T w) noexcept: _w(w), _x(x), _y(y), _z(z)
		{

		}

		/**
		 * @brief Construct a new Quaternion object from euler angles
		 * @param eulerAngles The euler angles
		 */
		explicit constexpr Quaternion(const EulerAngles<T>& eulerAngles) noexcept: _w(0), _x(0), _y(0), _z(0)
		{
			Set(eulerAngles.Pitch(), eulerAngles.Yaw(), eulerAngles.Roll());
		}

		/**
		 * @brief Normalize the quaternion
		 */
		Quaternion<T> Normalize()
		{
			auto res = *this;
			T length = Length();
			res._w /= length;
			res._x /= length;
			res._y /= length;
			res._z /= length;
			return res;
		}

		/**
		 * @brief Calculates the Magnitude of the quaternion
		 * @return T The Magnitude
		 */
		T Magnitude() const
		{
			return _w * _w + _x * _x + _y * _y
				+ _z * _z;
		}

		/**
		 * @brief Calculates the length of the quaternion
		 * @return T The length
		 */
		T Length() const
		{
			return std::sqrt(Magnitude());
		}

		/**
		 * @brief Convert a quaternion to euler angles
		 * @attention The quaternion must be normalized
		 * @return Vector3<T> The euler angles
		 */
		EulerAngles<T> ToEulerAngles() const
		{
			//According to http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToEuler/
			T test = _x * _y + _z * _w;
			if (test > T(0.499))
				return EulerAngles<T>(T(Math::Pi<T>) / T(2), T(2) * std::atan2(_x, _w), T(0));
			if (test < T(-0.499))
				return EulerAngles<T>(-T(Math::Pi<T>), T(-2) * std::atan2(_x, _w), T(0));
			T sqx = _x * _x;
			T sqy = _y * _y;
			T sqz = _z * _z;
			return EulerAngles<T>(
				ToDegrees(std::atan2(T(2.0) * _x * _w - T(2.0) * _y * _z, T(1.0) - T(2.0) * sqx - T(2.0) * sqz)),
				ToDegrees(std::atan2(T(2.0) * _y * _w - T(2.0) * _x * _z, T(1.0) - T(2.0) * sqy - T(2.0) * sqz)),
				ToDegrees(std::asin(T(2) * test)));
		}

		/**
		 * @brief Assign a new value to this quaternion
		 * @param vector The vector
		 * @return Quaternion& A reference to this quaternion
		 */
		Quaternion<T>& operator=(const Vector3<T>& vector) noexcept
		{
			Set(vector.X(), vector.Y(), vector.Z());
			return *this;
		}

		/**
		 * @brief Assign a new value to this quaternion
		 */
		void Set(T pitch, T yaw, T roll) noexcept
		{
			T cosRoll = std::cos(ToRadians(roll / T(2.0)));
			T cosPitch = std::cos(ToRadians(pitch / T(2.0)));
			T cosYaw = std::cos(ToRadians(yaw / T(2.0)));

			T sinRoll = std::sin(ToRadians(roll / T(2.0)));
			T sinPitch = std::sin(ToRadians(pitch / T(2.0)));
			T sinYaw = std::sin(ToRadians(yaw / T(2.0)));

			_w = cosYaw * cosRoll * cosPitch - sinYaw * sinRoll * sinPitch;
			_x = sinYaw * sinRoll * cosPitch + cosYaw * cosRoll * sinPitch;
			_y = sinYaw * cosRoll * cosPitch + cosYaw * sinRoll * sinPitch;
			_z = cosYaw * sinRoll * cosPitch - sinYaw * cosRoll * sinPitch;
		}

		/**
		 * @brief Get the w scalar
		 * @return The reference to the w scalar
		 */
		T& W() noexcept
		{
			return _w;
		}

		/**
		 * @brief Get the x axis
		 * @return The x axis value
		 */
		constexpr T X() const noexcept
		{
			return _x;
		}

		/**
		 * @brief Get the y axis
		 * @return The y axis value
		 */
		constexpr T Y() const noexcept
		{
			return _y;
		}

		/**
		 * @brief Get the z axis
		 * @return The z axis value
		 */
		constexpr T Z() const noexcept
		{
			return _z;
		}

		/**
		 * @brief Get the w scalar
		 * @return The w scalar value
		 */
		constexpr T W() const noexcept
		{
			return _w;
		}

		/**
		 * @brief Get the inverse of this quaternion
		 * @return Quaternion The inverse of this quaternion
		 */
		Quaternion<T> Inverse() const noexcept
		{
			return Quaternion<T>(-_x, -_y, -_z, -_w);
		}

		/**
		 * @brief Conjugate the vector by multiplying X, Y, Z, part by -1
		 * @return The quaternion's conjugate
		 */
		Quaternion<T> Conjugate() const noexcept
		{
			Quaternion<T> q = *this;
			q._vector = Vector3<T>(-q.X(), -q.Y(), -q.Z());
			return q;
		}

		/**
		 * @brief Add the given quaternion to the current one
		 * @param other The quaternion to add
		 * @return A new quaternion that is the sum of the two
		 */
		Quaternion<T> operator+(const Quaternion<T>& other) const noexcept
		{
			return Quaternion<T>(_x + other._x, _y + other._y, _z + other._z,
				_w + other._w);
		}

		/**
		 * @brief Subtract the given quaternion to the current one
		 * @param other The quaternion to subtract
		 * @return A new quaternion that is the subtraction of the two
		 */
		Quaternion<T> operator-(const Quaternion<T>& other) const noexcept
		{
			return Quaternion<T>(_x - other._x, _y - other._y, _z - other._z,
				_w - other._w);
		}

		/**
		 * @brief Multiply the given quaternion to the current one
		 * @param other The quaternion to multiply
		 * @attention Quaternion multiplication is not commutative
		 * @return A new quaternion that is the multiplication of the two
		 */
		Quaternion<T> operator*(const Quaternion<T>& other) const noexcept
		{
			Quaternion<T> result;
			result._x =
				_w * other._x + other._w * _x + _y * other._z -
					_z * other._y;
			result._y =
				_w * other._y + other._w * _y + _z * other._x -
					_x * other._z;
			result._z =
				_w * other._z + other._w * _z + _x * other._y -
					_y * other._x;
			result._w =
				_w * other._w - _x * other._x - _y * other._y -
					_z * other._z;
			return result;
		}

		/**
		 * @brief Divide the given quaternion to the current one
		 * @param other The quaternion to divide
		 * @return A new quaternion that is the division of the two
		 */
		Quaternion<T> operator/(const Quaternion<T>& other) const noexcept
		{
			return *this * other.Inverse();
		}

		/**
		 * @brief Add the given value to the current quaternion
		 * @param value The value to add
		 * @return A new quaternion that is the sum of the quaternion and the value
		 */
		Quaternion<T> operator+(T value) const noexcept
		{
			return Quaternion<T>(_x + value, _y + value, _z + value,
				_w + value);
		}

		/**
		 * @brief Subtract the given value to the current quaternion
		 * @param value The value to subtract
		 * @return A new quaternion that is the subtraction of the quaternion and the value
		 */

		Quaternion<T> operator-(T value) const noexcept
		{
			return Quaternion<T>(_x - value, _y - value, _z - value,
				_w - value);
		}

		/**
		 * @brief Multiply the given value to the current quaternion
		 * @param value The value to multiply
		 * @return A new quaternion that is the multiplication of the quaternion and the value
		 */

		Quaternion<T> operator*(T value) const noexcept
		{
			return Quaternion<T>(_x * value, _y * value, _z * value,
				_w * value);
		}

		/**
		 * @brief Divide the given value to the current quaternion
		 * @param value The value to divide
		 * @return A new quaternion that is the division of the quaternion and the value
		 */

		Quaternion<T> operator/(T value) const noexcept
		{
			return Quaternion<T>(_x / value, _y / value, _z / value,
				_w / value);
		}

		/**
		 * @brief Add the given quaternion to the current one
		 * @param other The quaternion to add
		 * @return A reference to the current quaternion
		 */
		Quaternion<T>& operator+=(const Quaternion<T>& other) noexcept
		{
			_x += other._x;
			_y += other._y;
			_z += other._z;
			_w += other._w;
			return *this;
		}

		/**
		 * @brief Subtract the given quaternion to the current one
		 * @param other The quaternion to subtract
		 * @return A reference to the current quaternion
		 */
		Quaternion<T>& operator-=(const Quaternion<T>& other) noexcept
		{
			_x -= other._x;
			_y -= other._y;
			_z -= other._z;
			_w -= other._w;
			return *this;
		}

		/**
		 * @brief Multiply the given quaternion to the current one
		 * @param other The quaternion to multiply
		 * @return A reference to the current quaternion
		 */
		Quaternion<T>& operator*=(const Quaternion<T>& other) noexcept
		{
			*this = *this * other;
			return *this;
		}

		/**
		 * @brief Divide the given quaternion to the current one
		 * @param other The quaternion to divide
		 * @return A reference to the current quaternion
		 */
		Quaternion<T>& operator/=(const Quaternion<T>& other) noexcept
		{
			*this = *this / other;
			return *this;
		}

		/**
		 * @brief Apply the quaternion to the given vector3D
		 * @param vector The vector to apply the quaternion to
		 * @return A new vector that is the result of the quaternion application
		 */
		Vector3<T> operator*(const Vector3<T>& vector) const noexcept
		{
			Vector3<T> q(_x, _y, _z);
			Vector3<T> uv = q.Cross(vector);
			Vector3<T> uuv = q.Cross(uv);
			uv *= T(2.0) * _w;
			uuv *= T(2.0);
			return vector + uv + uuv;
		}

		/**
		 * @brief Check if the quaternion is equal to the given one
		 * @param other The quaternion to compare to
		 * @return True if the quaternion is equal to the given one, false otherwise
		 */
		bool operator==(const Quaternion<T>& other) const noexcept
		{
			return _x == other._x && _y == other._y && _z == other._z &&
				_w == other._w;
		}

		/**
		 * @brief Check if the quaternion is not equal to the given one
		 * @param other The quaternion to compare to
		 * @return True if the quaternion is not equal to the given one, false otherwise
		 */
		bool operator!=(const Quaternion<T>& other) const noexcept
		{
			return !(*this == other);
		}

	 private:
		T _w;
		T _x;
		T _y;
		T _z;
	};

	// Aliases
	using Quaternionf = Quaternion<float>;
	using Quaterniond = Quaternion<double>;

	template<typename T>
	std::ostream& operator<<(std::ostream& stream, const Quaternion<T>& quaternion) noexcept
	{
		stream << "Quaternion(X: " << quaternion.X() << ", Y: " << quaternion.Y() << ", Z: " << quaternion.Z()
			   << ", W: " << quaternion.W() << ")";
		return stream;
	}
}

#endif //CONCERTO_QUATERNION_H
