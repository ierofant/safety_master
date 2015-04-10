#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <iostream>

class output
{
public:
    output(std::ostream &stream, bool verbose = false);

    void set_verbose(bool verbose = true);

    template<typename T>
    const output& operator<<(const T &data) const;
    const output& operator<<(std::ostream&(*pf)(std::ostream&)) const;

private:
    std::ostream &stream;
    bool verbose;
};

template<typename T>
const output& 
output::operator<<(const T &data) const
{
    if(verbose)
    {
        stream << data;
    }
    return *this;
}

extern output out;
extern output err;

#endif //OUTPUT_HPP
