//
// Created by arthur on 29/05/2023.
//

#ifndef CONCERTOCORE_INCLUDE_CONCERTO_CORE_ISERIALIZABLE_HPP_
#define CONCERTOCORE_INCLUDE_CONCERTO_CORE_ISERIALIZABLE_HPP_

namespace Concerto
{
	class Stream;

	class ISerializable
	{
	 public:
		virtual ~ISerializable() = default;

		virtual void Serialize(Stream& stream) const = 0;
		virtual void Deserialize(Stream& stream) = 0;
	};
}

#endif //CONCERTOCORE_INCLUDE_CONCERTO_CORE_ISERIALIZABLE_HPP_
