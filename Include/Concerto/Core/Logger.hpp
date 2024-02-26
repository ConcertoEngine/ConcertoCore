//
// Created by arthur on 25/05/22.
//

#ifndef CONCERTO_CORE_LOGGER_HPP
#define CONCERTO_CORE_LOGGER_HPP

#include <format>
#include <iostream>
#include <source_location>

#include "Concerto/Core/Types.hpp"

namespace Concerto
{
	namespace Terminal::Color
	{
		static constexpr auto DEFAULT = "\x1B[0m";
		static constexpr auto RED = "\x1B[31m";
		static constexpr auto GREEN = "\x1B[32m";
		static constexpr auto YELLOW = "\x1B[33m";
		static constexpr auto BLUE = "\x1B[34m";
		static constexpr auto MAGENTA = "\x1B[35m";
		static constexpr auto CYAN = "\x1B[36m";
	}// namespace Terminal::Color
	class CONCERTO_CORE_PUBLIC_API Logger
	{
	 public:
		enum class LogLevel
		{
			Debug,
			Info,
			Warning,
			Error
		};

		/**
	    * @brief Log a message with the DEBUG level = INFO
	    * @param fmt The format of the message to Log
	    * @param args The arguments of the message to Log
	    */
		template<typename... Types>
		static void Info(const std::format_string<Types...> fmt, Types&&... args)
		{
			Log(std::format(std::move(fmt), std::forward<Types>(args)...), LogLevel::Info);
		}

		/**
	    * @brief Log a message with the DEBUG level = DEBUG
	    * @param fmt The format of the message to Log
	    * @param args The arguments of the message to Log
	    */
		template<typename... Types>
		static void Debug(const std::format_string<Types...> fmt, Types&&... args, const std::source_location& location = std::source_location::current())
		{
			Log(std::format(std::move(fmt), std::forward<Types>(args)...), LogLevel::Debug, location);
		}

		/**
	    * @brief Log a message with the DEBUG level = WARNING
	    * @param fmt The format of the message to Log
	    * @param args The arguments of the message to Log
	    */
		template<typename... Types>
		static void Warning(const std::format_string<Types...> fmt, Types&&... args)
		{
			Log(std::format(std::move(fmt), std::forward<Types>(args)...), LogLevel::Warning);
		}

		/**
	    * @brief Log a message with the DEBUG level = ERROR
		* @param fmt The format of the message to Log
	    * @param args The arguments of the message to Log
	    */
		template<typename... Types>
		static void Error(const std::format_string<Types...> fmt, Types&&... args)
		{
			Log(std::format(std::move(fmt), std::forward<Types>(args)...), LogLevel::Error);
		}

		/**
	    * @brief Log a message
	    * @param level The level of the message
	    * @param message The message to Log
	    * @param location The location of the message
	    */
		template<typename T>
		static void Log(const T& message, LogLevel level, const std::source_location& location = std::source_location::current())
		{
			switch (level)
			{
			case LogLevel::Debug:
				std::cout << Terminal::Color::CYAN << location.function_name() << ":" << location.line() << " message: " << message << Terminal::Color::DEFAULT << std::endl;
				break;
			case LogLevel::Info:
				std::cout << Terminal::Color::GREEN << message << Terminal::Color::DEFAULT << std::endl;
				break;
			case LogLevel::Warning:
				std::cout << Terminal::Color::YELLOW << message << Terminal::Color::DEFAULT << std::endl;
				break;
			case LogLevel::Error:
				std::cerr << Terminal::Color::RED << message << Terminal::Color::DEFAULT << std::endl;
				break;
			}
		}
	};
}// namespace Concerto
#endif//CONCERTO_CORE_LOGGER_HPP