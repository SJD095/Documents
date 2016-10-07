#include <iostream>
#include <string>

using namespace std;

//四个幻数
#define A 0x67452301
#define B 0xefcdab89
#define C 0x98badcfe
#define D 0x10325476


//一个4*4矩阵
#define S11 7
#define S12 12
#define S13 17
#define S14 22

#define S21 5
#define S22 9
#define S23 14
#define S24 20

#define S31 4
#define S32 11
#define S33 16
#define S34 23

#define S41 6
#define S42 10
#define S43 15
#define S44 21

//四个线性函数
int F(int x, int y, int z)
{
	return (x & y) | ((~x) & z);
}

int G(int x, int y, int z)
{
	return (x & z) | (y & (~z));
}

int H(int x, int y, int z)
{
	return x ^ y ^ z;
}

int I(int x, int y, int z)
{
	return y ^ (x | (~z));
}

//线性函数对应的四个操作
int FF(int a, int b, int c, int d, int x, int s,
		int ac)
{
	a += (F(b, c, d)&0xFFFFFFFF) + x + ac;
	a = ((a&0xFFFFFFFF)<< s) | ((a&0xFFFFFFFF) >> (32 - s));
	a += b;
	return (a&0xFFFFFFFF);
}

int GG(int a, int b, int c, int d, int x, int s,
		int ac)
{
	a += (G(b, c, d)&0xFFFFFFFF) + x + ac;
	a = ((a&0xFFFFFFFF) << s) | ((a&0xFFFFFFFF) >> (32 - s));
	a += b;
	return (a&0xFFFFFFFF);
}

int HH(int a, int b, int c, int d, int x, int s,
		int ac)
{
	a += (H(b, c, d)&0xFFFFFFFF) + x + ac;
	a = ((a&0xFFFFFFFF) << s) | ((a&0xFFFFFFFF) >> (32 - s));
	a += b;
	return (a&0xFFFFFFFF);
}

int II(int a, int b, int c, int d, int x, int s,
		int ac)
{
	a += (I(b, c, d)&0xFFFFFFFF) + x + ac;
	a = ((a&0xFFFFFFFF) << s) | ((a&0xFFFFFFFF) >> (32 - s));
	a += b;
	return (a&0xFFFFFFFF);
}

