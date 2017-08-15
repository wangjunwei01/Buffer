#pragma once
using namespace std;

class CByte
{
public:
	CByte();
	CByte(size_t size);
	CByte(CByte& byte);
	CByte& operator=(CByte& byte);
	virtual ~CByte();
	void Clear();
	char* Contents();
	inline uint32 Size();
	inline uint32 wpos() { return m_wpos; }

	void WriteByte(char* src, size_t len);
	void ReadByte(char* dest, size_t len);
	void WriteByteByIndex(uint32 index, char* src, size_t len);

	void WriteString(const string& str);
	void ReadString(string& str);

	void appendNetString(const string& str);
	void readNetString(string& str);

	template<typename T>
	void append(T& value);
	template<typename T>
	T read();
	template<typename T>
	void Put(uint32 index, T value);
	template<typename T>
	T read(uint32 index);

public:
	CByte& operator<<(uint64 value);
	CByte& operator<<(int64 value);
	CByte& operator<<(uint32 value);
	CByte& operator<<(int32 value);
	CByte& operator<<(uint16 value);
	CByte& operator<<(int16 value);
	CByte& operator<<(uint8 value);
	CByte& operator<<(int8 value);
	CByte& operator<<(double value);
	CByte& operator<<(const string& value);

	CByte& operator>>(uint64& value);
	CByte& operator>>(int64& value);
	CByte& operator>>(uint32& value);
	CByte& operator>>(int32& value);
	CByte& operator>>(uint16& value);
	CByte& operator>>(int16& value);
	CByte& operator>>(uint8& value);
	CByte& operator>>(int8& value);
	CByte& operator>>(double& value);
	CByte& operator>>(string& value);
private:
	void ReCapacity();
	void ReSize(size_t size);
	void Init(size_t size);
private:
	const static size_t DEFAULT_SIZE = 128;
	uint32 m_capacity = 0;
	uint32 m_rpos = 0;
	uint32 m_wpos = 0;
	char* m_byte = nullptr;
};


template<typename T>
void CByte::append(T& value)
{
	//memcpy(&m_byte[m_wpos], (char*)(&value), sizeof(T));
	//m_wpos += sizeof(T);
	WriteByte((char*)(&value), sizeof(T));
}

template<typename T>
T CByte::read()
{
	if (sizeof(T) + m_rpos > Size()) {
		return T();
	}
	T t = *((T*)&m_byte[m_rpos]);
	m_rpos += sizeof(T);
	return t;
}

template<typename T>
T CByte::read(uint32 index)
{
	if (sizeof(T) + index > Size()) {
		return T();
	}
	T t = *(T*)(&m_byte[index]);
	return t;
}

template<typename T>
void CByte::Put(uint32 index, T value)
{
	WriteByteByIndex(index, (char*)(&value), sizeof(T));
}

