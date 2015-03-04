#ifndef CONDITION_HPP
#define CONDITION_HPP

#include "sl_variable.hpp"

class cond_not;
class cond_or;
class cond_and;

template<typename Tag>
class unary_op;

template<typename Tag>
class binary_op;

typedef boost::variant< comparator,
                        boost::recursive_wrapper<unary_op<cond_not> >,
                        boost::recursive_wrapper<binary_op<cond_or> >,
                        boost::recursive_wrapper<binary_op<cond_and> >
        > condition;

template<typename Tag>
struct unary_op
{
    unary_op() {}
    unary_op(const condition &cond) : cond(cond) {}
    condition cond;
};

template<typename Tag>
struct binary_op
{
    binary_op() {}
    binary_op(const condition &left, const condition &right) : left(left), right(right) {}
    condition left, right;
};

struct cond_visitor : public boost::static_visitor<bool>
{
    bool operator()(const comparator &op) const;
    bool operator()(const unary_op<cond_not> &op) const;
    bool operator()(const binary_op<cond_or> &op) const;
    bool operator()(const binary_op<cond_and> &op) const;
};

#endif //CONDITION_HPP
