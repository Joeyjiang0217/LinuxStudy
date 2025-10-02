#include "PollServer.hpp"
#include <memory>

int main()
{
    // cout << "fd_set size: " << sizeof(fd_set) * 8 << endl;
    std::unique_ptr<PollServer> svr(new PollServer());
    svr->Init();
    svr->Start();
    return 0;
}