//
// Created by arthur on 02/06/2024.
//

#include <gtest/gtest.h>
#include <Concerto/Core/DynLib.hpp>

TEST(DynLib, Load)
{
	Concerto::DynLib lib;
	bool res = lib.Load("ConcertoCoreTestsDummyLib");
	ASSERT_TRUE(res);

	lib.Invoke<void>("Dummy");
	const int value = lib.Invoke<int>("DummyInt");
	ASSERT_EQ(value, 42);

	const int* globalValue = lib.GetValue<int>("GlobalInt");
	ASSERT_TRUE(globalValue != nullptr);
	ASSERT_EQ(*globalValue, 42);

	const int* notExisting = lib.GetValue<int>("NotExisting");
	ASSERT_EQ(notExisting, nullptr);

	res = lib.Unload();
	ASSERT_TRUE(res);
}