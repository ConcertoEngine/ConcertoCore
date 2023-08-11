//
// Created by arthur on 29/05/2023.
//

#ifndef CONCERTOCORE_INCLUDE_CONCERTO_CORE_BYTESWAP_HPP_
#define CONCERTOCORE_INCLUDE_CONCERTO_CORE_BYTESWAP_HPP_
#include <bit>
#include "Concerto/Core/Types.hpp"

namespace Concerto
{
	/**
	 * @brief Performs a byte swap on the given value
	 * @tparam T The type of the value, must be integral
	 * @param value The value to swap the bytes of
	 * @return The swapped value
	 */
	template<typename T>
	requires std::is_integral_v<T> || std::is_floating_point_v<T>
	[[nodiscard]] inline T ByteSwap(T value)
	{
		if constexpr (std::endian::native == std::endian::little)
			return value;
		Byte* bytes = reinterpret_cast<Byte*>(&value);
		std::size_t i = 0;
		std::size_t j = sizeof(T) - 1;

		while (i < j)
			std::swap(bytes[i++], bytes[j--]);
		return value;
	}
}

#endif //CONCERTOCORE_INCLUDE_CONCERTO_CORE_BYTESWAP_HPP_