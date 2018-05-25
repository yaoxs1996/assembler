#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<cstdlib>
#include"asm2bin.h"
using namespace std;

ofstream outFile;
ifstream inFile;

int main()
{
	inFile.open("inst.txt");
	outFile.open("bin.txt");
	
	char buf[64];
	string str;
	//string bin;
	vector<string> res;

	//ภเสตภýปฏ
	asm2bin test;

	while (inFile.getline(buf, sizeof(buf)))
	{
		str = buf;
		res = test.split(str);
		outFile << test.convert(res);
		outFile << endl;
	}

	inFile.close();
	outFile.close();

	system("pause");
}