//操作运算
void shiftGroup(int* Groups, int* result)
{
	//取出当前的结果
	int a = result[0], b = result[1], c = result[2], d = result[3];

	a = FF(a, b, c, d, Groups[0], S11, 0xd76aa478L);
	d = FF(d, a, b, c, Groups[1], S12, 0xe8c7b756L);
	c = FF(c, d, a, b, Groups[2], S13, 0x242070dbL);
	b = FF(b, c, d, a, Groups[3], S14, 0xc1bdceeeL);
	a = FF(a, b, c, d, Groups[4], S11, 0xf57c0fafL);
	d = FF(d, a, b, c, Groups[5], S12, 0x4787c62aL);
	c = FF(c, d, a, b, Groups[6], S13, 0xa8304613L);
	b = FF(b, c, d, a, Groups[7], S14, 0xfd469501L);
	a = FF(a, b, c, d, Groups[8], S11, 0x698098d8L);
	d = FF(d, a, b, c, Groups[9], S12, 0x8b44f7afL);
	c = FF(c, d, a, b, Groups[10], S13, 0xffff5bb1L);
	b = FF(b, c, d, a, Groups[11], S14, 0x895cd7beL);
	a = FF(a, b, c, d, Groups[12], S11, 0x6b901122L);
	d = FF(d, a, b, c, Groups[13], S12, 0xfd987193L);
	c = FF(c, d, a, b, Groups[14], S13, 0xa679438eL);
	b = FF(b, c, d, a, Groups[15], S14, 0x49b40821L);

	a = GG(a, b, c, d, Groups[1], S21, 0xf61e2562L);
	d = GG(d, a, b, c, Groups[6], S22, 0xc040b340L);
	c = GG(c, d, a, b, Groups[11], S23, 0x265e5a51L);
	b = GG(b, c, d, a, Groups[0], S24, 0xe9b6c7aaL);
	a = GG(a, b, c, d, Groups[5], S21, 0xd62f105dL);
	d = GG(d, a, b, c, Groups[10], S22, 0x2441453L);
	c = GG(c, d, a, b, Groups[15], S23, 0xd8a1e681L);
	b = GG(b, c, d, a, Groups[4], S24, 0xe7d3fbc8L);
	a = GG(a, b, c, d, Groups[9], S21, 0x21e1cde6L);
	d = GG(d, a, b, c, Groups[14], S22, 0xc33707d6L);
	c = GG(c, d, a, b, Groups[3], S23, 0xf4d50d87L);
	b = GG(b, c, d, a, Groups[8], S24, 0x455a14edL);
	a = GG(a, b, c, d, Groups[13], S21, 0xa9e3e905L);
	d = GG(d, a, b, c, Groups[2], S22, 0xfcefa3f8L);
	c = GG(c, d, a, b, Groups[7], S23, 0x676f02d9L);
	b = GG(b, c, d, a, Groups[12], S24, 0x8d2a4c8aL);

	a = HH(a, b, c, d, Groups[5], S31, 0xfffa3942L);
	d = HH(d, a, b, c, Groups[8], S32, 0x8771f681L);
	c = HH(c, d, a, b, Groups[11], S33, 0x6d9d6122L);
	b = HH(b, c, d, a, Groups[14], S34, 0xfde5380cL);
	a = HH(a, b, c, d, Groups[1], S31, 0xa4beea44L);
	d = HH(d, a, b, c, Groups[4], S32, 0x4bdecfa9L);
	c = HH(c, d, a, b, Groups[7], S33, 0xf6bb4b60L);
	b = HH(b, c, d, a, Groups[10], S34, 0xbebfbc70L);
	a = HH(a, b, c, d, Groups[13], S31, 0x289b7ec6L);
	d = HH(d, a, b, c, Groups[0], S32, 0xeaa127faL);
	c = HH(c, d, a, b, Groups[3], S33, 0xd4ef3085L);
	b = HH(b, c, d, a, Groups[6], S34, 0x4881d05L);
	a = HH(a, b, c, d, Groups[9], S31, 0xd9d4d039L);
	d = HH(d, a, b, c, Groups[12], S32, 0xe6db99e5L);
	c = HH(c, d, a, b, Groups[15], S33, 0x1fa27cf8L);
	b = HH(b, c, d, a, Groups[2], S34, 0xc4ac5665L);

	a = II(a, b, c, d, Groups[0], S41, 0xf4292244L);
	d = II(d, a, b, c, Groups[7], S42, 0x432aff97L);
	c = II(c, d, a, b, Groups[14], S43, 0xab9423a7L);
	b = II(b, c, d, a, Groups[5], S44, 0xfc93a039L);
	a = II(a, b, c, d, Groups[12], S41, 0x655b59c3L);
	d = II(d, a, b, c, Groups[3], S42, 0x8f0ccc92L);
	c = II(c, d, a, b, Groups[10], S43, 0xffeff47dL);
	b = II(b, c, d, a, Groups[1], S44, 0x85845dd1L);
	a = II(a, b, c, d, Groups[8], S41, 0x6fa87e4fL);
	d = II(d, a, b, c, Groups[15], S42, 0xfe2ce6e0L);
	c = II(c, d, a, b, Groups[6], S43, 0xa3014314L);
	b = II(b, c, d, a, Groups[13], S44, 0x4e0811a1L);
	a = II(a, b, c, d, Groups[4], S41, 0xf7537e82L);
	d = II(d, a, b, c, Groups[11], S42, 0xbd3af235L);
	c = II(c, d, a, b, Groups[2], S43, 0x2ad7d2bbL);
	b = II(b, c, d, a, Groups[9], S44, 0xeb86d391L);

	//累加得到新的结果
	result[0] += a;
	result[1] += b;
	result[2] += c;
	result[3] += d;
	result[0]=result[0]&0xFFFFFFFFL;
	result[1]=result[1]&0xFFFFFFFFL;
	result[2]=result[2]&0xFFFFFFFFL;
	result[3]=result[3]&0xFFFFFFFFL;
}

//防止出现负数
int b2iu(char b)
{
	return b < 0 ? b & 0x7F + 128 : b;
}

