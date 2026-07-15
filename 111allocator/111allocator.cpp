/*
## 分配器allocator
- 分配器用于实现容器算法时，将其与存储细节隔离从而解耦合。
- 分配器提供存储分配与释放的标准方法
- 对象内存分配和构造分离
*/
#include <iostream>
#include <vector>
#include <list>
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
    ~XData()
    {
        cout << "Drop XData " << index << endl;
    }
    int index = 0;
};

template <typename Ty>
class MyAllocator
{
public:
    using value_type = Ty;

    MyAllocator() {}

    template<class Other>
    MyAllocator(const MyAllocator<Other>&) {}

    //内存释放
    void deallocate(Ty* const ptr, const size_t count)
    {
        cout << "deallocate " << count << endl;
        free(ptr);
    }

    //内存分配
    Ty* allocate(const size_t count)
    {
        cout << "allocate " << count << endl;
        cout << typeid(Ty).name() << endl;
        return static_cast<Ty*> (malloc(sizeof(Ty) * count));
    }
};
int main(int argc, char* argv[])
{
    std::cout << "cppds.com" << endl;

    /*
    #include <memory>
    std::allocator
    address (C++17 中弃用)(C++20 中移除)
    allocate 分配未初始化的存储
    deallocate 解分配存储
    max_size(C++17 中弃用)(C++20 中移除)
    construct (C++17 中弃用)(C++20 中移除)
    destroy(C++17 中弃用)(C++20 中移除)
    */
    allocator<XData> xdata_allco;
    int size = 3;

    //分配对象空间 不调用构造
    auto dataarr = xdata_allco.allocate(size);

    for (int i = 0; i < size; i++)
    {
        //allocator_traits 类模板提供访问分配器 (Allocator) 各种属性的标准化方式
        //allocator_traits< allocator<XData> >

        //调用构造
        allocator_traits< decltype(xdata_allco)>::construct(xdata_allco, &dataarr[i]);

        //调用析构函数
        allocator_traits< decltype(xdata_allco)>::destroy(xdata_allco, &dataarr[i]);
    }

    //释放对象内存 不调用析构
    xdata_allco.deallocate(dataarr, size);

    cout << "====================================" << endl;
    //## 自定义分配器
    //- 可以实现内存共享、内存泄漏探测，预分配对象存储、内存池
    //- 演示自定义vector和list分配器，并分析其源码
    vector<XData, MyAllocator<XData> > vd;
    XData d;
    d.index = 111;
    vd.push_back(d);
    d.index = 222;
    vd.push_back(d);
    d.index = 333;
    vd.push_back(d);
    for (auto& xd : vd)
    {
        cout << xd.index << endl;
    }
    cout << "==================== list =======================" << endl;
    list<XData, MyAllocator<XData>> datas;
    d.index = 444;
    datas.push_back(d);
    d.index = 555;
    datas.push_back(d);
    d.index = 666;
    datas.push_back(d);
    for (auto& d : datas)
    {
        cout << d.index << endl;
    }
    getchar();


    return 0;
}