#pragma once
#include <string>
#include <openssl/des.h>

class XCrypt
{
public:
    ///初始化秘钥,DES加密算法 秘钥最多8位 多余丢弃不足补0
    bool Init(std::string password);

    /// <summary>
    /// 加密数据，结尾填充补充的大小，加密数据大小如果不是 8,16的倍数
    /// </summary>
    /// <param name="in_data">输入数据</param>
    /// <param name="insize">输入大小</param>
    /// <param name="out_data">输出数据</param>
    /// <param name="is_end">是否到加密结尾</param>
    /// <returns>返回加密后数据，有可能大于输入，添加补充</returns>
    int Encrypt(const char* in_data, int insize, char* out_data, bool is_end = false);

    /// <summary>
    /// 解密数据，结尾去掉填充大小
    /// </summary>
    /// <param name="in_data">输入数据</param>
    /// <param name="insize">输入大小</param>
    /// <param name="out_data">输出数据</param>
    /// <param name="is_end">是否到加密结尾</param>
    /// <returns>返回加密后数据，有可能小于输入，去掉</returns>
    int Decrypt(const char* in_data, int insize, char* out_data, bool is_end = false);

    //获取需要填充的数据字节数
    int GetPadding(int datasize);
private:
    //存储秘钥
    DES_key_schedule key_sch_;
};