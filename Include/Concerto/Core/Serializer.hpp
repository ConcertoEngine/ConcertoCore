//
// Created by arthur on 29/05/2023.
//

#ifndef CONCERTOCORE_INCLUDE_CONCERTO_SERIALIZER_HPP_
#define CONCERTOCORE_INCLUDE_CONCERTO_SERIALIZER_HPP_

#include <type_traits>

namespace Concerto
{
	class Stream;

	/**
	 * @brief Serialize a boolean value into a stream
	 * @param stream The stream to write to
	 * @param value The value to serialize
	 * @param endian The endianness to use
	 */
	template<typename T>
	requires(std::is_same_v<T, bool>)
	inline void CONCERTO_PUBLIC_API Serialize(Stream& stream, T value);

	/**
	 * @brief Serialize an arithmetic value into a stream
	 * @tparam T The type of the value to serialize
	 * @param stream The stream to write to
	 * @param value The value to serialize
	 * @param endian The endianness to use
	 */
	template<typename T>
		requires((std::is_integral_v<T> || std::is_floating_point_v<T>) && !std::is_same_v<T, bool>)
	inline void CONCERTO_PUBLIC_API Serialize(Stream& stream, T value);

	/**
	 * @brief Deserialize a boolean value from a stream
	 * @param stream The stream to read from
	 * @param value The value to deserialize
	 * @param endian The endianness to use
	 */
	template<typename T>
		requires(std::is_same_v<T, bool>)
	inline void CONCERTO_PUBLIC_API Deserialize(Stream& stream, T& value);

	/**
	 * @brief Deserialize an arithmetic value from a stream
	 * @tparam T The type of the value to deserialize
	 * @param stream The stream to read from
	 * @param value The value to deserialize
	 * @param endian The endianness to use
	 */
	template<typename T>
		requires((std::is_integral_v<T> || std::is_floating_point_v<T>) && !std::is_same_v<T, bool>)
	inline void CONCERTO_PUBLIC_API Deserialize(Stream& stream, T& value);
}
#include "Serializer.inl"
#endif //CONCERTOCORE_INCLUDE_CONCERTO_SERIALIZER_HPP_