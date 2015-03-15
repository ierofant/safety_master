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
rules::refresh_vartable()
{
	table.refresh();
}