//
// Created by arthur on 24/12/2023.
//

#include <gtest/gtest.h>
#include <memory>
#include <Concerto/Core/TypeInfo.hpp>

enum class EnumClass{};
enum struct EnumStruct{};
class Class{};
struct Struct{};
namespace CONCERTO_ANONYMOUS_NAMESPACE
{
	TEST(TypeInfo, TypeName)
	{
		{
			constexpr auto typeName = Concerto::TypeName<int>();
			ASSERT_EQ(typeName, "int");
		}
		{
			constexpr auto typeName = Concerto::TypeName<std::shared_ptr<float>>();
			ASSERT_EQ(typeName, "std::shared_ptr<float>");
		}
		{
			constexpr auto typeName  = Concerto::TypeName<EnumClass>();
			ASSERT_EQ(typeName, "EnumClass");
		}
		{
			constexpr auto typeName = Concerto::TypeName<EnumStruct>();
			ASSERT_EQ(typeName, "EnumStruct");
		}
		{
			constexpr auto typeName = Concerto::TypeName<Class>();
			ASSERT_EQ(typeName, "Class");
		}
		{
			constexpr auto typeName = Concerto::TypeName<Struct>();
			ASSERT_EQ(typeName, "Struct");
		}
	}
}// namespace CONCERTO_ANONYMOUS_NAMESPACE