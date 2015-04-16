#ifndef TESTING_HH
# define TESTING_HH

# include <iostream>
# include "Sign.hh"
# include "VecParam.hh"
# include <math.h>
# include <limits.h>
# include <float.h>
# include <stdlib.h>
# include "Parseur.hh"

# define PNORM 0.2
# define THRESHOLD_ACCEPTATION -34
# define MULTIPLICATOR 100

namespace Testing
{
    double distance(Sign* s1, Sign* s2);

    void test_sign(Sign* test_sign, string& filename, string& filenameTest);
}

#endif //TESTING_HH
