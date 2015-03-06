#define BOOST_TEST_MODULE rule
#include <boost/test/unit_test.hpp>
#include <rule.hpp>

struct fixture
{
    rule r;
};

BOOST_FIXTURE_TEST_CASE(getters, fixture)
{
    BOOST_CHECK_EQUAL(clear, r.get_safety_level());
    BOOST_CHECK_EQUAL(false, r.get_beep());
}

BOOST_FIXTURE_TEST_CASE(set_safety_level, fixture)
{
    r.set_safety_level(clear);
    BOOST_CHECK_EQUAL(clear, r.get_safety_level());

    r.set_safety_level(safety);
    BOOST_CHECK_EQUAL(safety, r.get_safety_level());

    r.set_safety_level(warning1);
    BOOST_CHECK_EQUAL(warning1, r.get_safety_level());

    r.set_safety_level(warning2);
    BOOST_CHECK_EQUAL(warning2, r.get_safety_level());
}

BOOST_FIXTURE_TEST_CASE(set_beep, fixture)
{
    r.set_beep(true);
    BOOST_CHECK_EQUAL(true, r.get_beep());

    r.set_beep(false);
    BOOST_CHECK_EQUAL(false, r.get_beep());
}
