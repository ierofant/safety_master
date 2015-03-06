#ifndef RULE_HPP
#define RULE_HPP

#include "condition.hpp"

class rule
{
public:
    rule();

    void set_condition(const condition &cond);

    safety_level get_safety_level() const;
    void set_safety_level(safety_level level);

    bool get_beep() const;
    void set_beep(bool beep);

private:
    condition cond;
    safety_level level;
    bool beep;
};

#endif //RULE_HPP
