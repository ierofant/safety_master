#define BOOST_TEST_MODULE variable
#include <boost/test/unit_test.hpp>
#include <variable.hpp>

struct fixture
{
	fixture() 
		: ident(1, 2),
		  alias("foo"),
		  var(ident, alias, manual_policy())
	{

	}

	variable::ident_type ident;
	std::string alias;
	variable var;
};

BOOST_FIXTURE_TEST_CASE(getters, fixture)
{
	BOOST_CHECK(ident == var.get_ident());
	BOOST_CHECK_EQUAL(ident.first, var.get_subsystem());
	BOOST_CHECK_EQUAL(ident.second, var.get_code());
	BOOST_CHECK_EQUAL(alias, var.get_alias());
	BOOST_CHECK_EQUAL(safety, var.get_safety_level());
}

BOOST_FIXTURE_TEST_CASE(set_safety_level, fixture)
{
	var.set_safety_level(clear);
	BOOST_CHECK_EQUAL(clear, var.get_safety_level());

	var.set_safety_level(safety);
	BOOST_CHECK_EQUAL(safety, var.get_safety_level());

	var.set_safety_level(warning1);
	BOOST_CHECK_EQUAL(warning1, var.get_safety_level());

	var.set_safety_level(warning2);
	BOOST_CHECK_EQUAL(warning2, var.get_safety_level());
}