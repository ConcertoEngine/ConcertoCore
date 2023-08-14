//
// Created by arthur on 12/08/2023.
//

#include <enet/enet.h>
#include "Concerto/Core/Network/Enet/Host.hpp"
#include "Concerto/Core/Logger.hpp"

namespace Concerto::Network
{
	::ENetHost* ToENetHost(ENetHost::ENetHostHandle handle)
	{
		return static_cast<::ENetHost*>(handle);
	}

	ENetHost::ENetHost(IpAddress* address, std::size_t maxConnections,
		std::size_t maxChannels, UInt32 maxIncomingBandwidth, UInt32 maxOutgoingBandwidth) :
		_enetHost(nullptr),
		_maxConnections(maxConnections),
		_maxChannels(maxChannels),
		_maxIncomingBandwidth(maxIncomingBandwidth),
		_maxOutgoingBandwidth(maxOutgoingBandwidth)
	{
		bool ret = CreateHost(address);
		CONCERTO_ASSERT(ret);
		if (!ret)
			Logger::Error("An error occurred while trying to create an ENetHost");
	}
	
	ENetHost::~ENetHost()
	{
		enet_host_destroy(ToENetHost(_enetHost));
	}

	Int32 ENetHost::PollEvent(ENetEvent* event, UInt32 timeout)
	{
		CONCERTO_ASSERT(_enetHost != nullptr);
		::ENetEvent enetEvent;
		Int32 ret = enet_host_service(ToENetHost(_enetHost), &enetEvent, timeout);
		if (ret <= 0)
		{
			event->eventType = ENetEvent::Type::None;
			event->peer = nullptr;
			return ret;
		}
		
		switch (enetEvent.type)
		{
			case ENET_EVENT_TYPE_NONE:
			{
				event->eventType = ENetEvent::Type::None;
				break;
			}
			case ENET_EVENT_TYPE_CONNECT:
			{
				event->eventType = ENetEvent::Type::Connect;
				event->peer = std::make_unique<ENetPeer>(static_cast<void*>(enetEvent.peer));
				event->channelId = enetEvent.channelID;
				event->data = enetEvent.data;
				event->packet = nullptr;
				break;
			}
			case ENET_EVENT_TYPE_DISCONNECT:
			{
				event->eventType = ENetEvent::Type::Disconnect;
				event->peer = std::make_unique<ENetPeer>(static_cast<void*>(enetEvent.peer));
				event->channelId = enetEvent.channelID;
				event->data = enetEvent.data;
				event->packet = nullptr;
				break;
			}
			case ENET_EVENT_TYPE_RECEIVE:
			{
				event->eventType = ENetEvent::Type::Receive;
				event->peer = std::make_unique<ENetPeer>(static_cast<void*>(enetEvent.peer));
				event->channelId = enetEvent.channelID;
				event->data = enetEvent.data;
				event->packet = std::make_unique<Packet>();
				event->packet->Write(enetEvent.packet->data, enetEvent.packet->dataLength);
				break;
			}
		}
		return ret;
	}

	bool ENetHost::SendPacket(const void* data, std::size_t size, ENetPeer* peer, UInt8 channel, ENetPacket::Flag flags)
	{
		CONCERTO_ASSERT(peer != nullptr);
		return peer->SendPacket(data, size, channel, flags);
	}

	bool ENetHost::SendPacket(const Packet& packet, ENetPeer* peer, UInt8 channel, ENetPacket::Flag flags)
	{
		return SendPacket(packet.GetData(), packet.GetSize(), peer, channel, flags);
	}

	void ENetHost::Flush()
	{
		enet_host_flush(ToENetHost(_enetHost));
	}

	bool ENetHost::CreateHost(IpAddress* address)
	{
		if (address == nullptr)
		{
			_enetHost = enet_host_create(nullptr, _maxConnections, _maxChannels, _maxIncomingBandwidth, _maxOutgoingBandwidth);
			return _enetHost != nullptr;
		}
		
		::ENetAddress enetAddress = {
			.host = address->ToUInt32(),
			.port = address->GetPort()
		};
		_enetHost = enet_host_create(&enetAddress, _maxConnections, _maxChannels, _maxIncomingBandwidth, _maxOutgoingBandwidth);
		return _enetHost != nullptr;
	}
}