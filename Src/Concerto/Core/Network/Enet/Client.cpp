//
// Created by arthur on 12/08/2023.
//

#include "Concerto/Core/Network/Enet/Client.hpp"
#include "Concerto/Core/Logger.hpp"

namespace Concerto::Network
{
	EnetClient::EnetClient(UInt32 maxIncomingBandwidth, UInt32 maxOutgoingBandwidth) : 
		EnetHost(nullptr, 1, 2, maxIncomingBandwidth, maxOutgoingBandwidth)
	{
	}

}// namespace Concerto::Network