#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>

using namespace boost::asio;
using namespace boost::asio::ip;

class server;
class connection : public boost::enable_shared_from_this<connection>
{
public:
    boost::shared_ptr<connection> create(server &s);
    tcp::socket& get_socket();
    void receive();

private:
    connection(server &s);

    void on_receive(const boost::system::error_code &error);

    server &s;
    tcp::socket socket;
    boost::array<char, 1000> buf;
};

#endif //CONNECTION_HPP
