//
// Created by arthur on 12/08/2023.
//

#include "Concerto/Core/Network/Enet/Server.hpp"
#include <enet/enet.h>

namespace Concerto::Network
{
	EnetServer::EnetServer(IpAddress address, std::size_t maxClients, UInt32 maxIncomingBandwidth, UInt32 maxOutgoingBandwidth) :
		ENetHost(&address, maxClients, 2, maxIncomingBandwidth, maxOutgoingBandwidth),
		_address(address)
	{
	}
}// namespace Concerto::Network