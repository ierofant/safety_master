#include <boost/bind.hpp>
#include "master.hpp"

using namespace boost::property_tree;

/*static*/ boost::shared_ptr<connection> 
connection::create(server &s)
{
    return boost::shared_ptr<connection>(new connection(s));
}

tcp::socket& 
connection::get_socket()
{
    return socket;
}

void 
connection::receive()
{
    rbuffer.assign(0);
    socket.async_receive(buffer(rbuffer), boost::bind(&connection::on_receive, this, placeholders::error));
}

connection::connection(server &s)
    : s(s),
      socket(s.get_service()),
      handler(s.get_service())
{

}

void 
connection::send(const std::string &response)
{
    socket.async_send(buffer(response.c_str(), response.size()), boost::bind(&connection::on_send, this, placeholders::error));
}

void 
connection::on_send(const boost::system::error_code &error)
{
    if(error) s.disconnect(shared_from_this());
    else receive();
}

void
connection::on_receive(const boost::system::error_code &error)
{
    if(error) s.disconnect(shared_from_this());
    else
    {
        std::string response;
        handler.message(rbuffer.data(), response);
        send(response);
    }
}
