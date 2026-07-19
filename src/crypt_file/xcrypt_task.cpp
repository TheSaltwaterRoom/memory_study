#include "xcrypt_task.h"
#include "xcrypt.h"
#include <iostream>
#include <chrono>
using namespace std;

//初始化加解密秘钥
void XCryptTask::Init(std::string passwd)
{
    enc_ = make_shared<XCrypt>();
    enc_->Init(passwd);
}
void XCryptTask::Main()
{
    cout << "begin XCryptTask::Main()" << endl;
    while (!is_exit_)
    {
        auto data = PopFront();
        if (!data)
        {
            this_thread::sleep_for(10ms);
            continue;
        }
        auto out = XData::Make(mem_pool_);
        int outsize = data->size() + enc_->GetPadding(data->size());
        out->New(outsize);
        int data_size = 0;
        bool is_end = data->end();

        if (is_encrypt_)
        {
            data_size = enc_->Encrypt((char*)data->data(), data->size(), (char*)out->data(), is_end);
        }
        else
        {
            data_size = enc_->Decrypt((char*)data->data(), data->size(), (char*)out->data(), is_end);
        }

        out->set_size(data_size);

        cout << "{" << out->size() << "}" << flush;
        out->set_end(data->end());

        if (next_)
        {
            next_->PushBack(out);
        }
        if (data->end())
        {
            break;
        }
    }
    cout << "end XCryptTask::Main()" << endl;
}