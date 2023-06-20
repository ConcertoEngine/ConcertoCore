//
// Created by arthur on 28/05/2023.
//

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

	std::size_t Packet::Capacity() const
	{
		return _buffer.capacity();
	}

	bool Packet::DecodeHeader(UInt32* packetType, UInt32* size)
	{
		if (_buffer.size() < HeaderSize)
			return false;
		std::memcpy(&_packetType, _buffer.data(), sizeof(UInt32));
		std::memcpy(&_size, _buffer.data() + sizeof(UInt32), sizeof(UInt32));
		_validHeader = true;
		if (packetType != nullptr)
			*packetType = _packetType;
		if (size != nullptr)
			*size = _size;
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