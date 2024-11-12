//
// Created by arthur on 12/10/2023.
//

#include <memory>
#include <gtest/gtest.h>
#include <Concerto/Core/SparseVector.hpp>

namespace CONCERTO_ANONYMOUS_NAMESPACE
{
	using namespace cct;

	TEST(SparseVector, IntEmplace)
    {
        SparseVector<int> sparseVector;
        sparseVector.Emplace(5, 999);
        sparseVector.Emplace(100, 999);
        ASSERT_TRUE(sparseVector.Has(5));
        ASSERT_TRUE(sparseVector.Has(100));
        ASSERT_FALSE(sparseVector.Has(0));
        ASSERT_FALSE(sparseVector.Has(102));
        ASSERT_EQ(sparseVector[5], 999);
        ASSERT_EQ(sparseVector[100], 999);
        ASSERT_THROW(sparseVector[0], std::runtime_error);
        ASSERT_THROW(sparseVector[102], std::out_of_range);
    }

    TEST(SparseVector, HardToCopyEmplace)
    {
        using Ptr = std::unique_ptr<int>;
        class HardToCopy
        {
        public:
            HardToCopy() = default;
            HardToCopy(Ptr a, int b, int c) :
                _ptr(std::move(a)), _b(b), _c(c) {}
            HardToCopy(const HardToCopy&) = delete;
            HardToCopy(HardToCopy&&) = default;
            ~HardToCopy() = default;
            HardToCopy& operator=(const HardToCopy&) = delete;
            HardToCopy& operator=(HardToCopy&&) = default;
        private:
            Ptr _ptr;
            int _b;
            int _c;
        };
        SparseVector<HardToCopy> sparseVector;
        sparseVector.Emplace(0, HardToCopy());

        auto ptr = std::make_unique<int>(5);
        sparseVector.Emplace(1, std::move(ptr), 2, 3);
    }

    TEST(SparseVector, DefaultConstructor)
    {
        SparseVector<int> sparseVector;
        ASSERT_FALSE(sparseVector.Has(0));
        ASSERT_FALSE(sparseVector.Has(1));
        ASSERT_FALSE(sparseVector.Has(2));
    }

    TEST(SparseVector, CopyConstructor)
    {
        SparseVector<int> sparseVector1;
        sparseVector1.Emplace(0, 1);
        sparseVector1.Emplace(1, 2);
        sparseVector1.Emplace(2, 3);

        SparseVector<int> sparseVector2(sparseVector1);
        ASSERT_TRUE(sparseVector2.Has(0));
        ASSERT_TRUE(sparseVector2.Has(1));
        ASSERT_TRUE(sparseVector2.Has(2));
        ASSERT_EQ(sparseVector2[0], 1);
        ASSERT_EQ(sparseVector2[1], 2);
        ASSERT_EQ(sparseVector2[2], 3);
    }

    TEST(SparseVector, MoveConstructor)
    {
        SparseVector<int> sparseVector1;
        sparseVector1.Emplace(0, 1);
        sparseVector1.Emplace(1, 2);
        sparseVector1.Emplace(2, 3);

        SparseVector<int> sparseVector2(std::move(sparseVector1));
        ASSERT_TRUE(sparseVector2.Has(0));
        ASSERT_TRUE(sparseVector2.Has(1));
        ASSERT_TRUE(sparseVector2.Has(2));
        ASSERT_EQ(sparseVector2[0], 1);
        ASSERT_EQ(sparseVector2[1], 2);
        ASSERT_EQ(sparseVector2[2], 3);
    }

    TEST(SparseVector, CopyAssignment)
    {
        SparseVector<int> sparseVector1;
        sparseVector1.Emplace(0, 1);
        sparseVector1.Emplace(1, 2);
        sparseVector1.Emplace(2, 3);

        SparseVector<int> sparseVector2;
        sparseVector2 = sparseVector1;
        ASSERT_TRUE(sparseVector2.Has(0));
        ASSERT_TRUE(sparseVector2.Has(1));
        ASSERT_TRUE(sparseVector2.Has(2));
        ASSERT_EQ(sparseVector2[0], 1);
        ASSERT_EQ(sparseVector2[1], 2);
        ASSERT_EQ(sparseVector2[2], 3);
    }

    TEST(SparseVector, MoveAssignment)
    {
        SparseVector<int> sparseVector1;
        sparseVector1.Emplace(0, 1);
        sparseVector1.Emplace(1, 2);
        sparseVector1.Emplace(2, 3);

        SparseVector<int> sparseVector2;
        sparseVector2 = std::move(sparseVector1);
        ASSERT_TRUE(sparseVector2.Has(0));
        ASSERT_TRUE(sparseVector2.Has(1));
        ASSERT_TRUE(sparseVector2.Has(2));
        ASSERT_EQ(sparseVector2[0], 1);
        ASSERT_EQ(sparseVector2[1], 2);
        ASSERT_EQ(sparseVector2[2], 3);
    }

    TEST(SparseVector, Clear)
    {
        SparseVector<int> sparseVector;
        sparseVector.Emplace(0, 1);
        sparseVector.Emplace(1, 2);
        sparseVector.Emplace(2, 3);

        sparseVector.Clear();
        ASSERT_FALSE(sparseVector.Has(0));
        ASSERT_FALSE(sparseVector.Has(1));
        ASSERT_FALSE(sparseVector.Has(2));
    }

    TEST(SparseVector, Erase)
    {
        SparseVector<int> sparseVector;
        sparseVector.Emplace(0, 1);
        sparseVector.Emplace(1, 2);
        sparseVector.Emplace(2, 3);

        sparseVector.Erase(1);
        ASSERT_TRUE(sparseVector.Has(0));
        ASSERT_FALSE(sparseVector.Has(1));
        ASSERT_TRUE(sparseVector.Has(2));
        ASSERT_EQ(sparseVector[0], 1);
        ASSERT_EQ(sparseVector[2], 3);
    }

    TEST(SparseVector, Iterator)
    {
        SparseVector<int> sparseVector;
        sparseVector.Emplace(0, 1);
        sparseVector.Emplace(1, 2);
        sparseVector.Emplace(2, 3);

        int i = 0;
        for (auto& value : sparseVector)
        {
            ASSERT_EQ(value, i + 1);
            i++;
        }

		i = 0;
        for (const auto& value : sparseVector)
        {
            ASSERT_EQ(value, i + 1);
            i++;
        }
    }	
}