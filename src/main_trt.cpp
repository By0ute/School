#include "main.hh"

using namespace std;
using namespace Testing;

int
main(int argc, char** argv)
{
    cout << "MAIN TREATMENT" << endl;
    cout << "--------------" << endl;

    if (argc < 2)
    {
	cerr << "Usage: " << argv[0] << " <test filename>" << endl;
	return 1;
    }

    /// Sign list and identities list
    /// Sign[0] has to be compared with identities[0]
    TestObj* testSign = parseTrt(argv[1]);

    if (!testSign)
    {
	cerr << "Error with file " << argv[1] << endl;
	return 1;
    }

    test();

    return 0;
}
