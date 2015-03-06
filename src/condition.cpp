#include "condition.hpp"

bool 
cond_visitor::operator()(const comparator &op) const
{
    return op.compare();
}

bool 
cond_visitor::operator()(const unary_op<cond_not> &op) const
{
    return !boost::apply_visitor(cond_visitor(), op.cond);
}

bool 
cond_visitor::operator()(const binary_op<cond_or> &op) const
{
    return boost::apply_visitor(cond_visitor(), op.left)
        || boost::apply_visitor(cond_visitor(), op.right);
}

bool 
cond_visitor::operator()(const binary_op<cond_and> &op) const
{
    return boost::apply_visitor(cond_visitor(), op.left)
        && boost::apply_visitor(cond_visitor(), op.right);
}
