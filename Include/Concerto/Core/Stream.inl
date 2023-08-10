//
// Created by arthur on 29/05/2023.
//

#ifndef CONCERTOCORE_INCLUDE_CONCERTO_CORE_STREAM_INL_
#define CONCERTOCORE_INCLUDE_CONCERTO_CORE_STREAM_INL_

#include "Stream.hpp"
#include "Serializer.hpp"

namespace Concerto
{
	template<typename T>
	Stream& Stream::operator<<(const T& data)
	{
		Concerto::Serialize(*this, data);
		return *this;
	}

	template<typename T>
	Stream& Stream::operator>>(T& data)
	{
		Concerto::Deserialize(*this, data);
		return *this;
	}
}

#endif //CONCERTOCORE_INCLUDE_CONCERTO_CORE_STREAM_INL_
