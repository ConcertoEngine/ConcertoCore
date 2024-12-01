//
// Created by arthur on 02/06/2024.
//

#include <gtest/gtest.h>
#include <Concerto/Core/DynLib.hpp>

#ifdef CCT_PLATFORM_POSIX
#define PREFIX "lib"
#else
#define PREFIX ""
#endif

namespace CCT_ANONYMOUS_NAMESPACE
{
	TEST(DynLib, Load)
	{
		cct::DynLib lib;
		bool res = lib.Load(PREFIX"ConcertoCoreTestsDummyLib");
		ASSERT_EQ(res, true);

		lib.Invoke<void>("Dummy");
		const cct::FunctionRef func = lib.GetFunction<void>("Dummy");
		ASSERT_EQ(func.operator bool(), true);
		{
			const int value = lib.Invoke<int>("DummyInt");
			ASSERT_EQ(value, 42);
		}
		{
			const int* globalValue = lib.GetValue<int>("GlobalInt");
			if (globalValue == nullptr)
				FAIL();
			ASSERT_EQ(globalValue != nullptr, true);
			ASSERT_EQ(*globalValue, 42);
		}
		{
			const int* notExisting = lib.GetValue<int>("NotExisting");
			ASSERT_EQ(notExisting, nullptr);
		}
		{
			const int value = lib.Invoke<int>("Increment", 5);
			ASSERT_EQ(value, 5 + 1);
		}

		res = lib.Unload();
		ASSERT_EQ(res, true);
	}
} // namespace CCT_ANONYMOUS_NAMESPACE