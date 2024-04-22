#pragma once
#define FMT_HEADER_ONLY
#include <vector>

#include <format.h>

namespace EM::Debug
{
	enum LogSeverity : unsigned char
	{
		INFO	= BIT(0),
		WARNING = BIT(1),
		ERROR	= BIT(2),
		MAX		= BIT(3)
	};

	inline LogSeverity operator|(LogSeverity a, LogSeverity b)
	{
		return static_cast<LogSeverity>(static_cast<int>(a) | static_cast<int>(b));
	}

	inline LogSeverity operator&(LogSeverity a, LogSeverity b)
	{
		return static_cast<LogSeverity>(static_cast<int>(a) & static_cast<int>(b));
	}

	inline LogSeverity operator|=(LogSeverity& a, LogSeverity b)
	{
		return a = a | b;
	}

	struct LogMessage
	{
		std::string Message;
		LogSeverity Severity;
	};
	
	void Log(const std::string& title, const std::string& message);
	void LogWarning(const std::string& title, const std::string& message);
	void LogError(const std::string& title, const std::string& message);
	
	const std::vector<LogMessage>&  GetLogs();
	LogMessage GetLastLogMessage();
	void ClearLogMessages();
}

#define EM_FMT(...) fmt::format(__VA_ARGS__)

#define EM_INFO(...) EM::Debug::Log(__FUNCTION__, EM_FMT(__VA_ARGS__))
#define EM_WARN(...) EM::Debug::LogWarning(__FUNCTION__, EM_FMT(__VA_ARGS__))
#define EM_ERROR(...) EM::Debug::LogError(__FUNCTION__, EM_FMT(__VA_ARGS__))