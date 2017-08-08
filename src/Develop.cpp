// byte.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int main()
{
	std::string sss = "asdfasdf\0sdfasdfsadf";

	char* a = '\0';


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