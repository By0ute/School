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
	//TestObj(list<Sign*> ls, list<string> ids);
	TestObj(list<pair<Sign*, string> > t);


	~TestObj();

	// Getter
	//list<Sign*> get_listSign();
	//list<string> get_identities();
	list<pair<Sign*, string> > get_tests();

	// Setter
	//void set_listSign(list<Sign*> ls);
	//void set_identities(list<string> ids);
	void set_test(list<pair<Sign*, string> > t);

    private:
	//list<Sign*> listSign;
	//list<string> identities;
	list<pair<Sign*, string> > tests_;
};

#endif
