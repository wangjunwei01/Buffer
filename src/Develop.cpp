// byte.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


void test() {
	char buffer[4096];
	CByte t;
	t.ReadByte(buffer, 4096);
	//t.append(9);
	t.append(buffer[0]);



}

int main()
{
	test();
	CByte cstr;
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

	CByte newCbyte = cstr;
	CByte newCbyte1;
	newCbyte1 = cstr;
	double dd = newCbyte1.read<double>(128);
	string readStr;
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
	system("pause");
	return 0;
}