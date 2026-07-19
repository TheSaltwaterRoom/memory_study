
/*
##  未初始化内存算法 uninitialized_copy
- 将范围内的对象复制到未初始化的内存区域
- 为什么不用memcpy或者std::copy? uninitialized_copy会对对象进行复制（拷贝构造），
- 不复制如果内部有堆栈空间，将产生问题
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

int main(int argc, char* argv[])
{
    XData datas[3];
    unsigned char buf[1024] = { 0 };
    cout << "===============memcpy==============" << endl;
    memcpy(buf, &datas, sizeof(datas));
    cout << "===============copy==============" << endl;
    std::copy(std::begin(datas), std::end(datas), (XData*)(buf));
    cout << "===============uninitialized_copy==============" << endl;
    uninitialized_copy(begin(datas), end(datas), (XData*)buf);
    cout << "===========================================" << endl;

    // c++17 20 construct_at destroy对象构造和销毁
    // c++17 destroy对象和销毁
    // c++20 construct_at 对象构造
    {
        cout << "===============construct_at destroy ============================" << endl;
        int size = 3;
        auto data = static_cast<XData*> (malloc(sizeof(XData) * size));
        for (int i = 0; i < size; i++)
        {
            // c++20 调用构造函数
            if (data)
                construct_at(&data[i]);
        }
        //c++ 17 调用析构
        destroy(data, data + size);
        free(data);
        cout << "===========================================" << endl;
    }
    return 0;
}