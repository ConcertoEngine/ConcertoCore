//
// Created by arthur on 12/08/2023.
//

#ifndef CONCERTO_CORE_NETWORK_ENET_EVENT_HPP_
#define CONCERTO_CORE_NETWORK_ENET_EVENT_HPP_

#include "enet/enet.h"
#include "Concerto/Core/Types.hpp"

namespace Concerto::Network
{
	struct CONCERTO_PUBLIC_API EnetEvent
	{
		enum Type 
		{
			None = ENET_EVENT_TYPE_NONE,
			Connect = ENET_EVENT_TYPE_CONNECT,
			Disconnect = ENET_EVENT_TYPE_DISCONNECT,
			Receive = ENET_EVENT_TYPE_RECEIVE
		};
		
		Type eventType;
		ENetPeer* peer;
		UInt8 channelId;
	};
}

#endif//CONCERTO_CORE_NETWORK_ENET_EVENT_HPP_