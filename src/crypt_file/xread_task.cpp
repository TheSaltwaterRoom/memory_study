#include "xread_task.h"
#include <iostream>
#include "xdata.h"
using namespace std;
/// <summary>
/// 初始化读取线程，获取文件大小
/// </summary>
/// <param name="filename"></param>
/// <returns></returns>
bool XReadTask::Init(std::string filename)
{
    if (filename.empty())return false;
    ifs_.open(filename, ios::binary); //二进制打开
    if (!ifs_)
    {
        cerr << "open file " << filename << " failed!" << endl;
        return false;
    }
    cout << filename << " open success!" << endl;
    ifs_.seekg(0, ios::end);
    data_byte_ = ifs_.tellg();
    ifs_.seekg(0, ios::beg);
    cout << " file size " << data_byte_ << endl;
    return true;
}
void XReadTask::Main()
{
    cout << "begin thread XReadTask::Main" << endl;
    while (!is_exit_)
    {
        if (ifs_.eof())break;
        //char buf[10240] = { 0 };

        //创建内存池空间管理对象
        auto data = XData::Make(this->mem_pool_);
        int data_size = 1024;

        //申请空间
        void* buf = data->New(data_size);

        //读取文件
        ifs_.read((char*)buf, data_size);

        if (ifs_.gcount() <= 0)break;
        data->set_size(ifs_.gcount());
        if (ifs_.eof())
        {
            data->set_end(true);
        }
        //cout << "["<<ifs_.gcount()<<"]" << flush;

        if (next_)
        {
            next_->PushBack(data);
        }
    }
    ifs_.close();
    cout << "end thread XReadTask::Main" << endl;
}