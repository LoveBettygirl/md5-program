#pragma once
#include <cctype>
#include <cstdio>
#include <vector>
#include <string>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sys/stat.h>
#ifdef _WIN32
#include <windows.h>
#pragma comment(lib, "wsock32.lib")
#else
#include <arpa/inet.h>
#endif
using namespace std;

class MD5
{
private:
	/* 基本常量定义 */
	static const uint32_t A;
	static const uint32_t B;
	static const uint32_t C;
	static const uint32_t D;
	static const uint32_t T[64];
	static const uint32_t S[64];
	static const uint32_t X[64];
	static const string testString[];  // 用于验证程序正确性的测试字符串

	/* 计算函数定义 */
	uint32_t F(uint32_t x, uint32_t y, uint32_t z) {
		return (x&y) | ((~x)&z);
	}
	uint32_t G(uint32_t x, uint32_t y, uint32_t z) {
		return (x&z) | (y&(~z));
	}
	uint32_t H(uint32_t x, uint32_t y, uint32_t z) {
		return x^y^z;
	}
	uint32_t I(uint32_t x, uint32_t y, uint32_t z) {
		return y ^ (x | (~z));
	}
	void FF(uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d, uint32_t x, uint32_t i) {
		uint32_t temp = F(b, c, d) + a + x + T[i];
		temp = (temp << S[i]) | (temp >> (32 - S[i]));
		a = b + temp;
	}
	void GG(uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d, uint32_t x, uint32_t i) {
		uint32_t temp = G(b, c, d) + a + x + T[i];
		temp = (temp << S[i]) | (temp >> (32 - S[i]));
		a = b + temp;
	}
	void HH(uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d, uint32_t x, uint32_t i) {
		uint32_t temp = H(b, c, d) + a + x + T[i];
		temp = (temp << S[i]) | (temp >> (32 - S[i]));
		a = b + temp;
	}
	void II(uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d, uint32_t x, uint32_t i) {
		uint32_t temp = I(b, c, d) + a + x + T[i];
		temp = (temp << S[i]) | (temp >> (32 - S[i]));
		a = b + temp;
	}

	vector<uint8_t> data; // 要计算MD5值的字节流
	uint32_t state[4];	// 保存加密结果的初始向量
	string result;	// 加密结果字符串（16进制）

	void calculateBlock(uint8_t *input); // 对字节流的一个分块（64字节）进行计算
	void string2BitStream(string src); // string转字节流
	void loadFile(char *filename); // 从文件中加载字节流
	void padding();	 // 按要求填充字节流
	void compute();	 // 计算填充后的字节流MD5值
	void genResultString();	 // MD5值转结果字符串
	void computeString(string src);	// 计算字符串的MD5值
	void resetVector();	 // 重置字节流、结果字符串、加密结果初始向量
	bool judgeHexString(string src); // 判断是不是16进制字符串

public:
	MD5();
	void testApplication();	 // 通过输出指定字符串的MD5值来验证程序正确性
	void computeFile(char *filename, bool verbose = true); // 计算输入文件的MD5值
	void validateFromString(char *srcFile);	 // 通过手动输入的MD5值来校验程序是否被修改
	void validateFromFile(char *md5File, char *srcFile); // 通过指定的MD5文件来校验程序是否被修改
};
