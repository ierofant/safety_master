#include <fstream>
#include "master.hpp"
#include "rules_grammar.hpp"

void 
master::bind_tcp(unsigned port)
{
    s.bind(port);  
}

void 
master::bind_can(const std::string &candev)
{

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
}

void
master::refresh_vartable()
{
    r.refresh_vartable();
}