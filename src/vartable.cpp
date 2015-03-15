#include "vartable.hpp"

safety_level 
vartable::get_safety_level(const std::string &alias) const
{
    typedef table_type::index<by_alias>::type index_type;

    const index_type &index = table.get<by_alias>();
    index_type::const_iterator itr = index.find(alias);

    return (itr != index.end()) ? itr->get_safety_level() : safety;
}

void
vartable::set_safety_level(const ident_type &ident, safety_level level)
{
    typedef table_type::index<by_ident>::type index_type;

    index_type &index = table.get<by_ident>();
    index_type::iterator itr = index.find(ident);

    if(itr != index.end()) table.modify(itr, set_level(level));
}

void
vartable::insert(const variable &var)
{
    table.insert(var);
}

void
vartable::refresh()
{
    typedef table_type::index<by_ident>::type index_type;

    index_type &index = table.get<by_ident>();
    for(index_type::iterator itr = index.begin(), end = index.end(); itr != end; ++itr)
    {
        table.modify(itr, refresh_variable());
    }
}

vartable::set_level::set_level(safety_level level)
    : level(level)
{

}

void
vartable::set_level::operator()(variable &var) const
{
    var.set_safety_level(level);
}

void
vartable::refresh_variable::operator()(variable &var) const
{
    var.refresh();
}