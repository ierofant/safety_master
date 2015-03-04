#ifndef RULES_GRAMMAR_HPP
#define RULES_GRAMMAR_HPP

#define BOOST_SPIRIT_USE_PHOENIX_V3

#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/operator.hpp>
#include <boost/phoenix/object/construct.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/lambda/lambda.hpp>

#include "rules.hpp"

namespace lazy
{
    void add_variable(rules &r, const variable &var);
    void add_rule(rules &r, const rule &r1);
    void cond_and_cond(condition &c1, const condition &c2);
    void cond_or_cond(condition &c1, const condition &c2);
    void set_condition(rule &r, const condition &c);
    void set_level(rule &r, const literal &lit);
    void set_beep(rule &r, bool beep);
}

namespace 
{
    BOOST_PHOENIX_ADAPT_FUNCTION(void, add_variable, lazy::add_variable, 2)
    BOOST_PHOENIX_ADAPT_FUNCTION(void, add_rule, lazy::add_rule, 2)
    BOOST_PHOENIX_ADAPT_FUNCTION(void, cond_and_cond, lazy::cond_and_cond, 2)
    BOOST_PHOENIX_ADAPT_FUNCTION(void, cond_or_cond, lazy::cond_or_cond, 2)
    BOOST_PHOENIX_ADAPT_FUNCTION(void, set_condition, lazy::set_condition, 2)
    BOOST_PHOENIX_ADAPT_FUNCTION(void, set_level, lazy::set_level, 2)
    BOOST_PHOENIX_ADAPT_FUNCTION(void, set_beep, lazy::set_beep, 2)
}

namespace qi = boost::spirit::qi;
namespace phoenix = boost::phoenix;

template<typename Iterator>
struct rules_grammar : public qi::grammar<Iterator, rules(), qi::space_type>
{
    typedef rules::ident_type ident_type;

    rules_grammar()
	: rules_grammar::base_type(result)
    {
	ident = qi::uint_ >> '.' >> qi::uint_;

        policy = qi::string("manual") [qi::_val = manual_policy()]
                | qi::string("auto_clear") [qi::_val = auto_policy<clear>()]
                | qi::string("auto_safety") [qi::_val = auto_policy<safety>()]
                | qi::string("auto_warning1") [qi::_val = auto_policy<warning1>()]
                | qi::string("auto_warning2") [qi::_val = auto_policy<warning2>()]
        ;

	alias = +(qi::char_("0-9A-Za-z"));

        var = (policy >> qi::space >> alias >> -qi::space >> qi::char_('=') >> -qi::space >> ident >> qi::space) 
                [qi::_val = phoenix::construct<variable>(qi::_7, qi::_3, qi::_1)]
        ;


        lit = qi::string("clear") [qi::_val = clear] 
                | qi::string("safety") [qi::_val = safety] 
                | qi::string("warning1") [qi::_val = warning1]
                | qi::string("warning2") [qi::_val = warning2]
        ;

        ref = (alias >> qi::char_('.') >> qi::string("level"))[qi::_val = phoenix::construct<refval>(qi::_1)];
        sl_var = (lit | ref);

        c_equal = (sl_var >> -qi::space >> qi::string("==") >> -qi::space >> sl_var)[qi::_val = phoenix::construct<comp_op<comp_equal> >(qi::_1, qi::_5)];
        cn_equal = (sl_var >> -qi::space >> qi::string("!=") >> -qi::space >> sl_var)[qi::_val = phoenix::construct<comp_op<comp_not_equal> >(qi::_1, qi::_5)];
        comp = c_equal | cn_equal;

        factor = comp[qi::_val = qi::_1]
                | qi::char_('(') >> -qi::space >> cond[qi::_val = qi::_1] >> -qi::space >> qi::char_(')')
                | qi::char_('!') >> factor[qi::_val = phoenix::construct<unary_op<cond_not> >(qi::_1)]
        ;

        term = factor[qi::_val = qi::_1] >> *(-qi::space >> qi::char_('&') >> -qi::space >> factor[cond_and_cond(qi::_val, qi::_1)]);
        cond = term[qi::_val = qi::_1] >> *(-qi::space >> qi::char_('|') >> -qi::space >> term[cond_or_cond(qi::_val, qi::_1)]);


        l_out = qi::string("level") >> *qi::space >> qi::char_(':') >> *qi::space >> lit[qi::_val = qi::_1];
        b_out = qi::string("beep") >> *qi::space >> qi::char_(':') >> *qi::space >> (qi::uint_(0) | qi::uint_(1));

        r = qi::string("if") >> *qi::space >> cond[set_condition(qi::_val, qi::_1)] >> *qi::space >> qi::string("then") >> *qi::space
            >> -((l_out[set_level(qi::_val, qi::_1)] >> *qi::space) | (b_out[set_beep(qi::_val, qi::_1)] >> *qi::space))
            >> -((l_out[set_level(qi::_val, qi::_1)] >> *qi::space) | (b_out[set_beep(qi::_val, qi::_1)] >> *qi::space))
            >> qi::string("fi") >> *qi::space;

	result = *((var[add_variable(qi::_val, qi::_1)] | r[add_rule(qi::_val, qi::_1)]));
    }

    qi::rule<Iterator, ident_type()> ident;
    qi::rule<Iterator, std::string()> alias;
    qi::rule<Iterator, variable_policy()> policy;
    qi::rule<Iterator, variable()> var;
    qi::rule<Iterator, rules(), qi::space_type> result;

    qi::rule<Iterator, literal()> lit;
    qi::rule<Iterator, refval()> ref;
    qi::rule<Iterator, sl_variable()> sl_var;

    qi::rule<Iterator, comp_op<comp_equal>()> c_equal;
    qi::rule<Iterator, comp_op<comp_not_equal>()> cn_equal;
    qi::rule<Iterator, comparator()> comp;

    qi::rule<Iterator, condition()> cond, term, factor;

    qi::rule<Iterator, literal()> l_out;
    qi::rule<Iterator, bool()> b_out;
    qi::rule<Iterator, rule()> r;
};

#endif //RULES_GRAMMAR_HPP
