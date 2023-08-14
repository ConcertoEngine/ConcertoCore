//
// Created by arthur on 12/08/2023.
//

#ifndef CONCERTOCORE_INCLUDE_CONCERTO_CORE_NETWORK_ENET_HPP_
#define CONCERTOCORE_INCLUDE_CONCERTO_CORE_NETWORK_ENET_HPP_

#include "Concerto/Core/Types.hpp"

namespace Concerto::Network
{
	class CONCERTO_PUBLIC_API Enet
	{
	 public:
		static void Initialize();
		static void Deinitialize();
	};
}// namespace Concerto::Network

#endif//CONCERTOCORE_INCLUDE_CONCERTO_CORE_NETWORK_ENET_HPP_