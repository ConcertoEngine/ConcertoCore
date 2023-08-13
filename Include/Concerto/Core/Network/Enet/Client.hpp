//
// Created by arthur on 12/08/2023.
//

#ifndef CONCERTO_CORE_NETWORK_ENET_CLIENT_HPP_
#define CONCERTO_CORE_NETWORK_ENET_CLIENT_HPP_

#include "Concerto/Core/Types.hpp"
#include "Concerto/Core/Network/Enet/Host.hpp"

namespace Concerto::Network
{
	class CONCERTO_PUBLIC_API EnetClient : public EnetHost
	{
	 public:
		EnetClient(UInt32 maxIncomingBandwidth = 0, UInt32 maxOutgoingBandwidth = 0);
	};
}

#endif//CONCERTO_CORE_NETWORK_ENET_CLIENT_HPP_