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
	TestObj(list<Sign*> ls, list<string> ids);

	~TestObj();

	// Getter
	list<Sign*> get_listSign();
	list<string> get_identities();

	// Setter
	void set_listSign(list<Sign*> ls);
	void set_identities(list<string> ids);
    private:
	list<Sign*> listSign;
	list<string> identities;
};

#endif
