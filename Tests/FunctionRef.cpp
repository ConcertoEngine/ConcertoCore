//
// Created by arthur on 03/06/2024.
//

#include <gtest/gtest.h>
#include <Concerto/Core/FunctionRef.hpp>

namespace CONCERTO_ANONYMOUS_NAMESPACE
{
	TEST(FunctionRef, Lambda)
	{
		Concerto::FunctionRef func = [](){};
	}
} // namespace CONCERTO_ANONYMOUS_NAMESPACE