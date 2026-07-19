#pragma once
#include <memory>
#include <memory_resource>
class XData
{
public:

    /// <summary>
    /// 创建空间
    /// </summary>
    /// <param name="mem_size">占用内存字节数</param>
    /// <returns></returns>
    void* New(long long mem_size);

    //设置实际数据字节数
    void set_size(long long s) { size_ = s; }
    long long size() { return size_; }
    void* data() { return data_; }
    bool end() { return end_; }
    void set_end(bool e) { end_ = e; }
    /// <summary>
    /// 创建XData智能指针对象
    /// </summary>
    /// <param name="pool"></param>
    /// <returns></returns>
    static std::shared_ptr<XData> Make(std::shared_ptr<std::pmr::memory_resource> pool);

    ~XData();

private:
    bool end_ = false;
    void* data_ = nullptr;
    long long size_ = 0;        //数据字节数
    long long mem_size_ = 0;    //占用空间字节数
    std::shared_ptr<std::pmr::memory_resource> mem_pool_;
    XData() {} //用户不能自己创建
};