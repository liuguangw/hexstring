#include "hex_tool.hpp"
#include <cstring>
#include <exception>

void hexToBytes(const char * input, vector<char>& output) {
	size_t leng = strlen(input);
	output.resize(2 * leng);
	output.clear();
	size_t outputIndex;
	for (size_t i = 0; i < leng; i++) {
		if (i % 2 == 0) {
			outputIndex = i / 2;
			output.emplace_back(input[i]);
		}
		else {
			outputIndex = (i - 1) / 2;
			output[outputIndex] += input[i];
		}
		if ((input[i] >= '0') && (input[i] <= '9')) {
			output[outputIndex] -= '0';
		}
		else if ((input[i] >= 'A') && (input[i] <= 'F')) {
			output[outputIndex] -= '7';
		}
		else if ((input[i] >= 'a') && (input[i] <= 'f')) {
			output[outputIndex] -= 'W';
		}
		else {
			//非16进制格式
			throw std::out_of_range("bad hex string format");
		}
		if (i % 2 == 0) {
			output[outputIndex] = output[outputIndex] << 4;
		}
	}
}
void hexToBytes(const char * input, string& output) {
	vector<char> charArr;
	hexToBytes(input, charArr);
	output.resize(charArr.size());
	output.clear();
	for (auto it = charArr.begin(); it != charArr.end(); it++) {
		output.append(1, *it);
	}
}

void bytesToHex(const vector<char>& input, string & output, bool upperCase) {
	size_t leng = input.size() * 2;
	output.resize(leng);
	output.clear();
	size_t inputIndex;
	unsigned char tmpChar;
	for (size_t i = 0; i < leng; i++) {
		if (i % 2 == 0) {
			//字符前4位
			inputIndex = i / 2;
			tmpChar = (unsigned char)input[inputIndex];
			tmpChar = tmpChar >> 4;
		}
		else {
			//字符后4位
			inputIndex = (i - 1) / 2;
			tmpChar = (unsigned char)input[inputIndex];
			tmpChar = tmpChar & 0xf;
			//output.append(1, tmpChar & 0xf);
		}
		if ((tmpChar >= 0) && (tmpChar <= 9)) {
			tmpChar += '0';
		}
		else {
			if (upperCase) {
				tmpChar += '7';
			}
			else {
				tmpChar += 'W';
			}
		}
		output.append(1, tmpChar);
	}
}

void bytesToHex(const char * input, string & output, bool upperCase) {
	size_t inputLength = strlen(input);
	vector<char> inputArr(inputLength);
	inputArr.clear();
	for (size_t i = 0; i < inputLength; i++) {
		inputArr.emplace_back(input[i]);
	}
	bytesToHex(inputArr, output, upperCase);
}

//debug工具
void hexStrToHexDebug(const char * hexStr, string& debugStr, size_t rowBytesCount) {
	debugStr.clear();
	size_t hexStrLength = strlen(hexStr);
	debugStr.append(rowBytesCount * 2 + rowBytesCount - 1, '=');
	for (size_t i = 0; i < hexStrLength; i++) {
		if (i % 2 == 0) {
			if (i % (rowBytesCount * 2) == 0) {
				debugStr.append("\r\n");
			}
			else {
				debugStr.append(" ");
			}
		}
		debugStr.append(1, hexStr[i]);
	}
	debugStr.append("\r\n");
	debugStr.append(rowBytesCount * 2 + rowBytesCount - 1, '=');
}
void bytesToHexDebug(const vector<char>& rawBytes, string& debugStr, size_t rowBytesCount, bool upperCase) {
	string hexStr;
	bytesToHex(rawBytes, hexStr, upperCase);
	hexStrToHexDebug(hexStr.c_str(), debugStr, rowBytesCount);
	debugStr.append("\r\n");
	debugStr.append(rowBytesCount, '=');
	unsigned char tmpChar;
	for (size_t i = 0; i < rawBytes.size(); i++) {
		if (i%rowBytesCount == 0) {
			debugStr.append("\r\n");
		}
		tmpChar = (unsigned char)rawBytes[i];
		if ((tmpChar >= 0x20) && (tmpChar <= 0x7e)) {
			//可显示ascii字符范围
			debugStr.append(1, tmpChar);
		}
		else {
			debugStr.append(1, '*');
		}
	}
	debugStr.append("\r\n");
	debugStr.append(rowBytesCount, '=');
}
void bytesToHexDebug(const char * rawBytes, string& debugStr, size_t rowBytesCount, bool upperCase) {
	string hexStr;
	bytesToHex(rawBytes, hexStr, upperCase);
	hexStrToHexDebug(hexStr.c_str(), debugStr, rowBytesCount);
	debugStr.append("\r\n");
	debugStr.append(rowBytesCount, '=');
	size_t charCount = hexStr.length() / 2;
	for (size_t i = 0; i < charCount; i++) {
		if (i%rowBytesCount == 0) {
			debugStr.append("\r\n");
		}
		debugStr.append(1, rawBytes[i]);
	}
	debugStr.append("\r\n");
	debugStr.append(rowBytesCount, '=');
}
