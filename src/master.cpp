#include <fstream>
#include <boost/program_options.hpp>
#include "master.hpp"
#include "rules_grammar.hpp"
#include "output.hpp"

master::master()
    : s(*this),
      timer(*this)
{

}

bool
master::parse_options(int argc, char *argv[])
{
    bool result = false;

    unsigned default_port = 45000;
    std::string default_candev = "can0";
    std::string default_config = "";

    using namespace boost::program_options;
    options_description opts("Safety Master Options");
    opts.add_options()
        ("port,p", value<unsigned>()->default_value(default_port), "TCP port")
        ("candev,d", value<std::string>()->default_value(default_candev), "CAN device name")
        ("rules,r", value<std::string>()->default_value(default_config), "Rules file")
        ("verbose,v", "Verbose")
        ("help,h", "This help message")
    ;
 
    variables_map variables;
    parsed_options parsed = command_line_parser(argc, argv).options(opts).allow_unregistered().run();
    store(parsed, variables);
    notify(variables);

    if(variables.count("help"))
    {
        std::cout << opts << std::endl;
        result = false;
    }
    else
    {
        unsigned port = variables["port"].as<unsigned>();
        std::string candev = variables["candev"].as<std::string>();
        std::string rules = variables["rules"].as<std::string>();

        out.set_verbose(variables.count("verbose"));
        err.set_verbose(variables.count("verbose"));

        bind_tcp(port);
        bind_can(candev);
        read_config_from_file(rules);
        timer.start();
        result = true;   
    }

    return result;
}

void 
master::set_safety_level(ident_type ident, safety_level level)
{
    r.set_safety_level(ident, level);
    update();
}

void
master::refresh_vartable()
{
    r.refresh_vartable();
    update();
}

void 
master::bind_tcp(unsigned port)
{
    s.bind(port);  
}

void 
master::bind_can(const std::string &candev)
{
    c.bind(candev);
}

void 
master::read_config_from_file(const std::string &filename)
{
    std::ifstream file(filename.c_str());
    if(file.good())
    {
    	typedef std::istreambuf_iterator<char> iterator;

    	std::string str;
    	std::copy(iterator(file), iterator(), std::back_inserter(str));
    	read_config(str);
    }
}

void
master::read_config(const std::string &str)
{
    std::string local_str = str;
    std::string::iterator beg = local_str.begin(), end = local_str.end();
    rules_grammar<std::string::iterator> grammar;
    bool result = qi::phrase_parse(beg, end, grammar, qi::space, r);
    if(result && (beg == end))
    {

    }
    else
    {
        std::cerr << "Error: Invalid rules!" << std::endl;
        std::terminate();
    }
}

void
master::update()
{
    safety_level level;
    bool beep;

    r.calculate(level, beep);
    c.set_safety_level(level);
    c.set_beep(beep);
}
