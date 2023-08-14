//
// Created by arthur on 13/08/2023.
//

#include <thread>
#include <chrono>
#include <span>

#include <gtest/gtest.h>
#include <Concerto/Core/Logger.hpp>
#include <Concerto/Core/Network/Enet/Enet.hpp>
#include <Concerto/Core/Network/Enet/Server.hpp>
#include <Concerto/Core/Network/Enet/Client.hpp>

namespace CONCERTO_ANONYMOUS_NAMESPACE
{
	using namespace Concerto;
	using namespace Concerto::Network;

	TEST(Enet, BasicConnection)
	{
		Enet::Initialize();
		bool running = true;
		std::thread serverThread([&]() {
			IpAddress listeningIp("0.0.0.0", 2121);
			EnetServer server(listeningIp);
			Int32 count = -1;
			server.SetConnectionCallback([&](EnetServer&, ENetPeer&) {
				count += 2;
			});
			server.SetDisconnectionCallback([&](EnetServer&, ENetPeer&) {
				count--;
			});
			ENetEvent event;
			while (running)
			{
				Int32 ret = server.PollEvent(&event, 100);
			}
			ASSERT_EQ(count, 0);
		});
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		EnetClient client;
		IpAddress ip("127.0.0.1", 2121);
		Int32 callbackCount = 0;
		client.Connect(ip);
		
		client.SetConnectionCallback([&](EnetClient& client) {
			ASSERT_TRUE(client.IsConnected());
			callbackCount++;
		});
		client.SetDisconnectCallback([&](EnetClient& client) {
			ASSERT_FALSE(client.IsConnected());
			callbackCount--;
		});

		ENetEvent event;
		Int32 ret = client.PollEvent(&event, 100);
		ASSERT_TRUE(client.IsConnected()); // Error client is not connected
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		ret = client.PollEvent(&event, 100);
		client.Disconnect();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		ret = client.PollEvent(&event, 100);
		ASSERT_FALSE(client.IsConnected());
		ASSERT_EQ(callbackCount, 0);
		running = false;
		serverThread.join();
		Enet::Deinitialize();
	}

	TEST(Enet, SendingPacket)
	{
		Enet::Initialize();
		bool running = true;
		constexpr UInt32 PacketType = 0xF;
		std::thread serverThread([&]() {
			IpAddress listeningIp("0.0.0.0", 2121);
			EnetServer server(listeningIp);
			ENetEvent event;
			while (running)
			{
				Int32 ret = server.PollEvent(&event, 100);
				if (ret <= 0)
					continue;
				if (event.eventType == ENetEvent::Type::Receive)
				{
					Packet& packet = *event.packet;
					UInt32 packetType = 0, packetSize = 0;
					ASSERT_TRUE(packet.DecodeHeader(&packetType, &packetSize));
					ASSERT_TRUE(PacketType == packetType);
					ASSERT_TRUE(packetSize == 2 * sizeof(Int32));
					Int32 v42, v84;
					packet >> v42 >> v84;
					ASSERT_EQ(v42, 42);
					ASSERT_EQ(v84, 84);
					ASSERT_TRUE(packet.EncodeHeader());
					ASSERT_TRUE(server.SendPacket(packet, event.peer.get()));
				}
			}
		});
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		EnetClient client;
		IpAddress ip("127.0.0.1", 2121);
		Int32 callbackCount = 0;
		client.Connect(ip);
		ENetEvent event;
		Int32 ret = client.PollEvent(&event, 100);
		ASSERT_TRUE(client.IsConnected());
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		
		Packet packet(PacketType);
		packet << Int32(42) << Int32(84);
		ASSERT_TRUE(packet.EncodeHeader());
		ASSERT_TRUE(client.SendPacket(packet));
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		ret = client.PollEvent(&event, 100);
		if (event.eventType == ENetEvent::Type::Receive)
		{
			Packet& newPacket = *event.packet;
			ASSERT_TRUE(newPacket.DecodeHeader());
			ASSERT_EQ(packet.GetDataSize(), newPacket.GetDataSize());
			ASSERT_EQ(packet, newPacket);
		}
		else
			ASSERT_FALSE(false);
		running = false;
		serverThread.join();
		Enet::Deinitialize();
	}
}// namespace CONCERTO_ANONYMOUS_NAMESPACE