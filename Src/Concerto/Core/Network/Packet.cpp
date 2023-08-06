//
// Created by arthur on 28/05/2023.
//

#include <cstring>

#include "Packet.hpp"

namespace Concerto::Network
{

	Packet::Packet() : Stream(HeaderSize), _size(0), _packetType(0), _validHeader(false)
	{
	}

	Packet::Packet(UInt32 packetType, const void* data, std::size_t size)
		: Stream(HeaderSize + size), _size(size), _packetType(packetType), _validHeader(true)
	{
		_buffer.resize(HeaderSize + size);
		std::memcpy(_buffer.data(), &_packetType, sizeof(UInt32));
		std::memcpy(_buffer.data() + sizeof(UInt32), &size, sizeof(UInt32));
		std::memcpy(_buffer.data() + HeaderSize, data, size);
		_cursorPos = HeaderSize + size;
	}

	Packet::Packet(UInt32 packetType, std::size_t capacity)
		: Stream(HeaderSize + capacity), _size(0), _packetType(packetType), _validHeader(true)
	{
		_buffer.resize(HeaderSize);
		std::memcpy(_buffer.data(), &_packetType, sizeof(UInt32));
		std::memcpy(_buffer.data() + sizeof(UInt32), &_size, sizeof(UInt32));
		_cursorPos = HeaderSize;
	}

	UInt32 Packet::GetPacketType() const
	{
		return _packetType;
	}

	const Byte* Packet::GetData() const
	{
		return _buffer.data();
	}

	UInt64 Packet::GetDataSize() const
	{
		return GetSize() - HeaderSize;
	}

	std::size_t Packet::Capacity() const
	{
		return _buffer.capacity();
	}

	bool Packet::DecodeHeader(UInt32* packetType, UInt32* size)
	{
		if (_buffer.size() < HeaderSize)
			return false;
		Stream headerStream(HeaderSize);
		headerStream.Write(_buffer.data(), HeaderSize);
		headerStream.SetCursorPos(0);
		headerStream >> _packetType >> _size;
		SetCursorPos(HeaderSize);
		_validHeader = true;
		if (packetType != nullptr)
			*packetType = _packetType;
		if (size != nullptr)
			*size = _size;
		return true;
	}

	bool Packet::EncodeHeader()
	{
		if (_buffer.size() < HeaderSize)
			return false;
		const UInt32 size = _buffer.size() - HeaderSize;
		Stream headerStream(HeaderSize);
		headerStream << _packetType << size;
		headerStream.SetCursorPos(0);
		headerStream.Read(_buffer.data(), HeaderSize);
		_validHeader = true;
		return true;
	}

	bool Packet::operator==(bool value) const
	{
		return _validHeader == value && _validData == value;
	}

	bool Packet::operator!=(bool value) const
	{
		return !operator==(value);
	}
}