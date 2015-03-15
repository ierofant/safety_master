#include "variable.hpp"

variable::variable()
{

}

variable::variable(const ident_type &ident, const std::string &alias, variable_policy policy)
    : ident(ident),
      alias(alias),
      level(safety),
      policy(policy),
      last_update(boost::chrono::steady_clock::now())
{
    policy.set_parent(*this);
}

const variable::ident_type& 
variable::get_ident() const
{
    return ident;
}

unsigned 
variable::get_subsystem() const
{
    return ident.first;
}

unsigned
variable::get_code() const
{
    return ident.second;
}

const std::string& 
variable::get_alias() const
{
    return alias;
}

safety_level
variable::get_safety_level() const
{
    return level;
}

void
variable::set_safety_level(safety_level level)
{
    this->level = level;
    last_update = boost::chrono::steady_clock::now();
}

variable::time_point
variable::get_last_update() const
{
    return last_update;
}

void
variable::refresh()
{
    policy.exec();
}