//
// Created by arthur on 10/08/2023.
//

#include <gtest/gtest.h>
#include <Concerto/Core/Math/Transform.hpp>

namespace CONCERTO_ANONYMOUS_NAMESPACE
{
	using namespace Concerto;
	using namespace Concerto;

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
}// namespace CONCERTO_ANONYMOUS_NAMESPACE