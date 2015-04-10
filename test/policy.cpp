#define BOOST_TEST_MODULE policy
#include <boost/test/unit_test.hpp>
#include <boost/thread.hpp>
#include <variable.hpp>

BOOST_AUTO_TEST_CASE(auto_policy_exec)
{
    variable var;

    auto_policy<safety> policy;
    policy.set_parent(var);
	
    policy.set_safety_level(clear);
    BOOST_CHECK_EQUAL(var.get_safety_level(), clear);

    boost::this_thread::sleep_for(boost::chrono::seconds(1));
    policy.exec();
    BOOST_CHECK_EQUAL(var.get_safety_level(), safety);
}
