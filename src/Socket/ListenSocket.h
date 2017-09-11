#pragma once

using namespace std;
template<typename T>
class ListenSocket
{
public:
	ListenSocket(const std::string& ip, WORD port);
	~ListenSocket();

	bool InitListenSocketByIpv4(const string& ip, WORD port);
	bool AcceptEx();
	inline bool IsOpened() { return m_opened; }
private:
	HANDLE m_iocp = nullptr;
	SOCKET m_listenSocket = 0;
	sockaddr_in m_serveraddress;
	T* m_clientSocket = nullptr;
	bool m_opened = false;

	LPFN_ACCEPTEX     m_lpfnAcceptEx = nullptr;         // AcceptEx函数指针 
	LPFN_GETACCEPTEXSOCKADDRS m_lpfnGetAcceptExSockAddrs = nullptr;
};

template<typename T>
bool ListenSocket<T>::AcceptEx()
{
	if (!m_lpfnAcceptEx) {
		return false;
	}

	SOCKET acceptSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	m_clientSocket = new T(acceptSocket);

	OverlappedStruct overlapped;
	overlapped.m_event = SEvent_Accept;

	BOOL result = m_lpfnAcceptEx(m_listenSocket, m_clientSocket, );
	if (!result && WSA_IO_PENDING != WSAGetLastError()) {
		slog.outInfo("ListenSocket<T>::AcceptEx", "lpfnAcceptEx faild");
		delete m_clientSocket;
		return false;
	}
}

template<typename T>
bool ListenSocket<T>::InitListenSocketByIpv4(const string& ip, WORD port)
{
	 m_listenSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);

	ZeroMemory(&m_serveraddress, sizeof(sockaddr_in));
	m_serveraddress.sin_family = AF_INET;
	m_serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
	m_serveraddress.sin_port = htons(port);

	int result = ::bind(m_listenSocket, (sockaddr*)&serveraddress, sizeof(sockaddr_in));
	if (result == SOCKET_ERROR) {
		slog.outInfo("SocketMgr::InitListenSocket", "Bind Error!");
		return false;
	}
	result = listen(m_listenSocket, SOMAXCONN);
	if (result == SOCKET_ERROR) {
		slog.outInfo("SocketMgr::InitListenSocket", "Listen Error!");
		return false;
	}
	m_iocp = sSocketMgr.GetCompletionPort();
	CreateIoCompletionPort(m_listenSocket, m_iocp, (ULONG_PTR)this, 0);

	DWORD dwBytes = 0;
	// GUID，这个是识别AcceptEx函数必须的
	GUID GuidAcceptEx = WSAID_ACCEPTEX;
	WSAIoctl(
		m_listenSocket,
		SIO_GET_EXTENSION_FUNCTION_POINTER,
		&GuidAcceptEx,
		sizeof(GuidAcceptEx),
		&m_lpfnAcceptEx,
		sizeof(m_lpfnAcceptEx),
		&dwBytes,
		NULL,
		NULL);

	GUID GuidGetAcceptExSockAddrs = WSAID_GETACCEPTEXSOCKADDRS;
	WSAIoctl(
		m_listenSocket,
		SIO_GET_EXTENSION_FUNCTION_POINTER,
		&GuidGetAcceptExSockAddrs,
		sizeof(GuidGetAcceptExSockAddrs),
		&m_lpfnGetAcceptExSockAddrs,
		sizeof(m_lpfnGetAcceptExSockAddrs),
		&dwBytes,
		NULL,
		NULL);


	for (UINT i = 0; i < PostAcceptSocketCount; i++)
	{
		AcceptEx();
	}
	return true;
}

template<typename T>
ListenSocket<T>::~ListenSocket()
{
	m_iocp = nullptr;
	m_clientSocket = nullptr;
}

template<typename T>
ListenSocket<T>::ListenSocket(const string& ip, WORD port)
{
	InitListenSocketByIpv4(ip, port);
}
