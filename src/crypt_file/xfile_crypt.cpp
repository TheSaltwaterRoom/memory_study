#include "xfile_crypt.h"
#include "xread_task.h"
#include "xwrite_task.h"
#include "xcrypt_task.h"
#include <iostream>
using namespace std;
bool XFileCrypt::Start(std::string infile, std::string outfile, std::string passwd, bool is_encrypt)
{
    //创建一个内存池
    shared_ptr<pmr::memory_resource> mp(new pmr::synchronized_pool_resource());

    rt_ = make_shared<XReadTask>();
    rt_->Init(infile);
    rt_->set_mem_pool(mp);

    ct_ = make_shared<XCryptTask>();
    ct_->set_mem_pool(mp);
    ct_->set_is_encrypt(is_encrypt);
    ct_->Init(passwd);
    rt_->set_next(ct_);

    wt_ = make_shared<XWriteTask>();
    wt_->set_mem_pool(mp);
    wt_->Init(outfile);

    ct_->set_next(wt_);

    rt_->Start();
    ct_->Start();
    wt_->Start();
    return true;
}
void XFileCrypt::Wait()
{
    if (rt_)
        rt_->Wait();
    if (ct_)
        ct_->Wait();
    if (wt_)
        wt_->Wait();
}