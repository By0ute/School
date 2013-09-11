#ifndef VECPARAM_HH
# define VECPARAM_HH

# include <iostream>

class VecParam
{
    public:
	VecParam();
	VecParam(int x, int y, int po, int a, int pr);

	~VecParam();

	//getter
	int get_x() const;
	int get_y() const;
	int get_position() const;
	int get_azimut() const;
	int get_pression() const;

	// setter
	void set_x(int x);
	void set_y(int y);
	void set_position(int p);
	void set_azimut(int a);
	void set_pression(int p);

	// utils
	void print();

    private:
	int x_;
	int y_;
	int position_;
	int azimut_;
	int pression_;
};

bool operator==(const VecParam& v1, const VecParam& v2);


bool operator<(const VecParam& v1, const VecParam& v2);


inline bool operator==(const VecParam& v1, const VecParam& v2)
{
    return ((v1.get_x() == v2.get_x()) &&
	    (v1.get_y() == v2.get_y()) &&
	    (v1.get_position() == v2.get_position()) &&
	    (v1.get_azimut() == v2.get_azimut()) &&
	    (v1.get_pression() == v2.get_pression()));
}


inline bool operator<(const VecParam& v1, const VecParam& v2)
{
    return ((v1.get_x() < v2.get_x()) &&
	    (v1.get_y() < v2.get_y()) &&
	    (v1.get_position() < v2.get_position()) &&
	    (v1.get_azimut() < v2.get_azimut()) &&
	    (v1.get_pression() < v2.get_pression()));
}




#endif //VECPARAM_HH
