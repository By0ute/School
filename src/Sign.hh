#ifndef SIGN_HH
# define SIGN_HH

# include "VecParam.hh"
# include <list>
# include <string>
# include <limits.h>
# include <vector>
# include <map>
# include <set>

# define NORMA_SIZE 25

using namespace std;

class Sign
{
    public:
	Sign();
	Sign(string i);
	Sign(list<VecParam> d, string i);
	Sign(const Sign& s) { Sign(s.datas_, s.id_); }

	~Sign();

	//getter
	list<VecParam> get_datas() const;
	string get_id() const;

	// setter
	void set_datas(list<VecParam> d);
	void set_id(string i);

	void add_data(VecParam v);

	// utils
	void normalize();
	int find_tmin();
	int find_tmax();
	VecParam norma_vect(list<VecParam>& list_v);
	void print();

    private:
	list<VecParam> datas_;
	string id_;
};


bool operator==(const Sign& s1, const Sign& s2);


bool operator<(const Sign& s1, const Sign& s2);


inline bool operator==(const Sign& s1, const Sign& s2)
{
    return (s1.get_id() == s2.get_id());
}


inline bool operator<(const Sign& s1, const Sign& s2)
{
    return (s1.get_id() < s2.get_id());
}


#endif //SIGN_HH
