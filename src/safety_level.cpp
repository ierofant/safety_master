#include "safety_level.hpp"

bool 
operator<(safety_level level1, safety_level level2)
{
    bool result;
    if(level1 == level2) result = false;
    else if(level1 == safety) result = false;
    else if(level2 == safety) result = true;
    else 
    {
        unsigned l1 = static_cast<unsigned>(level1), l2 = static_cast<unsigned>(level2);
        result = (l1 < l2);
    }

    return result;
}

bool
operator>(safety_level level1, safety_level level2)
{
    bool result;
    if(level1 == level2) result = false;
    else if(level1 == safety) result = true;
    else if(level2 == safety) result = false;
    else 
    {
        unsigned l1 = static_cast<unsigned>(level1), l2 = static_cast<unsigned>(level2);
        result = (l1 > l2);
    }

    return result;
}

bool 
operator<=(safety_level level1, safety_level level2)
{
    bool result;
    if(level1 == level2) result = true;
    else result = operator<(level1, level2);

    return result;
}

bool
operator>=(safety_level level1, safety_level level2)
{
    bool result;
    if(level1 == level2) result = true;
    else result = operator>(level1, level2);

    return result;
}
