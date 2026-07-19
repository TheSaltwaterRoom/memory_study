// 110operator_new.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
/*
## 重载new和delete
### 为什么要重载
- 监测内存创建销毁 ，统计和监控泄漏
- 内存对齐的处理
- 特定应用：例如多进程内存共享
### 重载全局的new和delete
*/
#include <iostream>
using namespace std;

//重载全局的new和delete
void* operator new(size_t size)
{
	cout << "operator new :" << size << endl;
	auto mem = malloc(size);
	if (!mem)
	{
		throw std::bad_alloc();
	}
	return mem;
}
void* operator new[](size_t size)
{
	cout << "operator new [] :" << size << endl;
	auto mem = malloc(size);
	if (!mem)
	{
		throw std::bad_alloc();
	}
	return mem;
}

void operator delete(void* ptr)
{
	cout << "operator delete" << endl;
	std::free(ptr);
}
void operator delete[](void* ptr)
{
	cout << "operator delete[]" << endl;
	std::free(ptr);
}
class TestMem
{
public:
	int index = 0;
	TestMem()
	{
		cout << "Create TestMem" << endl;
	}
	~TestMem()
	{
		cout << "Drop TestMem" << endl;
	}

	void* operator new (size_t size)
	{
		cout << "TestMem new " << size << endl;
		auto mem = malloc(size);
		if (!mem)
		{
			throw std::bad_alloc();
		}
		return mem;
	}

	void* operator new[](size_t size)
	{
		cout << "TestMem new []" << size << endl;
		auto mem = malloc(size);
		if (!mem)
		{
			throw std::bad_alloc();
		}
		return mem;
	}

	//placement new
	void* operator new (size_t size, void* ptr)
	{
		cout << "placement new" << endl;
		return ptr;
	}
	void operator delete(void* ptr)
	{
		cout << "TestMem operator delete" << endl;
		std::free(ptr);
	}
	void operator delete[](void* ptr)
	{
		cout << "TestMem operator delete[]" << endl;
		std::free(ptr);
	}
};

int main(int argc, char* argv[])
{
	//placement new
/*
### 放置placement new和delete,new的空间指向已有的地址中
- 普通new申请空间是从堆中分配空间，一些特殊的需求要在已分配的空间中创建对象，就可以使用放置placement new
操作
- placement new生成对象既可以在栈上，也可以在堆上
- placement new生成对象销毁要手动调用析构函数
*/

	std::cout << "cppds.com" << endl;
	int* i1 = new int;
	delete i1;

	auto mem1 = new TestMem();
	delete mem1;

	int* arr1 = new int[1024];
	delete[]arr1;

	TestMem* memarr1 = new TestMem[2];
	delete[] memarr1;

	cout << "=======================================" << endl;
	int buf1[1024] = { 0 };
	TestMem* mem2 = ::new(buf1) TestMem;
	cout << "buf1 addr:" << buf1 << endl;
	cout << "mem2 addr:" << mem2 << endl;
	mem2->~TestMem();

	int* buf2 = new int[1024] {0};
	auto mem3 = ::new(buf2) TestMem;

	// 错误示例：mem3 只是通过 placement new 构造在 buf2 的内存上，
	// delete mem3 会调用析构函数并尝试释放底层内存，
	// 但这块内存是通过 new int[] 分配的，释放方式不匹配，会产生未定义行为。
	// 正确做法：mem3->~TestMem(); 然后 delete[] buf2;
	delete mem3;


	int* buf3 = new int[1024] { 0 };
	auto mem4 = new(buf3)TestMem;
	cout << "buf3 addr:" << buf3 << endl;
	cout << "mem4 addr:" << mem4 << endl;
	mem4->~TestMem();
	delete[]buf3;


	return 0;
}
