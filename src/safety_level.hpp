#ifndef SAFETY_LEVEL_HPP
#define SAFETY_LEVEL_HPP

enum safety_level
{
    clear = 0,
    safety = 1,
    warning1 = 2,
    warning2 = 3
};

bool 
operator<(safety_level level1, safety_level level2);

bool
operator>(safety_level level1, safety_level level2);

#endif //SAFETY_LEVEL_HPP
