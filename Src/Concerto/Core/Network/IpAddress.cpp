//
// Created by arthur on 27/05/2023.
//

#include <cassert>
#include <stdexcept>
#include "Network/IpAddress.hpp"

namespace Concerto::Network
{
	const IpAddress IpAddress::AnyIPV4 = IpAddress(0, 0, 0, 0, 0);

	IpAddress::IpAddress(const IpAddress::IPv4& ip, UInt16 port) : _ipv4(ip), _protocol(IpProtocol::IPV4), _port(port)
	{

	}
	IpAddress::IpAddress(const IpAddress::IPv6& ip, UInt16 port) : _ipv6(ip), _protocol(IpProtocol::IPV6), _port(port)
	{

	}

	IpAddress::IpAddress(UInt8 a, UInt8 b, UInt8 c, UInt8 d, UInt16 port) : _ipv4({ a, b, c, d }),
																			_protocol(IpProtocol::IPV4), _port(port)
	{

	}

	IpAddress::IpAddress(UInt64 address, UInt16 port) : _ipv4({ static_cast<UInt8>(address >> 24),
																static_cast<UInt8>(address >> 16),
																static_cast<UInt8>(address >> 8),
																static_cast<UInt8>(address) }),
														_protocol(IpProtocol::IPV4), _port(port)
	{
	}

	IpAddress::IpAddress(UInt32 address, UInt16 port) : _ipv4({ static_cast<UInt8>(address >> 24),
																static_cast<UInt8>(address >> 16),
																static_cast<UInt8>(address >> 8),
																static_cast<UInt8>(address) }),
														_protocol(IpProtocol::IPV4),
														_port(port)
	{

	}

	IpAddress::IpAddress(const std::string& ip, UInt16 port) : _protocol(IpProtocol::IPV4), _port(port)
	{
		//TODO: Implement
		throw std::runtime_error("Not implemented");
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

	IpAddress IpAddress::MapToIPv4() const
	{
		//TODO: Implement
		throw std::runtime_error("Not implemented");
	}

	IpAddress IpAddress::MapToIPv6() const
	{
		//TODO: Implement
		throw std::runtime_error("Not implemented");
	}

	void IpAddress::SetPort(UInt16 i)
	{
		_port = i;
	}

	UInt32 IpAddress::ToUInt32() const
	{
		CONCERTO_ASSERT(_protocol == IpProtocol::IPV4);
		return (_ipv4[0] << 24) | (_ipv4[1] << 16) | (_ipv4[2] << 8) | _ipv4[3];
	}

	UInt64 IpAddress::ToUInt64() const
	{
		CONCERTO_ASSERT(_protocol == IpProtocol::IPV4);
		return (_ipv4[0] << 24) | (_ipv4[1] << 16) | (_ipv4[2] << 8) | _ipv4[3];
	}
}