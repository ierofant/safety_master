#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include <string>
#include "policy.hpp"

class variable
{
public:
    typedef std::pair<unsigned, unsigned> ident_type;

    variable();
    variable(const ident_type &ident, const std::string &alias, variable_policy policy);

    const ident_type& get_ident() const;
    unsigned get_subsystem() const;
    unsigned get_code() const;
    const std::string& get_alias() const;
    safety_level get_safety_level() const;

private:
    ident_type ident;
    std::string alias;
    safety_level level;
    variable_policy policy;
};

#endif //VARIABLE_HPP
