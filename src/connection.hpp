#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "request_handler.hpp"

using namespace boost::asio;
using namespace boost::asio::ip;

class server;
class connection : public boost::enable_shared_from_this<connection>
{
public:
    static boost::shared_ptr<connection> create(server &s);
    tcp::socket& get_socket();
    void receive();

private:
    connection(server &s);
    
    void send(const std::string &response);
    void on_send(const boost::system::error_code &error);
    void on_receive(const boost::system::error_code &error);

    server &s;
    tcp::socket socket;
    boost::array<char, 1000> rbuffer;
    request_handler handler;
};

#endif //CONNECTION_HPP
