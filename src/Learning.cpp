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

    Base make_base(list<Sign*>& signs)
    {
	// to iterate on parsed signatures
	list<Sign*>::iterator it = signs.begin();

	// to make models
	map<id_type, list<Sign*> > sort_models;
	map<id_type, list<Sign*> >::iterator it_map;

	// to make base
	set<Model*> models;

	// sort signatures in order to create Models
	for (it = signs.begin(); it != signs.end(); it++)
	{
	    id_type id = (*it)->get_id();

	    it_map = sort_models.find(id);

	    if (it_map == sort_models.end())
		sort_models[id] = list<Sign*>();

	    (*it)->normalize();
	    sort_models[id].push_back(*it);
	}

	// create Models
	for (it_map = sort_models.begin();
	     it_map != sort_models.end(); it_map++)
	{
	    Model* m = new Model(it_map->first, it_map->second);
	    models.insert(m);
	}

	return Base(models);
    }

    void write_base(Base& b)
    {
	set<Model*>::iterator it;

	cout << "1" << endl;
	for (it = b.get_models().begin();
	     it != b.get_models().end();
	     it++)
	{
	cout << "1.1" << endl;
	    string filename = (*it)->get_id() + ".txt";
	cout << "1.2" << endl;
	    ofstream file(filename, ios::out);

	cout << "1.2.1" << endl;
	    Sign s = (*it)->get_ref_sign(); // AREUM
	cout << "1.2.2" << endl;
	    int size = (*it)->get_ref_sign().get_datas().size();
	cout << "1.3" << endl;
	//file << (*it)->get_ref_sign().get_datas().size() << endl;
	file << size << endl;

	cout << "1.4" << endl;
	    list<VecParam>::iterator it_vec =
		(*it)->get_ref_sign().get_datas().begin();

	cout << "2" << endl;
	    for (it_vec = (*it)->get_ref_sign().get_datas().begin();
		 it_vec != (*it)->get_ref_sign().get_datas().end();
		 it_vec++)
	    {
		file << it_vec->get_x() << " ";
		file << it_vec->get_y() << " ";
		file << it_vec->get_timeStamp() << " ";
		file << it_vec->get_position() << " ";
		file << it_vec->get_azimut() << " ";
		file << it_vec->get_altitude() << " ";
		file << it_vec->get_pression() << endl;
	    }

	cout << "3" << endl;
	    file.close();
	}

    }

}
