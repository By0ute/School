#include "Learning.hh"

using namespace std;

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

    Base make_base (list<Sign*>& signs)
    {
	// to make models
	map<id_type, list<Sign*> > sort_models;
	map<id_type, list<Sign*> >::iterator it_map;

	// to make base
	set<Model*> models;

	// sort signatures in order to create Models
	for (Sign* s : signs)
	{
	    id_type id = s->get_id();

	    it_map = sort_models.find(id);

	    if (it_map == sort_models.end())
		sort_models[id] = list<Sign*>();

	    s->normalize();
	    sort_models[id].push_back(s);
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
	for (Model* m : b.get_models())
	{
	    int size = m->get_ref_sign().get_datas().size();
	    string filename = m->get_id() + ".txt";
	    ofstream file(filename, ios::out);

	    if (!file)
	    {
		cerr << "Error : while creating file" << filename << endl;
		return;
	    }

	    file << m->get_ref_sign().get_datas().size() << endl;
	    for (VecParam v : m->get_ref_sign().get_datas())
	    {
		file << v.get_x() << " ";
		file << v.get_y() << " ";
		file << v.get_timeStamp() << " ";
		file << v.get_position() << " ";
		file << v.get_azimut() << " ";
		file << v.get_altitude() << " ";
		file << v.get_pression() << endl;
	    }

	    file.close();
	}

    }

}
