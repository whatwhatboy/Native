#include "Logger.h"

namespace Base {
	Logger::Logger() {
		AllocConsole();
		SetConsoleTitleA("Native");

		FILE* stream;
		freopen_s(&stream, "CONOUT$", "w", stdout);

		m_Console.open("CONOUT$");
		SetConsoleMode(GetStdHandle(-11), ENABLE_PROCESSED_OUTPUT | ENABLE_WRAP_AT_EOL_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

		m_FilePath.append("C:\\Native\\log.txt");

		m_File.open(m_FilePath, std::ios_base::out | std::ios_base::trunc);
		m_File.clear();
	}
	Logger::~Logger() {
		fclose(stdout);
		FreeConsole();
		m_Console.clear();
		m_FilePath.clear();
		m_Console.close();
		m_File.close();
	}
}
