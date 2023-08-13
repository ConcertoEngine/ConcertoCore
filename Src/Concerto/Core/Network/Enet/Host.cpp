//
// Created by arthur on 12/08/2023.
//

#include "Concerto/Core/Network/Enet/Host.hpp"
#include "Concerto/Core/Logger.hpp"

namespace Concerto::Network
{
	EnetHost::EnetHost(IpAddress* address, std::size_t maxConnections,
		std::size_t maxChannels, UInt32 maxIncomingBandwidth, UInt32 maxOutgoingBandwidth) :
		_enetHost(nullptr),
		_maxConnections(maxConnections),
		_maxChannels(maxChannels),
		_maxIncomingBandwidth(maxIncomingBandwidth),
		_maxOutgoingBandwidth(maxOutgoingBandwidth)
	{
		bool res = false;
		if (address == nullptr)
		{
			res = CreateHost();
		}
		else
		{
			ENetAddress enetAddress = {
				.host = address->ToUInt32(),
				.port = address->GetPort()
			};
			res = CreateHost(&enetAddress);
		}
		CONCERTO_ASSERT(res);
		if (!res)
			Logger::Error("An error occurred while trying to create an ENetHost");
	}
	
	EnetHost::~EnetHost()
	{
		enet_host_destroy(_enetHost);
	}

	Int32 EnetHost::PollEvent(ENetEvent* event, UInt32 timeout)
	{
		return enet_host_service(_enetHost, event, timeout);
	}

	bool EnetHost::CreateHost(ENetAddress* address)
	{
		_enetHost = enet_host_create(address, _maxConnections, _maxChannels, _maxIncomingBandwidth, _maxOutgoingBandwidth);
		return _enetHost != nullptr;
	}
}