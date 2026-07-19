#include "xdata.h"
#include <iostream>
using namespace std;

/// <summary>
/// 创建XData智能指针对象
/// </summary>
/// <param name="pool"></param>
/// <returns></returns>
std::shared_ptr<XData> XData::Make(std::shared_ptr<std::pmr::memory_resource> pool)
{
    std::shared_ptr<XData> ptr(new XData);
    ptr->mem_pool_ = pool;
    return ptr;
}

/// <summary>
/// 创建空间
/// </summary>
/// <param name="mem_size">占用内存字节数</param>
/// <returns></returns>
void* XData::New(long long mem_size)
{
    if (mem_size <= 0)
    {
        cerr << "XData::New failed! mem_size<=0" << endl;
        return nullptr;
    }
    if (!mem_pool_)return nullptr;
    data_ = mem_pool_->allocate(mem_size);
    this->mem_size_ = mem_size;
    this->size_ = mem_size;
    //cout << "+" << flush;
    return data_;
}

XData::~XData()
{
    if (!data_ || !mem_pool_)return;
    mem_pool_->deallocate(data_, mem_size_);
    data_ = nullptr;
    mem_size_ = 0;
    size_ = 0;
    //cout << "-" << flush;
}