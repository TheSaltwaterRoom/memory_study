#pragma once
#include "xiostream.h"
#include <string>
#include <fstream>
class XReadTask :public XIOStream
{
public:

    /// <summary>
    /// 初始化读取线程，获取文件大小
    /// </summary>
    /// <param name="filename"></param>
    /// <returns></returns>
    bool Init(std::string filename);
private:
    //线程入口
    void Main();
    std::ifstream ifs_; //读取文件
};
