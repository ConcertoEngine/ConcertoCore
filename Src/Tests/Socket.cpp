//
// Created by arthur on 23/02/2023.
//

#include <cstring>
#include <thread>

#include <gtest/gtest.h>
#include "Concerto/Core/Network/Socket/Socket.hpp"
#include "Concerto/Core/Buffer/Buffer.hpp"

#ifdef CCT_PLATFORM_MACOS // because the CI is failing in release mode
#include <thread>
#endif


namespace CCT_ANONYMOUS_NAMESPACE
{
	using namespace cct;
	using namespace cct::net;

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
		EXPECT_TRUE(server.Accept(serverClient));

		Buffer buffer2(1024);

#ifdef CCT_PLATFORM_MACOS // because the CI is failing in release mode
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
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

	TEST(Socket, Errors)
	{
		Socket::Initialize();
		Socket server(SocketType::Tcp, IpProtocol::Ipv4);
		Socket client(SocketType::Udp, IpProtocol::Ipv4);
		EXPECT_FALSE(server.Accept(client));
		
		Socket::UnInitialize();
	}
}// namespace CCT_ANONYMOUS_NAMESPACE