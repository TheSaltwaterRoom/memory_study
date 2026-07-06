// 101pointer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;
int main()
{
    cout << "101 pointer" << endl;
    //指针类型 p1变量存在栈中
    //new int 堆中
    int* p1 = new int;
    // *间接符号
    *p1 = 101;
    int i = 10;
    cout << "i = " << i << endl;
    int* p2 = &i;
    *p2 = 102;
    cout << "i = " << i << endl;
    cout << "p1 = " << p1 << endl;
    cout << "sizeof(p1) = " << sizeof(p1) << endl;
    cout << "sizeof(*p1) = " << sizeof(*p1) << endl;
    delete p1;
    cout << "after delete p1 = " << p1 << endl;
    if (p1)
    {
        cout << "p1 not empty?" << endl;
    }
    p1 = nullptr; // nullptr c++11 NULL 0
    delete p1;
    if (!p1)
    {
        cout << "p1 is empty!" << endl;
    }
    //delete p1;
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
