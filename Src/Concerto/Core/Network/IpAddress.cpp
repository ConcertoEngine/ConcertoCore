//
// Created by arthur on 27/05/2023.
//

#include <cassert>
#include <stdexcept>
#include <regex>
#include <ranges>
#include <charconv>

#include "Concerto/Core/Network/IpAddress.hpp"
#include "Concerto/Core/Logger.hpp"

namespace Concerto::Network
{
	const IpAddress IpAddress::AnyIPV4 = IpAddress(0, 0, 0, 0, 0);

	IpAddress::IpAddress(const IpAddress::IPv4& ip, UInt16 port) :
		_ipv4(ip), 
		_protocol(IpProtocol::IPV4), 
		_port(port)
	{

	}
	IpAddress::IpAddress(const IpAddress::IPv6& ip, UInt16 port) : 
		_ipv6(ip), 
		_protocol(IpProtocol::IPV6), 
		_port(port)
	{

	}

	IpAddress::IpAddress(UInt8 a, UInt8 b, UInt8 c, UInt8 d, UInt16 port) :
		_ipv4({ a, b, c, d }),
		_protocol(IpProtocol::IPV4),
		_port(port)
	{

	}

	IpAddress::IpAddress(UInt32 address, UInt16 port) :
		_ipv4({ static_cast<UInt8>(address >> 24),
				static_cast<UInt8>(address >> 16),
				static_cast<UInt8>(address >> 8),
				static_cast<UInt8>(address) }),
		_protocol(IpProtocol::IPV4),
		_port(port)
	{

	}

	IpAddress::IpAddress(std::string_view ip, UInt16 port) :
		_protocol(IpProtocol::Error),
		_port(port)
	{
		if (IsIpV4(ip))
		{
#ifdef CONCERTO_PLATFORM_POSIX
			Logger::Error("Parsing IP address on POSIX systems is not yet supported");
			CONCERTO_ASSERT_FALSE;
#else
			_protocol = IpProtocol::IPV4;
			auto segments = ip
				| std::views::split('.')
				| std::views::transform([](auto v) {
					UInt8 i = 0;
					std::from_chars(v.data(), v.data() + v.size(), i);
					return i;
				});
			UInt8 i = 0;
			for (const UInt8& segment : segments)
			{
				_ipv4[i++] = segment;
			}
			return;
#endif
		}
		else if (IsIpV6(ip))
		{
			CONCERTO_ASSERT_FALSE;
			return;
		}
		_protocol = IpProtocol::Error;
	}

	IpProtocol IpAddress::GetProtocol() const
	{
		return _protocol;
	}

	const IpAddress::IPv4& IpAddress::GetIPv4() const
	{
		CONCERTO_ASSERT(_protocol == IpProtocol::IPV4);
		return _ipv4;
	}

	const IpAddress::IPv6& IpAddress::GetIPv6() const
	{
		CONCERTO_ASSERT(_protocol == IpProtocol::IPV6);
		return _ipv6;
	}

	UInt16 IpAddress::GetPort() const
	{
		return _port;
	}

	void IpAddress::SetPort(UInt16 port)
	{
		_port = port;
	}

	UInt32 IpAddress::ToUInt32() const
	{
		CONCERTO_ASSERT(_protocol == IpProtocol::IPV4);
		return (_ipv4[0] << 24) | (_ipv4[1] << 16) | (_ipv4[2] << 8) | _ipv4[3];
	}

	std::string IpAddress::ToString() const
	{
		std::string ip;
		if (_protocol == IpProtocol::IPV4)
		{
			ip = std::to_string(_ipv4[0]) + "." + std::to_string(_ipv4[1]) + "." + std::to_string(_ipv4[2]) + "." + std::to_string(_ipv4[3]);
		}
		else if (_protocol == IpProtocol::IPV6)
		{
			CONCERTO_ASSERT_FALSE;
		}
		else
		{
			CONCERTO_ASSERT_FALSE;
		}
		return ip;
	}
	
	bool IpAddress::IsIpV4(std::string_view ip)
	{
		std::regex ipv4Pattern(R"(\b(?:\d{1,3}\.){3}\d{1,3}\b)");
		return std::regex_match(ip.data(), ipv4Pattern);
	}

	bool IpAddress::IsIpV6(std::string_view ip)
	{
		//from https://stackoverflow.com/questions/53497/regular-expression-that-matches-valid-ipv6-addresses
		std::regex ipv6Pattern(R"(([0-9a-fA-F]{1,4}:){7,7}[0-9a-fA-F]{1,4}|([0-9a-fA-F]{1,4}:){1,7}:|([0-9a-fA-F]{1,4}:){1,6}:[0-9a-fA-F]{1,4}|([0-9a-fA-F]{1,4}:){1,5}(:[0-9a-fA-F]{1,4}){1,2}|([0-9a-fA-F]{1,4}:){1,4}(:[0-9a-fA-F]{1,4}){1,3}|([0-9a-fA-F]{1,4}:){1,3}(:[0-9a-fA-F]{1,4}){1,4}|([0-9a-fA-F]{1,4}:){1,2}(:[0-9a-fA-F]{1,4}){1,5}|[0-9a-fA-F]{1,4}:((:[0-9a-fA-F]{1,4}){1,6})|:((:[0-9a-fA-F]{1,4}){1,7}|:)|fe80:(:[0-9a-fA-F]{0,4}){0,4}%[0-9a-zA-Z]{1,}|::(ffff(:0{1,4}){0,1}:){0,1}((25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])\.){3,3}(25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])|([0-9a-fA-F]{1,4}:){1,4}:((25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])\.){3,3}(25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9]))");
		return std::regex_match(ip.data(), ipv6Pattern);
	}
	
	IpProtocol IpAddress::DetectProtocol(std::string_view ip)
	{
		if (IsIpV4(ip))
			return IpProtocol::IPV4;
		else if (IsIpV6(ip))
			return IpProtocol::IPV6;
		return IpProtocol::Error;
	}
}