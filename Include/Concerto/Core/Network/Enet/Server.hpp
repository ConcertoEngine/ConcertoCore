//
// Created by arthur on 12/08/2023.
//

#ifndef CONCERTO_CORE_NETWORK_ENET_SERVER_HPP_
#define CONCERTO_CORE_NETWORK_ENET_SERVER_HPP_

#include <functional>

#include "Concerto/Core/Network/IpAddress.hpp"
#include "Concerto/Core/Network/Enet/Host.hpp"

namespace Concerto::Network
{
	class CONCERTO_PUBLIC_API EnetServer : public ENetHost
	{
	 public:
		using OnConnectionCallback = std::function<void(EnetServer&, ENetPeer&)>;
		using OnDisconnectionCallback = std::function<void(EnetServer&, ENetPeer&)>;
		EnetServer(IpAddress address, std::size_t maxClients = 32, UInt32 maxIncomingBandwidth = 0, UInt32 maxOutgoingBandwidth = 0);
		
		Int32 PollEvent(ENetEvent* event, UInt32 timeout = 0) override;
		
		void SetConnectionCallback(OnConnectionCallback&& callback);
		void SetDisconnectionCallback(OnDisconnectionCallback&& callback);
	private:
		OnConnectionCallback _onConnectionCallback;
	   OnDisconnectionCallback _onDisconnectionCallback;
		IpAddress _address;
	};
}// namespace Concerto::Network

#endif//CONCERTO_CORE_NETWORK_ENET_SERVER_HPP_