//
// Created by arthur on 12/08/2023.
//

#ifndef CONCERTO_CORE_NETWORK_ENET_HOST_HPP_
#define CONCERTO_CORE_NETWORK_ENET_HOST_HPP_

#include "Concerto/Core/Types.hpp"
#include "Concerto/Core/Network/IpAddress.hpp"
#include "Concerto/Core/Network/Enet/Event.hpp"
#include "Concerto/Core/Network/Enet/Packet.hpp"

namespace Concerto::Network
{
	class CONCERTO_PUBLIC_API ENetHost
	{
	 public:
		using ENetHostHandle = void*;
		ENetHost(IpAddress* address = nullptr, std::size_t maxConnections = 1, std::size_t maxChannels = 2, UInt32 maxIncomingBandwidth = 0, UInt32 maxOutgoingBandwidth = 0);
		virtual ~ENetHost();

		virtual Int32 PollEvent(ENetEvent* event, UInt32 timeout = 0);
		bool SendPacket(const void* data, std::size_t size, ENetPeer* peer, UInt8 channel = 0, ENetPacket::Flag flags = ENetPacket::Flag::Reliable);
		bool SendPacket(const Packet& packet, ENetPeer* peer, UInt8 channel = 0, ENetPacket::Flag flags = ENetPacket::Flag::Reliable);
		void Flush();
	 protected:
		bool CreateHost(IpAddress* address = nullptr);

		ENetHostHandle _enetHost;
		std::size_t _maxConnections;
		std::size_t _maxChannels;
		UInt32 _maxIncomingBandwidth;
		UInt32 _maxOutgoingBandwidth;
	};
}// namespace Concerto::Network

#endif//CONCERTO_CORE_NETWORK_HOST_CLIENT_HPP_