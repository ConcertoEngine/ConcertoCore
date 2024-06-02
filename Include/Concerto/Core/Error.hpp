//
// Created by arthur on 02/06/2024.
//

#include <string>

#include "Concerto/Core/Types.hpp"

namespace Concerto
{
	class CONCERTO_CORE_PUBLIC_API Error
	{
	public:
		inline static std::string GetLastSystemErrorString();
	};
}
