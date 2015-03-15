#include "variable.hpp"

void
policy_base::set_parent(variable &var)
{
	this->var = &var;
}

void
policy_base::set_safety_level(safety_level level)
{
    if(var) var->set_safety_level(level);
}

policy_base::time_point
policy_base::get_last_update() const
{
	return var ? var->get_last_update() : time_point();
}

policy_base::policy_base()
	: var(NULL)
{

}

void 
manual_policy::exec()
{

}

variable_policy::variable_policy()
{

}

variable_policy::variable_policy(const manual_policy &policy)
    : impl(policy)
{

}

void
variable_policy::set_parent(variable &var)
{
	boost::apply_visitor(set_parent_visitor(var), impl);
}

void
variable_policy::exec()
{
	boost::apply_visitor(exec_visitor(), impl);
}

variable_policy::set_parent_visitor::set_parent_visitor(variable &var)
	: var(var)
{

}