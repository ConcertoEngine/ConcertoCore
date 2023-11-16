//
// Created by arthur on 28/05/2023.
//

#ifndef CONCERTO_CORE_NETWORK_PACKET_HPP_
#define CONCERTO_CORE_NETWORK_PACKET_HPP_

#include <cstddef>
#include "Concerto/Core/Types.hpp"
#include "Concerto/Core/Buffer.hpp"
#include "Concerto/Core/Stream.hpp"

namespace Concerto::Network
{
	class CONCERTO_PUBLIC_API Packet : public Stream
	{
	 public:
		Packet();
		Packet(UInt8 packetType, const void* data, std::size_t size);
		explicit Packet(UInt8 packetType, std::size_t capacity = 0);

		[[nodiscard]] UInt8 GetPacketType() const;
		[[nodiscard]] const Byte* GetData() const;
		[[nodiscard]] UInt64 GetDataSize() const;
		[[nodiscard]] std::size_t Capacity() const;

		[[nodiscard]] bool DecodeHeader(UInt8* packetType = nullptr, UInt32* size = nullptr);
		[[nodiscard]] bool EncodeHeader();

		bool operator==(bool) const;
		bool operator==(const Packet&) const;
		bool operator!=(bool) const;

		template<typename T>
		Packet& operator<<(T value)
		{
			Stream::operator<<(value);
			_size += sizeof(T);
			return *this;
		}

		static constexpr std::size_t HeaderSize = sizeof(UInt8) + sizeof(UInt32);
	 private:
		UInt32 _size;
		UInt8 _packetType;
		bool _validHeader;
	};
}

#endif //CONCERTO_CORE_NETWORK_PACKET_HPP_
