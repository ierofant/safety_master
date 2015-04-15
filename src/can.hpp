#ifndef CAN_HPP
#define CAN_HPP

#if defined (WIN32)
#define WIN32_LEAN_AND_MEAN
#define BOOST_ASIO_NO_WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <windows.h>
#endif

#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/atomic.hpp>
#include "safety_level.hpp"

using namespace boost::asio;
#if !defined(WIN32) // TODO: win32
using namespace boost::asio::posix;
#endif

class can : public io_service
{
public:
    can();

    void bind(const std::string &devname);
    void set_safety_level(safety_level level);
    void set_beep(bool beep);

private:
    void start();
    void write();
    void on_timeout(const boost::system::error_code &error);
    void on_write(const boost::system::error_code &error);

#if !defined(WIN32) // TODO: win32
    basic_stream_descriptor<> desc;
#endif
    steady_timer timer;
    boost::atomic<unsigned> level;
    boost::atomic<bool> beep;
};

#endif //CAN_HPP
