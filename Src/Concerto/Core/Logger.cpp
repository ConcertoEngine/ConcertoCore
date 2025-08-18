//
// Created by arthur on 18/08/2025.
//

#include "Concerto/Core/Logger.hpp"

#ifdef CCT_PLATFORM_WINDOWS
#include <Windows.h>
#undef OutputDebugString
#endif

namespace cct
{
	void Logger::OutputDebugString(std::string_view string)
	{
#ifdef CCT_PLATFORM_WINDOWS
	#ifdef UNICODE
		OutputDebugStringW(reinterpret_cast<LPCWSTR>(string.data()));
	#else
		OutputDebugStringA(string.data());
	#endif // !UNICODE
#else
		std::cerr << string;
#endif
	}
}
