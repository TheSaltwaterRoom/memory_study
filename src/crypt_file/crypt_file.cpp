#include <iostream>
#include <memory>
#include <memory_resource>
#include "xcrypt.h"
#include "xread_task.h"
#include "xcrypt_task.h"
#include "xwrite_task.h"
#include "xfile_crypt.h"
#include <filesystem>
#include<list>
using namespace std;
using namespace filesystem;
using namespace std;

int main(int argc, char* argv[])
{
    // 加密文件指令： crypt_file 输入文件夹 输出文件夹 密码  
    // 解密文件指令： crypt_file 输入文件夹 输出文件夹 密码  -d
    if (argc < 4)
    {
        cerr << "para error" << endl;
        return -1;
    }
    string in_file = argv[1]; //输入文件夹
    string out_file = argv[2];//输出文件夹
    string password = argv[3];//密码
    bool is_encrypt = true;
    if (argc > 4)is_encrypt = false;

    //创建输出文件夹
    create_directories(out_file);
    //if (is_encrypt)
    {
        list<shared_ptr<XFileCrypt>> fes;

        for (auto& p : directory_iterator(in_file)) //遍历输入目录
        {
            if (!p.is_regular_file())continue;//只处理文件
            auto fe = make_shared<XFileCrypt>();
            fe->Start(p.path().string(),  //输入文件
                out_file + "\\" + p.path().filename().string(), //输出文件
                password, is_encrypt
            );
            fes.push_back(fe);
        }

        for (auto fe : fes)
        {
            fe->Wait();
        }

    }

    cout << "目录下文件批量加密" << endl;
    std::string passwd = "12345678";
    #include "xfile_crypt.h"
    {
        auto xfc = make_shared<XFileCrypt>();
        xfc->Start("test.txt", "test_end.txt", passwd, true);
        xfc->Wait();

        auto xfd = make_shared<XFileCrypt>();
        xfd->Start("test_end.txt", "test_dec.txt", passwd, false);
        xfd->Wait();
    }

    {
        //创建一个内存池
        shared_ptr<pmr::memory_resource> mp(new pmr::synchronized_pool_resource());

        auto rt = make_shared<XReadTask>();
        rt->Init("./img/test.png");
        rt->set_mem_pool(mp);

        auto ct = make_shared<XCryptTask>();
        ct->set_mem_pool(mp);
        ct->set_is_encrypt(true);
        ct->Init(passwd);
        rt->set_next(ct);

        auto wt = make_shared<XWriteTask>();
        wt->set_mem_pool(mp);
        wt->Init("test_out.png");

        ct->set_next(wt);

        rt->Start();
        ct->Start();
        wt->Start();
        rt->Wait();
        ct->Wait();
        wt->Wait();
    }

    //////////////////////////////////
    //开始解密
    {
        shared_ptr<pmr::memory_resource> mp(new pmr::synchronized_pool_resource());
        auto rt = make_shared<XReadTask>();
        rt->Init("test_out.png");
        rt->set_mem_pool(mp);

        auto ct = make_shared<XCryptTask>();
        ct->set_mem_pool(mp);
        ct->Init(passwd);
        ct->set_is_encrypt(false);
        rt->set_next(ct);

        auto wt = make_shared<XWriteTask>();
        wt->set_mem_pool(mp);
        wt->Init("test_dec.png");

        ct->set_next(wt);

        rt->Start();
        ct->Start();
        wt->Start();
        rt->Wait();
        ct->Wait();
        wt->Wait();


    }






    XCrypt crypt;
    crypt.Init("12345678");
    char out[1024] = { 0 };
    int en_size = crypt.Encrypt("abcdefgh", 8, out, true);
    cout << "en_size = " << en_size << endl;
    cout << out << endl;
    char de_out[1024] = { 0 };
    int de_size = crypt.Decrypt(out, en_size, de_out, true);
    cout << de_size << ":de_out=" << de_out << endl;





    return 0;
}