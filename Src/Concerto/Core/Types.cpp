//
// Created by arthur on 05/08/2023.
//

#include "Types.hpp"

#if defined(CONCERTO_PLATFORM_WINDOWS)
#include <windows.h>
namespace Concerto
{
	inline bool Concerto::IsDebuggerAttached()
	{
		return IsDebuggerPresent() != 0;
	}
}
#elif defined(CONCERTO_PLATFORM_POSIX)
#include <fstream>
namespace Concerto
{
	bool Concerto::IsDebuggerAttached()
	{
		std::ifstream status_file("/proc/self/status");
		std::string line;
		while (std::getline(status_file, line))
		{
			if (line.substr(0, 11) == "TracerPid:\t")
			{
				int tracerPid = std::stoi(line.substr(11));
				return tracerPid != 0;
			}
		}
		return false;
	}
}
#else
namespace Concerto
{
	inline bool Concerto::IsDebuggerAttached()
	{
		return false;
	}
}
#endif