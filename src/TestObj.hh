#ifndef TESTOBJ_HH
# define TESTOBJ_HH

# include <string>
# include <list>
# include "Sign.hh"

using namespace std;

class TestObj
{
    public:
	TestObj();
	TestObj(list<pair<Sign*, string> > t);

	~TestObj();

	// Getter
	list<pair<Sign*, string> > get_tests();

	// Setter
	void set_test(list<pair<Sign*, string> > t);

    private:
	list<pair<Sign*, string> > tests_;
};

#endif
