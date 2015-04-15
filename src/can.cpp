#ifdef HAVE_LINUX_CAN_H
#include <linux/can.h>
#endif

#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include "output.hpp"
#include "can.hpp"

can::can() :
#if !defined(WIN32) // TODO: win32
    desc(*this),
#endif
    timer(*this),
    level(clear),
    beep(false)
{

}

void 
can::bind(const std::string &devname)
{
#ifdef HAVE_LINUX_CAN_H
    int sock = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    
    struct ifreq ifr;
    std::strcpy(ifr.ifr_name, devname.c_str());
    ioctl(sock, SIOCGIFINDEX, &ifr);

    struct sockaddr_can addr;
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    ::bind(sock, (struct sockaddr*) &addr, sizeof(addr));

    desc.assign(sock);

    start();

    boost::thread thread(boost::bind(&can::run, this));
    thread.detach();
#endif
}

void 
can::set_safety_level(safety_level level)
{
    this->level = level;
}

void 
can::set_beep(bool beep)
{
    this->beep = beep;
}

void
can::start()
{
    timer.expires_from_now(boost::chrono::milliseconds(500));
    timer.async_wait(boost::bind(&can::on_timeout, this, placeholders::error));
}

void
can::write()
{
#ifdef HAVE_LINUX_CAN_H
    struct can_frame frame;
    std::memset(&frame, 0, sizeof(frame));
    frame.can_id = 0x2c1;
    frame.can_dlc = 8;
    frame.data[0] = level;
    frame.data[1] = beep;

    desc.async_write_some(buffer(&frame, sizeof(frame)), boost::bind(&can::on_write, this, placeholders::error));
    out << "Write to CAN: safety_level=" << level << " beep=" << beep << std::endl;
#endif
}

void
can::on_timeout(const boost::system::error_code &error)
{
    if(error == boost::asio::error::operation_aborted) return;

    write();
}

void
can::on_write(const boost::system::error_code &error)
{
    if(error == boost::asio::error::operation_aborted) return;
    if(error)
    {
        err << "Error CAN: " << error.message() << std::endl;
    }

    start();
}
