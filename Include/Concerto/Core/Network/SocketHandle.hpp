//
// Created by arthur on 25/05/2023.
//

#ifndef CONCERTOCORE_INCLUDE_CONCERTO_CORE_NETWORK_SOCKETHANDLE_HPP_
#define CONCERTOCORE_INCLUDE_CONCERTO_CORE_NETWORK_SOCKETHANDLE_HPP_

#include "Types.hpp"
#ifdef CONCERTO_PLATFORM_WINDOWS
#include <basetsd.h>
#endif
namespace Concerto::Network
{
#ifdef CONCERTO_PLATFORM_WINDOWS
	using SocketHandle = UINT_PTR;
#else
	using SocketHandle = int;
#endif

	enum class SocketType
	{
		TCP,
		UDP
	};

	enum class SocketError
	{
		NoError, // No error
		ConnectionRefused, // Connection with remote host was refused
		ConnectionClosed, // Connection with remote host was closed
		AddressNotAvailable, // Address is not available
		InternError, // Internal error
		NotInitialized, // Socket is not initialized
		TimedOut, // Connection timed out
		NetworkError, // Network error
		UnreachableHost, // Unreachable host
		Unknown // Unknown error
	};

}
#endif //CONCERTOCORE_INCLUDE_CONCERTO_CORE_NETWORK_SOCKETHANDLE_HPP_
