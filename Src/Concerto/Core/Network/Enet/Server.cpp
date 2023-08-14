//
// Created by arthur on 12/08/2023.
//

#include "Concerto/Core/Network/Enet/Server.hpp"
#include <enet/enet.h>

namespace Concerto::Network
{
	EnetServer::EnetServer(IpAddress address, std::size_t maxClients, UInt32 maxIncomingBandwidth, UInt32 maxOutgoingBandwidth) :
		ENetHost(&address, maxClients, 2, maxIncomingBandwidth, maxOutgoingBandwidth),
		_onConnectionCallback(),
		_onDisconnectionCallback(),
		_address(address)
	{
	}

	Int32 EnetServer::PollEvent(ENetEvent* event, UInt32 timeout)
	{
		Int32 ret = ENetHost::PollEvent(event, timeout);
		if (ret <= 0)
			return ret;
		switch (event->eventType)
		{
			case ENetEvent::Connect:
			{
				if (_onConnectionCallback)
					_onConnectionCallback(*this, *event->peer);
				break;
			}
			case ENetEvent::Disconnect:
			{
				if (_onDisconnectionCallback)
					_onDisconnectionCallback(*this, *event->peer);
				break;
			}
		}
		return ret;
	}
	
	void EnetServer::SetConnectionCallback(OnConnectionCallback&& callback)
	{
		_onConnectionCallback = std::move(callback);
	}
	
	void EnetServer::SetDisconnectionCallback(OnDisconnectionCallback&& callback)
	{
		_onDisconnectionCallback = std::move(callback);
	}
}// namespace Concerto::Network