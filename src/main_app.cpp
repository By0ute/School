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
	cout << "Usage: " << argv[0] << " <filename>" << endl;
	return 1;
    }

    list<Sign*> listSign;
    listSign = parse(argv[1]);

//    VecParam v;
//    Sign s;
//    Base b;

    cout << "------------------" << endl;
//    cout << "--- Test Parseur ---" << endl;
//    for (auto it : listSign)
//    {
//	print(*it);
//    }
//    cout << "--------------------" << endl;
//    cout << "Before Add : Size of S = " << s.get_datas().size() << endl;

//    s.add_data(v);

//    cout << "After Add : Size of S = " << s.get_datas().size() << endl;

//    cout << "------------------" << endl;

//    cout << "Trying to print s" << endl;
//    print(s);

//    cout << "------------------" << endl;


//    cout << "Before Add : Size of b = " << b.get_signatures().size() << endl;

//    b.add_signature(s);

//    cout << "After Add : Size of b = " << b.get_signatures().size() << endl;

    return 0;
}
