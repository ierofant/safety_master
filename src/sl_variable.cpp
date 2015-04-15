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
    : alias(alias),
      table(NULL)
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

void 
sl_variable::set_vartable(vartable &table)
{
    boost::apply_visitor(set_vartable_visitor(table), impl);    
}

comparator::comparator()
{

}

bool
comparator::compare() const
{
    return boost::apply_visitor(comp_visitor(), impl);
}

void 
comparator::set_vartable(vartable &table)
{
    boost::apply_visitor(set_vartable_visitor(table), impl);
}

bool 
comparator::comp_visitor::operator()(const comp_op<comp_equal> &op) const
{
    return op.left.get_safety_level() == op.right.get_safety_level();
}

bool 
comparator::comp_visitor::operator()(const comp_op<comp_not_equal> &op) const
{
    return op.left.get_safety_level() != op.right.get_safety_level();
}

bool
comparator::comp_visitor::operator()(const comp_op<comp_less> &op) const
{
    return op.left.get_safety_level() < op.right.get_safety_level();
}

bool
comparator::comp_visitor::operator()(const comp_op<comp_greater> &op) const
{
    return op.left.get_safety_level() > op.right.get_safety_level();
}

bool
comparator::comp_visitor::operator()(const comp_op<comp_less_or_equal> &op) const
{
    return op.left.get_safety_level() <= op.right.get_safety_level();
}

bool
comparator::comp_visitor::operator()(const comp_op<comp_greater_or_equal> &op) const
{
    return op.left.get_safety_level() >= op.right.get_safety_level();
}

comparator::set_vartable_visitor::set_vartable_visitor(vartable &table)
    : table(table)
{

}
