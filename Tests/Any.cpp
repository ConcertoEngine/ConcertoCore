//
// Created by arthur on 16/11/2023.
//

#include <cstring>
#include <memory>

#include <gtest/gtest.h>

#include <Concerto/Core/Any.hpp>

namespace CCT_ANONYMOUS_NAMESPACE
{
	using namespace cct;

	TEST(Any, MakeAnyFunc)
	{
		Any erasedType = Any::Make<int>(6);
		const int& value = erasedType.As<const int&>();
		EXPECT_EQ(value, 6);
		EXPECT_TRUE(erasedType.HasValue());
		using Pointer = std::unique_ptr<char*, std::function<void(char**)>>;

		std::string string = "Hello this is a testing string";
		char* str = string.data();
		Pointer ptr(&str, [&](char**) {
			std::memset(str, 'W', string.size());
			});

		Any erasedType2 = Any::Make<Pointer>(std::move(ptr));
		auto& value2 = erasedType2.As<const Pointer&>();
		EXPECT_EQ(*value2, str);
	}

	TEST(Any, Emtpty)
	{
		Any empty;
		EXPECT_EQ(empty.HasValue(), false);
		EXPECT_THROW(empty.As<int>(), std::bad_cast);

		empty = Any::Make<int>(42);
		EXPECT_TRUE(empty.HasValue());
		empty.Reset();
		EXPECT_FALSE(empty.HasValue());
	}
} // namespace CCT_ANONYMOUS_NAMESPACE