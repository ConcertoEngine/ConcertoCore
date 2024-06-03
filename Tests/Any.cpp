//
// Created by arthur on 16/11/2023.
//

#include <cstring>
#include <memory>

#include <gtest/gtest.h>

#include <Concerto/Core/Any.hpp>

namespace CONCERTO_ANONYMOUS_NAMESPACE
{
	using namespace Concerto;

	TEST(Any, MakeAnyFunc)
	{
		Any erasedType = Any::Make<int>(6);
		const int& value = erasedType.As<const int&>();
		EXPECT_EQ(value, 6);
		using Pointer = std::unique_ptr<char*, std::function<void(char**)>>;

		std::string string = "Hello this is a testing string";
		char* str = string.data();
		Pointer ptr(&str, [&](char** ptr) {
			std::memset(str, 'W', string.size());
			});

		Any erasedType2 = Any::Make<Pointer>(std::move(ptr));
		auto& value2 = erasedType2.As<const Pointer&>();
		EXPECT_EQ(*value2, str);
	}
} // namespace CONCERTO_ANONYMOUS_NAMESPACE