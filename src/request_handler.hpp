#ifndef REQUEST_HANDLER_HPP
#define REQUEST_HANDLER_HPP

#include <boost/property_tree/ptree.hpp>

class master;
class request_handler
{
public:
    request_handler(master &service);

    bool message(const std::string &request, std::string &response) const;

private:
    void handle(const boost::property_tree::ptree &request, boost::property_tree::ptree &response) const;
    void handle_set_level(const boost::property_tree::ptree &request, boost::property_tree::ptree &response) const;
    void handle_get_alarm(const boost::property_tree::ptree &request, boost::property_tree::ptree &response) const;

    master &service;
};

#endif //REQUEST_HANDLER_HPP
