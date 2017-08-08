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

	void WriteByte(char* src, size_t len);
	void ReadByte(char* dest, size_t len);

	void WriteString(const string& str);
	void ReadString(string& str);

	template<typename T>
	void append(T& value);
	void appendNetString(const string& str);
	template<typename T>
	T read();
	void readNetString(string& str);
	
private:
	void ReCapacity();
	void ReSize(size_t size);
	void Init(size_t size);
private:
	const static size_t DEFAULT_SIZE = 128;
	uint32 m_capacity = 0;
	//uint32 m_len = 0;
	uint32 m_rpos = 0;
	uint32 m_wpos = 0;
	char* m_byte = nullptr;
};

template<typename T>
void CByte::append(T& value)
{
	memcpy(m_byte, (char*)(&value), sizeof(T));
	m_wpos += sizeof(T);
}

template<typename T>
T CByte::read()
{
	T t = *((T*)&m_byte[m_rpos]);
	m_rpos += sizeof(T);
	return t;
}


