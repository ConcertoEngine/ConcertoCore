//
// Created by arthur on 25/05/22.
//

#ifndef CONCERTO_LOGGER_HPP
#define CONCERTO_LOGGER_HPP

#include <iostream>
#include <version>
#include <stdexcept>
#include <source_location>

#include "Concerto/Core/Types.hpp"

namespace Concerto
{
    namespace Terminal::Color {
        static constexpr auto DEFAULT = "\x1B[0m";
        static constexpr auto RED = "\x1B[31m";
        static constexpr auto GREEN = "\x1B[32m";
        static constexpr auto YELLOW = "\x1B[33m";
        static constexpr auto BLUE = "\x1B[34m";
        static constexpr auto MAGENTA = "\x1B[35m";
        static constexpr auto CYAN = "\x1B[36m";
    }// namespace Terminal::Color
	class CONCERTO_PUBLIC_API Logger
    {
        public:
            enum class LogLevel {
                Debug,
                Info,
                Warning,
                Error
            };

        /**
        * @brief Log a message with the DEBUG level = INFO
        * @param message The message to Log
        */
        template<typename T>
        static void Info(const T& message)
        {
			Log(message, LogLevel::Info);
        }

        /**
        * @brief Log a message with the DEBUG level = DEBUG
        * @param message The message to Log
        */
        template<typename T>
        static void Debug(const T& message, const std::source_location& location = std::source_location::current())
        {
			Log(message, LogLevel::Debug, location);
        }

        /**
        * @brief Log a message with the DEBUG level = WARNING
        * @param message The message to Log
        */
        template<typename T>
        static void Warning(const T& message)
        {
			Log(message, LogLevel::Warning);
        }

        /**
        * @brief Log a message with the DEBUG level = ERROR
        * @param message The message to Log
        */
        template<typename T>
        static void Error(const T& message)
        {
			Log(message, LogLevel::Error);
			throw std::runtime_error(message);
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
                    std::cout << Terminal::Color::CYAN << "[D] " << location.function_name() << ":" << location.line() << " message: " << message << Terminal::Color::DEFAULT << std::endl;
                    break;
                case LogLevel::Info:
                    std::cout << Terminal::Color::GREEN << "[i] " << message << Terminal::Color::DEFAULT << std::endl;
                    break;
                case LogLevel::Warning:
                    std::cout << Terminal::Color::YELLOW << "[!] " << message << Terminal::Color::DEFAULT << std::endl;
                    break;
                case LogLevel::Error:
                    std::cerr << Terminal::Color::RED << "[X] " << message << Terminal::Color::DEFAULT << std::endl;
                    break;
            }
        }
    };
}
#endif //CONCERTO_LOGGER_HPP