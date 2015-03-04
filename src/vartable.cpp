#include "vartable.hpp"

safety_level 
vartable::get_safety_level(const std::string &alias) const
{
    return table.get<by_alias>().find(alias)->get_safety_level();
}

void
vartable::insert(const variable &var)
{
    table.insert(var);
}
