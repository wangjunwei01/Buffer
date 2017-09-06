#pragma once

enum LogLevel 
{
	loglevel_always,
	loglevel_fatal,
	loglevel_error,
	loglevel_warning,
	loglevel_debug,
	loglevel_info,
	loglevel_max
};

enum LogColors 
{
	log_color_white = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	log_color_red = FOREGROUND_RED,
	log_color_green = FOREGROUND_GREEN,
	log_color_blue = FOREGROUND_BLUE,
	log_color_yellow = FOREGROUND_RED | FOREGROUND_GREEN,
	log_color_purple = FOREGROUND_RED | FOREGROUND_BLUE,
	log_color_cyan = FOREGROUND_GREEN | FOREGROUND_BLUE,
	log_color_white_intensity = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	log_color_red_intensity = FOREGROUND_RED | FOREGROUND_INTENSITY,
	log_color_green_intensity = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	log_color_blue_intensity = FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	log_color_yellow_intensity = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	log_color_purple_intensity = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	log_color_cyan_intensity = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
};

class Log
{
public:
	Log();
	~Log();
	void outError(const char *source, const char* str, ...);
	void outDebug(const char *source, const char* str, ...);
	void outInfo(const char *source, const char* str, ...);
	void logScreen(LogColors color, const char *source, const char* str, ...);
private:
	std::string LogString(LogLevel level, const char* source, const char* str, va_list ap);
	void outScreen(const std::string& str, LogLevel level);

private:
#ifdef WIN32
	HANDLE stdout_handle;
	HANDLE stderr_handle;
#endif
};

extern Log slog;
