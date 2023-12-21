//
// Created by arthur on 25/05/2023.
//

#include "Concerto/Core/Assert.hpp"
#include "Concerto/Core/Network/Socket.hpp"
#include "Concerto/Core/Buffer.hpp"
#ifdef CONCERTO_PLATFORM_WINDOWS
#include "Socket/WinSocketImpl.hpp"
#endif// CONCERTO_PLATFORM_WINDOWS
#ifdef CONCERTO_PLATFORM_POSIX
#include "Socket/PosixSocketImpl.hpp"
#endif//CONCERTO_PLATFORM_POSIX

namespace Concerto::Network
{
	Socket::Socket(SocketType socketType, IpProtocol ipProtocol) :
		_handle(SocketImpl::InvalidSocket), 
		_type(socketType),
		_lastError(SocketError::NoError),
		_ipProtocol(ipProtocol),
		_blocking(false)
	{
	}

  Socket::Socket(Socket&& other) noexcept :
		_handle(other._handle),
		_type(other._type),
		_lastError(other._lastError),
		_ipProtocol(other._ipProtocol),
		_blocking(other._blocking)
	{
		_handle = other._handle;
		_lastError = other._lastError;
		other._handle = SocketImpl::InvalidSocket;
		other._lastError = SocketError::NoError;
	}

	Socket::~Socket()
	{
		Close();
	}

    Socket& Socket::operator=(Socket&& other) noexcept
    {
		_handle = other._handle;
		_lastError = other._lastError;
		other._handle = SocketImpl::InvalidSocket;
		other._lastError = SocketError::NoError;
		return *this;
    }

	void Socket::Close()
	{
		if (_handle == SocketImpl::InvalidSocket)
			return;
		SocketImpl::Close(_handle, &_lastError);
		_handle = SocketImpl::InvalidSocket;
	}

	SocketType Socket::GetType() const
	{
		return _type;
	}

	SocketError Socket::GetLastError() const
	{
		return _lastError;
	}

	std::size_t Socket::GetAvailableBytes() const
	{
		if (_handle == SocketImpl::InvalidSocket)
			return 0;
		return SocketImpl::GetAvailableBytes(_handle);
	}

	void Socket::SetBlocking(bool blocking)
	{
		if (_handle == SocketImpl::InvalidSocket)
			return;
		SocketImpl::SetBlocking(_handle, blocking, &_lastError);
	}

	void Socket::Listen(IpAddress address, UInt16 port, int backlog)
	{
		address.SetPort(port);
		SocketHandle handle = SocketImpl::Create(_type, _ipProtocol, &_lastError);
		if (handle == SocketImpl::InvalidSocket)
			return;
		if (!SocketImpl::Listen(handle, address, backlog, &_lastError))
			return;
		_handle = handle;
	}

	bool Socket::Bind(IpAddress address, UInt16 port)
	{
		address.SetPort(port);
		SocketHandle handle = SocketImpl::Create(_type, _ipProtocol, &_lastError);
		if (handle == SocketImpl::InvalidSocket)
			return false;
		if (!SocketImpl::Bind(handle, address, &_lastError))
			return false;
		_handle = handle;
		return true;
	}

	void Socket::Accept(Socket& socket)
	{
		CONCERTO_ASSERT(_handle != SocketImpl::InvalidSocket);
		SocketHandle handle = SocketImpl::Accept(_handle, nullptr, &_lastError);
		if (handle == SocketImpl::InvalidSocket)
			return;
		socket.Close();
		socket._handle = handle;
	}

	void Socket::Connect(IpAddress address)
	{
		Close();
		SocketHandle handle = SocketImpl::Create(_type, _ipProtocol, &_lastError);
		if (handle == SocketImpl::InvalidSocket)
			return;
		if (!SocketImpl::Connect(handle, address, &_lastError))
			return;
		_handle = handle;
	}

	std::size_t Socket::Receive(Buffer& buffer)
	{
		return Receive(buffer.GetRawData(), buffer.Size());
	}

	std::size_t Socket::Receive(void* buffer, std::size_t size)
	{
		CONCERTO_ASSERT(_handle != SocketImpl::InvalidSocket);
		std::size_t received = 0;
		SocketImpl::Receive(_handle, buffer, size, &received, &_lastError);
		return received;
	}

	std::size_t Socket::Send(const Buffer& buffer)
	{
		return Send(buffer.GetRawData(), buffer.Size());
	}

	std::size_t Socket::Send(const void* buffer, std::size_t size)
	{
		CONCERTO_ASSERT(_handle != SocketImpl::InvalidSocket);
		std::size_t sent = 0;
		SocketImpl::Send(_handle, buffer, size, &sent, &_lastError);
		return sent;
	}

	bool Socket::Initialize()
	{
		return SocketImpl::Initialize();
	}

	bool Socket::UnInitialize()
	{
		return SocketImpl::UnInitialize();
	}
}