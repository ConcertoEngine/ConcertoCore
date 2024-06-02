//
// Created by arthur on 02/06/2024.
//
#include "Concerto/Core/Assert.hpp"
#include "Concerto/Core/Error.hpp"

#ifdef CONCERTO_PLATFORM_POSIX
#include "PosixDynLibImpl.hpp"

namespace Concerto
{
	bool DynLibImpl::Load(const std::filesystem::path& path, std::string* error)
	{
		_module = dlopen(path.c_str());
		if (_module == nullptr)
		{
			if (error)
				*error = Error::GetLastSystemErrorString();
			CONCERTO_ASSERT_FALSE("ConcertoCore: Couldn't load library '{}'", path);
			return false;
		}
		return true;
	}

	bool DynLibImpl::Unload(std::string* error)
	{
		CONCERTO_ASSERT(_module, "ConcertoCore: Library handle must be valid");
		const int res = dlclose(_module);
		if (!res)
		{
			if (error)
				*error = dlerror();
			CONCERTO_ASSERT(_module, "ConcertoCore: Couldn't free library");
			return false;
		}
		_module = nullptr;
		return true;
	}
}// namespace Concerto
#endif