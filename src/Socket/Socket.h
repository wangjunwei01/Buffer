#pragma once

class Socket
{
public:
	Socket(SOCKET socket);
	~Socket();

private:
	SOCKET m_socket = 0;
};

