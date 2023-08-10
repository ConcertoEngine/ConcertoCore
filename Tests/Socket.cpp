//
// Created by arthur on 23/02/2023.
//

#include <cstring>
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
		Socket server(SocketType::TCP, IpProtocol::IPV4);
		server.SetBlocking(true);
		server.Listen(IpAddress::AnyIPV4, 8080);
		Socket client(SocketType::TCP, IpProtocol::IPV4);
		IpAddress ip(127, 0, 0, 1, 8080);
		client.Connect(ip);
		std::string helloWorld = "Hello World";
		Buffer buffer(11);
		std::memcpy(buffer.GetRawData(), helloWorld.c_str(), 11);
		client.Send(buffer);

		Socket serverClient(SocketType::TCP, IpProtocol::IPV4);
		serverClient.SetBlocking(true);
		server.Accept(serverClient);

		Buffer buffer2(1024);
		std::size_t availableBytes = serverClient.GetAvailableBytes();
		ASSERT_EQ(availableBytes, 11);
		std::size_t receivedSize = serverClient.Receive(buffer2);
		buffer2.Resize(receivedSize);
		ASSERT_EQ(buffer2, buffer);
		Socket::UnInitialize();
	}

	TEST(Socket, UdpServer)
	{
		Socket::Initialize();
		Socket server(SocketType::UDP, IpProtocol::IPV4);
		server.SetBlocking(true);
		ASSERT_TRUE(server.Bind(IpAddress::AnyIPV4, 8080));

		
		Socket client(SocketType::UDP, IpProtocol::IPV4);
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