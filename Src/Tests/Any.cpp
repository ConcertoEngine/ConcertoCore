//
// Created by Arthur on 08/10/2025.
//

#include <gtest/gtest.h>

#include <Concerto/Core/Any/Any.hpp>
#include <Concerto/Core/TypeInfo/TypeInfo.hpp>

namespace CCT_ANONYMOUS_NAMESPACE
{
    using namespace cct;

    struct Big
    {
        Big() = default;
        explicit Big(int v) : x(v) {}
        int x = 0;
        std::array<char, 64> buf{}; // ensure > small buffer
    };

    TEST(Any, SmallValue)
    {
        auto a = Any::Make<int>(42);
        ASSERT_TRUE(a.HasValue());
        ASSERT_TRUE(a.Is<int>());
        ASSERT_FALSE(a.Is<float>());
        EXPECT_EQ(a.As<int>(), 42);

        a.Reset();
        EXPECT_FALSE(a.HasValue());
    }

    TEST(Any, LargeValue)
    {
        Big b(99);
        auto a = Any::Make<Big>(b);
        ASSERT_TRUE(a.HasValue());
        ASSERT_TRUE(a.Is<Big>());
        auto v = a.As<Big>();
        EXPECT_EQ(v.x, 99);
    }

    TEST(Any, Pointer)
    {
        int v = 5;
        auto a = Any::Make<int*>(&v);
        ASSERT_TRUE(a.HasValue());
        ASSERT_TRUE(a.Is<int*>());
        int* p = a.As<int*>();
        *p = 11;
        EXPECT_EQ(v, 11);
    }

    TEST(Any, Reference)
    {
        int v = 7;
        auto a = Any::Make<int&>(v);
        ASSERT_TRUE(a.HasValue());
        ASSERT_TRUE(a.Is<int&>());
        int& r = a.As<int&>();
        r = 15;
        EXPECT_EQ(v, 15);
    }

    TEST(Any, WrongCastThrows)
    {
        auto a = Any::Make<int>(3);
        ASSERT_TRUE(a.Is<int>());
        EXPECT_THROW((void)a.As<float>(), std::bad_cast);
    }
}

