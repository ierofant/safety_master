#include "sl_variable.hpp"
#include "vartable.hpp"

literal::literal(safety_level level)
	: level(level)
{

}

safety_level
literal::get_safety_level() const
{
    return level;
}

void 
literal::set_vartable(const vartable &table)
{

}

refval::refval(const std::string &alias)
	: alias(alias)
{

}

safety_level
refval::get_safety_level() const
{
    return table ? table->get_safety_level(alias) : safety;
}

void 
refval::set_vartable(const vartable &table)
{
    this->table = &table;
}

sl_variable::sl_variable()
{

}

sl_variable::sl_variable(const literal &lit)
    : impl(lit)
{

}

sl_variable::sl_variable(const refval &ref)
    : impl(ref)
{

}

safety_level 
sl_variable::get_safety_level() const
{
    return boost::apply_visitor(gsl_visitor(), impl);
}

bool 
comp_visitor::operator()(const comp_op<comp_equal> &op) const
{
    return op.left.get_safety_level() == op.right.get_safety_level();
}

bool 
comp_visitor::operator()(const comp_op<comp_not_equal> &op) const
{
    return op.left.get_safety_level() != op.right.get_safety_level();
}
