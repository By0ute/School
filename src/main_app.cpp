#include "main.hh"

using namespace std;
using namespace Learning;

int
main(int argc, char** argv)
{
    cout << "MAIN APPRENTISSAGE" << endl;
    cout << "------------------" << endl;

    if (argc < 2)
    {
	cout << "[Usage] : " << argv[0] << " {filename}.txt" << endl;
	return -1;
    }

    list<Sign*> listSign;
    listSign = parse(argv[1]);

    Base b = make_base(listSign);

    write_base(b);


    set<Model*>::iterator it = b.get_models().begin();
    Sign s;

    cout << "base size = " << b.get_models().size() << endl;

    for (it = b.get_models().begin();
	 it != b.get_models().end(); it++)
    {
	s = (*it)->get_ref_sign();
	s.print();
    }


    cout << "------------------" << endl;

    return 0;
}
