#include <boost/property_tree/json_parser.hpp>
#include "request_handler.hpp"
#include "master.hpp"
#include "output.hpp"

enum sf_proto_type
{
    SET_LEVEL = 0,
    GET_ALARM = 1
};


request_handler::request_handler(master &service)
    : service(service)
{

}

bool 
request_handler::message(const std::string &request, std::string &response) const
{
    bool result = true;

    try
    {
        boost::property_tree::ptree req, resp;
        std::stringstream stream(request);
        boost::property_tree::read_json(stream, req);

        response.clear();
        handle(req, resp);

        stream.str("");
        boost::property_tree::write_json(stream, resp, false);
        response = stream.str();
    }
    catch(const std::exception &ex)
    {
        result = false;
        err << "Error: " << ex.what() << std::endl;
    }

    return result;
}

void
request_handler::handle(const boost::property_tree::ptree &request, boost::property_tree::ptree &response) const
{
    sf_proto_type type = static_cast<sf_proto_type>(request.get<unsigned>("type"));
    switch(type)
    {
        case SET_LEVEL:
            handle_set_level(request, response);            
            break;

        case GET_ALARM:
            handle_get_alarm(request, response);
            break;

        default:
            throw std::runtime_error("Bad message");
    }
}

void 
request_handler::handle_set_level(const boost::property_tree::ptree &request, boost::property_tree::ptree &response) const
{
    unsigned sub = request.get<unsigned>("request.subsystem");
    unsigned code = request.get<unsigned>("request.code");
    safety_level level = static_cast<safety_level>(request.get<unsigned>("request.level"));

    service.set_safety_level(variable::ident_type(sub, code), level);

    response.put("type", SET_LEVEL);
    response.put("response.result", true);
    response.put("response.level", level);
}

void 
request_handler::handle_get_alarm(const boost::property_tree::ptree &request, boost::property_tree::ptree &response) const
{
/*
    using namespace boost::property_tree;

    response.put("type", GET_ALARM);
    ptree &child = response.put_child("response.rules", ptree());

    std::vector<std::string> alarms;
    rules &r = master::get().get_rules();
    r.get_alarm(alarms);
    
    for(std::size_t i = 0; i < alarms.size(); ++i)
    {
        child.push_back(std::make_pair("", ptree(alarms[i])));
    }
*/
}
