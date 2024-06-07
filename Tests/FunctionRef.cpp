//
// Created by arthur on 03/06/2024.
//

#include <gtest/gtest.h>
#include <string>
#include <Concerto/Core/FunctionRef.hpp>

namespace CONCERTO_ANONYMOUS_NAMESPACE
{
	void foo(int& value) { value = 42;}

	TEST(FunctionRef, HasValue)
	{
		Concerto::FunctionRef<void()> func;
		ASSERT_FALSE(func);
		auto lambda = []() {};
		func = lambda;
		ASSERT_TRUE(func);
	}

	TEST(FunctionRef, Lambda)
	{
		int value = 0;
		auto lambda = [&value]() {value = 42;};
		Concerto::FunctionRef<void()> func = lambda;
		func();
		ASSERT_EQ(value, 42);
	}

	TEST(FunctionRef, Function)
	{
		Concerto::FunctionRef<void(int&)> func = foo;
		int value = 0;
		func(value);
		ASSERT_EQ(value, 42);
	}

	TEST(FunctionRef, Args)
	{
		auto lambda = [](std::size_t& value, const std::string& str) {value = str.size();};
		Concerto::FunctionRef<void(std::size_t&, const std::string&)> func = lambda;
		std::size_t value = 0;
		std::string str = "Hello";
		func(value, str);
		ASSERT_EQ(value, str.size());
	}
} // namespace CONCERTO_ANONYMOUS_NAMESPACE