#include "policy.hpp"

policy_base::policy_base()
{

}

void
policy_base::set_safety_level(safety_level &level)
{
    this->level = &level;
}

void 
policy_base::set_last_update(time_point &last_update)
{
    this->last_update = &last_update;
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
