#ifndef RULE_HPP
#define RULE_HPP

#include "condition.hpp"

struct rule
{
    rule();

    condition cond;
    safety_level level;
    bool beep;
};

#endif //RULE_HPP