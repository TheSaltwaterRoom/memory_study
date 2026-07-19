#pragma once
#include <thread>
#include <memory_resource>
#include <list>
#include "xdata.h"
class XIOStream
{
public:
    /// <summary>
    /// 线程启动
    /// </summary>
    void Start();

    /// <summary>
    /// 等待线程退出
    /// </summary>
    void Wait();

    //线程退出，需要用Wait等待
    void Stop() { is_exit_ = true; }

    void set_mem_pool(std::shared_ptr<std::pmr::memory_resource> p) { mem_pool_ = p; }

    //设置责任链下一个节点
    void set_next(std::shared_ptr<XIOStream> next) { next_ = next; }

    //给对象传递数据，线程安全
    void PushBack(std::shared_ptr<XData> data);

    std::shared_ptr<XData> PopFront();
protected:
    //线程入口
    virtual void Main() {}

    bool is_exit_ = false;

    long long data_byte_ = 0; //所有要处理数据的字节数

    std::shared_ptr<std::pmr::memory_resource> mem_pool_;
    /// <summary>
    /// 责任链代码
    /// </summary>
    std::shared_ptr<XIOStream> next_;



private:
    std::thread th_;
    std::mutex mux_;
    std::list<std::shared_ptr<XData>> datas_;
};