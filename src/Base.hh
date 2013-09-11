#ifndef BASE_HH
# define BASE_HH

# include "Sign.hh"
# include <set>

using namespace std;

class Base
{
    public:
	Base();
	Base(set<Sign> s);

	~Base();

	//getter
	set<Sign> get_signatures() const;

	// setter
	void set_signatures(set<Sign> s);

	void add_signature(Sign s);

    private:
	set<Sign> signatures_;
};


#endif //BASE_HH
