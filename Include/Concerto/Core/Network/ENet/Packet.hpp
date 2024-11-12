//
// Created by arthur on 14/08/2023.
//

#ifndef CONCERTO_CORE_NETWORK_ENET_PACKET_HPP
#define CONCERTO_CORE_NETWORK_ENET_PACKET_HPP

#include "Concerto/Core/Types.hpp"
#include "Concerto/Core/Stream.hpp"

namespace cct::Network
{
	class CONCERTO_CORE_PUBLIC_API ENetPacket : public Stream
	{
	public:
		enum Flag
		{
			Reliable,
			Unsequenced,
			NoAllocate,
			UnreliableFragment,
			Sent
		};

	   ENetPacket();
	   ENetPacket(const void* data, std::size_t size);

	   [[nodiscard]] const Byte* GetData() const;
	   [[nodiscard]] std::size_t Capacity() const;

	   bool operator==(const ENetPacket&) const;
	   bool operator!=(const ENetPacket&) const;
	};
}// namespace cct::Network::ENetPacket

#endif//CONCERTO_CORE_NETWORK_ENET_PACKET_HPP