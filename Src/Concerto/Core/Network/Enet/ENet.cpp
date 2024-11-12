//
// Created by arthur on 12/08/2023.
//

#include <enet/enet.h>

#include "Concerto/Core/Logger.hpp"
#include "Concerto/Core/Assert.hpp"
#include "Concerto/Core/Network/ENet/ENet.hpp"

namespace cct::net
{
	void ENet::Initialize()
	{
		const auto res = enet_initialize();
		if (res == 0)
			return;
		CONCERTO_ASSERT_FALSE("An error occurred while initializing Enet: {}", res);
	}
	
	void ENet::Deinitialize()
	{
		enet_deinitialize();		
	}
}// namespace cct::net