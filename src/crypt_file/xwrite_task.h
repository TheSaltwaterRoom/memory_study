#pragma once
#include "xiostream.h"
#include <fstream>
class XWriteTask :public XIOStream
{
public:
    bool Init(std::string filename);
private:
    void Main();
    std::ofstream ofs_;
};