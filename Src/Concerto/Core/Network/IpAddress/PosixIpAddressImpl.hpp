//
// Created by arthur on 28/05/2023.
//


#ifndef CONCERTO_CORE_SRC_CONCERTO_CORE_NETWORK_IPADDRESS_POSIXIPADDRESSIMPL_HPP_
#define CONCERTO_CORE_SRC_CONCERTO_CORE_NETWORK_IPADDRESS_POSIXIPADDRESSIMPL_HPP_
#include "Concerto/Core/Types.hpp"
#ifdef CONCERTO_PLATFORM_POSIX
#include "IpAddress.hpp"
#include <netdb.h>
#include <netinet/in.h>
namespace cct::Network
{
	class IpAddressImpl
	{
	 public:
		IpAddressImpl() = delete;
		~IpAddressImpl() = delete;
		static IpAddress FromSockAddr(const sockaddr* addr);
		static sockaddr_in ToSockAddr(const IpAddress& address);
	};
}
#endif
#endif //CONCERTO_CORE_SRC_CONCERTO_CORE_NETWORK_IPADDRESS_POSIXIPADDRESSIMPL_HPP_
