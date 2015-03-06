#define BOOST_TEST_MODULE sl_variable
#include <boost/test/unit_test.hpp>
#include <sl_variable.hpp>
#include <vartable.hpp>

struct fixture
{
    fixture()
        : clear_literal(clear),
	  safety_literal(safety),
          warning1_literal(warning1),
          warning2_literal(warning2)
    {
        table.insert(variable(variable::ident_type(1, 1), "foo"));
    }

    vartable table;
    sl_variable var;
    literal default_literal, clear_literal, safety_literal, warning1_literal, warning2_literal;
};

BOOST_FIXTURE_TEST_CASE(literal_getters, fixture)
{
    BOOST_CHECK_EQUAL(safety, default_literal.get_safety_level());
    BOOST_CHECK_EQUAL(clear, clear_literal.get_safety_level());
    BOOST_CHECK_EQUAL(safety, safety_literal.get_safety_level());
    BOOST_CHECK_EQUAL(warning1, warning1_literal.get_safety_level());
    BOOST_CHECK_EQUAL(warning2, warning2_literal.get_safety_level());
}

BOOST_AUTO_TEST_CASE(refval_getters)
{
    refval ref("foo");
    BOOST_CHECK_EQUAL(ref.get_safety_level(), safety);
}

BOOST_FIXTURE_TEST_CASE(refval_set_table, fixture)
{
    refval ref("foo");
    ref.set_vartable(table);

    variable::ident_type ident(1, 1);
    table.set_safety_level(ident, clear);
    BOOST_CHECK_EQUAL(ref.get_safety_level(), clear);

    table.set_safety_level(ident, safety);
    BOOST_CHECK_EQUAL(ref.get_safety_level(), safety);

    table.set_safety_level(ident, warning1);
    BOOST_CHECK_EQUAL(ref.get_safety_level(), warning1);

    table.set_safety_level(ident, warning2);
    BOOST_CHECK_EQUAL(ref.get_safety_level(), warning2);
}

BOOST_FIXTURE_TEST_CASE(getters, fixture)
{
    BOOST_CHECK_EQUAL(safety, var.get_safety_level());
}
