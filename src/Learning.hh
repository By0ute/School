#ifndef LEARNING_HH
# define LEARNING_HH

# include <iostream>
# include <fstream>
# include <sstream>
# include "Base.hh"

namespace Learning
{
    void print(Sign s);

    Base make_base(list<Sign*>& signs);
    void write_base(Base& b);
}

#endif //LEARNING_HH
