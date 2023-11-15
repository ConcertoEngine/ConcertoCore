//
// Created by arthur on 29/05/2023.
//

#ifndef CONCERTOCORE_SERIALIZER_INL_
#define CONCERTOCORE_SERIALIZER_INL_
#include "Concerto/Core/Serializer.hpp"
#include "Concerto/Core/Stream.hpp"
#include "Concerto/Core/ByteSwap.hpp"

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
		value = ByteSwap(value);
		stream.Write(&value, sizeof(T));
	}

	template<typename T>
	requires ((std::is_integral_v<T> || std::is_floating_point_v<T>) && !std::is_same_v<T, bool>)
	void Deserialize(Stream& stream, T& value)
	{
		stream.Read(&value, sizeof(T));
		value = ByteSwap(value);
	}

	template<typename T>
	requires(std::is_same_v<T, bool>)
	void Concerto::Deserialize(Stream& stream, T& value)
	{
		stream.Read(&value, sizeof(T));
	}
}

#endif //CONCERTOCORE_SERIALIZER_INL_
