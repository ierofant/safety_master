#define BOOST_TEST_MODULE comporator
#include <boost/test/unit_test.hpp>
#include <sl_variable.hpp>
#include <vartable.hpp>

struct fixture
{
    fixture()
        : clear_literal(clear),
          safety_literal(safety),
          warning1_literal(warning1),
          warning2_literal(warning2),
          clear_refval("clear"),
          safety_refval("safety"),
          warning1_refval("warning1"),
          warning2_refval("warning2")
    {
        variable::ident_type ident1(1, 1), ident2(1, 2), ident3(1, 3), ident4(1, 4);
        table.insert(variable(ident1, "clear"));
        table.insert(variable(ident2, "safety"));
        table.insert(variable(ident3, "warning1"));
        table.insert(variable(ident4, "warning2"));
        table.set_safety_level(ident1, clear);
        table.set_safety_level(ident2, safety);
        table.set_safety_level(ident3, warning1);
        table.set_safety_level(ident4, warning2);

        clear_refval.set_vartable(table);
        safety_refval.set_vartable(table);
        warning1_refval.set_vartable(table);
        warning2_refval.set_vartable(table);
    }

    literal clear_literal, safety_literal, warning1_literal, warning2_literal;
    refval clear_refval, safety_refval, warning1_refval, warning2_refval;
    vartable table;
};

BOOST_FIXTURE_TEST_CASE(equal, fixture)
{
    comparator comp1(comp_op<comp_equal>(clear_literal, clear_literal));
    BOOST_CHECK(comp1.compare());

    comparator comp2(comp_op<comp_equal>(safety_literal, safety_literal));
    BOOST_CHECK(comp2.compare());

    comparator comp3(comp_op<comp_equal>(warning1_literal, warning1_literal));
    BOOST_CHECK(comp3.compare());

    comparator comp4(comp_op<comp_equal>(warning2_literal, warning2_literal));
    BOOST_CHECK(comp4.compare());

    comparator comp5(comp_op<comp_equal>(clear_literal, safety_literal));
    BOOST_CHECK(!comp5.compare());

    comparator comp6(comp_op<comp_equal>(warning1_literal, warning2_literal));
    BOOST_CHECK(!comp6.compare());

    comparator comp7(comp_op<comp_equal>(clear_refval, clear_literal));
    BOOST_CHECK(comp7.compare());

    comparator comp8(comp_op<comp_equal>(safety_refval, safety_literal));
    BOOST_CHECK(comp8.compare());

    comparator comp9(comp_op<comp_equal>(warning1_refval, warning1_literal));
    BOOST_CHECK(comp9.compare());

    comparator comp10(comp_op<comp_equal>(warning2_refval, warning2_literal));
    BOOST_CHECK(comp10.compare());

    comparator comp11(comp_op<comp_equal>(clear_refval, safety_literal));
    BOOST_CHECK(!comp11.compare());

    comparator comp12(comp_op<comp_equal>(warning1_refval, warning2_literal));
    BOOST_CHECK(!comp12.compare());
}

BOOST_FIXTURE_TEST_CASE(not_equal, fixture)
{
    comparator comp1(comp_op<comp_not_equal>(clear_literal, safety_literal));
    BOOST_CHECK(comp1.compare());

    comparator comp2(comp_op<comp_not_equal>(warning1_literal, warning2_literal));
    BOOST_CHECK(comp2.compare());

    comparator comp3(comp_op<comp_not_equal>(safety_literal, safety_literal));
    BOOST_CHECK(!comp3.compare());

    comparator comp4(comp_op<comp_not_equal>(clear_refval, safety_literal));
    BOOST_CHECK(comp4.compare());

    comparator comp5(comp_op<comp_not_equal>(warning1_refval, warning2_literal));
    BOOST_CHECK(comp5.compare());

    comparator comp6(comp_op<comp_not_equal>(clear_refval, clear_literal));
    BOOST_CHECK(!comp6.compare());
}
