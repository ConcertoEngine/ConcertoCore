//
// Created by arthur on 17/06/2022.
//

#include <gtest/gtest.h>
#include <Concerto/Core/Logger.hpp>

int main(int argc, char** argv)
{
	cct::Logger::Info("Begin InitGoogleTest");
	::testing::InitGoogleTest(&argc, argv);
	cct::Logger::Info("End InitGoogleTest");
	cct::Logger::Info("Begin RUN_ALL_TESTS");
	try
	{
		const auto ret = RUN_ALL_TESTS();
		cct::Logger::Info("End RUN_ALL_TESTS returned: {}", ret);
		return ret;
	}
	catch (const std::exception& e)
	{
		cct::Logger::Info("End RUN_ALL_TESTS throwed: {}", e.what());
	}
	catch (...)
	{
		cct::Logger::Info("End RUN_ALL_TESTS throwed unknown exception");
	}
	return 254;
}