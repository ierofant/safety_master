#ifndef RULES_HPP
#define RULES_HPP

#include "vartable.hpp"
#include "rule.hpp"

class rules
{
public:
    typedef vartable::ident_type ident_type;
    typedef std::vector<rule> rules_list;

    void add_variable(const variable &var);
    void add_rule(const rule &r);
    void set_safety_level(const ident_type &ident, safety_level level);
    void refresh_vartable();

    void calculate(safety_level &level, bool &beep) const;

private:
    vartable table;
    rules_list rules;
};

#endif //RULES_HPP