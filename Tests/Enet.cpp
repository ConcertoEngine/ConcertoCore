//
// Created by arthur on 13/08/2023.
//

#include <thread>
#include <chrono>
#include <span>

#include <gtest/gtest.h>
#include <Concerto/Core/Logger.hpp>
#include <Concerto/Core/Network/ENet/ENet.hpp>
#include <Concerto/Core/Network/ENet/Server.hpp>
#include <Concerto/Core/Network/ENet/Client.hpp>

namespace CONCERTO_ANONYMOUS_NAMESPACE
{
	using namespace cct;
	using namespace cct::Network;

	TEST(Enet, BasicConnection)
	{
		ENet::Initialize();
		bool running = true;
		std::thread serverThread([&]() {
			IpAddress listeningIp("0.0.0.0", 2121);
			EnetServer server(listeningIp);
			Int32 count = -1;
			ENetEvent event;
			while (running)
			{
				Int32 ret = server.PollEvent(&event, 100);
				if (ret <= 0)
					continue;
				if (event.eventType == ENetEvent::Type::Connect)
					count += 2;
				else if (event.eventType == ENetEvent::Type::Disconnect)
					count--;
			}
			ASSERT_EQ(count, 0);
		});
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		EnetClient client;
		IpAddress ip("127.0.0.1", 2121);
		Int32 callbackCount = 0;
		client.Connect(ip);
		ENetEvent event;
		Int32 ret = client.PollEvent(&event, 100);
		ASSERT_TRUE(ret > 0 && event.eventType == ENetEvent::Type::Connect);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		ret = client.PollEvent(&event, 100);
		client.Disconnect();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		ret = client.PollEvent(&event, 100);
		ASSERT_TRUE(ret > 0 && event.eventType == ENetEvent::Type::Disconnect);
		ASSERT_EQ(callbackCount, 0);
		running = false;
		serverThread.join();
		ENet::Deinitialize();
	}

	TEST(Enet, SendingPacket)
	{
		ENet::Initialize();
		bool running = true;
		constexpr UInt8 PacketType = 0xF;
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
					ENetPacket& packet = *event.packet;
					UInt8 packetType = 0;
					packet >> packetType;
					ASSERT_TRUE(PacketType == packetType);
					Int32 v42, v84;
					packet >> v42 >> v84;
					ASSERT_EQ(v42, 42);
					ASSERT_EQ(v84, 84);
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
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		
		ENetPacket packet;
		packet << PacketType << Int32(42) << Int32(84);
		ASSERT_TRUE(client.SendPacket(packet));
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		ret = client.PollEvent(&event, 100);
		if (event.eventType == ENetEvent::Type::Receive)
		{
			ENetPacket& newPacket = *event.packet;
			ASSERT_EQ(packet.GetSize(), newPacket.GetSize());
			ASSERT_EQ(packet, newPacket);
		}
		else
			ASSERT_FALSE(false);
		running = false;
		serverThread.join();
		ENet::Deinitialize();
	}
}// namespace CONCERTO_ANONYMOUS_NAMESPACE