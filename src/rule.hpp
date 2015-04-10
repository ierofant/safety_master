#ifndef RULE_HPP
#define RULE_HPP

#include <boost/optional.hpp>
#include "condition.hpp"

class rule
{
public:
    rule();

    void set_vartable(vartable &table);
    void set_condition(const condition &cond);
    bool check() const;

    boost::optional<safety_level> get_safety_level() const;
    void set_safety_level(safety_level level);

    boost::optional<bool> get_beep() const;
    void set_beep(bool beep);

private:
    condition cond;

    boost::optional<safety_level> level;
    boost::optional<bool> beep;
};

#endif //RULE_HPP
