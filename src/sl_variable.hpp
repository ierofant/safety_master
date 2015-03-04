#ifndef SL_VARIABLE_HPP
#define SL_VARIABLE_HPP

#include <string>
#include <boost/variant.hpp>
#include "safety_level.hpp"

class vartable;
class literal
{
public:
    literal(safety_level level = safety);

    safety_level get_safety_level() const;
    void set_vartable(const vartable &table);

private:
    safety_level level; 
};

class refval
{
public:
    refval(const std::string &alias = std::string());

    safety_level get_safety_level() const;
    void set_vartable(const vartable &table);

private:
    std::string alias;
    const vartable *table;
};

struct gsl_visitor : public boost::static_visitor<safety_level>
{
    template<typename T>
    safety_level operator()(const T &var) const {return var.get_safety_level();}
};

class sl_variable
{
public:
    sl_variable();
    sl_variable(const literal &lit);
    sl_variable(const refval &ref);

    safety_level get_safety_level() const;

private:
    typedef boost::variant<literal, refval> impl_type;

    impl_type impl;
};


class comp_equal;
class comp_not_equal;

template<typename Tag>
struct comp_op
{
    comp_op() {}
    comp_op(const sl_variable &left, const sl_variable &right) : left(left), right(right) {}
    sl_variable left, right;
};

typedef boost::variant< comp_op<comp_equal>,
                        comp_op<comp_not_equal>
        > comparator;

struct comp_visitor : public boost::static_visitor<bool>
{
    bool operator()(const comp_op<comp_equal> &op) const;
    bool operator()(const comp_op<comp_not_equal> &op) const;
};

#endif //SL_VARIABLE_HPP
