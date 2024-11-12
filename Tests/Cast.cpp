//
// Created by arthur on 08/08/2024.
//

#include <string_view>

#include <gtest/gtest.h>

#include <Concerto/Core/Cast.hpp>

namespace CONCERTO_ANONYMOUS_NAMESPACE
{
	using namespace cct;

	constexpr std::string_view BaseStr = "Base";
	constexpr std::string_view DerivedStr = "Derived";

	class Base {
	public:
		virtual ~Base() = default;
		virtual std::string_view Speak() const {
			return BaseStr;
		}
	};

	class Derived : public Base {
	public:
		std::string_view Speak() const override {
			return DerivedStr;
		}
	};

	TEST(CastTest, ValidCast) {
		Derived derived;
		Base& base = derived;

		Derived& casted = Cast<Derived&>(base);

		EXPECT_EQ(casted.Speak(), DerivedStr);
	}

	TEST(CastTest, RvalueCast) {
		Derived derived;
		Base&& base = std::move(derived);

		Derived&& casted = Cast<Derived&&>(std::move(base));

		EXPECT_EQ(casted.Speak(), DerivedStr);
	}

	TEST(CastTest, ConstReferenceCast) {
		const Derived derived;
		const Base& base = derived;
		auto& casted = Cast<const Derived&>(base);

		EXPECT_EQ(casted.Speak(), DerivedStr);
	}
}
