#ifndef ASM2BIN_H_
#define ASM2BIN_H_

#include<vector>
#include<string>
#include<bitset>
#include<sstream>

class asm2bin
{
public:
	asm2bin();
	~asm2bin();

	std::vector<std::string> split(const std::string str);
	std::string convert(std::vector<std::string> res);
	std::string reg2bin(std::string reg);

	std::string m_add_and_or_xor(std::vector<std::string> res);
	std::string m_addi_andi_ori_xori(std::vector<std::string> res);
	std::string m_sra_srl_sll(std::vector<std::string> res);
};

asm2bin::asm2bin(){}
asm2bin::~asm2bin(){}

//分割指令
std::vector<std::string> asm2bin::split(const std::string str)
{
	std::vector<std::string> res;
	std::string delim = " ,";		//使用多个分隔符
	if (str == " ")
		return res;

	char* strs = new char[str.length() + 1];
	strcpy(strs, str.c_str());
	char* d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());

	char* p = strtok(strs, d);
	std::string s;
	while (p)
	{
		s = p;
		res.push_back(s);
		p = strtok(NULL, d);
	}

	return res;
}

//寄存器转为对应二进制编码
std::string asm2bin::reg2bin(std::string reg)
{
	std::stringstream ss;
	std::bitset<5> t;
	int a;

	ss << reg[1];
	ss >> a;
	t = a;
	return t.to_string();
}

//汇编指令转换为二进制串
std::string asm2bin::convert(std::vector<std::string> res)
{
	if ((res[0] == "add") || (res[0] == "and") || (res[0] == "or") || (res[0] == "xor"))
	{
		return m_add_and_or_xor(res);
	}
	else if ((res[0] == "addi") || (res[0] == "andi") || (res[0] == "ori") || (res[0] == "xori"))
	{
		return m_addi_andi_ori_xori(res);
	}
	else if ((res[0] == "sra") || (res[0] == "srl") || (res[0] == "sll"))
	{
		return m_sra_srl_sll(res);
	}
}

//add、and、or、xor指令的转换
std::string asm2bin::m_add_and_or_xor(std::vector<std::string> res)
{
	std::string temp;
	std::string bin;

	if (res[0] == "add")
		bin = "00000000000100000";
	else if (res[0] == "and")
		bin = "00000100000100000";
	else if (res[0] == "or")
		bin = "00000100001000000";
	else if (res[0] == "xor")
		bin = "00010000010000000";
	else
		bin = "";

	temp = reg2bin(res[1]);
	bin = bin + temp;
	temp = reg2bin(res[2]);
	bin = bin + temp;
	temp = reg2bin(res[3]);
	bin = bin + temp;

	return bin;
}

//addi、andi、ori、xori指令的转换
std::string asm2bin::m_addi_andi_ori_xori(std::vector<std::string> res)
{
	std::string temp;
	std::string bin;
	std::stringstream ss;
	int a;

	if (res[0] == "addi")
		bin = "000101";
	else if (res[0] == "andi")
		bin = "001001";
	else if (res[0] == "ori")
		bin = "001010";
	else if (res[0] == "xori")
		bin = "001100";

	//将字符串转化为int类型后，变为16位二进制，再转为字符串插入结果
	ss << res[3];
	ss >> a;
	std::bitset<16> t;
	t = a;
	bin = bin + t.to_string();

	for (int i = 2; i >= 1; i--)
	{
		temp = reg2bin(res[i]);
		bin = bin + temp;
	}

	return bin;
}

//sra、srl、sll指令的转换
std::string asm2bin::m_sra_srl_sll(std::vector<string> res)
{
	std::string temp;
	std::string bin;
	std::stringstream ss;
	std::bitset<5> t;
	int a;

	if (res[0] == "sra")
		bin = "000010000001";
	else if (res[0] == "srl")
		bin = "000010000010";
	else if (res[0] == "sll")
		bin = "000010000011";
	else
		bin = "";

	ss << res[3];
	ss >> a;
	t = a;
	bin = bin + t.to_string();

	temp = reg2bin(res[1]);
	bin = bin + temp;
	bin = bin + "00000";
	temp = reg2bin(res[2]);
	bin = bin + temp;

	return bin;
}

#endif // !asm2bin_H_