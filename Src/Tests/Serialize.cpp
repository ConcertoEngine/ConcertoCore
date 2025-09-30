//
// Created by arthur on 10/08/2023.
//

#include <gtest/gtest.h>
#include <Concerto/Core/Math/Transform/Transform.hpp>

namespace CCT_ANONYMOUS_NAMESPACE
{
	using namespace cct;
	using namespace cct;

	TEST(Serialize, Basics)
	{
		Vector3f location(10.f, 15.f, 20.f);
		Quaternion rotation = EulerAngles(20.f, 30.f, 40.f).ToQuaternion();
		Vector3f scale(10.f, 20.f, 30.f);
		Transform transform(location, rotation, scale);
		
		Stream stream;
		transform.Serialize(stream);
		
		stream.SetCursorPos(0);
		Transform result;
		result.Deserialize(stream);

		ASSERT_EQ(transform, result);
	}
}// namespace CCT_ANONYMOUS_NAMESPACE