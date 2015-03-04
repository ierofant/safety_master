#include "master.hpp"

server::server(master &service)
    : service(service),
      acceptor(service, tcp::v4())
{

}

master&
server::get_service()
{
    return service;
}

void 
server::bind(unsigned port)
{
    acceptor.set_option(socket_base::reuse_address(true));
    acceptor.bind(tcp::endpoint(tcp::v4(), port));
    acceptor.listen(10);
}

void 
server::disconnect(const boost::shared_ptr<connection> &client)
{
    clients.erase(client);
}
