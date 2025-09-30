//
// Created by arthur on 02/06/2024.
//

#include <gtest/gtest.h>
#include <Concerto/Core/DynLib/DynLib.hpp>

#ifdef CCT_PLATFORM_POSIX
#define PREFIX "lib"
#else
#define PREFIX ""
#endif

namespace CCT_ANONYMOUS_NAMESPACE
{
	TEST(DynLib, Invoke)
	{
		cct::DynLib lib;
		bool res = lib.Load(PREFIX"concerto-core-dummy");
		EXPECT_TRUE(res);

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
		{
			ASSERT_THROW(lib.Invoke<int>("NotExisting", 5), std::runtime_error);
		}

		res = lib.Unload();
		ASSERT_EQ(res, true);
	}

	TEST(DynLib, Loading)
	{
		cct::DynLib lib;
		EXPECT_FALSE(lib.Unload());
		bool res = lib.Load(PREFIX"not-exist");
		EXPECT_FALSE(res);
		EXPECT_EQ(lib.GetSymbol("foo"), nullptr);

		res = lib.Load(PREFIX"concerto-core-dummy");
		EXPECT_TRUE(res);
	}
} // namespace CCT_ANONYMOUS_NAMESPACE