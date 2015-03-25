#include <boost/asio.hpp>
#include <boost/program_options.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost::program_options;
using namespace boost::property_tree;

static const char* default_host = "127.0.0.1";
static const unsigned default_port = 45000;
static const unsigned default_subsystem = 0;
static const unsigned default_code = 0;
static const char* default_level = "clear";

int main(int argc, char *argv[])
{
    options_description opts("sfm_set options");
    opts.add_options()
        ("host,h", value<std::string>()->default_value(default_host), "Safety Master address")
        ("port,p", value<unsigned>()->default_value(default_port), "TCP port")
        ("subsystem,s", value<unsigned>()->default_value(default_subsystem), "Subsistem code")
        ("code,c", value<unsigned>()->default_value(default_code), "Message code")
        ("level,l", value<std::string>()->default_value(default_level), "Safety level (clear, urgent, warning1, warning2)")
        ("help,h", "This help messsge")
    ;
    variables_map variables;
    parsed_options parsed = command_line_parser(argc, argv).options(opts).allow_unregistered().run();
    store(parsed, variables);
    notify(variables);

    if(variables.count("help"))
    {
        std::cout << opts << std::endl;
    }
    else
    {
        try
        {
            unsigned port = variables["port"].as<unsigned>();
            unsigned subsystem = variables["subsystem"].as<unsigned>();
            unsigned code = variables["code"].as<unsigned>();
            std::string level = variables["level"].as<std::string>();

            const char *level_arr[] = {"clear", "urgent", "warning1", "warning2"};
            if(std::find(boost::begin(level_arr), boost::end(level_arr), level) == boost::end(level_arr)) std::runtime_error("Bad level");

            io_service service;
            tcp::socket socket(service, tcp::v4());
            socket.connect(tcp::endpoint(address_v4::from_string(default_host), default_port));

            ptree request;
            request.put("type", 0);
            request.put("request.subsystem", subsystem);
            request.put("request.code", code);
            //request.put("request.value");

            std::stringstream stream;
            write_json(stream, request, false);

            std::string msg = stream.str();
            socket.send(buffer(msg.c_str(), msg.size()));

            boost::array<char, 1000> buf;
            buf.assign(0);
            socket.receive(buffer(buf));

            stream.str(buf.data());

            ptree response;
            read_json(stream, response);

            if(response.get<unsigned>("type") != 0) std::runtime_error("Bad message type");
            if(response.get<bool>("response.result")) std::cout << "Ok!" << std::endl;
            else std::cerr << "Fail!" << std::endl;
        }
        catch(const std::exception &ex)
        {
            std::cerr << "Error: " << ex.what() << std::endl;
        }
    }

    return 0;
}
