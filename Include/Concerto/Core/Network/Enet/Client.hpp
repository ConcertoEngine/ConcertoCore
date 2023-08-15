//
// Created by arthur on 12/08/2023.
//

#ifndef CONCERTO_CORE_NETWORK_ENET_CLIENT_HPP_
#define CONCERTO_CORE_NETWORK_ENET_CLIENT_HPP_

#include <functional>
#include <memory>

#include "Concerto/Core/Network/Enet/Host.hpp"

namespace Concerto::Network
{
	class CONCERTO_PUBLIC_API EnetClient : public ENetHost
	{
	 public:
		EnetClient(UInt32 maxIncomingBandwidth = 0, UInt32 maxOutgoingBandwidth = 0);

		bool SendPacket(const ENetPacket& packet, UInt8 channel = 0, ENetPacket::Flag flags = ENetPacket::Flag::Reliable);
		void Connect(IpAddress address);
		void Disconnect();
	private:
		std::unique_ptr<ENetPeer> _peer;
	};
}

#endif//CONCERTO_CORE_NETWORK_ENET_CLIENT_HPP_