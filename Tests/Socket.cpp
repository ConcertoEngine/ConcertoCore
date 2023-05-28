//
// Created by arthur on 23/02/2023.
//

#include <cstring>
#include <gtest/gtest.h>
#include "Concerto/Core/Network/Socket.hpp"
#include "Concerto/Core/Buffer.hpp"

using namespace Concerto;
using namespace Concerto::Network;

TEST(Socket, Server)
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