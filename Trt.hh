#ifndef TRT_HH
# define TRT_HH

# include <opencv2/core/core.hpp>
# include <cv.h>
# include <opencv2/highgui/highgui.hpp>

# include <iostream>
# include <string>
# include <vector>
# include <map>
# include <math.h>
# include <sstream>

# include "Axe.hh"
# include "Box.hh"
//# include <stdlib>

using namespace cv;
using namespace std;

class Trt
{
    public:
	    // constructor and co
	    Trt();
	    Trt(Mat m);
	    Trt(Mat m, vector<vector <Point> > c,
		vector<Axe> a,
		vector<set<Axe> > f,
		vector<RotatedRect> r);

	    ~Trt();

	    // Treatment methods
	    Mat contours_bounding();
	    Mat axes_bounding();
	    Mat find_friends();

	    // utils
	    void print_contours();
	    void print_friends();

	    // getters setters
	    Mat get_mat();
	    vector<vector<Point> > get_contours();

	    void set_mat(Mat m);
	    void set_contours(vector<vector<Point> > c);
	    void set_axes(vector<Axe> a);
	    void set_friends(vector<set<Axe> > f);
	    void set_rects(vector<RotatedRect> r);

    private:
	    Mat mat_;
	    vector<vector<Point> > contours_;
	    vector<Axe> axes_;
	    vector<set<Axe> > friends_;
	    vector<RotatedRect> rects_;

};


Axe points_axe(vector<Point> v);

Axe rect_axe(RotatedRect r);

RotatedRect rect_bar(vector<Point> v);

int distance(Point p1, Point p2);

vector<vector<Point> > make_vector(map<int, vector<Point> > m);

vector<Rect> make_boundings(map<int, vector<Point> > m, vector<Rect> b);

//int second_area_moment(Rect r1);

void print_point(Point p, int i);

void print_axe(Axe a);

int parallel_axes(Axe a1, Axe a2);



#endif //TRT_HH
