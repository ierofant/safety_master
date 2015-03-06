#ifndef VARTABLE_HPP
#define VARTABLE_HPP

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/tag.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include "variable.hpp"

using namespace boost::multi_index;

class vartable
{
public:
    typedef variable::ident_type ident_type;

    void insert(const variable &var);
    safety_level get_safety_level(const std::string &alias) const;
    void set_safety_level(const ident_type &ident, safety_level level);

private:
    struct set_level
    {
        set_level(safety_level level);
        void operator()(variable &var) const;
        safety_level level;
    };

    struct by_ident;
    struct by_alias;
    typedef boost::multi_index_container<variable, indexed_by<
			hashed_unique<tag<by_ident>, const_mem_fun<variable, const ident_type&, &variable::get_ident> >,
			hashed_unique<tag<by_alias>, const_mem_fun<variable, const std::string&, &variable::get_alias> >
		> > table_type;

    table_type table;
};

#endif //VARIABLE_HPP
