//
// Created by arthur on 30/11/2023.
//

#include "Types.hpp"

#ifndef CONCERTO_CORE_HARDWARECAPABILITIES_HPP
#define CONCERTO_CORE_HARDWARECAPABILITIES_HPP

namespace Concerto
{

	class CpuInfo
	{
		
	};

	class RamInfo
	{
	};

	class DiskInfo
	{
	};

	class GpuInfo
	{
	};

	class NetworkInfo
	{
	};

	class OsInfo
	{
	};

	class HardwareCapabilities
	{
	public:
		[[nodiscard]] const CpuInfo& GetCpuInfo() const;
		[[nodiscard]] const RamInfo& GetRamInfo() const;
		[[nodiscard]] const DiskInfo& GetDiskInfo() const;
		[[nodiscard]] const GpuInfo& GetGpuInfo() const;
		[[nodiscard]] const NetworkInfo& GetNetworkInfo() const;
		[[nodiscard]] const OsInfo& GetOsInfo() const;
	private:
		HardwareCapabilities() = default;
	};
}
#endif//CONCERTO_CORE_HARDWARECAPABILITIES_HPP