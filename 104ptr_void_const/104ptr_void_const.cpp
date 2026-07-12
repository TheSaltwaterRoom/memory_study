// 104ptr_void_const.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;
struct Frame
{
    void* ctx;
};
int main(int argc, char* argv[])
{
    std::cout << "cppds.com" << endl;

    //void 指针和指针类型转换
    void* ptr1 = malloc(1024);
    free(ptr1);

    int num = 1;
    void* ptr = &num;
    int* ptr2 = static_cast<int*>(ptr); //void * 
    int* ptr3 = (int*)ptr;
    //static_cast 增加了一些验证
    const int* cptr1 = new int[1024];

    //int* ptr4 = static_cast<int*>(cptr1);
    int* ptr4 = (int*)(cptr1);
    int* ptr6 = const_cast<int*>(cptr1); //去掉const

    unsigned char* ucptr = new unsigned char[1024];
    //int* ptr5 = static_cast<int*>(ucptr);
    auto ptr5 = (int*)ucptr;
    auto ptr7 = reinterpret_cast<int*>(ucptr); //替换指针类型



    delete[]ucptr;
    delete[]cptr1;

    //常量指针和指针常量
    const int i1 = 100;
    const int* pi1 = &i1; //指向常量的指针
    //(*pi1)++; 指向的值不可修改
    int const* pi2 = &i1; // 同上
    //(*pi2)++;
    //指针本身是常量 指向不能修改 指向的值可以修改
    int* const pi3 = new int;
    //pi3++;
    //pi3 = new int;
    *pi3 = 200;
    delete pi3;
    const int* const pi4 = &i1; //指向和值都不能修改
    //pi4 = new int;
    //*pi4 = 300;






    return 0;
}