//取出进行操作运算的部分
int* divGroup(string Group, int index)
{
	int* Point = new int[16];
	for(int i = 0; i < 16; i++)
	{
		Point[i] = b2iu(Group[4*i+index])|
		(b2iu(Group[4*i+1+index]))<<8|
		(b2iu(Group[4*i+2+index]))<<16|
		(b2iu(Group[4*i+3+index]))<<24;
	}
	return Point;
}

//八进制转换
char HexNumber[16] = {
	'0', '1', '2', '3',
	'4', '5', '6', '7',
	'8', '9', 'A', 'B',
	'C', 'D', 'E', 'F'
};

int main()
{
	//保存结果的数组
	int result[4];

	result[0] = A;
	result[1] = B;
	result[2] = C;
	result[3] = D;

	string Strs[4] = {
		"abcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabc",
		"abc",
		"()fds%%^!``~dfj238749236dfjk]df[jsflknvc,sldfidsoen",
		""
	};

	//输入字符串
	string InputString, LastString;
	cout << "请输入一个字符串" << endl;
	cin >> LastString;

	Strs[3] = LastString;

	for(int i = 0; i < 4; i++)
	{
		InputString = Strs[i];

		result[0] = A;
		result[1] = B;
		result[2] = C;
		result[3] = D;

		//计算字符串的大小，以byte为单位
		auto ByteLength = InputString.size();

		//计算字符串有多少个大小为64个byte,512bit的块
		int GroupCount = ByteLength / 64;

		//存储每次进行操作运算的512个bit
		int* Groups;

		Groups = new int[16];

		//对每一块数据进行操作运算
		for(int i = 0; i < GroupCount; i++)
		{
			Groups = divGroup(InputString, i * 64);
			shiftGroup(Groups, result);
		}

		//操作剩余的bits
		int rest = ByteLength % 64;
		string TmpGroup(64, '0');

		//如果剩余bits小于56，即有8bits空间用于存储字符串大小
		if(rest <= 56)
		{
			//复制
			for(int i = 0; i < rest; i++)
			{
				TmpGroup[i] = InputString[ByteLength - rest + i];
			}

			if(rest < 56)
			{
				//除了一个bit存储为1，剩下的56位以前的均赋值为0
				TmpGroup[rest] = (char)(1 << 7);
				for(int i = 1; i < 56 - rest; i++)
				{
					TmpGroup[rest + i] = 0;
				}

				//最后8位存入字符串大小
				int TmpLength = ByteLength << 3;
				for(int i = 0; i < 8; i++)
				{
					TmpGroup[56 + i] = (char)(TmpLength&0xFF);
					TmpLength = TmpLength >> 8;
				}

				Groups = divGroup(TmpGroup, 0);
				shiftGroup(Groups, result);
			}
			else
			{
				//复制
				for(int i = 0; i < rest; i++)
				{
					TmpGroup[i] = InputString[ByteLength - rest + i];
				}
				TmpGroup[rest] = (char)(1 << 7);

				//剩下的全部为0
				for(int i = rest + 1; i < 64; i++)
					TmpGroup[i] = 0;
				Groups = divGroup(TmpGroup, 0);

				//处理分组
				shiftGroup(Groups, result);

				//新构造一个前56位为0，最后8位为字符串大小的临时数组
				for(int i = 0;i < 56;i++)
					TmpGroup[i] = 0;
				int TmpLength = ByteLength << 3;
				for(int i = 0;i < 8; i++)
				{
					TmpGroup[56 + i] = (char)(TmpLength&0xFF);
					TmpLength = TmpLength >> 8;
				}
				Groups = divGroup(TmpGroup, 0);

				//处理分组
				shiftGroup(Groups, result);
			}

			//存储输出MD5值得字符串
			string resStr = "";
			int temp = 0;

			//依次处理
			for(int i = 0; i < 4; i++)
			{
				for(int j = 0; j < 4; j++)
				{
					temp = result[i]&0x0F;
					string b = "";
					string a = b + HexNumber[temp];
					result[i] = result[i] >> 4;
					temp = result[i]&0x0F;
					resStr += HexNumber[temp] + a;
					result[i] = result[i] >> 4;
				}
			}
			cout << InputString << " MD5: \n" << resStr << endl;
		}
	}
}
