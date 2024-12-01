//
// Created by arthur on 04/09/2022.
//

#include <gtest/gtest.h>

#include "Concerto/Core/Math/Quaternion.hpp"

namespace CCT_ANONYMOUS_NAMESPACE
{
	// results are from https://www.redcrab-software.com/en/Calculator/Quaternion-Calculator
	constexpr float near = 1.2e-05f;
	using namespace cct;
	using namespace cct;

	TEST(Quaternion, Quaternion)
	{
		Quaternionf quaternion(1, 2, 3, 4);
		EXPECT_EQ(quaternion.X(), 1);
		EXPECT_EQ(quaternion.Y(), 2);
		EXPECT_EQ(quaternion.Z(), 3);
		EXPECT_EQ(quaternion.W(), 4);
	}

	TEST(Quaternion, QuaternionFromEuler)
	{
		Quaternionf quaternion(EulerAnglesf(45, 25, 68));
		EXPECT_NEAR(quaternion.X(), 0.421557218f, near);
		EXPECT_NEAR(quaternion.Y(), 0.374699116f, near);
		EXPECT_NEAR(quaternion.Z(), 0.435713291, near);
		EXPECT_NEAR(quaternion.W(), 0.701458514f, near);
	}

	TEST(Quaternion, operatorAdd)
	{
		Quaternionf quaternion1(1, 2, 3, 4);
		Quaternionf quaternion2(1, 2, 3, 4);
		Quaternionf quaternion3 = quaternion1 + quaternion2;
		EXPECT_EQ(quaternion3.X(), 2);
		EXPECT_EQ(quaternion3.Y(), 4);
		EXPECT_EQ(quaternion3.Z(), 6);
		EXPECT_EQ(quaternion3.W(), 8);
	}

	TEST(Quaternion, operatorSub)
	{
		Quaternionf quaternion1(1, 2, 3, 4);
		Quaternionf quaternion2(1, 2, 3, 4);
		Quaternionf quaternion3 = quaternion1 - quaternion2;
		EXPECT_EQ(quaternion3.X(), 0);
		EXPECT_EQ(quaternion3.Y(), 0);
		EXPECT_EQ(quaternion3.Z(), 0);
		EXPECT_EQ(quaternion3.W(), 0);
	}

	TEST(Quaternion, operatorMul)
	{
		EulerAnglesf eulerAngles(10, 20, 30);
		Quaternionf quaternion1(eulerAngles);
		Quaternionf quaternion2(eulerAngles);
		Quaternionf quaternion3 = quaternion1 * quaternion2;
		EXPECT_NEAR(quaternion3.X(), 0.240985841f, near);
		EXPECT_NEAR(quaternion3.Y(), 0.357305080f, near);
		EXPECT_NEAR(quaternion3.Z(), 0.451658517f, near);
		EXPECT_NEAR(quaternion3.W(), 0.781193554f, near);
	}

	TEST(Quaternion, operatorDiv)
	{
		Quaternionf quaternion1(0.4431357f, 0.2080396f, -0.4884507f, 0.7223339f);
		Quaternionf quaternion2(0.4431357f, 0.2080396f, -0.4884507f, 0.7223339f);
		Quaternionf quaternion3 = quaternion1 / quaternion2;
		EXPECT_NEAR(quaternion3.X(), 0.f, near);
		EXPECT_NEAR(quaternion3.Y(), 0.f, near);
		EXPECT_NEAR(quaternion3.Z(), 0.f, near);
		EXPECT_NEAR(quaternion3.W(), 1.f, near);
	}

	TEST(Quaternion, operatorAddEqual)
	{
		Quaternionf quaternion1(1, 2, 3, 4);
		Quaternionf quaternion2(1, 2, 3, 4);
		quaternion1 += quaternion2;
		EXPECT_EQ(quaternion1.X(), 2);
		EXPECT_EQ(quaternion1.Y(), 4);
		EXPECT_EQ(quaternion1.Z(), 6);
		EXPECT_EQ(quaternion1.W(), 8);
	}

	TEST(Quaternion, operatorSubEqual)
	{
		Quaternionf quaternion1(1, 2, 3, 4);
		Quaternionf quaternion2(1, 2, 3, 4);
		quaternion1 -= quaternion2;
		EXPECT_EQ(quaternion1.X(), 0);
		EXPECT_EQ(quaternion1.Y(), 0);
		EXPECT_EQ(quaternion1.Z(), 0);
		EXPECT_EQ(quaternion1.W(), 0);
	}

	TEST(Quaternion, operatorMulEqual)
	{
		Quaternionf quaternion1(0.4431357f, 0.2080396f, -0.4884507f, 0.7223339f);
		Quaternionf quaternion2(0.4431357f, 0.2080396f, -0.4884507f, 0.7223339f);
		quaternion1 *= quaternion2;
		EXPECT_NEAR(quaternion1.X(), 0.6401839f, near);
		EXPECT_NEAR(quaternion1.Y(), 0.3005481f, near);
		EXPECT_NEAR(quaternion1.Z(), -0.705649f, near);
		EXPECT_NEAR(quaternion1.W(), 0.04353243, near);
	}

