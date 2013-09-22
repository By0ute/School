#ifndef TESTOBJ_HH
# define TESTOBJ_HH

# include <string>
# include <list>
# include <tuple>
# include "Sign.hh"

using namespace std;

class TestObj
{
    public:
	TestObj();
	TestObj(list<tuple<Sign*, string, string>> t);

	~TestObj();

	// Getter
	list<tuple<Sign*, string, string> > get_tests();

	// Setter
	void set_test(list<tuple<Sign*, string, string> > t);

    private:
	// Signature, identity to test and test filename
	list<tuple<Sign*, string, string> > tests_;
};

#endif
