// ConsoleApplication2.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <cstring>
using std::cout;
using std::cin;
using std::endl;

int main()
{
	const char* str = "abc hello";
	std::string hexString;
	charsToHex(str, hexString, false);
	cout << str << " = 0x" << hexString << endl;
	std::string str1;
	hexToChars(hexString.c_str(), str1);
	cout << "0x" << hexString << " = " << str1 << endl;
	cin.get();
	return 0;
}