	TEST(Quaternion, operatorDivEqual)
	{
		Quaternionf quaternion1(0.4431357f, 0.2080396f, -0.4884507f, 0.7223339f);
		Quaternionf quaternion2(0.4431357f, 0.2080396f, -0.4884507f, 0.7223339f);
		quaternion1 /= quaternion2;
		EXPECT_NEAR(quaternion1.X(), 0.f, near);
		EXPECT_NEAR(quaternion1.Y(), 0.f, near);
		EXPECT_NEAR(quaternion1.Z(), 0.f, near);
		EXPECT_NEAR(quaternion1.W(), 1.f, near);
	}

	TEST(Quaternion, operatorEqual)
	{
		Quaternionf quaternion1(1, 2, 3, 4);
		Quaternionf quaternion2(1, 2, 3, 4);
		EXPECT_EQ(quaternion1, quaternion2);
	}

	TEST(Quaternion, operatorNotEqual)
	{
		Quaternionf quaternion1(1, 2, 3, 4);
		Quaternionf quaternion2(1, 2, 3, 5);
		EXPECT_NE(quaternion1, quaternion2);
	}

	TEST(Quaternion, operatorAddScalar)
	{
		Quaternionf quaternion1(1, 2, 3, 4);
		Quaternionf quaternion2 = quaternion1 + 1;
		EXPECT_EQ(quaternion2.X(), 2);
		EXPECT_EQ(quaternion2.Y(), 3);
		EXPECT_EQ(quaternion2.Z(), 4);
		EXPECT_EQ(quaternion2.W(), 5);
	}

	TEST(Quaternion, operatorSubScalar)
	{
		Quaternionf quaternion1(1, 2, 3, 4);
		Quaternionf quaternion2 = quaternion1 - 1;
		EXPECT_EQ(quaternion2.X(), 0);
		EXPECT_EQ(quaternion2.Y(), 1);
		EXPECT_EQ(quaternion2.Z(), 2);
		EXPECT_EQ(quaternion2.W(), 3);
	}

	TEST(Quaternion, operatorMulScalar)
	{
		Quaternionf quaternion1(1, 2, 3, 4);
		Quaternionf quaternion2 = quaternion1 * 2;
		EXPECT_EQ(quaternion2.X(), 2);
		EXPECT_EQ(quaternion2.Y(), 4);
		EXPECT_EQ(quaternion2.Z(), 6);
		EXPECT_EQ(quaternion2.W(), 8);
	}

	TEST(Quaternion, operatorDivScalar)
	{
		Quaternionf quaternion1(1, 2, 3, 4);
		Quaternionf quaternion2 = quaternion1 / 2;
		EXPECT_EQ(quaternion2.X(), 0.5);
		EXPECT_EQ(quaternion2.Y(), 1);
		EXPECT_EQ(quaternion2.Z(), 1.5);
		EXPECT_EQ(quaternion2.W(), 2);
	}

	TEST(Quaternion, operatorMultVector)
	{
		EulerAnglesf eulerAngles(0, 0, 0);
		Quaternionf quaternion1(eulerAngles);
		Vector3f vec = quaternion1 * Vector3f::Forward();
		EXPECT_EQ(vec, Vector3f::Forward());
	}

	TEST(Quaternion, Normalize)
	{
		EulerAnglesf eulerAngles(45, 50, 78);
		Quaternionf quaternion1(eulerAngles);
		quaternion1.Normalize();
		EXPECT_NEAR(1.f, quaternion1.Length(), near);
	}

	TEST(Quaternion, ToEulerAngles)
	{
		Quaternionf q1(EulerAnglesf(0, 0, 0));
		EulerAnglesf angles1 = q1.ToEulerAngles();
		EXPECT_NEAR(angles1.Pitch(), 0, near);
		EXPECT_NEAR(angles1.Yaw(), 0, near);
		EXPECT_NEAR(angles1.Roll(), 0, near);

		Quaternionf q2(EulerAnglesf(30, 25, 68));
		EulerAnglesf angles2 = q2.ToEulerAngles();
		EXPECT_NEAR(angles2.Pitch(), 30.f, near);
		EXPECT_NEAR(angles2.Yaw(), 25.f, near);
		EXPECT_NEAR(angles2.Roll(), 68.f, near);
	}

	TEST(Quaternion, ToRotationMatrix)
	{
		//results calculated from https://www.andre-gaschler.com/rotationconverter/
		//Angles are expressed in radians
		auto matrix1 = Quaternionf(-0.122257f, 0.4018732f, -0.9020968f, -0.0988561f).ToRotationMatrix<Matrix4f>();
		constexpr Matrix4f expected(
			-0.9505614f, -0.2766193f, 0.1411200f, 0.f,
			0.0800920f, -0.6574507f, -0.7492288f, 0.f,
			0.3000306f, -0.7008854f, 0.6471023f, 0.f,
			 0.f, 0.f, 0.f, 1.f
		);

		const auto* matData= matrix1.Data();
		const auto* expectData = expected.Data();
		for (std::size_t i = 0; i < matrix1.GetSize(); ++i)
		{
			EXPECT_NEAR(matData[i], expectData[i], near);
		}
	}
}// namespace CCT_ANONYMOUS_NAMESPACE