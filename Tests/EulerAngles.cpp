//
// Created by arthur on 14/03/2023.
//

#include <gtest/gtest.h>

#include "Concerto/Core/Math/EulerAngles.hpp"

namespace CCT_ANONYMOUS_NAMESPACE
{
	using namespace cct;
	constexpr float near = 0.001f;

	TEST(EulerAngles, Constructor)
	{
		EulerAnglesf e(1.f, 2.f, 3.f);
		ASSERT_EQ(1.f, e.Pitch());
		ASSERT_EQ(2.f, e.Yaw());
		ASSERT_EQ(3.f, e.Roll());
	}

	TEST(EulerAngles, operatorAdd)
	{
		EulerAnglesf e1(1.f, 2.f, 3.f);
		EulerAnglesf e2(1.f, 2.f, 3.f);
		EulerAnglesf e3 = e1 + e2;
		ASSERT_EQ(2.f, e3.Pitch());
		ASSERT_EQ(4.f, e3.Yaw());
		ASSERT_EQ(6.f, e3.Roll());
	}

	TEST(EulerAngles, operatorSub)
	{
		EulerAnglesf e1(1.f, 2.f, 3.f);
		EulerAnglesf e2(1.f, 2.f, 3.f);
		EulerAnglesf e3 = e1 - e2;
		ASSERT_EQ(0.f, e3.Pitch());
		ASSERT_EQ(0.f, e3.Yaw());
		ASSERT_EQ(0.f, e3.Roll());
	}

	TEST(EulerAngles, operatorMul)
	{
		EulerAnglesf e1(1.f, 2.f, 3.f);
		EulerAnglesf e2 = e1 * e1;
		ASSERT_EQ(1.f, e2.Pitch());
		ASSERT_EQ(4.f, e2.Yaw());
		ASSERT_EQ(9.f, e2.Roll());
	}

	TEST(EulerAngles, operatorDiv)
	{
		EulerAnglesf e1(1.f, 2.f, 3.f);
		EulerAnglesf e2 = e1 / e1;
		ASSERT_EQ(1.f, e2.Pitch());
		ASSERT_EQ(1.f, e2.Yaw());
		ASSERT_EQ(1.f, e2.Roll());
	}

	TEST(EulerAngles, operatorAddAssign)
	{
		EulerAnglesf e1(1.f, 2.f, 3.f);
		EulerAnglesf e2(1.f, 2.f, 3.f);
		e1 += e2;
		ASSERT_EQ(2.f, e1.Pitch());
		ASSERT_EQ(4.f, e1.Yaw());
		ASSERT_EQ(6.f, e1.Roll());
	}

	TEST(EulerAngles, operatorSubAssign)
	{
		EulerAnglesf e1(1.f, 2.f, 3.f);
		EulerAnglesf e2(1.f, 2.f, 3.f);
		e1 -= e2;
		ASSERT_EQ(0, e1.Pitch());
		ASSERT_EQ(0, e1.Yaw());
		ASSERT_EQ(0, e1.Roll());
	}

	TEST(EulerAngles, operatorMulAssign)
	{
		EulerAnglesf e1(1.f, 2.f, 3.f);
		e1 *= e1;
		ASSERT_EQ(1.f, e1.Pitch());
		ASSERT_EQ(4.f, e1.Yaw());
		ASSERT_EQ(9.f, e1.Roll());
	}

	TEST(EulerAngles, operatorDivAssign)
	{
		EulerAnglesf e1(1.f, 2.f, 3.f);
		e1 /= e1;
		ASSERT_EQ(1, e1.Pitch());
		ASSERT_EQ(1, e1.Yaw());
		ASSERT_EQ(1, e1.Roll());
	}

	TEST(EulerAngles, ToQuaternion)
	{
		EulerAnglesf e1(45.f, 25.f, 68.f);
		Quaternionf q = e1.ToQuaternion();
		EulerAnglesf e2 = q.ToEulerAngles();
		EXPECT_NEAR(e1.Pitch(), e2.Pitch(), near);
		EXPECT_NEAR(e1.Roll(), e2.Roll(), near);
		EXPECT_NEAR(e1.Yaw(), e2.Yaw(), near);
	}
}// namespace CCT_ANONYMOUS_NAMESPACE