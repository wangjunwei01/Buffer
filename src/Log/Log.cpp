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

void Log::outDebug(const char *source, const char* str, ...)
{
	va_list ap;
	va_start(ap, str);
	string logMessage = "";//logString(LogLevel::loglevel_debug, source, str, ap);
	va_end(ap);
	outScreen(logMessage, LogLevel::loglevel_debug);
}

static const int LevelColors[loglevel_max] = {
	FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	FOREGROUND_RED | FOREGROUND_INTENSITY,
	FOREGROUND_RED | FOREGROUND_INTENSITY,
	FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY,
	FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	FOREGROUND_GREEN | FOREGROUND_INTENSITY,
};

void Log::outScreen(const string& str, LogLevel level)
{
	int color = LevelColors[level];
	SetConsoleTextAttribute(stdout_handle, color);
	fprintf(stderr, str.c_str());
	SetConsoleTextAttribute(stdout_handle, log_color_white);
}
