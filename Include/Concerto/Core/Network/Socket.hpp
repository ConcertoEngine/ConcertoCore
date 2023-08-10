//
// Created by arthur on 25/05/2023.
//

#ifndef CONCERTOCORE_INCLUDE_CONCERTO_CORE_NETWORK_SOCKET_HPP_
#define CONCERTOCORE_INCLUDE_CONCERTO_CORE_NETWORK_SOCKET_HPP_

#include <cstddef>

#include "SocketHandle.hpp"
#include "IpAddress.hpp"

namespace Concerto
{
	class Buffer;
}

namespace Concerto::Network
{
	class Socket
	{
	 public:
		Socket(SocketType socketType, IpProtocol ipProtocol);
		Socket(const Socket&) = delete;
		Socket(Socket&&) noexcept;
		virtual ~Socket();

		void Close();

		[[nodiscard]] SocketType GetType() const;
		[[nodiscard]] SocketError GetLastError() const;
		[[nodiscard]] std::size_t GetAvailableBytes() const;

		void SetBlocking(bool blocking);

		void Listen(IpAddress address, UInt16 port, int backlog = 5);
		bool Bind(IpAddress address, UInt16 port);
		void Accept(Socket& socket);
		void Connect(IpAddress address);
		std::size_t Receive(Buffer& buffer);
		std::size_t Receive(void* buffer, std::size_t size);

		std::size_t Send(const Buffer& buffer);
		std::size_t Send(const void* buffer, std::size_t size);

		static bool Initialize();
		static bool UnInitialize();
	 protected:
		SocketHandle _handle{};
		SocketType _type;
		SocketError _lastError;
		IpProtocol _ipProtocol;
		bool _blocking;
	};
}

#endif //CONCERTOCORE_INCLUDE_CONCERTO_CORE_NETWORK_SOCKET_HPP_
