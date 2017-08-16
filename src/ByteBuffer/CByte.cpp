#include "stdafx.h"
#include "CByte.h"


ByteBuffer::ByteBuffer()
{
	Init(DEFAULT_SIZE);
}

ByteBuffer::ByteBuffer(size_t size)
{
	Init(size);
}

ByteBuffer::ByteBuffer(ByteBuffer& byte)
{
	Init(byte.m_capacity);

	memcpy(m_byte, byte.m_byte, byte.m_wpos);
	//m_len = byte.m_len;
	m_rpos = byte.m_rpos;
	m_wpos = byte.m_wpos;
}

ByteBuffer& ByteBuffer::operator=(ByteBuffer& byte)
{
	//assert(m_byte != byte.m_byte);
	if (m_byte == byte.m_byte) {
		return byte;
	}
	if (byte.m_capacity > m_capacity) {
		ReSize(byte.m_capacity);
	}
	else {
		Clear();
	}

	memcpy(m_byte, byte.m_byte, byte.m_wpos);
	//m_len = byte.m_len;
	m_rpos = byte.m_rpos;
	m_wpos = byte.m_wpos;
	return *this;
}

ByteBuffer::~ByteBuffer()
{
	free(m_byte);
	m_byte = nullptr;
}



void ByteBuffer::Clear()
{
	assert(m_byte);
	//memset(m_byte, 0, m_capacity);
	m_rpos = 0;
	m_wpos = 0;
	//m_len = 0;
}

char* ByteBuffer::Contents()
{
	return m_byte;
}

void ByteBuffer::ReCapacity()
{
	ReSize(m_capacity + DEFAULT_SIZE);
}

void ByteBuffer::ReSize(size_t size)
{
	if (size <= m_capacity) {
		return;
	}
	char* newBuff = (char*)malloc(size);
	assert(newBuff);
	/*游标控制不用初始化，影响效率*/
	//memset(newBuff, 0, size);
	memcpy(newBuff, m_byte, m_wpos);
	free(m_byte);
	m_byte = newBuff;
	m_capacity = size;
}

uint32 ByteBuffer::Size()
{
	return m_wpos;
}

void ByteBuffer::WriteByte(char* src, size_t len)
{
	if (!src)
		return;
	uint32 remaindCapacity = m_capacity - Size();
	if (remaindCapacity < len) {
		ReSize(m_capacity + len + DEFAULT_SIZE);
	}
	memcpy(&m_byte[Size()], src, len);
	m_wpos += len;
	//m_len += len;
}

uint32 ByteBuffer::ReadByte(char* dest, size_t len)
{
	if (m_rpos + len > Size()) {
		uint32 readLen = Size() - m_rpos;
		memcpy(dest, &m_byte[m_rpos], readLen);
		return readLen;
	}
	memcpy(dest, &m_byte[m_rpos], len);
	m_rpos += len;
	return len;
}

void ByteBuffer::WriteByteFrom(uint32 index, char* src, size_t len)
{
	if (!src)
		return;
	//index ---> [0,)
	if (index >= m_capacity || index + len > m_capacity) {
		ReSize(m_capacity + len + DEFAULT_SIZE);
	}
	memcpy(&m_byte[index], src, len);
	m_wpos += len;
}

void ByteBuffer::WriteString(const string& str)
{
	short len = (short)str.length();
	if (len > 0) {
		WriteByte((char*)str.c_str(), len);
		char end[1] = { '\0' };
		WriteByte(end, sizeof(char));
	}
}

void ByteBuffer::ReadString(string& str)
{
	short len = 0;
	uint32 index = m_rpos;
	while (true)
	{
		if (m_byte[index] == '\0') {
			break;
		}
		len++;
		index++;
	}
	if (len == 0) {
		m_rpos += 1;
		return;
	}
	str.assign(&m_byte[m_rpos], len);
	m_rpos += (len + 1);
}

void ByteBuffer::Init(size_t size)
{
	m_byte = (char*)malloc(size);
	assert(m_byte);
	m_capacity = size;
	Clear();
}


void ByteBuffer::appendNetString(const string& str)
{
	//两个字节表示长度
	short len = (short)str.length();
	if (len > 0) {
		append<short>(len);
		WriteByte((char*)str.c_str(), len);
	}
}

void ByteBuffer::readNetString(string& str)
{
	short len = read<short>();
	if (len > 0) {
		if (len + m_rpos <= Size()) {
			str.assign(&m_byte[m_rpos], len);
			m_rpos += len;
		}
	}
}

ByteBuffer& ByteBuffer::operator<<(short value)
{
	append<short>(value);
	return *this;
}

ByteBuffer& ByteBuffer::operator<<(double value)
{
	append<double>(value);
	return *this;
}

ByteBuffer& ByteBuffer::operator<<(const string& value)
{
	appendNetString(value);
	return *this;
}

ByteBuffer& ByteBuffer::operator<<(uint8 value)
{
	append<uint8>(value);
	return *this;
}

ByteBuffer& ByteBuffer::operator<<(uint32 value)
{
	append<uint32>(value);
	return *this;
}

ByteBuffer& ByteBuffer::operator >> (uint32& value)
{
	value = read<uint32>();
	return *this;
}

ByteBuffer& ByteBuffer::operator >> (uint8& value)
{
	value = read<uint8>();
	return *this;
}

ByteBuffer& ByteBuffer::operator >> (string& value)
{
	readNetString(value);
	return *this;
}

ByteBuffer& ByteBuffer::operator >> (short& value)
{
	value = read<short>();
	return *this;
}

ByteBuffer& ByteBuffer::operator >> (uint64& value)
{
	value = read<uint64>();
	return *this;
}
