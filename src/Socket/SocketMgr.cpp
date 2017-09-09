#include "SocketDefines.h"
#include "SocketMgr.h"

SocketMgr sSocketMgr;

SocketMgr::SocketMgr()
{
	Initialize();
}


SocketMgr::~SocketMgr()
{
}

bool SocketMgr::Initialize()
{
	if (!SocketMgr::LoadWsaSocketLib())
		return false;
	return true;
}

bool SocketMgr::LoadWsaSocketLib()
{
	WSADATA wsaData = { 0 };
	int result = WSAStartup(MAKEWORD(2, 0), &wsaData);
	if (result != 0) return false;

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 0) {
		WSACleanup();
		return false;
	}
	return true;
}

bool SocketMgr::StartIoComplete()
{
	m_completePort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, (ULONG_PTR)0, 0);

	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	int threadCount = sysInfo.dwNumberOfProcessors * 2;

	for (int i = 0; i < threadCount; i++)
	{
		m_workerThread.push_back(new thread(&SocketMgr::WorkerThreadRun, this));
	}
	return true;
}

bool SocketMgr::WorkerThreadRun()
{
	return true;
}

