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

    cout << "------------------" << endl;

    return 0;
}
