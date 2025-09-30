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
namespace CCT_ANONYMOUS_NAMESPACE
{
	TEST(TypeInfo, TypeName)
	{
		{
			constexpr auto typeName = cct::TypeName<int>();
			ASSERT_EQ(typeName, "int");
		}
		{
			constexpr auto typeName = cct::TypeName<std::shared_ptr<float>>();
			ASSERT_EQ(typeName, "std::shared_ptr<float>");
		}
		{
			constexpr auto typeName  = cct::TypeName<EnumClass>();
			ASSERT_EQ(typeName, "EnumClass");
		}
		{
			constexpr auto typeName = cct::TypeName<EnumStruct>();
			ASSERT_EQ(typeName, "EnumStruct");
		}
		{
			constexpr auto typeName = cct::TypeName<Class>();
			ASSERT_EQ(typeName, "Class");
		}
		{
			constexpr auto typeName = cct::TypeName<Struct>();
			ASSERT_EQ(typeName, "Struct");
		}
	}
}// namespace CCT_ANONYMOUS_NAMESPACE