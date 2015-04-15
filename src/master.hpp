#ifndef MASTER_HPP
#define MASTER_HPP

#include "server.hpp"
#include "rules.hpp"
#include "storage.hpp"
#include "can.hpp"

class master : public io_service
{
public:
    typedef rules::ident_type ident_type;

    master();

    bool parse_options(int argc, char *argv[]);
    void set_safety_level(ident_type ident, safety_level level);
    void refresh_vartable();
    
private:
    void bind_tcp(unsigned port);
    void bind_can(const std::string &candev);
    void read_config_from_file(const std::string &filename);
    void read_config(const std::string &str);
    void update();

private:
    server s;
    rules r;
    storage timer;
    can c;
};

#endif //MASTER_HPP