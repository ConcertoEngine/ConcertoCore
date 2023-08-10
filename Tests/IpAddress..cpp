//
// Created by arthur on 09/08/2023.
//

#include <gtest/gtest.h>
#include "Concerto/Core/Network/IpAddress.hpp"

namespace CONCERTO_ANONYMOUS_NAMESPACE
{
	using namespace Concerto;
	using namespace Concerto::Network;
	static constexpr UInt32 LocalHost = 2130706433;
	static constexpr IpAddress::IPv4 LocalHostArray = {127, 0, 0, 1};

	TEST(IpAddress, ParseIPV4)
	{
		IpAddress ip(LocalHost, 2121);
		EXPECT_EQ(ip.ToUInt32(), LocalHost);
		EXPECT_EQ(ip.GetProtocol(), IpProtocol::IPV4);
		EXPECT_EQ(ip.GetIPv4(), LocalHostArray);

		ip = IpAddress("127.0.0.1", 2121);
		EXPECT_EQ(ip.ToUInt32(), LocalHost);
		EXPECT_EQ(ip.GetIPv4(), LocalHostArray);
		EXPECT_EQ(ip.GetProtocol(), IpProtocol::IPV4);

		ip = IpAddress(LocalHostArray, 2121);
		EXPECT_EQ(ip.ToUInt32(), LocalHost);
		EXPECT_EQ(ip.GetIPv4(), LocalHostArray);
		EXPECT_EQ(ip.GetProtocol(), IpProtocol::IPV4);

		ip = IpAddress("xxx.x.x.x", 2121);
		EXPECT_EQ(ip.GetProtocol(), IpProtocol::Error);
	}

	TEST(IpAddress, IsIpV4)
	{
		EXPECT_TRUE(IpAddress::IsIpV4("127.0.0.1"));
		
		EXPECT_FALSE(IpAddress::IsIpV4("1277.0.0.1"));
		EXPECT_FALSE(IpAddress::IsIpV4("127.1277.0.1"));
		EXPECT_FALSE(IpAddress::IsIpV4("127.0.1277.1"));
		EXPECT_FALSE(IpAddress::IsIpV4("127.0.127.1277"));
		EXPECT_FALSE(IpAddress::IsIpV4("127..0.1"));
		EXPECT_FALSE(IpAddress::IsIpV4("0:0:0:0:0:0:0:1"));
	}
	
	TEST(IpAddress, IsIpV6)
	{
		EXPECT_TRUE(IpAddress::IsIpV6("0:0:0:0:0:0:0:1"));
		EXPECT_TRUE(IpAddress::IsIpV6("::1"));
		EXPECT_TRUE(IpAddress::IsIpV6("2001:db8:3333:4444:5555:6666:7777:8888"));
		EXPECT_TRUE(IpAddress::IsIpV6("2001:0db8:0001:0000:0000:0ab9:C0A8:010"));
		EXPECT_TRUE(IpAddress::IsIpV6("fe80:0000:0000:0000:0000:0000:0000:1"));
		EXPECT_TRUE(IpAddress::IsIpV6("2001:db8::1234:5678"));
		EXPECT_TRUE(IpAddress::IsIpV6("::1234:5678"));
		EXPECT_TRUE(IpAddress::IsIpV6("2001:db8::"));

		EXPECT_FALSE(IpAddress::IsIpV6("192.168.1.1"));
		EXPECT_FALSE(IpAddress::IsIpV6("2001:0db8:85a3:0000:0000:8a2e:0370:7334:1234"));
		EXPECT_FALSE(IpAddress::IsIpV6("fe80:::1"));
	}
}// namespace CONCERTO_ANONYMOUS_NAMESPACE