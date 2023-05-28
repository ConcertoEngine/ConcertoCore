//
// Created by arthur on 26/05/2023.
//

#include "Types.hpp"
#ifdef CONCERTO_PLATFORM_WINDOWS
#include <stdexcept>
#include "WinIpAddressImpl.hpp"

namespace Concerto::Network
{
	IpAddress Concerto::Network::IpAddressImpl::FromSockAddr(const sockaddr* addr)
	{
		if (addr->sa_family == AF_INET)
		{
			const auto sockaddIn = reinterpret_cast<const sockaddr_in*>(addr);
			const auto ipv4 = sockaddIn->sin_addr.S_un.S_un_b;
			return { ipv4.s_b1, ipv4.s_b2, ipv4.s_b3, ipv4.s_b4, ntohs(sockaddIn->sin_port) };
		}
		else
		{
			throw std::runtime_error("Not implemented");
		}
	}

	sockaddr_in IpAddressImpl::ToSockAddr(const IpAddress& address)
	{
		if (address.GetProtocol() != IpProtocol::IPV4)
			throw std::runtime_error("Not implemented");
		sockaddr_in addr = {};
		const IpAddress::IPv4 ipv4 = address.GetIPv4();
		addr.sin_family = AF_INET;
		addr.sin_port = htons(address.GetPort());
		std::memcpy(&addr.sin_addr, ipv4.data(), ipv4.size());
		return addr;
	}
}
#endif