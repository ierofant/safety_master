#include <boost/bind.hpp>
#include "master.hpp"

boost::shared_ptr<connection> 
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
    socket.async_receive(buffer(buf), boost::bind(&connection::on_receive, this, placeholders::error));
}

connection::connection(server &s)
    : s(s),
      socket(s.get_service())
{

}

void
connection::on_receive(const boost::system::error_code &error)
{
    if(error)
    {
        s.disconnect(shared_from_this());
    }
    else
    {
        receive();
    }
}
