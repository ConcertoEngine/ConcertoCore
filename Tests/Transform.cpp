//
// Created by arthur on 23/02/2023.
//

#include <gtest/gtest.h>
#include "Math/Transform.hpp"

using namespace Concerto::Math;

TEST(Transform, Constructor)
{
	Transform transform(Vector3f(0.f, 0.f, 0.f), Quaternionf (0.f, 0.f, 0.f, 0.f), Vector3f(0.f, 0.f, 0.f));
	ASSERT_EQ(transform.Location, Vector3f(0.f, 0.f, 0.f));
	ASSERT_EQ(transform.Rotation, Quaternionf (0.f, 0.f, 0.f, 0.f));
	ASSERT_EQ(transform.Scale, Vector3f(0.f, 0.f, 0.f));
}