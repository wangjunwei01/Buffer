#pragma once
#pragma comment(lib, "ws2_32.lib")

#include <WinSock2.h>
#include <windows.h>
#include <mswsock.h>

#include "stdafx.h"
#include "Socket.h"
#include "ListenSocket.h"
#include "Socket/SocketMgr.h"

static const UINT PostAcceptSocketCount = 1;

struct ServerConfig
{
	std::string address = "127.0.0.1";
	WORD port = 11111;
};

enum SocketIOEvent
{
	SEvent_None,
	SEvent_Accept,
};

struct OverlappedStruct
{
	OVERLAPPED m_overlap;
	SocketIOEvent m_event;
	VOID* pSocket;
}; 

