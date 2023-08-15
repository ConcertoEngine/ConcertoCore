//
// Created by arthur on 12/08/2023.
//

#ifndef CONCERTO_CORE_NETWORK_ENET_EVENT_HPP_
#define CONCERTO_CORE_NETWORK_ENET_EVENT_HPP_

#include <memory>
#include "Concerto/Core/Network/ENet/Packet.hpp"
#include "Concerto/Core/Network/Enet/Peer.hpp"

namespace Concerto::Network
{
	struct CONCERTO_PUBLIC_API ENetEvent
	{
		enum Type 
		{
			None,
			Connect,
			Disconnect,
			Receive
		};

		Type eventType;
		std::unique_ptr<ENetPeer> peer;
		UInt8 channelId;
		UInt32 data;
		std::unique_ptr<ENetPacket> packet;
	};
}

#endif//CONCERTO_CORE_NETWORK_ENET_EVENT_HPP_