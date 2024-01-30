//
// Created by arthur on 22/02/2023.
//

#include <gtest/gtest.h>
#include <fstream>
#include "Concerto/Core/StructuredData.hpp"

namespace CONCERTO_ANONYMOUS_NAMESPACE
{
	using namespace Concerto;

	TEST(StructuredData, Constructor)
	{
		try
		{
			StructuredData data("./goodConfig.json");
			const auto& config = data.GetConfig();
			ASSERT_EQ(config["Test1"].As<Int32>(), 1);
			ASSERT_EQ(config["Test2"].AsString(), "teststring");
			ASSERT_EQ(config["Test3"]["Test4"].As<Int32>(), 2);
			ASSERT_EQ(config["Test3"]["Test5"].AsString(), "teststring2");
			ASSERT_EQ(config["Test6"][0]["Test7"].As<Int32>(), 3);
			ASSERT_EQ(config["Test6"][0]["Test8"].AsString(), "teststring3");
			ASSERT_EQ(config["Test6"][1]["Test7"].As<Int32>(), 4);
			ASSERT_EQ(config["Test6"][1]["Test8"].AsString(), "teststring4");
		}
		catch (const std::exception& e)
		{
			FAIL() << e.what();
		}
	}

	TEST(StructuredData, ifstreamConstructor)
	{
		try
		{
			std::ifstream file("./goodConfig.json");
			StructuredData data(file);
			const auto& config = data.GetConfig();
			ASSERT_EQ(config["Test1"].As<Int32>(), 1);
			ASSERT_EQ(config["Test2"].AsString(), "teststring");
			ASSERT_EQ(config["Test3"]["Test4"].As<Int32>(), 2);
			ASSERT_EQ(config["Test3"]["Test5"].AsString(), "teststring2");
			ASSERT_EQ(config["Test6"][0]["Test7"].As<Int32>(), 3);
			ASSERT_EQ(config["Test6"][0]["Test8"].AsString(), "teststring3");
			ASSERT_EQ(config["Test6"][1]["Test7"].As<Int32>(), 4);
			ASSERT_EQ(config["Test6"][1]["Test8"].AsString(), "teststring4");
		}
		catch (const std::exception& e)
		{
			FAIL() << e.what();
		}
	}

	TEST(StructuredData, BadConstructor)
	{
		ASSERT_THROW(StructuredData data("./badConfig.json"), std::runtime_error);
	}
}// namespace CONCERTO_ANONYMOUS_NAMESPACE