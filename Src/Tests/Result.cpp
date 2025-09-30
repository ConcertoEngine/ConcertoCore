//
// Created by arthur on 09/12/2024.
//

#include <string>

#include <gtest/gtest.h>
#include <Concerto/Core/Types/Types.hpp>
#include <Concerto/Core/Result/Result.hpp>

namespace CCT_ANONYMOUS_NAMESPACE
{
	using namespace cct;
	class Bar
	{
	public:
		Bar() : a(0), b(false), c(0) {}
		Bar(Int32 aa, bool bb, Int32 cc) : a(aa), b(bb), c(cc) {}

		Int32 a;
		bool b;
		Int32 c;
	};

	TEST(Result, ValueContruction)
	{
		Result<Int32, std::string> result(28);
		ASSERT_TRUE(result.IsOk());
		ASSERT_FALSE(result.IsError());
		ASSERT_EQ(result.GetValue(), 28);
	}

	TEST(Result, ErrorConstruction)
	{
		Result<Int32, std::string> result(std::string("Foo"));
		ASSERT_FALSE(result.IsOk());
		ASSERT_TRUE(result.IsError());
		ASSERT_EQ(result.GetError(), "Foo");
	}

	TEST(Result, ValueVariadicConstruction)
	{
		Result<Bar, std::string> result(std::in_place_type_t<Bar>(), 1, true, 2);

		ASSERT_TRUE(result.IsOk());
		ASSERT_FALSE(result.IsError());
		auto value = result.GetValue();
		ASSERT_EQ(value.a, 1);
		ASSERT_EQ(value.b, true);
		ASSERT_EQ(value.c, 2);
	}

	TEST(Result, ErrorVariadicConstruction)
	{
		Result<std::string, Bar> result(std::in_place_type_t<Bar>(), 1, true, 2);

		ASSERT_FALSE(result.IsOk());
		ASSERT_TRUE(result.IsError());
		auto value = result.GetError();
		ASSERT_EQ(value.a, 1);
		ASSERT_EQ(value.b, true);
		ASSERT_EQ(value.c, 2);
	}

	TEST(Result, VoidTemplateSpecialisation)
	{
		Result<void, Bar> result(std::in_place_type_t<Bar>(), 1, true, 2);

		ASSERT_FALSE(result.IsOk());
		ASSERT_TRUE(result.IsError());
		auto value = result.GetError();
		ASSERT_EQ(value.a, 1);
		ASSERT_EQ(value.b, true);
		ASSERT_EQ(value.c, 2);
	}
} // namespace CCT_ANONYMOUS_NAMESPACE