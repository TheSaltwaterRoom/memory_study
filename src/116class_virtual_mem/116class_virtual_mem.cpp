#include <iostream>
#include <cstdint>  // std::uintptr_t

using namespace std;

// 虚函数表分析
class B
{
public:
    virtual void Test1()
    {
        cout << "B test1" << endl;
    }

    virtual void Test2()
    {
        cout << "B test2" << endl;
    }
};

class A : public B
{
public:
    void Test1() override
    {
        cout << "A test1" << endl;
    }

    void Test2() override
    {
        cout << "A test2" << endl;
    }
};

class C : public B
{
public:
    void Test1() override
    {
        cout << "C test1" << endl;
    }

    void Test2() override
    {
        cout << "C test2" << endl;
    }
};

void TestClass(B* b)
{
    cout << "in TestClass" << endl;
    b->Test1();
}

int main()
{
    // 测试虚函数表，只用于验证编译器实现原理，不可工程化
    {
        A a1;
        A a2;

        /*
         * &a1 的类型是 A*
         *
         * reinterpret_cast<void***>(&a1)
         * 将对象地址看成“指向 vfptr 的指针”
         *
         * 解引用一次后取得对象中的 vfptr，
         * 也就是虚函数表地址。
         */
        void** vftable1 = *reinterpret_cast<void***>(&a1);
        void** vftable2 = *reinterpret_cast<void***>(&a2);

        cout << "a1 address       = "
            << reinterpret_cast<std::uintptr_t>(&a1)
            << endl;

        cout << "a1 vftable       = "
            << reinterpret_cast<std::uintptr_t>(vftable1)
            << endl;

        cout << "a2 address       = "
            << reinterpret_cast<std::uintptr_t>(&a2)
            << endl;

        cout << "a2 vftable       = "
            << reinterpret_cast<std::uintptr_t>(vftable2)
            << endl;

        cout << "A::Test1 address = "
            << reinterpret_cast<std::uintptr_t>(vftable1[0])
            << endl;

        cout << "A::Test2 address = "
            << reinterpret_cast<std::uintptr_t>(vftable1[1])
            << endl;

        cout << boolalpha;

        cout << "a1和a2地址是否相同："
            << (&a1 == &a2)
            << endl;

        cout << "a1和a2虚函数表是否相同："
            << (vftable1 == vftable2)
            << endl;

        /*
         * 非静态成员函数实际上存在隐藏的 this 参数。
         *
         * 下面的写法相当于手动向虚函数传递 this：
         *
         * test1(&a1);
         *
         * 注意：这种调用方式依赖 MSVC x64 ABI，
         * 不属于 C++ 标准保证的行为。
         */
        using VFunc = void (*)(A*);

        auto test1 = reinterpret_cast<VFunc>(vftable1[0]);
        auto test2 = reinterpret_cast<VFunc>(vftable1[1]);

        cout << "\n通过虚函数表调用：" << endl;

        test1(&a1);
        test2(&a1);
    }

    getchar();

    {
        cout << "\n正常的虚函数调用：" << endl;

        B b;
        b.Test1();

        A a;
        a.Test1();

        TestClass(&a);

        C c;
        TestClass(&c);
    }

    cout << "cppds.com" << endl;

    return 0;
}