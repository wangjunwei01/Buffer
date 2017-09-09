#pragma once


template<typename T>
class ListenSocket
{
public:
	ListenSocket(const string& ip, WORD port);
	~ListenSocket();

	bool InitListenSocketByIpv4(const string& ip, WORD port);
	inline bool IsOpened() { return m_opened; }
private:
	bool m_opened = false;

	HANDLE m_iocp;
};

template<typename T>
bool ListenSocket<T>::InitListenSocketByIpv4(const string& ip, WORD port)
{
	SOCKET socketListen = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);

	struct sockaddr_in serveraddress;
	ZeroMemory(&serveraddress, sizeof(sockaddr_in));
	serveraddress.sin_family = AF_INET;
	serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddress.sin_port = htons((port));

	int result = ::bind(socketListen, (sockaddr*)&serveraddress, sizeof(sockaddr_in));
	if (result == SOCKET_ERROR) {
		slog.outInfo("SocketMgr::InitListenSocket", "Bind Error!");
		return false;
	}
	result = listen(socketListen, SOMAXCONN);
	if (result == SOCKET_ERROR) {
		slog.outInfo("SocketMgr::InitListenSocket", "Listen Error!");
		return false;
	}
	m_iocp = sSocketMgr.GetCompletionPort();
	CreateIoCompletionPort(socketListen, m_iocp, (ULONG_PTR)0, 0);
	return true;
}

template<typename T>
ListenSocket<T>::~ListenSocket()
{

}

template<typename T>
ListenSocket<T>::ListenSocket(const string& ip, WORD port)
{
	InitListenSocketByIpv4(ip, port);
}
