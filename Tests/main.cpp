//
// Created by arthur on 17/06/2022.
//

#include <gtest/gtest.h>
#include <Concerto/Core/Logger.hpp>

int main(int argc, char** argv)
{
	Concerto::Logger::Info("Begin InitGoogleTest");
	::testing::InitGoogleTest(&argc, argv);
	Concerto::Logger::Info("End InitGoogleTest");
	Concerto::Logger::Info("Begin RUN_ALL_TESTS");
	const auto ret = RUN_ALL_TESTS();
	Concerto::Logger::Info("End RUN_ALL_TESTS returned: {}", ret);
	return ret;
}