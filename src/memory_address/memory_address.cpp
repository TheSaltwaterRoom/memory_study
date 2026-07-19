// memory_address.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <iomanip>

using namespace std;

// 全局变量
int g1;        // .bss：全局未初始化，默认 0
int g2 = 0;    // .bss：全局初始化为 0
int g3 = 1;    // .data：全局初始化为非 0
int g4 = 2;    // .data：全局初始化为非 0

static int sg1 = 3; // .data：静态全局初始化为非 0
static int sg2;     // .bss：静态全局未初始化，默认 0

int main(int argc, char* argv[])
{
    static int s1 = 5; // .data：静态局部初始化为非 0

    constexpr int WIDTH = 32;

    auto print_addr = [](const char* name, const void* addr) {
        cout << left << setw(WIDTH) << name
            << " = " << addr << endl;
        };

    cout << "memory address! cppds.com" << endl;
    cout << "----------------------------------------" << endl;

    // 代码区 .text
    // 注意：函数指针转 void* 在严格标准里不是完全可移植，
    // 但在 MSVC / Windows 下通常可以用于观察地址。
    print_addr("代码区 main", reinterpret_cast<const void*>(&main));

    cout << "----------------------------------------" << endl;

    // 全局区 / 静态区
    print_addr("全局未初始化 g1", static_cast<const void*>(&g1));
    print_addr("全局初始化为 0 g2", static_cast<const void*>(&g2));
    print_addr("静态全局未初始化 sg2", static_cast<const void*>(&sg2));

    print_addr("全局初始化为 1 g3", static_cast<const void*>(&g3));
    print_addr("全局初始化为 2 g4", static_cast<const void*>(&g4));
    print_addr("静态全局初始化为 3 sg1", static_cast<const void*>(&sg1));
    print_addr("静态局部初始化为 5 s1", static_cast<const void*>(&s1));

    cout << "----------------------------------------" << endl;

    // 堆空间
    int* p1 = new int;
    int* p2 = new int;

    // p1 / p2 本身保存的是堆空间地址
    print_addr("堆空间地址 p1", static_cast<const void*>(p1));
    print_addr("堆空间地址 p2", static_cast<const void*>(p2));

    cout << "----------------------------------------" << endl;

    // &p1 / &p2 是指针变量自己在栈上的地址
    print_addr("指针变量栈地址 &p1", static_cast<const void*>(&p1));
    print_addr("指针变量栈地址 &p2", static_cast<const void*>(&p2));

    cout << "----------------------------------------" << endl;

    // 栈空间
    int i1 = 100;
    int i2 = 101;

    print_addr("栈空间地址 i1", static_cast<const void*>(&i1));
    print_addr("栈空间地址 i2", static_cast<const void*>(&i2));

    cout << "----------------------------------------" << endl;

    delete p1;
    delete p2;

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
