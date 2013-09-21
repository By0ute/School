#ifndef BASE_HH
# define BASE_HH

# include "Model.hh"
# include <set>

using namespace std;

class Base
{
    public:
	Base();
	Base(set<Model*> m);

	~Base();

	//getter
	set<Model*> get_models() const;

	// setter
	void set_models(set<Model*> m);

	void add_model(Model* m);

    private:
	set<Model*> models_;
};


#endif //BASE_HH
