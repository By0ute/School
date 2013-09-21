#ifndef VECPARAM_HH
# define VECPARAM_HH

# include <iostream>
# include <vector>

using namespace std;

class VecParam
{
    public:
	VecParam();
	VecParam(int x, int y, int t, int po, int a, int alt, int pr);

	~VecParam();

	//getter
	int get_x() const;
	int get_y() const;
	int get_timeStamp() const;
	int get_position() const;
	int get_azimut() const;
	int get_altitude() const;
	int get_pression() const;

	/**
	 * returns [x, y, timeStamp, position, azimut, altitude, pression]
	 */
	vector<int> get_vector_params() const;

	// setter
	void set_x(int x);
	void set_y(int y);
	void set_timeStamp(int t);
	void set_position(int p);
	void set_azimut(int a);
	void set_altitude(int a);
	void set_pression(int p);

	void set_vector_params(vector<int> params);

	// utils
	void print();

    private:
	int x_; /// x-coord
	int y_; /// y-coord
	int timeStamp_;
	int position_; /// Pen up or down
	int azimut_;
	int altitude_;
	int pression_;
};

bool operator==(const VecParam& v1, const VecParam& v2);


bool operator<(const VecParam& v1, const VecParam& v2);


inline bool operator==(const VecParam& v1, const VecParam& v2)
{
    return ((v1.get_x() == v2.get_x()) &&
	    (v1.get_y() == v2.get_y()) &&
	    (v1.get_timeStamp() == v2.get_timeStamp()) &&
	    (v1.get_position() == v2.get_position()) &&
	    (v1.get_azimut() == v2.get_azimut()) &&
	    (v1.get_altitude() == v2.get_altitude()) &&
	    (v1.get_pression() == v2.get_pression()));
}


inline bool operator<(const VecParam& v1, const VecParam& v2)
{
    return ((v1.get_x() < v2.get_x()) &&
	    (v1.get_y() < v2.get_y()) &&
	    (v1.get_timeStamp() < v2.get_timeStamp()) &&
	    (v1.get_position() < v2.get_position()) &&
	    (v1.get_azimut() < v2.get_azimut()) &&
	    (v1.get_altitude() < v2.get_altitude()) &&
	    (v1.get_pression() < v2.get_pression()));
}


#endif //VECPARAM_HH
