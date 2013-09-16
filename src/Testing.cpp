#include "Testing.hh"

using namespace std;

namespace Testing
{

    void test()
    {
		Sign s1;
		Sign s2;

		VecParam v1 = VecParam(1, 1, 3, 0, 2);
		VecParam v2 = VecParam(2, 2, 3, 0, 1);
		VecParam v3 = VecParam(3, 4, 5, 0, 1);
		VecParam v4 = VecParam(1, 0, 3, 0, 2);
		VecParam v5 = VecParam(2, 1, 3, 0, 1);
		VecParam v6 = VecParam(3, 2, 5, 0, 1);

		s1.add_data(v1);
		s1.add_data(v2);
		s1.add_data(v3);

		s2.add_data(v4);
		s2.add_data(v5);
		s2.add_data(v6);

		cout << "SIZE1: " << s1.get_datas().size() << ", SIZE2: " << s2.get_datas().size() << endl;
		cout << "SUPER DISTANCE: " << distance(s1, s2) << endl;
    }

	double distance(Sign s1, Sign s2)
	{
		int size_1 = s1.get_datas().size();
		int size_2 = s2.get_datas().size();
		double p = 0.2;
		double dist_res = 0;

		if (size_1 != size_2)
			return -1;

		std::list<VecParam>::iterator it1 = s1.get_datas().begin();
		std::list<VecParam>::iterator it2 = s2.get_datas().begin();

		while (it1 != (s1.get_datas()).end())
		{
			VecParam v1 = *it1;
			VecParam v2 = *it2;

			double dist_x = pow( abs(v1.get_x() - v2.get_x()), p);
			double dist_y = pow(abs(v1.get_y() - v2.get_y()), p);
			double dist_pos = pow(abs(v1.get_position() - v2.get_position()), p);
			double dist_azimut = pow(abs(v1.get_azimut() - v2.get_azimut()), p);
			double dist_pression = pow(abs(v1.get_pression() - v2.get_pression()), p);

			dist_res += dist_x + dist_y + dist_pos + dist_azimut + dist_pression;
			it1++;
			it2++;
		}

		dist_res = pow(dist_res, 1 / p);

		return dist_res;
	}
}
