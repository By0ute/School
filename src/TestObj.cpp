#include "TestObj.hh"

TestObj::TestObj()
{
}


TestObj::TestObj(list<tuple<Sign*, string, string> > t)
    : tests_ (t)
{
}

TestObj::~TestObj()
{
}

list<tuple<Sign*, string, string> >
TestObj::get_tests()
{
    return tests_;
}

void
TestObj::set_test(list<tuple<Sign*, string, string> > t)
{
    tests_ = t;
}
