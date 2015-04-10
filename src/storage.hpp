#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <boost/asio/steady_timer.hpp>

class master;
class storage
{
public:
    storage(master &service);

    void start();

private:
    void on_timeout(const boost::system::error_code &error);

    master &service;
    boost::asio::steady_timer timer;
};

#endif //STORAGE_HPP