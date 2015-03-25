#include <boost/bind.hpp>
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
    accept();
}

void 
server::disconnect(const boost::shared_ptr<connection> &client)
{
    clients.erase(client);
}

void
server::connect(const boost::shared_ptr<connection> &client)
{
	clients.insert(client);
}

void
server::accept()
{
	boost::shared_ptr<connection> client = connection::create(*this);
	acceptor.async_accept(client->get_socket(), boost::bind(&server::on_accept, this, client, placeholders::error));
}

void
server::on_accept(boost::shared_ptr<connection> client, const boost::system::error_code &error)
{
	if(error != boost::asio::error::operation_aborted)
	{
		if(!error)
		{
			connect(client);
			client->receive();
		}
		accept();
	}
}