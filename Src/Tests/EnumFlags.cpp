//
// Created by Arthur on 06/10/2025.
//

#include <gtest/gtest.h>

#include <Concerto/Core/EnumFlags/EnumFlags.hpp>

enum class MyFlags : unsigned
{
	None = 0u,
	A = 1u << 0,
	B = 1u << 1,
	C = 1u << 2,
};
CCT_ENABLE_ENUM_FLAGS(MyFlags)

namespace CCT_ANONYMOUS_NAMESPACE
{
	using namespace cct;

	TEST(EnumFlags, BasicOrAndContains)
	{
		auto f = MyFlags::A | MyFlags::B;
		EXPECT_TRUE(f.Contains(MyFlags::A));
		EXPECT_TRUE(f.Contains(MyFlags::B));
		EXPECT_FALSE(f.Contains(MyFlags::C));

		auto g = f & MyFlags::A;
		EXPECT_TRUE(g.Contains(MyFlags::A));
		EXPECT_FALSE(g.Contains(MyFlags::B));
		EXPECT_FALSE(g.Contains(MyFlags::C));

		EXPECT_TRUE(static_cast<bool>(f));
		EXPECT_FALSE(static_cast<bool>(EnumFlags<MyFlags>{}));
	}

	TEST(EnumFlags, XorToggleReset)
	{
		EnumFlags<MyFlags> f = MyFlags::A;
		f ^= MyFlags::B;
		EXPECT_TRUE(f.Contains(MyFlags::B));
		f.Toggle(MyFlags::A);
		EXPECT_FALSE(f.Contains(MyFlags::A));
		f.Set(MyFlags::C);
		EXPECT_TRUE(f.Contains(MyFlags::C));
		f.Reset(MyFlags::B);
		EXPECT_FALSE(f.Contains(MyFlags::B));
	}

	TEST(EnumFlags, UnaryNotAndClear)
	{
		EnumFlags<MyFlags> f = MyFlags::A | MyFlags::B;
		auto notA = ~EnumFlags<MyFlags>(MyFlags::A);
		auto masked = notA & MyFlags::A;
		EXPECT_TRUE(masked.None());

		f.Clear();
		EXPECT_TRUE(f.None());
		EXPECT_FALSE(f.Any());
	}

	TEST(EnumFlags, RawValue)
	{
		EnumFlags<MyFlags> f = MyFlags::A | MyFlags::C;
		using U = EnumFlags<MyFlags>::Underlying;
		EXPECT_EQ(f.Value(), static_cast<U>(static_cast<U>(MyFlags::A) | static_cast<U>(MyFlags::C)));
	}
}
