//
// Created by arthur on 02/06/2023.
//

#include "Concerto/Core/DynLib.hpp"

#include "Assert.hpp"
#ifdef CONCERTO_PLATFORM_WINDOWS
#include "DynLib/WindowsDynLibImpl.hpp"
#elif defined(CONCERTO_PLATFORM_POSIX)
#include "DynLib/PosixDynLibImpl.hpp"
#else
#error Current platform is not supported
#endif

#define TO_DYNLIB_IMPL static_cast<DynLibImpl*>(_impl.get())

namespace Concerto
{
	DynLib::~DynLib()
	{
		if (IsLoaded())
			TO_DYNLIB_IMPL->Unload();
		_impl = nullptr;
	}

	bool DynLib::IsLoaded() const
	{
		return _impl != nullptr;
	}

	bool DynLib::Load(const std::filesystem::path& path)
	{
		CONCERTO_ASSERT(_impl, "ConcertoCore: A DynLib is already loaded, please call DynLib::Unload before.");
		_impl = std::unique_ptr<void, ImplDeleter>(new DynLibImpl, ImplDeleter());
		bool res = false;
		if (path.extension() != CONCERTO_DYNLIB_EXTENSION)
			res = TO_DYNLIB_IMPL->Load(path.string() + CONCERTO_DYNLIB_EXTENSION, &_lastError);
		else
			res = TO_DYNLIB_IMPL->Load(path, &_lastError);
		if (res)
			return true;
		_impl = nullptr;
		return false;
	}

	bool DynLib::Unload()
	{
		const bool res = TO_DYNLIB_IMPL->Unload(&_lastError);
		_impl = nullptr;
		return res;
	}

	void* DynLib::GetSymbol(const std::string& symbol) const
	{
		void* res = TO_DYNLIB_IMPL->GetSymbol(symbol, &_lastError);
		return res;
	}

	void DynLib::ImplDeleter::operator()(void* impl) const
	{
		if (!impl)
			return;
		std::default_delete<DynLibImpl>()(static_cast<DynLibImpl*>(impl));
	}
}// namespace Concerto
