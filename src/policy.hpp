#ifndef POLICY_HPP
#define POLICY_HPP

#include <boost/chrono.hpp>
#include <boost/variant.hpp>
#include "safety_level.hpp"

class policy_base
{
public:
    typedef boost::chrono::steady_clock::time_point time_point;

    void set_safety_level(safety_level &level);
    void set_last_update(time_point &last_update);

protected:
    policy_base();

    safety_level *level;
    time_point *last_update;
};


class manual_policy : public policy_base
{
public:
    typedef policy_base::time_point time_point;

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
        if((now - *last_update) > boost::chrono::seconds(1))
        {
            *level = default_level;
            *last_update = boost::chrono::steady_clock::now();
        }
    }
};

class variable_policy
{
public:
    variable_policy();
    variable_policy(const manual_policy &policy);

    template<safety_level default_level>
    variable_policy(const auto_policy<default_level> &policy) : impl(policy) {}

private:
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
