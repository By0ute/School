#ifndef TESTING_HH
# define TESTING_HH

# include <iostream>
# include "Sign.hh"
# include "VecParam.hh"
# include <math.h>
# include <limits.h>
# include <stdlib.h>
# include "Parseur.hh"

# define PNORM 0.2
# define THRESHOLD_ACCEPTATION 100 // need to test to find the right threshold

namespace Testing
{
    double distance(Sign* s1, Sign* s2);

    void test_sign(Sign* test_sign, string& filename);

    void test();
}

#endif //TESTING_HH
