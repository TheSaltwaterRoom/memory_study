#include <iostream>
using namespace std;

// 指针与面向对象
//  限制栈中创建对象，限制调用delete销毁对象
class TestMem
{
public:
    static TestMem* Create()
    {
        cout << "static Create " << endl;
        return new TestMem();
    }
    static void Drop(TestMem* tm)
    {
        cout << "static Drop" << endl;
        delete tm;
    }
protected:

    TestMem()
    {
        cout << "Create TestMem" << endl;
    }
    virtual ~TestMem()
    {
        cout << "Drop TestMem" << endl;
    }
};

// 继承的内存指针分析
class Base
{
public:
    int x1 = 1;
    int x2 = 2;
};
class A :public Base
{
public:
    int a1 = 4;
    int x1 = 5;
};


class Base1
{
public:
    int b11 = 1;
    int b12 = 2;
};
class Base2
{
public:
    int b21 = 3;
    int b22 = 4;
};
//[Base1][Base2][A2]
class A2 :public Base1, public Base2
{
public:
    int a1 = 5;
    int a2 = 6;
};


//多继承二义性问题
class C
{
public:
    int c1;
};
class B1 :public C
{
public:
    int b1;
};
class B2 :public C
{
public:
    int b2;
};
/*
C  C
B1 B2
  A3
*/
class A3 :public B1, public B2
{
public:
    int a1 = 0;
};


class B3 :virtual public C
{
public:
    int b1;
};
class B4 :virtual public C
{
public:
    int b2;
};

/*
  C
B1 B2
  A4
*/
class A4 :public B3, public B4
{
public:
    int a1 = 0;
};
int main()
{
    {
        ////多继承二义性问题
        A3 a;
        a.B1::c1 = 1;
        cout << "&a.B1::c1 = " << (long long)&a.B1::c1 << endl;
        cout << "&a.B2::c1 = " << (long long)&a.B2::c1 << endl;

        A4 a4;
        cout << "&a4.C::c1 = " << (long long)&a4.C::c1 << endl;
        cout << "&a4.B3::c1 = " << (long long)&a4.B3::c1 << endl;
        cout << "&a4.B4::c1 = " << (long long)&a4.B4::c1 << endl;
    }
    getchar();

    //多继承内存分析
    {
        A2 a;
        cout << "&a = \t\t" << (long long)&a << endl;
        cout << "&a.b11 = \t" << (long long)&a.b11 << endl;
        cout << "&a.b21 = \t" << (long long)&a.b21 << endl;
        cout << "&a.a1 = \t" << (long long)&a.a1 << endl;
    }
    // 单继承的内存指针分析
    {
        Base b;
        //&b
        cout << "address b = " << (long long)addressof(b) << endl;
        cout << "b.x1 address:" << (long long)&b.x1 << endl;
        cout << "b.x2 address:" << (long long)&b.x2 << endl;

        A* a = new A();
        cout << "address a = \t" << (long long)a << endl;
        cout << "a->x1 = " << a->x1 << endl;
        cout << "a->Base::x1 = " << a->Base::x1 << endl;
        cout << "a->x1 address = \t" << (long long)&a->x1 << endl;
        cout << "a->Base::x1 address = \t" << (long long)&a->Base::x1 << endl;
    }

    //  限制栈中创建对象，限制调用delete销毁对象
    //TestMem tm1;
    //auto tm2 = new TestMem();
    TestMem* tm3 = TestMem::Create();
    //delete tm3;
    TestMem::Drop(tm3);

    std::cout << "cppds.com" << endl;
    return 0;
}
