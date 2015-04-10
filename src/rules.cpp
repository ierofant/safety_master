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
    rules.back().set_vartable(table);
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

void 
rules::calculate(safety_level &level, bool &beep) const
{
    level = clear;
    beep = false;

    for(rules_list::const_iterator itr = rules.begin(); itr != rules.end(); ++itr)
    {
        if(itr->check())
        {
            boost::optional<safety_level> level_out = itr->get_safety_level();
            boost::optional<bool> beep_out = itr->get_beep();

            if(beep_out) beep |= *beep_out;
            if(level_out) level = std::max(level, *level_out);
        }
    }
}
