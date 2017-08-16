#include "stdafx.h"
#include "test.h"

void ModleTest()
{
	test();
	testReadWrite();
	TestReadRrom();
}


void testReadWrite()
{
	ByteBuffer date;
	for (uint32 i = 0; i < 100000; i++) {
		char buff[10];
		sprintf_s(buff, 10, "%d", i);
		date.WriteByte(buff, 8);
	}
	for (uint32 i = 0; i < 100000; i++) {
		char buff[10];
		date.ReadByte(buff, 8);
		if (i % 5000 == 0) {
			printf("%s\n", buff);
		}
	}
}

void TestReadRrom()
{
	ByteBuffer cstr;
	std::string sss = "asdfas\0sdfasdfsadf";
	cstr.appendNetString(sss);
	for (uint32 i = 0; i < 15; i++)
	{
		char buff[10] = { 0 };
		sprintf_s(buff, 10, "%d", i);
		cstr.WriteByte(buff, 8);
	}
	double d = 1.0;
	cstr << d;

	ByteBuffer newCbyte = cstr;
	ByteBuffer newCbyte1;
	newCbyte1 = cstr;
	double dd = newCbyte1.read<double>(128);
	string readStr;
	newCbyte1.readNetString(readStr);
}

void test() {
	char buffer[4096];
	ByteBuffer t;
	std::string sss = "asdfas\0sdfasdfsadf";
	t.appendNetString(sss);
	for (uint32 i = 0; i < 15; i++)
	{
		char buff[10] = { 0 };
		sprintf_s(buff, 10, "%d", i);
		t.WriteByte(buff, 8);
	}
	uint32 count = t.ReadByte(buffer, 129);
	//t.append(9);
	//t.append(&buffer[0]);
}