//
// Created by arthur on 28/05/2023.
//

#ifndef CONCERTOCORE_INCLUDE_CONCERTO_CORE_NETWORK_PACKET_HPP_
#define CONCERTOCORE_INCLUDE_CONCERTO_CORE_NETWORK_PACKET_HPP_

#include <cstddef>
#include "Types.hpp"
#include "Buffer.hpp"
#include "Stream.hpp"

namespace Concerto::Network
{
	class CONCERTO_PUBLIC_API Packet : public Stream
	{
	 public:
		explicit Packet();
		Packet(UInt32 packetType, const void* data, std::size_t size);
		explicit Packet(UInt32 packetType, std::size_t capacity = 0);

		[[nodiscard]] UInt32 GetPacketType() const;
		[[nodiscard]] const Byte* GetData() const;
		[[nodiscard]] UInt64 GetDataSize() const;
		[[nodiscard]] std::size_t Capacity() const;

		[[nodiscard]] bool DecodeHeader(UInt32 *packetType = nullptr, UInt32 *size = nullptr);
		[[nodiscard]] bool EncodeHeader();

		bool operator==(bool) const;
		bool operator!=(bool) const;

		template<typename T>
		Packet& operator<<(T value)
		{
			Stream::operator<<(value);
			_size += sizeof(T);
			return *this;
		}

		static constexpr std::size_t HeaderSize = sizeof(UInt32) + sizeof(UInt32);
	 private:
		UInt32 _size;
		UInt32 _packetType;
		bool _validHeader;
		bool _validData{};
	};
}

#endif //CONCERTOCORE_INCLUDE_CONCERTO_CORE_NETWORK_PACKET_HPP_
