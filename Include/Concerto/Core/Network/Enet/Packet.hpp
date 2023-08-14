//
// Created by arthur on 14/08/2023.
//

#ifndef CONCERTO_CORE_NETWORK_ENET_PACKET_HPP_
#define CONCERTO_CORE_NETWORK_ENET_PACKET_HPP_

#include "Concerto/Core/Types.hpp"

namespace Concerto::Network::ENetPacket
{
	enum Flag
	{
		Reliable,
		Unsequenced,
		NoAllocate,
		UnreliableFragment,
		Sent
	};
}// namespace Concerto::Network::ENetPacket

#endif//CONCERTO_CORE_NETWORK_ENET_PACKET_HPP_