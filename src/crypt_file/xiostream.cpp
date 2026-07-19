#include "xiostream.h"
using namespace std;
void XIOStream::Start()
{
    th_ = thread(&XIOStream::Main, this);
}
std::shared_ptr<XData> XIOStream::PopFront()
{
    std::unique_lock<mutex> lock(mux_);
    if (datas_.empty())return nullptr;
    auto re = datas_.front();
    datas_.pop_front();
    return re;
}
//给对象传递数据，线程安全
void XIOStream::PushBack(std::shared_ptr<XData> data)
{
    std::unique_lock<mutex> lock(mux_);
    datas_.push_back(data);
    //考虑最大列表
}
/// <summary>
/// 等待线程退出
/// </summary>
void XIOStream::Wait()
{
    if (th_.joinable())
        th_.join();
}