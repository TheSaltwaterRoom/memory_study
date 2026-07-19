// 114_string_vector_mem.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include <iostream>
#include <string>
#include <vector>
using namespace std;

class XData
{
public:
	XData()
	{
		cout << "Create XData" << endl;
	}
	XData(const XData& d)
	{
		this->index = d.index;
		cout << "Copy XData " << index << endl;
	}
	XData& operator=(const XData& d)
	{
		this->index = d.index;
		cout << "=XData" << index << endl;
		return *this;
	}
	~XData()
	{
		cout << "Drop XData " << index << endl;
	}

	int index = 0;
};

void TestString(string& in_data, string& out_data)
{
	cout << "in_data=" << in_data << endl;
	cout << in_data.size() << endl;
	cout << "in_data addr:" << (long long)in_data.data() << endl;
	out_data.resize(1024);
	cout << "out_data addr:" << (long long)out_data.data() << endl;
}

vector<XData> TestVec(vector<XData>& data)
{
	cout << "TestVec data:" << data.data() << endl;
	vector<XData> re;
	re.resize(3);
	cout << "re.data()" << re.data() << endl;
	cout << "re Byte=" << re.size() * sizeof(XData) << endl;

	return re;
}

int main(int argc, char* argv[])
{

	// 使用string 传递和获取内存
	// 不需要考虑内存释放
	// 可以获取已申请内存大小

	std::cout << "cppds.com" << endl;

	string str1;
	str1.resize(1024);
	auto data = const_cast<char*>(str1.data());
	cout << "addr:" << (long long)data << endl;
	memset(data, 'A', 5);
	cout << str1 << endl;
	string out_str;
	cout << "out_str addr:" << (long long)out_str.data() << endl;
	TestString(str1, out_str);
	cout << "out_str size = " << out_str.size() << endl;
	cout << "out_str addr:" << (long long)out_str.data() << endl;

	std::cout << "cppds.com" << endl;
	// 使用vector 传递和获取内存
	// 功能等同于string
	// 可用传递不同的类型
	// 可以用作返回值支持move
	{
		vector<XData> vd;
		XData d;
		d.index = 1;
		vd.push_back(d);
		d.index = 2;
		vd.push_back(d);
		d.index = 3;
		vd.push_back(d);
		cout << "vd.data() = " << vd.data() << endl;
		auto rd = TestVec(vd);
		cout << "rd.data()" << rd.data() << endl;
	}
	getchar();
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
