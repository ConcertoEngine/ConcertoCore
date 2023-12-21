//
// Created by arthur on 21/12/2023.
//

#ifndef CONCERTO_CORE_ASSERT_HPP
#define CONCERTO_CORE_ASSERT_HPP

#include "Concerto/Core/Logger.hpp"

#if defined(CONCERTO_DEBUG)
#define CONCERTO_ASSERT(expression)                                                            \
	{                                                                                          \
		if (Concerto::IsDebuggerAttached() && !(expression)) CONCERTO_BREAK_IN_DEBUGGER;       \
		else if (!(expression)) { Concerto::Logger::Debug("Assertion failed: " #expression); } \
	}
#else
#include <cassert>
#define CONCERTO_ASSERT(expression) assert(expression)
#endif

#define CONCERTO_ASSERT_FALSE CONCERTO_ASSERT(false)

#endif//CONCERTO_CORE_ASSERT_HPP
