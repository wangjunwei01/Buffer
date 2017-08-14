// byte.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int main()
{
	CByte cstr;
	uint32 index = cstr.wpos();
	uint8 count = 0;
	cstr << count;
	std::string sss = "asdfasdf\0sdfasdfsadf";
	cstr.WriteString(sss);
	cstr.WriteString("1234");
	cstr.appendNetString("5678");
	cstr.appendNetString(sss);
	cstr.Put(index, uint8(10));

	CByte newCbyte = cstr;
	CByte newCbyte1;
	newCbyte1 = cstr;
	string readStr;
	newCbyte1 >> count;
	newCbyte1.ReadString(readStr);
	newCbyte1.ReadString(readStr);
	newCbyte1.readNetString(readStr);
	newCbyte1.readNetString(readStr);

	CByte date;
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

	return 0;
}