//
// Created by arthur on 29/05/2023.
//

#ifndef CONCERTOCORE_INCLUDE_CONCERTO_CORE_SERIALIZER_INL_
#define CONCERTOCORE_INCLUDE_CONCERTO_CORE_SERIALIZER_INL_
#include "Serializer.hpp"
#include "Stream.hpp"
#include "ByteSwap.hpp"

namespace Concerto
{
	template<typename T>
	requires(std::is_same_v<T, bool>)
	void Serialize(Stream& stream, T value)
	{
		stream.Write(&value, sizeof(T));
	}

	template<typename T>
	requires ((std::is_integral_v<T> || std::is_floating_point_v<T>) && !std::is_same_v<T, bool>)
	void Concerto::Serialize(Stream& stream, T value)
	{
		if constexpr (std::endian::native == std::endian::little)
			ByteSwap(value);
		stream.Write(&value, sizeof(T));

	}

	template<typename T>
	requires ((std::is_integral_v<T> || std::is_floating_point_v<T>) && !std::is_same_v<T, bool>)
	void Deserialize(Stream& stream, T& value)
	{
		stream.Read(&value, sizeof(T));
		if constexpr (std::endian::native == std::endian::little)
			ByteSwap(value);
	}

	template<typename T>
	requires(std::is_same_v<T, bool>)
	void Concerto::Deserialize(Stream& stream, T& value)
	{
		stream.Read(&value, sizeof(T));
	}
}

#endif //CONCERTOCORE_INCLUDE_CONCERTO_CORE_SERIALIZER_INL_
