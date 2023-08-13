//
// Created by arthur on 13/08/2023.
//

#include <Concerto/Core/Network/Enet/Enet.hpp>
#include <Concerto/Core/Network/Enet/Server.hpp>
#include <Concerto/Core/Network/Enet/Client.hpp>
#include <gtest/gtest.h>

namespace CONCERTO_ANONYMOUS_NAMESPACE
{
	using namespace Concerto;
	using namespace Concerto::Network;

	TEST(Enet, Basics)
	{
		Enet::Initialize();
		IpAddress ip("127.0.0.1", 2121);
		EnetServer server(ip);

		EnetClient client;

		//client.Connect(ip);
		Enet::Deinitialize();
	}
}// namespace CONCERTO_ANONYMOUS_NAMESPACE