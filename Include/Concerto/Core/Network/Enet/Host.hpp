//
// Created by arthur on 12/08/2023.
//

#ifndef CONCERTO_CORE_NETWORK_ENET_HOST_HPP_
#define CONCERTO_CORE_NETWORK_ENET_HOST_HPP_

#include <enet/enet.h>

#include "Concerto/Core/Types.hpp"
#include "Concerto/Core/Network/IpAddress.hpp"

namespace Concerto::Network
{
	class CONCERTO_PUBLIC_API EnetHost
	{
	 public:
		EnetHost(IpAddress* address = nullptr, std::size_t maxConnections = 1, std::size_t maxChannels = 2, UInt32 maxIncomingBandwidth = 0, UInt32 maxOutgoingBandwidth = 0);
		~EnetHost();

		Int32 PollEvent(ENetEvent* event, UInt32 timeout = 0);
	 private:
		bool CreateHost(ENetAddress* address = nullptr);
	 
		ENetHost* _enetHost;
		std::size_t _maxConnections;
		std::size_t _maxChannels;
		UInt32 _maxIncomingBandwidth;
		UInt32 _maxOutgoingBandwidth;
	};
}// namespace Concerto::Network

#endif//CONCERTO_CORE_NETWORK_HOST_CLIENT_HPP_