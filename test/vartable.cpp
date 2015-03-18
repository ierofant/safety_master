#define BOOST_TEST_MODULE vartable
#include <boost/test/unit_test.hpp>
#include <boost/thread.hpp>
#include <vartable.hpp>

struct fixture
{
    fixture() {}
    vartable table;
};

BOOST_FIXTURE_TEST_CASE(getters, fixture)
{
    BOOST_CHECK_EQUAL(safety, table.get_safety_level("foo"));
}

BOOST_FIXTURE_TEST_CASE(set_safety_level, fixture)
{
    variable::ident_type ident(1, 1);
    variable var(ident, "foo", manual_policy());
    table.insert(var);
    BOOST_CHECK_EQUAL(table.get_safety_level("foo"), var.get_safety_level());

    table.set_safety_level(ident, clear);
    BOOST_CHECK_EQUAL(table.get_safety_level("foo"), clear);
}

BOOST_FIXTURE_TEST_CASE(refresh, fixture)
{
    variable::ident_type ident(1, 1);
    variable var(ident, "foo", auto_policy<safety>());
    table.insert(var);
    table.set_safety_level(ident, clear);
    BOOST_CHECK_EQUAL(table.get_safety_level("foo"), clear);

    boost::this_thread::sleep_for(boost::chrono::seconds(1));
    table.refresh();
    BOOST_CHECK_EQUAL(table.get_safety_level("foo"), safety);
}