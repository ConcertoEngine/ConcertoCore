//
// Created by arthur on 21/12/2023.
//

#ifndef CONCERTO_CORE_ASSERT_HPP
#define CONCERTO_CORE_ASSERT_HPP

#include "Concerto/Core/Logger.hpp"

#if defined(CONCERTO_DEBUG)
#define CONCERTO_ASSERT(expression, fmt, ...)						    \
	do																	\
	{																	\
		if (Concerto::IsDebuggerAttached())								\
		{																\
			if (!(expression))											\
			{															\
				Concerto::Logger::Debug(fmt __VA_OPT__(,) __VA_ARGS__); \
				CONCERTO_BREAK_IN_DEBUGGER;								\
			}															\
		}																\
		else if (!(expression))											\
		{																\
			Concerto::Logger::Debug(fmt __VA_OPT__(,) __VA_ARGS__);		\
		}																\
	} while (false)
#else
#define CONCERTO_ASSERT(expression, fmt, ...) ((void)0)
#endif

#define CONCERTO_ASSERT_FALSE(fmt, ...) CONCERTO_ASSERT(false, fmt __VA_OPT__(,) __VA_ARGS__)

#endif//CONCERTO_CORE_ASSERT_HPP
