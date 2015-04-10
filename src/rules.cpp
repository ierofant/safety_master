#include "rules.hpp"

void
rules::add_variable(const variable &var)
{
    table.insert(var);
}

void
rules::add_rule(const rule &r)
{
    rules.push_back(r);
}

void 
rules::set_safety_level(const ident_type &ident, safety_level level)
{
    table.set_safety_level(ident, level);
}

void
rules::refresh_vartable()
{
    table.refresh();
}

safety_level 
rules::calculate_safety_level() const
{
    safety_level result = safety;

    return result;
}

bool
rules::calculate_beep() const
{
    bool result = false;
    for(rules_list::const_iterator itr = rules.begin(); itr != rules.end(); ++itr) 
    {
        result = itr->get_beep();
        if(result) break;
    }

    return result;
}