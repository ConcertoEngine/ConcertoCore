//
// Created by arthur on 12/08/2023.
//

#ifndef CONCERTO_CORE_NETWORK_ENET_EVENT_HPP
#define CONCERTO_CORE_NETWORK_ENET_EVENT_HPP

#include <memory>
#include "Concerto/Core/Network/ENet/Packet.hpp"
#include "Concerto/Core/Network/ENet/Peer.hpp"

namespace cct::Network
{
	struct CONCERTO_CORE_PUBLIC_API ENetEvent
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

#endif//CONCERTO_CORE_NETWORK_ENET_EVENT_HPP