//
// Created by arthur on 12/08/2023.
//

#ifndef CONCERTO_CORE_NETWORK_ENET_SERVER_HPP
#define CONCERTO_CORE_NETWORK_ENET_SERVER_HPP

#include <functional>

#include "Concerto/Core/Network/IpAddress.hpp"
#include "Concerto/Core/Network/ENet/Host.hpp"

namespace cct::Network
{
	class CONCERTO_CORE_PUBLIC_API EnetServer : public ENetHost
	{
	 public:
		EnetServer() = delete;
		explicit EnetServer(IpAddress address, std::size_t maxClients = 32, UInt32 maxIncomingBandwidth = 0, UInt32 maxOutgoingBandwidth = 0);
	private:
		IpAddress _address;
	};
}// namespace cct::Network

#endif//CONCERTO_CORE_NETWORK_ENET_SERVER_HPP