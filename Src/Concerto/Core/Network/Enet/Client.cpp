//
// Created by arthur on 12/08/2023.
//

#include "Concerto/Core/Network/Enet/Client.hpp"
#include "Concerto/Core/Logger.hpp"

#include <enet/enet.h>

namespace Concerto::Network
{
	EnetClient::EnetClient(UInt32 maxIncomingBandwidth, UInt32 maxOutgoingBandwidth) : 
		ENetHost(nullptr, 1, 2, maxIncomingBandwidth, maxOutgoingBandwidth),
		_onConnectCallback(),
		_onDisconnectCallback(),
		_peer(nullptr),
		_isConnected(false)
	{
	}

	Int32 EnetClient::PollEvent(ENetEvent* event, UInt32 timeout)
	{
		Int32 ret = ENetHost::PollEvent(event, timeout);
		if (ret <= 0)
			return ret;
		switch (event->eventType)
		{
		case ENetEvent::Connect: 
		{
			_isConnected = true;
			if (_onConnectCallback)
				_onConnectCallback(*this);
			return 0;
		}
		case ENetEvent::Disconnect:
		{
			_isConnected = false;
			if (_onDisconnectCallback)
				_onDisconnectCallback(*this);
			return 0;
		}
		case ENetEvent::Receive:
		{
			if (!_isConnected)
			{
				event->packet = nullptr;
				return 0;
			}
		}
		default:
			break;
		}
		return ret;
	}

	bool EnetClient::SendPacket(const Packet& packet, UInt8 channel, ENetPacket::Flag flags)
	{
		return ENetHost::SendPacket(packet, _peer.get(), channel, flags);
	}
	
	void EnetClient::Connect(IpAddress address)
	{
		ENetAddress enetAddress = {};
		std::string addressStr = address.ToString();
		enet_address_set_host(&enetAddress, addressStr.c_str());
		enetAddress.port = address.GetPort();
		auto peer = enet_host_connect(static_cast<::ENetHost*>(_enetHost), &enetAddress, _maxChannels, 0);
		if (peer == nullptr)
		{
			CONCERTO_ASSERT_FALSE;
			Logger::Error("Cannot create an Enet connection");
			return;
		}
		_peer = std::make_unique<ENetPeer>(peer);
	}

	bool EnetClient::IsConnected() const
	{
		return _isConnected;
	}

	void EnetClient::SetConnectionCallback(OnConnectCallback&& callback)
	{
		_onConnectCallback = std::move(callback);
	}

	void EnetClient::SetDisconnectCallback(OnDisconnectCallback&& callback)
	{
		_onDisconnectCallback = std::move(callback);
	}

	void EnetClient::Disconnect()
	{
		_isConnected = false;
		CONCERTO_ASSERT(_peer);
		_peer->Disconnect();
	}

}// namespace Concerto::Network