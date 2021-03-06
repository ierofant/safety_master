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

class sl_variable
{
public:
    sl_variable();
    sl_variable(const literal &lit);
    sl_variable(const refval &ref);

    safety_level get_safety_level() const;
    void set_vartable(vartable &table);

private:
    struct gsl_visitor : public boost::static_visitor<safety_level>
    {
        template<typename T>
        safety_level operator()(const T &var) const {return var.get_safety_level();}
    };

    struct set_vartable_visitor : public boost::static_visitor<void>
    {
        set_vartable_visitor(vartable &table) : table(table) {}

        template<typename T>
        void operator()(T &var) const {return var.set_vartable(table);}

        vartable &table;
    };

    typedef boost::variant<literal, refval> impl_type;

    impl_type impl;
};

class comp_equal;
class comp_not_equal;
class comp_less;
class comp_greater;
class comp_less_or_equal;
class comp_greater_or_equal;

template<typename Tag>
struct comp_op
{
    comp_op() {}
    comp_op(const sl_variable &left, const sl_variable &right) : left(left), right(right) {}
    sl_variable left, right;
};

class comparator
{
public:
    comparator();

    template<typename Tag>
    comparator(const comp_op<Tag> &op)
        : impl(op)
    {

    }

    bool compare() const;
    void set_vartable(vartable &table);

private:
    struct comp_visitor : public boost::static_visitor<bool>
    {
        bool operator()(const comp_op<comp_equal> &op) const;
        bool operator()(const comp_op<comp_not_equal> &op) const;
        bool operator()(const comp_op<comp_less> &op) const;
        bool operator()(const comp_op<comp_greater> &op) const;
        bool operator()(const comp_op<comp_less_or_equal> &op) const;
        bool operator()(const comp_op<comp_greater_or_equal> &op) const;
    };

    struct set_vartable_visitor : public boost::static_visitor<void>
    {
        set_vartable_visitor(vartable &table);

        template<typename Tag>
        void operator()(comp_op<Tag> &op) const
        {
            op.left.set_vartable(table);
            op.right.set_vartable(table);
        }

        vartable &table;
    };

    typedef boost::variant< comp_op<comp_equal>,
                            comp_op<comp_not_equal>,
                            comp_op<comp_less>,
                            comp_op<comp_greater>,
                            comp_op<comp_less_or_equal>,
                            comp_op<comp_greater_or_equal>
             > impl_type;

    impl_type impl;
};

#endif //SL_VARIABLE_HPP
