#ifndef TESTING_HH
# define TESTING_HH

# include <iostream>
# include "Sign.hh"
# include "VecParam.hh"
# include <math.h>
# include <limits.h>
# include <stdlib.h>

# define PNORM 0.2

namespace Testing
{
    double distance(Sign s1, Sign s2);

    void test();
}

#endif //TESTING_HH
