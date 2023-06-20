//
// Created by arthur on 30/05/2023.
//

#include <gtest/gtest.h>
#include "Concerto/Core/Network/Packet.hpp"

using namespace Concerto;
using namespace Concerto::Network;
constexpr UInt32 PacketType = 0xF;
struct PacketHeader
{
	UInt32 PacketType;
	UInt32 Size;
};
TEST(Packet, Constructor)
{
	Packet packet(PacketType, nullptr, 0);
	EXPECT_EQ(packet.GetPacketType(), PacketType);
	EXPECT_EQ(packet.GetSize(), 0);
	EXPECT_EQ(packet.GetSize(), 0);
	EXPECT_EQ(packet.Capacity(), Packet::HeaderSize);

	Packet packet2(PacketType, 5);
	EXPECT_EQ(packet2.GetPacketType(), PacketType);
	EXPECT_EQ(packet2.GetSize(), 0);
	EXPECT_EQ(packet2.GetSize(), 0);
	EXPECT_EQ(packet2.Capacity(), Packet::HeaderSize + 5);

	Packet packet3;
	EXPECT_EQ(packet3.GetPacketType(), 0);
	EXPECT_EQ(packet3.GetSize(), 0);
	EXPECT_EQ(packet3.GetSize(), 0);
	EXPECT_EQ(packet3.Capacity(), Packet::HeaderSize);
}

TEST(Packet, DecodeHeader)
{
	PacketHeader header = {};
	Packet packet(PacketType, nullptr, 0);
	EXPECT_TRUE(packet.DecodeHeader(&header.PacketType, &header.Size));
	EXPECT_EQ(header.PacketType, PacketType);
	EXPECT_EQ(header.Size, 0);

	Packet packet2(PacketType, 5);
	EXPECT_TRUE(packet2.DecodeHeader(&header.PacketType, &header.Size));
	EXPECT_EQ(header.PacketType, PacketType);
	EXPECT_EQ(header.Size, 0);

	Packet packet3;
	EXPECT_FALSE(packet3.DecodeHeader(&header.PacketType, &header.Size));
	EXPECT_EQ(header.PacketType, PacketType);
	EXPECT_EQ(header.Size, 0);

	const char* data = "Hello";
	Packet packet4(PacketType, data, 5);
	EXPECT_TRUE(packet4.DecodeHeader(&header.PacketType, &header.Size));
	EXPECT_EQ(header.PacketType, PacketType);
	EXPECT_EQ(header.Size, 5);

	Packet packet5(PacketType);
	packet5 << UInt32(12) << UInt32(15);
	EXPECT_TRUE(packet5.DecodeHeader(&header.PacketType, &header.Size));
	EXPECT_EQ(header.PacketType, PacketType);
	EXPECT_EQ(header.Size, 2 * sizeof(Int32));
}