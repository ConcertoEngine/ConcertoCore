//
// Created by arthur on 12/08/2023.
//

#ifndef CONCERTO_CORE_NETWORK_ENET_PEER_HPP_
#define CONCERTO_CORE_NETWORK_ENET_PEER_HPP_

#include <cstddef>
#include "Concerto/Core/Types.hpp"
#include "Concerto/Core/Network/Enet/Packet.hpp"

namespace Concerto::Network
{
	class Packet;
	class ENetHost;

	class ENetPeer
	{
	public:
		using ENetPeerHandle = void*;
		ENetPeer(ENetPeerHandle peer);
		void Disconnect(UInt32 data = 0);
		void DisconnectNow(UInt32 data = 0);
		void DisconnectLater(UInt32 data = 0);
		void SetTimeout(UInt32 timeoutLimit, UInt32 timeoutMinimum, UInt32 timeoutMaximum);
		void Ping();
		void SetPingInterval(UInt32 pingInterval);
		bool SendPacket(const Packet& packet, UInt8 channel = 0, ENetPacket::Flag flags = ENetPacket::Flag::Reliable);
		bool SendPacket(const void* data, std::size_t size, UInt8 channel = 0, ENetPacket::Flag flags = ENetPacket::Flag::Reliable);
	private:
		ENetPeerHandle _peer;
	};
}

#endif//CONCERTO_CORE_NETWORK_ENET_PEER_HPP_
