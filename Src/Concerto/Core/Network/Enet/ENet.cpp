//
// Created by arthur on 12/08/2023.
//

#include <enet/enet.h>

#include "Concerto/Core/Logger.hpp"
#include "Concerto/Core/Assert.hpp"
#include "Concerto/Core/Network/ENet/ENet.hpp"

namespace Concerto::Network
{
	void ENet::Initialize()
	{
		if (enet_initialize() == 0)
			return;
		CONCERTO_ASSERT_FALSE("An error occurred while initializing Enet");
	}
	
	void ENet::Deinitialize()
	{
		enet_deinitialize();		
	}
}// namespace Concerto::Network