#include "rule.hpp"

rule::rule()
    : level(clear),
      beep(false)
{

}

void
rule::set_condition(const condition &cond)
{
    this->cond = cond;
}

safety_level
rule::get_safety_level() const
{
    return level;
}

void
rule::set_safety_level(safety_level level)
{
    this->level = level;
}

bool
rule::get_beep() const
{
    return beep;
}

void
rule::set_beep(bool beep)
{
    this->beep = beep;
}
