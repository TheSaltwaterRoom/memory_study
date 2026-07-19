#pragma once
#include "xiostream.h"
class XCrypt;
class XCryptTask :public XIOStream
{
public:

    //初始化加解密秘钥
    void Init(std::string passwd);
    void set_is_encrypt(int ise) { is_encrypt_ = ise; }
private:
    void Main();
    std::shared_ptr<XCrypt> enc_;
    bool is_encrypt_ = true;
};