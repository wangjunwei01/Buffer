#pragma once
using namespace std;


class SocketMgr
{
public:
	SocketMgr();
	~SocketMgr();

	bool Initialize();
	static bool LoadWsaSocketLib();

	inline HANDLE GetCompletionPort() { return m_completePort; }
private:
	bool StartIoComplete();
	bool WorkerThreadRun();

private:
	HANDLE m_completePort = nullptr;
	vector<std::thread*> m_workerThread;
};

extern SocketMgr sSocketMgr;
