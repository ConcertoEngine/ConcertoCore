//
// Created by arthur on 14/03/2023.
//

#ifndef CONCERTOCORE_MATH_EULERANGLES_HPP_
#define CONCERTOCORE_MATH_EULERANGLES_HPP_

#include "Concerto/Core/Math/Vector.hpp"
#include "Concerto/Core/Stream.hpp"

namespace Concerto::Math
{
	template<typename T>
	class Quaternion;
	/**
	 * @brief A class representing Euler angles
	 * @tparam T The type of the angles
	 */
	template<typename T>
	class EulerAngles
	{
	 public:
		EulerAngles() = default;
		/**
		 * @brief Construct a new EulerAngles object
		 * @param pitch The X axis
		 * @param yaw The Y axis
		 * @param roll The Z axis
		 */
		EulerAngles(T pitch, T yaw, T roll);

		/**
		 * @brief Get the pitch
		 * @return T A reference to pitch
		 */
		[[nodiscard]] T& Pitch();
		/**
		 * @brief Get the yaw
		 * @return T A reference to yaw
		 */
		[[nodiscard]] T& Yaw();

		/**
		 * @brief Get the roll
		 * @return T A reference to roll
		 */
		[[nodiscard]] T& Roll();

		/**
		 * @brief Get the pitch
		 * @return T The pitch
		 */
		[[nodiscard]] T Pitch() const;
		/**
		 * @brief Get the yaw
		 * @return T The yaw
		 */
		[[nodiscard]] T Yaw() const;

		/**
		 * @brief Get the roll
		 * @return T The roll
		 */
		[[nodiscard]] T Roll() const;

		/**
		 * @brief Convert the Euler angles to a quaternion
		 * @return Quaternion<T> The quaternion
		 */
		[[nodiscard]] Quaternion<T> ToQuaternion() const;

		EulerAngles<T> operator+(const EulerAngles<T>& other) const;
		EulerAngles<T> operator-(const EulerAngles<T>& other) const;
		EulerAngles<T> operator*(const EulerAngles<T>& other) const;
		EulerAngles<T> operator/(const EulerAngles<T>& other) const;
		EulerAngles<T>& operator+=(const EulerAngles<T>& other);
		EulerAngles<T>& operator-=(const EulerAngles<T>& other);
		EulerAngles<T>& operator*=(const EulerAngles<T>& other);
		EulerAngles<T>& operator/=(const EulerAngles<T>& other);

		EulerAngles<T> operator+(const Vector<T, 3>& other) const;
		EulerAngles<T> operator-(const Vector<T, 3>& other) const;
		EulerAngles<T> operator*(const Vector<T, 3>& other) const;
		EulerAngles<T> operator/(const Vector<T, 3>& other) const;
		EulerAngles<T>& operator+=(const Vector<T, 3>& other);
		EulerAngles<T>& operator-=(const Vector<T, 3>& other);
		EulerAngles<T>& operator*=(const Vector<T, 3>& other);
		EulerAngles<T>& operator/=(const Vector<T, 3>& other);

		/**
		 * @brief Get the zero Euler angles
		 * @return EulerAngles<T> The zero Euler angles
		 */
		[[nodiscard]] static EulerAngles<T> Zero();

		void Serialize(Stream& stream) const;
		void Deserialize(Stream& stream);

	 private:
		T _pitch;
		T _yaw;
		T _roll;
	};

	//Alias
	using EulerAnglesf = EulerAngles<float>;
	using EulerAnglesd = EulerAngles<double>;
}
#include "EulerAngles.inl"

#endif //CONCERTOCORE_MATH_EULERANGLES_HPP_
