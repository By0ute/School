#include "Testing.hh"

using namespace std;

namespace Testing
{
    void test_sign(Sign* test_sign, string& filename, string& filenameTest)
    {
	Sign* ref_sign = parseFile(filename + ".txt", filename);

	if (ref_sign != nullptr)
	{
	    test_sign->normalize();

	    double dist = distance(test_sign, ref_sign);
	    // IF  dist  IS IN  ]0;+inf[  THEN  -log(dist)  IS IN  ]-inf;+inf[
	    double score = (dist == 0) ? DBL_MAX : -log(dist);

	    char decision = 'u'; // for 'u'ndecided

	    if (score >= THRESHOLD_ACCEPTATION)
		// need to test to find the right threshold
		decision = 't';
	    else
		decision = 'f';

	    // name of the file_test lost in parsing
	    // need to add it either as an attribute to TestObj
	    // or something else
	    cout << filename << " " << score << endl;
	    writeFinalFile(filenameTest, filename, score, decision);
	}
	else
	{
	    cerr << "Error: The model for " << filename;
	    cerr << " has not been found." << endl;
	}
    }

    double distance(Sign* s1, Sign* s2)
    {
	list<VecParam> datas1 = s1->get_datas();
	list<VecParam> datas2 = s2->get_datas();
	list<VecParam>::iterator it1 = datas1.begin();
	list<VecParam>::iterator it2 = datas2.begin();


	if (datas1.size() == datas2.size())
	{
	    double res = 0;

	    for (it1 = datas1.begin(), it2 = datas2.begin();
		 it1 != datas1.end(), it2 != datas2.end();
		 it1++, it2++)
	    {
		vector<int> params1 = it1->get_vector_params();
		vector<int> params2 = it2->get_vector_params();

		for (int i = 0; i < params1.size(); i++)
		    res += (pow(abs(params1[i] - params2[i]), PNORM));
	    }

	    return (pow(res, (1 / PNORM)));
	}

	return DBL_MAX;
    }
}
