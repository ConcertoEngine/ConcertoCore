//
// Created by arthur on 02/06/2024.
//

#ifndef CONCERTO_CORE_POSIX_DYNLIBIMPL_HPP
#define CONCERTO_CORE_POSIX_DYNLIBIMPL_HPP
#include "Concerto/Core/Types.hpp"
#ifdef CONCERTO_PLATFORM_POSIX
#include <filesystem>
#include <string>
#include <dlfcn.h>

namespace Concerto
{
	class DynLibImpl
	{
	 public:
		DynLibImpl() = default;
		DynLibImpl(const DynLibImpl&) = delete;

		bool Load(const std::filesystem::path& path, std::string* error = nullptr);
		bool Unload(std::string* error = nullptr);

	 private:
		void* _module = {};
	};
}// namespace Concerto
#endif //CONCERTO_PLATFORM_POSIX
#endif //CONCERTO_CORE_POSIX_DYNLIBIMPL_HPP
