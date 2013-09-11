#include "Learning.hh"

namespace Learning
{

    void print(Sign s)
    {
	int i = 0;

	list<VecParam> d = s.get_datas();

	for (VecParam v : d)
	{
	    cout << "----------------" << endl;
	    cout << "Vector " << i << endl;
	    v.print();
	    cout << "----------------" << endl;
	    i++;
	}
    }

}
