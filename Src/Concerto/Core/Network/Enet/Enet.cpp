//
// Created by arthur on 12/08/2023.
//

#include <enet/enet.h>

#include "Concerto/Core/Logger.hpp"
#include "Concerto/Core/Network/Enet/Enet.hpp"

namespace Concerto::Network
{
	void Enet::Initialize()
	{
		if (enet_initialize() == 0)
			return;
		CONCERTO_ASSERT_FALSE;
		Logger::Error("An error occured while initializing Enet");
	}
	
	void Enet::Deinitialize()
	{
		enet_deinitialize();		
	}
}// namespace Concerto::Network