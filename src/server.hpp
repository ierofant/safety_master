#ifndef SERVER_HPP
#define SERVER_HPP

#include <set>
#include "connection.hpp"

class master;
class server
{
public:
    server(master &service);

    master& get_service();
    void bind(unsigned port);
    void disconnect(const boost::shared_ptr<connection> &client);

private:
    master &service;
    tcp::acceptor acceptor;
    std::set<boost::shared_ptr<connection> > clients;
};

#endif //SERVER_HPP
