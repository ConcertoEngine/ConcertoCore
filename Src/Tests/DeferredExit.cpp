//
// Created by arthur on 23/02/2023.
//

#include <gtest/gtest.h>
#include "Concerto/Core/DeferredExit.hpp"

#include "Concerto/Core/Types/Types.hpp"

namespace CCT_ANONYMOUS_NAMESPACE
{
	using namespace cct;

	TEST(DeferredExit, General)
	{
		Int32 i = 0;
		{
			DeferredExit _([&]()
			{
				i = 42;
			});
		}
		ASSERT_EQ(i, 42);
	}
}// namespace CCT_ANONYMOUS_NAMESPACE