#ifndef SIGN_HH
# define SIGN_HH

# include "VecParam.hh"
# include <list>

using namespace std;

class Sign
{
    public:
	Sign();
	Sign(int i);
	Sign(list<VecParam> d, int i);

	~Sign();

	//getter
	list<VecParam> get_datas() const;
	int get_id() const;

	// setter
	void set_datas(list<VecParam> d);
	void set_id(int i);

	void add_data(VecParam v);

    private:
	list<VecParam> datas_;
	int id_;
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
