//
// Created by arthur on 23/02/2023.
//

#include <cstring>

#ifdef CONCERTO_PLATFORM_MACOS // because the CI is failing in release mode
#include <thread>
#endif

#include <gtest/gtest.h>
#include "Concerto/Core/Network/Socket.hpp"
#include "Concerto/Core/Buffer.hpp"

namespace CONCERTO_ANONYMOUS_NAMESPACE
{
	using namespace Concerto;
	using namespace Concerto::Network;

	TEST(Socket, TcpServer)
	{
		Socket::Initialize();
		const IpAddress ipAddress(127, 0, 0, 1, 8080);
		Socket server(SocketType::Tcp, IpProtocol::Ipv4);
		server.SetBlocking(true);
		server.Listen(ipAddress);
		Socket client(SocketType::Tcp, IpProtocol::Ipv4);
		client.Connect(ipAddress);
		const std::string helloWorld = "Hello World";
		Buffer buffer(11);
		std::memcpy(buffer.GetRawData(), helloWorld.c_str(), 11);
		client.Send(buffer);

		Socket serverClient(SocketType::Tcp, IpProtocol::Ipv4);
		serverClient.SetBlocking(true);
		server.Accept(serverClient);

		Buffer buffer2(1024);

#ifdef CONCERTO_PLATFORM_MACOS // because the CI is failing in release mode
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(500ms);
#endif

		const std::size_t availableBytes = serverClient.GetAvailableBytes();
		ASSERT_EQ(availableBytes, 11);
		const std::size_t receivedSize = serverClient.Receive(buffer2);
		buffer2.Resize(receivedSize);
		ASSERT_EQ(buffer2, buffer);
		Socket::UnInitialize();
	}

	TEST(Socket, UdpServer)
	{
		Socket::Initialize();
		Socket server(SocketType::Udp, IpProtocol::Ipv4);
		server.SetBlocking(true);
		auto ipAddress = IpAddress::AnyIPV4;
		ipAddress.SetPort(8080);
		ASSERT_TRUE(server.Bind(ipAddress));

		
		Socket client(SocketType::Udp, IpProtocol::Ipv4);
		IpAddress ip(127, 0, 0, 1, 8080);
		client.Connect(ip);
		std::string helloWorld = "Hello World";
		Buffer buffer(11);
		std::memcpy(buffer.GetRawData(), helloWorld.c_str(), 11);
		client.Send(buffer);

		Buffer receivedBuffer(1024);
		std::size_t receivedSize = server.Receive(receivedBuffer);
		receivedBuffer.Resize(receivedSize);
		ASSERT_EQ(receivedBuffer, buffer);
		
		Socket::UnInitialize();
	}
}// namespace CONCERTO_ANONYMOUS_NAMESPACE