//
// Created by arthur on 22/02/2023.
//

#ifndef CONCERTO_CORE_TYPE_HPP
#define CONCERTO_CORE_TYPE_HPP

#include <string_view>

#include "Concerto/Core/Types.hpp"

namespace Concerto
{
	template<typename T>
	constexpr std::string_view TypeName()
	{
		//from https://github.com/NazaraEngine/NazaraUtils/blob/main/include/NazaraUtils/TypeName.inl
		using namespace std::string_view_literals;

		constexpr std::string_view functionSignature = CONCERTO_FUNCTION_SIGNATURE;
#ifdef CONCERTO_COMPILER_MSVC
		constexpr auto prefix = "Concerto::TypeName<"sv;
		constexpr auto suffix = ">"sv;
#else
		constexpr auto prefix = "T = "sv;
		constexpr auto suffix = ";]"
#endif
		constexpr auto prefixStartPos = functionSignature.find(prefix);
		static_assert(prefixStartPos != std::string_view::npos);

		constexpr auto suffixPos = functionSignature.substr(prefixStartPos).find_last_of(suffix);
		static_assert(suffixPos != std::string_view::npos);

		constexpr auto prefixEndPos = prefixStartPos + prefix.size();

		constexpr auto typeName = functionSignature.substr(prefixEndPos, suffixPos - prefix.size());

#ifdef CONCERTO_COMPILER_MSVC

		for (std::string_view p : {"class "sv, "struct "sv, "enum class "sv, "enum struct "sv, "enum "sv})
		{
			if (typeName.starts_with(p))
			{
				return typeName.substr(p.size());
			}
		}
#endif
		return typeName;

	}

	template<typename T>
	constexpr UInt64 TypeId()
	{
		constexpr std::string_view typeName = TypeName<T>();
		return 0ui64;
	}
}

#endif
