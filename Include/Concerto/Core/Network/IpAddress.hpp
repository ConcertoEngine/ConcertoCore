//
// Created by arthur on 25/05/2023.
//

#ifndef CONCERTOCORE_INCLUDE_CONCERTO_CORE_NETWORK_IPADRESS_HPP_
#define CONCERTOCORE_INCLUDE_CONCERTO_CORE_NETWORK_IPADRESS_HPP_

#include <array>
#include <string>
#include "Types.hpp"

namespace Concerto::Network
{
	enum class IpProtocol
	{
		IPV4,
		IPV6
	};

	class CONCERTO_PUBLIC_API IpAddress
	{
	 public:
		using IPv4 = std::array<UInt8, 4>;
		using IPv6 = std::array<UInt16, 16>;

		IpAddress() = default;
		explicit IpAddress(const IPv4& ip, UInt16 port);
		explicit IpAddress(const IPv6& ip, UInt16 port);
		explicit IpAddress(const std::string& ip, UInt16 port);
		IpAddress(UInt8 a, UInt8 b, UInt8 c, UInt8 d, UInt16 port);
		explicit IpAddress(UInt64 address, UInt16 port);
		explicit IpAddress(UInt32 address, UInt16 port);

		[[nodiscard]] IpProtocol GetProtocol() const;
		[[nodiscard]] const IPv4& GetIPv4() const;
		[[nodiscard]] const IPv6& GetIPv6() const;
		[[nodiscard]] UInt16 GetPort() const;

		[[nodiscard]] IpAddress MapToIPv4() const;
		[[nodiscard]] IpAddress MapToIPv6() const;

		[[nodiscard]] UInt32 ToUInt32() const;
		[[nodiscard]] UInt64 ToUInt64() const;

		static const IpAddress AnyIPV4;
		void SetPort(UInt16 i);
	 private:
		union
		{
			IPv4 _ipv4;
			IPv6 _ipv6;
		};
		IpProtocol _protocol;
		UInt16 _port;
	};
}
#endif //CONCERTOCORE_INCLUDE_CONCERTO_CORE_NETWORK_IPADRESS_HPP_
