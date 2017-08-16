#pragma once
using namespace std;

class ByteBuffer
{
public:
	ByteBuffer();
	ByteBuffer(size_t size);
	ByteBuffer(ByteBuffer& byte);
	ByteBuffer& operator=(ByteBuffer& byte);
	virtual ~ByteBuffer();
	void Clear();
	char* Contents();
	inline uint32 Size();
	inline uint32 wpos() { return m_wpos; }

	void WriteByte(char* src, size_t len);
	uint32 ReadByte(char* dest, size_t len);
	void WriteByteFrom(uint32 index, char* src, size_t len);

	void WriteString(const string& str);
	void ReadString(string& str);

	void appendNetString(const string& str);
	void readNetString(string& str);

	template<typename T> void append(T& value);
	template<typename T> void append(T* value);
	template<typename T> T read();
	template<typename T> void Put(uint32 index, T value);
	template<typename T> T read(uint32 index);

public:
	ByteBuffer& operator<<(uint64 value);
	ByteBuffer& operator<<(int64 value);
	ByteBuffer& operator<<(uint32 value);
	ByteBuffer& operator<<(int32 value);
	ByteBuffer& operator<<(uint16 value);
	ByteBuffer& operator<<(int16 value);
	ByteBuffer& operator<<(uint8 value);
	ByteBuffer& operator<<(int8 value);
	ByteBuffer& operator<<(double value);
	ByteBuffer& operator<<(const string& value);

	ByteBuffer& operator>>(uint64& value);
	ByteBuffer& operator>>(int64& value);
	ByteBuffer& operator>>(uint32& value);
	ByteBuffer& operator>>(int32& value);
	ByteBuffer& operator>>(uint16& value);
	ByteBuffer& operator>>(int16& value);
	ByteBuffer& operator>>(uint8& value);
	ByteBuffer& operator>>(int8& value);
	ByteBuffer& operator>>(double& value);
	ByteBuffer& operator>>(string& value);
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
void ByteBuffer::append(T& value)
{
// 	if (is_pointer<T>::value) {
// 	}

	//memcpy(&m_byte[m_wpos], (char*)(&value), sizeof(T));
	//m_wpos += sizeof(T);
	WriteByte((char*)(&value), sizeof(T));
}

template<typename T>
void ByteBuffer::append(T* value)
{
	static_assert(false, "pointer is not valid");
	//#error ("not pointer");
}

template<typename T>
T ByteBuffer::read()
{
	if (sizeof(T) + m_rpos > Size()) {
		return T();
	}
	T t = *((T*)&m_byte[m_rpos]);
	m_rpos += sizeof(T);
	return t;
}

template<typename T>
T ByteBuffer::read(uint32 index)
{
	if (sizeof(T) + index > Size()) {
		return T();
	}
	T t = *(T*)(&m_byte[index]);
	return t;
}

template<typename T>
void ByteBuffer::Put(uint32 index, T value)
{
	WriteByteFrom(index, (char*)(&value), sizeof(T));
}

