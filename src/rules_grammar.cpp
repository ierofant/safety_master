#include "rules_grammar.hpp"

namespace lazy
{

void 
add_variable(rules &r, const variable &var)
{
    r.add_variable(var);
}

void
add_rule(rules &r, const rule &r1)
{
    r.add_rule(r1);
}

void 
cond_and_cond(condition &c1, const condition &c2)
{
    c1 = binary_op<cond_and>(c1, c2);
}

void 
cond_or_cond(condition &c1, const condition &c2)
{
    c1 = binary_op<cond_or>(c1, c2);
}

void 
set_condition(rule &r, const condition &c)
{
    r.set_condition(c);
}

void 
set_level(rule &r, const literal &lit)
{
    r.set_safety_level(lit.get_safety_level());
}

void
set_beep(rule &r, bool beep)
{
    r.set_beep(beep);
}

}
