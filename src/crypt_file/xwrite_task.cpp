#include "xwrite_task.h"
#include<iostream>
#include <chrono>
using namespace std;
bool XWriteTask::Init(std::string filename)
{
    ofs_.open(filename, ios::binary);
    if (!ofs_)
    {
        cerr << "文件打开失败" << filename << endl;
        return false;
    }
    cout << filename << " open success!" << endl;
    return true;
}

void XWriteTask::Main()
{
    while (!is_exit_)
    {
        auto data = PopFront();
        if (!data)
        {
            this_thread::sleep_for(10ms);
            continue;
        }
        ofs_.write((char*)data->data(), data->size());
        if (data->end())
            break;
    }

    ofs_.close();
}