//
// Created by arthur on 30/05/2023.
//

#include <gtest/gtest.h>
#include <array>
#include "Concerto/Core/Network/Packet.hpp"

namespace CONCERTO_ANONYMOUS_NAMESPACE
{
	using namespace cct;
	using namespace cct::Network;

	constexpr UInt8 PacketType = 0xF;
	const UInt8 ByteSwappedPacketType = ByteSwap(PacketType);

	struct PacketHeader
	{
		UInt8 PacketType;
		UInt32 Size;
	};

	TEST(Packet, Constructor)
	{
		Packet packet(PacketType, nullptr, 0);
		EXPECT_EQ(packet.GetPacketType(), PacketType);
		EXPECT_EQ(packet.GetSize(), Packet::HeaderSize);
		EXPECT_EQ(packet.GetDataSize(), 0);
		EXPECT_EQ(packet.Capacity(), Packet::HeaderSize);

		Packet packet2(PacketType, 5);
		EXPECT_EQ(packet2.GetPacketType(), PacketType);
		EXPECT_EQ(packet2.GetSize(), Packet::HeaderSize);
		EXPECT_EQ(packet2.GetDataSize(), 0);
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
		EXPECT_TRUE(packet.EncodeHeader());
		EXPECT_TRUE(packet.DecodeHeader(&header.PacketType, &header.Size));
		EXPECT_EQ(header.PacketType, ByteSwappedPacketType);
		EXPECT_EQ(header.Size, 0);

		Packet packet2(PacketType, 5);
		EXPECT_TRUE(packet2.EncodeHeader());
		EXPECT_TRUE(packet2.DecodeHeader(&header.PacketType, &header.Size));
		EXPECT_EQ(header.PacketType, ByteSwappedPacketType);
		EXPECT_EQ(header.Size, 0);

		Packet packet3;
		EXPECT_FALSE(packet3.EncodeHeader());
		EXPECT_FALSE(packet3.DecodeHeader(&header.PacketType, &header.Size));
		EXPECT_EQ(header.PacketType, ByteSwappedPacketType);
		EXPECT_EQ(header.Size, 0);

		const char* data = "Hello";
		Packet packet4(PacketType, data, 5);
		EXPECT_TRUE(packet4.EncodeHeader());
		EXPECT_TRUE(packet4.DecodeHeader(&header.PacketType, &header.Size));
		EXPECT_EQ(header.PacketType, ByteSwappedPacketType);
		EXPECT_EQ(header.Size, 5);

		Packet packet5(PacketType);
		packet5 << UInt32(12) << UInt32(13);
		EXPECT_TRUE(packet5.EncodeHeader());
		EXPECT_TRUE(packet5.DecodeHeader(&header.PacketType, &header.Size));
		EXPECT_EQ(header.PacketType, ByteSwappedPacketType);
		EXPECT_EQ(header.Size, 2 * sizeof(Int32));
		UInt32 a, b;
		packet5 >> a >> b;
		EXPECT_EQ(a, 12);
		EXPECT_EQ(b, 13);
	}
} // namespace CONCERTO_ANONYMOUS_NAMESPACE