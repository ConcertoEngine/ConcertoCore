//
// Created by arthur on 23/02/2023.
//

#include <gtest/gtest.h>
#include "Concerto/Core/Math/Transform.hpp"

namespace CONCERTO_ANONYMOUS_NAMESPACE
{
	using namespace Concerto::Math;

	TEST(Transform, Constructor)
	{
		Transform transform(Vector3f(0.f, 0.f, 0.f), Quaternionf(0.f, 0.f, 0.f, 0.f), Vector3f(0.f, 0.f, 0.f));
		ASSERT_EQ(transform.GetLocation(), Vector3f(0.f, 0.f, 0.f));
		ASSERT_EQ(transform.GetRotation(), Quaternionf(0.f, 0.f, 0.f, 0.f));
		ASSERT_EQ(transform.GetScale(), Vector3f(0.f, 0.f, 0.f));
	}
}// namespace CONCERTO_ANONYMOUS_NAMESPACE