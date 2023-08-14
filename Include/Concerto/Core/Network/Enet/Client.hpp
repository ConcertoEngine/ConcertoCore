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
		using OnConnectCallback = std::function<void(EnetClient&)>;
		using OnDisconnectCallback = std::function<void(EnetClient&)>;

		EnetClient(UInt32 maxIncomingBandwidth = 0, UInt32 maxOutgoingBandwidth = 0);

		virtual Int32 PollEvent(ENetEvent* event, UInt32 timeout = 0) override;
		bool SendPacket(const Packet& packet, UInt8 channel = 0, ENetPacket::Flag flags = ENetPacket::Flag::Reliable);
		void Connect(IpAddress address);
		void Disconnect();

		bool IsConnected() const;
		
		void SetConnectionCallback(OnConnectCallback&& callback);
		void SetDisconnectCallback(OnDisconnectCallback&& callback);
	private:
		OnConnectCallback _onConnectCallback;
		OnDisconnectCallback _onDisconnectCallback;
		std::unique_ptr<ENetPeer> _peer;
		bool _isConnected;
	};
}

#endif//CONCERTO_CORE_NETWORK_ENET_CLIENT_HPP_