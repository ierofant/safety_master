#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include <string>
#include <boost/chrono.hpp>
#include "policy.hpp"

class variable
{
public:
    typedef std::pair<unsigned, unsigned> ident_type;
    typedef boost::chrono::steady_clock::time_point time_point;

    variable();
    variable(const ident_type &ident, const std::string &alias, variable_policy policy = manual_policy());

    const ident_type& get_ident() const;
    unsigned get_subsystem() const;
    unsigned get_code() const;
    const std::string& get_alias() const;

    safety_level get_safety_level() const;
    void set_safety_level(safety_level level);

    time_point get_last_update() const;

    void refresh();

private:
    ident_type ident;
    std::string alias;
    safety_level level;
    variable_policy policy;
    time_point last_update;
};

#endif //VARIABLE_HPP
