#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <Windows.h>
#include "src/utility/common/common.h"
namespace Base {
	enum class eLogColor : uint16_t {
		Black = 0,
		DarkBlue = FOREGROUND_BLUE,
		DarkGreen = FOREGROUND_GREEN,
		DarkCyan = FOREGROUND_GREEN | FOREGROUND_BLUE,
		DarkRed = FOREGROUND_RED,
		DarkMagneta = FOREGROUND_RED | FOREGROUND_BLUE,
		DarkYellow = FOREGROUND_RED | FOREGROUND_GREEN,
		DarkGray = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		Gray = FOREGROUND_INTENSITY,
		Blue = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
		Green = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
		Cyan = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
		Red = FOREGROUND_INTENSITY | FOREGROUND_RED,
		Magneta = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
		Yellow = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
		White = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		Grey = FOREGROUND_INTENSITY,
		LightRed = Red | FOREGROUND_INTENSITY,
		LightGreen = Green | FOREGROUND_INTENSITY,
		LightBlue = Blue | FOREGROUND_INTENSITY
	};

	inline eLogColor operator|(eLogColor a, eLogColor b) {
		return static_cast<eLogColor>(static_cast<std::underlying_type_t<eLogColor>>(a) | static_cast<std::underlying_type_t<eLogColor>>(b));
	}

	enum class eLogType : uint8_t {
		Info,
		Warn,
		Fatal,
		Exception,
		Registers,
		Stackwalker,
		Detours,
		Success
	};

	namespace forgound_color
	{
		enum Code
		{
			Default = 0,
			Generic = 243,
			Success = 84,
			Error = 196,
			Warning = 3,
			Developer = 26,
		};

		inline std::ostream& operator<<(std::ostream& os, Code code)
		{
			return os << "\033[38;5;" << static_cast<int>(code) << "m";
		}
	}

	namespace background_color
	{
		enum code2
		{
			Default = 0,
			Generic = 243,
			Success = 84,
			Error = 196,
			Warning = 3,
			Developer = 26,
		};

		inline std::ostream& operator<<(std::ostream& os, code2 code)
		{
			return os << "\033[48;5;" << static_cast<int>(code) << "m";
		}
	}
	class Logger {
	public:
		Logger();
		~Logger();

		template <typename... arguments>
		void DirectSend(int col, std::string type, std::string fmt, arguments... args) {
			std::string msg{ std::format("[{}] {}", type, std::vformat(fmt, std::make_format_args(args...))) };
			std::cout << background_color::code2(col) << " " << background_color::Default << forgound_color::Code(col) << " " << msg << std::endl;
			m_File << msg << std::endl;
		}


		template <typename... arguments>
		void Send(eLogType type, std::string fmt, arguments... args) {
			switch (type) {
			case eLogType::Info: {
				this->DirectSend<arguments...>(forgound_color::Generic, "Info", fmt, args...);
			} break;
			case eLogType::Warn: {
				this->DirectSend<arguments...>(forgound_color::Warning, "Warn", fmt, args...);
			} break;
			case eLogType::Fatal: {
				this->DirectSend<arguments...>(forgound_color::Error, "Fatal", fmt, args...);
			} break;
			case eLogType::Exception: {
				this->DirectSend<arguments...>(forgound_color::Error, "Exception", fmt, args...);
			} break;
			case eLogType::Registers: {
				this->DirectSend<arguments...>(forgound_color::Generic, "Registers", fmt, args...);
			} break;
			case eLogType::Stackwalker: {
				this->DirectSend<arguments...>(forgound_color::Error, "StackWalker", fmt, args...);
			} break;
			case eLogType::Detours: {
				this->DirectSend<arguments...>(forgound_color::Error, "Hooking", fmt, args...);
			} break;
			case eLogType::Success: {
				this->DirectSend<arguments...>(forgound_color::Success, "Success", fmt, args...);
			} break;
			default: {
			} break;
			}
		}

		std::string ReadLine() {
			std::string input;
			std::getline(m_Input, input);
			return input;
		}

	private:
		std::filesystem::path m_FilePath;
		std::ofstream m_File;
		std::ofstream m_Console;
		std::ifstream m_Input;
	};

	inline std::unique_ptr<Logger> g_logger;
}

#define LOG(type, fmt, ...) Base::g_logger->Send(Base::eLogType::type, fmt, __VA_ARGS__)
#define HEX_TO_UPPER(value) "0x" << std::hex << std::uppercase << (DWORD64)value << std::dec << std::nouppercase
#define logNow(type, fmt, ...) Base::g_logger->Send(Base::eLogType::type, fmt, __VA_ARGS__)



// Example usage:
// std::string userToken;
// LOG(Info, "Enter your user token: ");
// userToken = Base::g_logger->ReadLine();
