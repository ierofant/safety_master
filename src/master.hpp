#ifndef MASTER_HPP
#define MASTER_HPP

#include "server.hpp"
#include "rules.hpp"

class master : public io_service
{
public:
    void bind_tcp(unsigned port);
    void bind_can(const std::string &candev);
    void read_config(const std::string &filename);

private:
    server s;
    rules r;
};

#endif //MASTER_HPP