// 108weak_ptr.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

/*
## weak_ptr
    use_count
        返回管理该对象的 shared_ptr 对象数量
    lock
        创建管理被引用的对象的shared_ptr
*/
#include <iostream>
using namespace std;
class XData
{
public:
    XData()
    {
        cout << "Create XData" << endl;
    }
    ~XData()
    {
        cout << "Drop XData" << endl;
    }
    int index1 = 0;
    int idnex2 = 0;
};

class B;
class A
{
public:
    A() { cout << "Create A" << endl; }
    ~A() { cout << "Drop A" << endl; }
    void Do()
    {
        cout << "Do b2.use_count() = " << b2.use_count() << endl;
        auto b = b2.lock(); //复制一个共享智能指针 引用计数+1
        cout << "Do b2.use_count() = " << b2.use_count() << endl;
    }
    shared_ptr<B> b1;
    weak_ptr<B> b2;
};
class B
{
public:
    B() { cout << "Create B" << endl; }
    ~B() { cout << "Drop B" << endl; }
    shared_ptr<A> a1;
};
int main(int argc, char* argv[])
{
    std::cout << "cppds.com" << endl;
    //5 shared_ptr循环引用问题原理
    {
        auto a = make_shared<A>(); //=1
        auto b = make_shared<B>(); //=1
        a->b1 = b; //+1 =2
        cout << "a->b1 = b b.use_count()=" << b.use_count() << endl;
        b->a1 = a; //+1 =2
        cout << "b->a1 = a a.use_count()=" << a.use_count() << endl;
    }
    //a 出作用域 a.use_count - 1 = 1 a资源不释放 a.b1不释放 
    // ?  b.use_count = 2
    // b 出作用域 b.use_count - 1 = 1 b资源不释放 b.a1 不释放
    // ? b.use_count = 1 a.use_count = 1

    cout << "after AB}" << endl;
    {
        auto a = make_shared<A>(); //=1
        auto b = make_shared<B>(); //=1
        a->b2 = b; //=1
        a->Do();
        cout << "a->b2 = b, b.use_count() = "
            << b.use_count() << endl;
        b->a1 = a; //+1 =2
        cout << "b->a1 = a a.use_count()=" << a.use_count() << endl;
    }

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
