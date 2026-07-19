#pragma once
#include <string>
#include <memory>
class XReadTask;
class XWriteTask;
class XCryptTask;
class XFileCrypt
{
public:
    bool Start(std::string infile, std::string outfile, std::string passwd, bool is_encrypt);
    void Wait();
private:
    std::shared_ptr<XReadTask> rt_;
    std::shared_ptr<XCryptTask> ct_;
    std::shared_ptr<XWriteTask> wt_;
};
