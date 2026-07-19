// 106unique_ptr.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
using namespace std;
class Data
{
public:
	static int count;
	int index = 0;
	Data()
	{
		count++;
		index = count;
		cout << index << ":Create Data" << endl;
	}
	~Data()
	{
		cout << index << ":Drop Data" << endl;
	}
};
struct XPacket
{
	unsigned char* data = nullptr;
	int size = 0;
};
class PacketDelete
{
public:
	void Close()
	{
		cout << "Call PakcetDelete Close!" << endl;
	}
	void operator()(XPacket* p) const
	{
		cout << "call PacketDelete()" << endl;
		delete p->data;
		delete p;
	}


};
int Data::count = 0;
int main(int argc, char* argv[])
{
	std::cout << "cppds.com" << endl;
	//1 unique_ptr 初始化
	// RAII资源获取即初始化（Resource Acquisition Is Initialization）
	{
		unique_ptr<int> p1(new int);
		unique_ptr<Data> p2(new Data);
		cout << "======1======" << endl;
		auto p3 = make_unique<Data>();

		//空智能指针
		unique_ptr<Data> p4;
		unique_ptr<int[]> pa1 = make_unique<int[]>(1024);
		unique_ptr<int[]> pa2(new int[1024]);
		unique_ptr<Data[]> pa3(new Data[3]);

		// unique_ptr智能指针访问和移动构造赋值
		*p1 = 10;
		cout << "p1 value=" << *p1 << endl;
		cout << "(*p2).index =" << (*p2).index << endl;
		cout << "p2->index = " << p2->index << endl;
		auto d1 = new Data();
		unique_ptr<Data> p5(d1);
		cout << "p5 address:" << p5 << endl;
		cout << "d1 address:" << d1 << endl;
		cout << "p5.get():" << p5.get() << endl;
		//unique_ptr智能指针数组访问
		pa2[1] = 100;
		pa2[0] = 1;
		cout << " pa3[1].index = " << pa3[1].index << endl;
		cout << "pa3.get()[2].index = " << pa3.get()[2].index << endl;


		//重置和移动内存资源
	    // unique_ptr

		unique_ptr<Data> p6(new Data());
		// 不可复制构造
		//unique_ptr<Data> p7 = p6;
		//不可以赋值
		//p7 = p6;
		//支持移动构造 p6释放所有权 转移到p7
		unique_ptr<Data> p7 = move(p6);
		unique_ptr<Data> p8(new Data());

		//支持移动赋值
		p7 = move(p8);

		//重置空间，原空间清理
		p7.reset(new Data());

		cout << "begin p7 = nullptr" << endl;
		//释放所有权和自定义空间删除方法
		//主动释放空间
		p7 = nullptr;


		unique_ptr<Data> p9(new Data);
		//释放所有权
		auto ptr9 = p9.release();
		delete ptr9;

		cout << "end p7 = nullptr" << endl;

		//自定义空间删除方法
		unique_ptr<XPacket, PacketDelete> pd1(new XPacket);
		unique_ptr<XPacket, PacketDelete> pd2(new XPacket);
		pd2.get_deleter().Close();
		//pd2.get_deleter()(pd2.get());
		//pd2.release();

		XPacket* raw = pd2.release();
		pd2.get_deleter()(raw);
	}
	cout << "======2======" << endl;
	getchar();
	return 0;
}