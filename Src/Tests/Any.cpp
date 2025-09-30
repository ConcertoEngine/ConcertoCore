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
		EXPECT_TRUE(erasedType.HasValue());
		EXPECT_TRUE(erasedType.Is<int>());
		const int value = erasedType.As<int>();
		EXPECT_EQ(value, 6);
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

	TEST(Any, Move)
	{
		Any erasedType = Any::Make<int>(6);
		Any other(std::move(erasedType));
		EXPECT_TRUE(other.HasValue());
		EXPECT_TRUE(other.Is<int>());
		EXPECT_EQ(other.As<int>(), 6);
	}

	TEST(Any, Pointer)
	{
		//Try with int*
		{
			auto ptr = std::make_unique<int>(6);
			Any any = Any::Make<int*>(ptr.get());

			EXPECT_TRUE(any.HasValue());
			EXPECT_TRUE(any.Is<int*>());
			EXPECT_EQ(any.As<int*>(), ptr.get());
			{
				const int* value = any.As<const int*>();
				EXPECT_EQ(value, ptr.get());
			}
			{
				int* value = any.As<int*>();
				EXPECT_EQ(value, ptr.get());
			}
		}
		//Try with void*
		{
			auto ptr = std::make_unique<int>(6);
			Any any = Any::Make<void*>(ptr.get());

			EXPECT_TRUE(any.HasValue());
			EXPECT_TRUE(any.Is<void*>());
			EXPECT_EQ(any.As<void*>(), ptr.get());
			{
				const void* value = any.As<const void*>();
				EXPECT_EQ(value, ptr.get());
			}
			{
				void* value = any.As<void*>();
				EXPECT_EQ(value, ptr.get());
			}
		}
	}

	TEST(Any, Reference)
	{
		Any any = Any::Make<int>(6);

		EXPECT_TRUE(any.HasValue());
		EXPECT_TRUE(any.Is<int>());
		EXPECT_EQ(any.As<int>(), 6);
		{
			const int& value = any.As<const int&>();
			EXPECT_EQ(value, 6);
		}
		{
			int& value = any.As<int&>();
			EXPECT_EQ(value, 6);
		}
	}
} // namespace CCT_ANONYMOUS_NAMESPACE