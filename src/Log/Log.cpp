#include "stdafx.h"
#include "Log.h"

Log slog;

Log::Log()
{
	// get error handle
#ifdef WIN32
	stderr_handle = GetStdHandle(STD_ERROR_HANDLE);
	stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
#endif
}

Log::~Log()
{
}


class InternalLogger {
private:
	int m_Cursor = 0;
	static const int StrBufSize = 32 * 1024;
	char m_Buffer[StrBufSize];
public:
	string getLogString() {
		if (m_Cursor > 0) {
			if (m_Cursor + 1 < StrBufSize) {
				m_Buffer[m_Cursor] = '\n';
				m_Cursor += 1;
				m_Buffer[m_Cursor] = '\0';
			}
			return string(m_Buffer);
		}
		else
			return "";
	};

	void writeTime() {
		time_t now = time(NULL);
		tm lt = {};
		localtime_s(&lt, &now);
		m_Cursor += strftime(&m_Buffer[m_Cursor], StrBufSize - m_Cursor, "%F %T ", &lt);
	};

	void writeLog(const char* log) {
		m_Cursor += sprintf_s(&m_Buffer[m_Cursor], StrBufSize - m_Cursor, "%s ", log);
	}

	void writeLog(const char * str, va_list args) {
		m_Cursor += vsnprintf((char*)&m_Buffer[m_Cursor], StrBufSize - m_Cursor, str, args);
	};
};


void Log::outError(const char *source, const char* str, ...)
{
	va_list ap;
	va_start(ap, str);
	string logMessage = LogString(LogLevel::loglevel_error, source, str, ap);
	va_end(ap);
	outScreen(logMessage, LogLevel::loglevel_error);
}

void Log::outDebug(const char *source, const char* str, ...)
{
	va_list ap;
	va_start(ap, str);
	string logMessage = LogString(LogLevel::loglevel_debug, source, str, ap);
	va_end(ap);
	outScreen(logMessage, LogLevel::loglevel_debug);
}

void Log::outInfo(const char *source, const char* str, ...)
{
	va_list ap;
	va_start(ap, str);
	string logMessage = LogString(LogLevel::loglevel_info, source, str, ap);
	va_end(ap);
	outScreen(logMessage, LogLevel::loglevel_info);
}

void Log::logScreen(LogColors color, const char *source, const char* str, ...)
{
	va_list ap;
	va_start(ap, str);
	string logMessage = LogString(loglevel_debug, source, str, ap);
	va_end(ap);
	SetConsoleTextAttribute(stdout_handle, color);
	fprintf(stderr, logMessage.c_str());
	SetConsoleTextAttribute(stdout_handle, log_color_white);
}

static const char* LogLevelNames[LogLevel::loglevel_max] =
{
	"[always]",
	"[Fatal]",
	"[Error]",
	"[Warning]",
	"[Debug]",
	"[Info ]"
};

static const int LevelColors[loglevel_max] = {
	FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	FOREGROUND_RED | FOREGROUND_INTENSITY,
	FOREGROUND_RED | FOREGROUND_INTENSITY,
	FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY,
	FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	FOREGROUND_GREEN | FOREGROUND_INTENSITY,
};

std::string Log::LogString(LogLevel level, const char* source, const char* str, va_list ap)
{
	InternalLogger logger;
	logger.writeTime();
	logger.writeLog(LogLevelNames[level]);
	
	if (source && *source != '\0') {
		logger.writeLog(source);
	}
	if (str) {
		logger.writeLog(str, ap);
	}
	return logger.getLogString();
}

void Log::outScreen(const string& str, LogLevel level)
{
	int color = LevelColors[level];
	SetConsoleTextAttribute(stdout_handle, color);
	fprintf(stderr, str.c_str());
	SetConsoleTextAttribute(stdout_handle, log_color_white);
}
