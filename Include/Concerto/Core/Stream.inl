//
// Created by arthur on 29/05/2023.
//

#ifndef CONCERTO_CORE_STREAM_INL_
#define CONCERTO_CORE_STREAM_INL_

#include "Concerto/Core/Stream.hpp"
#include "Concerto/Core/Serializer.hpp"

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

#endif //CONCERTO_CORE_STREAM_INL_
