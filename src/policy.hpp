#ifndef POLICY_HPP
#define POLICY_HPP

#include <boost/chrono.hpp>
#include <boost/variant.hpp>
#include "safety_level.hpp"

class variable;
class policy_base
{
public:
    typedef boost::chrono::steady_clock::time_point time_point;

    void set_parent(variable &var);
    void set_safety_level(safety_level level);
    time_point get_last_update() const;

protected:
    policy_base();

private:
    variable *var;
};


class manual_policy : public policy_base
{
public:
    void exec();
};

template<safety_level default_level>
class auto_policy : public policy_base
{
public:
    typedef policy_base::time_point time_point;

    void exec()
    {
        time_point now = boost::chrono::steady_clock::now();
        if((now - get_last_update()) > boost::chrono::seconds(1)) set_safety_level(default_level);
    }
};

class variable_policy
{
public:
    variable_policy();
    variable_policy(const manual_policy &policy);

    template<safety_level default_level>
    variable_policy(const auto_policy<default_level> &policy) : impl(policy) {}

    void set_parent(variable &var);
    void exec();

private:
    struct exec_visitor : public boost::static_visitor<void>
    {
        template<typename T>
        void operator()(T &policy) const {policy.exec();}
    };

    struct set_parent_visitor : public boost::static_visitor<void>
    {
        set_parent_visitor(variable &var);

        template<typename T>
        void operator()(T &policy) const {policy.set_parent(var);}

        variable &var;
    };

    typedef boost::variant<
                manual_policy,
                auto_policy<clear>,
                auto_policy<safety>,
                auto_policy<warning1>,
                auto_policy<warning2>
            > impl_type;

    impl_type impl;
};

#endif //POLICY_HPP
