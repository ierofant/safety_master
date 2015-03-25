#include <fstream>
#include "master.hpp"

int main(int argc, char *argv[])
{
    master app;
    if(app.parse_options(argc, argv)) app.run();

/*
    typedef std::istreambuf_iterator<char> iterator;

    std::ifstream file(argv[1]);
    std::string str;
    std::copy(iterator(file), iterator(), std::back_inserter(str));
    std::string::iterator beg = str.begin(), end = str.end();
	
    rules r;
    rules_grammar<std::string::iterator> grammar;
    bool result = qi::phrase_parse(beg, end, grammar, qi::space, r);

    std::cout << "Result: " << result << std::endl;
    if(result && (beg == end)) std::cout << "Ok!" << std::endl;
    else
    {
    	std::cout << "Error!" << std::endl;

        std::string str_err;
        std::copy(beg, end, std::back_inserter(str_err));
        std::cout << str_err << std::endl;

    }
*/
    return 0;
}