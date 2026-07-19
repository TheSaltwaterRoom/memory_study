#include "xcrypt.h"
#include <iostream>
using namespace std;

//获取需要填充的数据字节数
int XCrypt::GetPadding(int datasize)
{
    const int block_size = sizeof(const_DES_cblock);
    int padding = block_size - datasize % block_size;
    if (padding == 0) padding = block_size;
    return padding;
}
///初始化秘钥,DES加密算法 秘钥最多8位 多余丢弃不足补0
bool XCrypt::Init(std::string password)
{
    const_DES_cblock key = { 0 }; //不足补0
    int key_size = password.size();
    if (key_size > sizeof(key)) //多余丢弃
    {
        key_size = sizeof(key);
    }
    memcpy(key, password.c_str(), key_size);
    DES_set_key(&key, &key_sch_);
    return true;
}


/// <summary>
/// 加密数据，结尾填充补充的大小，加密数据大小如果不是 8,16的倍数
/// </summary>
/// <param name="indata">输入数据</param>
/// <param name="insize">输入大小</param>
/// <param name="out_data">输出数据</param>
/// <param name="is_end">是否到加密结尾</param>
/// <returns>返回加密后数据，有可能大于输入，添加补充</returns>
int XCrypt::Encrypt(const char* in_data, int insize, char* out_data, bool is_end)
{
    if (!in_data || insize <= 0 || !out_data) return 0;
    int write_size = 0;
    const_DES_cblock in = { 0 };    //输入数据
    DES_cblock out = { 0 };         //输出
    const int block_size = sizeof(const_DES_cblock);
    int data_size = 0;
    int padding = block_size - insize % block_size;


    for (int i = 0; i < insize; i += block_size)
    {
        if (insize - i < block_size)
        {
            data_size = insize - i;
        }
        else
        {
            data_size = block_size;
        }

        //复制数据源
        memcpy(in, in_data + write_size, data_size);

        //填充 补充的数据大小  @@@@@@@1   @@@55555 @@@@@@@@8888888
        if (is_end && i + block_size >= insize) //处理最后一块数据
        {
            //@@@@@@@@8888888
            if (padding == block_size)
            {
                DES_ecb_encrypt(&in, &out, &key_sch_, DES_ENCRYPT);
                memcpy(out_data + write_size, &out, block_size);
                write_size += block_size;
                memset(in, padding, sizeof(in)); //填充8
            }
            //@@@@@@@1   @@@55555
            else
            {
                memset(in + insize % block_size, padding, padding);
            }

        }

        //加密数据
        DES_ecb_encrypt(&in, &out, &key_sch_, DES_ENCRYPT);
        memcpy(out_data + write_size, &out, block_size);

        write_size += block_size;
    }
    return write_size;
}

/// <summary>
/// 解密数据，结尾去掉填充大小
/// </summary>
/// <param name="in_data">输入数据</param>
/// <param name="insize">输入大小</param>
/// <param name="out_data">输出数据</param>
/// <param name="is_end">是否到加密结尾</param>
/// <returns>返回加密后数据，有可能小于输入，去掉</returns>
int XCrypt::Decrypt(const char* in_data, int insize, char* out_data, bool is_end)
{
    if (!in_data || insize <= 0 || !out_data) return 0;
    int write_size = 0;
    const_DES_cblock in = { 0 };    //输入数据
    DES_cblock out = { 0 };         //输出
    const int block_size = sizeof(const_DES_cblock);
    int data_size = 0;
    for (int i = 0; i < insize; i += block_size)
    {
        memcpy(in, in_data + write_size, block_size);

        //解密
        DES_ecb_encrypt(&in, &out, &key_sch_, DES_DECRYPT);
        data_size = block_size;
        //处理结尾填充 @@@55555 @@@@@@@@8888888
        if (is_end && insize - i <= block_size)
        {
            data_size = block_size - out[7];
            if (data_size == 0)
            {
                break;
            }
            else if (data_size < 0)
            {
                cerr << "Decrypt failed!padding size error!" << endl;
                break;
            }
        }
        memcpy(out_data + write_size, &out, data_size);
        write_size += data_size;
    }
    return write_size;
}