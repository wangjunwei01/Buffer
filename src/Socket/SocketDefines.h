#pragma once
#pragma comment(lib, "ws2_32.lib")

#include <WinSock2.h>
#include <windows.h>

#include "stdafx.h"
#include "Socket/SocketMgr.h"
#include "ListenSocket.h"

struct ServerConfig
{
	std::string address = "127.0.0.1";
	WORD port = 11111;
};



