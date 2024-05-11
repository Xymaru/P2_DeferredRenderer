#include "Debug.h"

#include <iostream>
#include <cstdarg>
#include <filesystem>
#include <sstream>

#include "filesystem/FileSystem.h"
#include "SimpleTypes.h"

#include <Windows.h>

namespace EM::Debug
{
	namespace 
	{
		std::vector<std::string> Logs; // Used to dump into a file can't be cleared
		std::vector<LogMessage> Messages; // Usage for a console can be cleared
		std::string LastLog;
		bool DumpLog = true;

		struct DebugStats
		{
			u32 InfoCount = 0;
			u32 WarningCount = 0;
			u32 ErrorCount = 0;

			CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo;
			HANDLE ConsoleHandle;

			u32 TotalCount() const
			{
				return InfoCount + WarningCount + ErrorCount;
			}

			DebugStats() {
				ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
				GetConsoleScreenBufferInfo(ConsoleHandle, &ConsoleInfo);
			}
			~DebugStats()
			{
				if(DumpLog)
				{
					if(!FileSystem::Exists("logs"))
						FileSystem::CreateDir("logs");

					EM::File dumpLog = FileSystem::OpenO("logs/log-dump.txt");
					for(const auto& log : Logs)
					{
						dumpLog.Write(log.data(), log.size());
					}
					dumpLog.Close();
				}
			}
		} DebugStats{};

	}
	
	std::string GetLastLog()
	{
		return LastLog;
	}

	void ClearLogMessages()
	{
		Messages.clear();
		DebugStats = {};
	}

	LogMessage GetLastLogMessage()
	{
		return Messages[Messages.size() - 1];
	}
	void Log(const std::string& title, const std::string& message)
	{
		std::stringstream buffer;
		buffer << "[Info] " << title << " - " << message << std::endl;
		LogMessage log { buffer.str(), LS_INFO };
		LastLog = buffer.str();

		Messages.emplace_back(log);
		Logs.emplace_back(buffer.str());

#ifndef EM_DIST
		SetConsoleTextAttribute(DebugStats.ConsoleHandle, FOREGROUND_GREEN);
		std::cout << LastLog;
		SetConsoleTextAttribute(DebugStats.ConsoleHandle, DebugStats.ConsoleInfo.wAttributes);
#endif
	}

	void LogWarning(const std::string& title, const std::string& message)
	{
		std::stringstream buffer;
		buffer << "[Warning] " << title << " - " << message << std::endl;
		LogMessage log { buffer.str(), LS_WARNING };
		LastLog = buffer.str();

		Messages.emplace_back(log);
		Logs.emplace_back(buffer.str());

#ifndef EM_DIST
		SetConsoleTextAttribute(DebugStats.ConsoleHandle, FOREGROUND_GREEN|FOREGROUND_RED);
		std::cout << LastLog;
		SetConsoleTextAttribute(DebugStats.ConsoleHandle, DebugStats.ConsoleInfo.wAttributes);
#endif
	}

	void LogError(const std::string& title, const std::string& message)
	{
		std::stringstream buffer;
		buffer << "[Error] " << title << " - " << message << std::endl;
		LogMessage log { buffer.str(), LS_ERROR };
		LastLog = buffer.str();
		
		Messages.emplace_back(log);
		Logs.emplace_back(buffer.str());

#ifndef EM_DIST
		SetConsoleTextAttribute(DebugStats.ConsoleHandle, FOREGROUND_RED);
		std::cout << LastLog;
		SetConsoleTextAttribute(DebugStats.ConsoleHandle, DebugStats.ConsoleInfo.wAttributes);
#endif
	}

	const std::vector<LogMessage>& GetLogs()
	{
		return Messages;
	}

	std::string GetLastLogInfo()
	{
		return Logs[Logs.size() - 1];
	}
}
