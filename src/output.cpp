#include "output.hpp"

output out(std::cout);
output err(std::cerr);

output::output(std::ostream &stream, bool verbose)
    : stream(stream),
      verbose(verbose)
{

}

void
output::set_verbose(bool verbose)
{
    this->verbose = verbose;
}

const output& 
output::operator<<(std::ostream&(*pf)(std::ostream&)) const
{
    if(verbose)
    {
        stream << pf;
    }

    return *this;
}
