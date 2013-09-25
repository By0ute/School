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
# include <stdlib.h>

# include "Axe.hh"
# include "BarCodeTrt.hh"

# define MAJO_ROTATEDRECT 20
# define WHITE Scalar(255, 255, 255)
# define BLACK Scalar(0, 0, 0)
# define BLUE Scalar(255, 0, 0)
# define GREEN Scalar(0, 255, 0)
# define RED Scalar(0, 0, 255)
# define PINK Scalar(100, 0, 255)
# define YELLOW Scalar(255, 255, 0)

using namespace cv;
using namespace std;

class Trt
{
    public:
	    // constructor and co
	    Trt ();
	    Trt (Mat m);
	    Trt (Mat m, vector<vector <Point> > c,
		vector<Axe> a,
		vector<set<Axe> > f,
		vector<RotatedRect> r);

	    ~Trt();

	    // Treatment methods
	    Mat contours_bounding ();
	    Mat axes_bounding ();
	    Mat find_friends ();
	    Mat& print_results (Mat& src);
	    //Mat extract_deskew (RotatedRect& r);
	    vector<int> extract_deskew (RotatedRect& r);
	    Mat subtreatment (Mat& cropped, RotatedRect& box);

	    // utils
	    void print_contours ();
	    void print_friends ();

	    // getters setters
	    Mat get_mat () const;
	    vector<vector<Point> > get_contours () const;
	    vector<RotatedRect> get_rects () const;

	    void set_mat (Mat m);
	    void set_contours (vector<vector<Point> > c);
	    void set_axes (vector<Axe> a);
	    void set_friends (vector<set<Axe> > f);
	    void set_rects (vector<RotatedRect> r);

    private:
	    Mat mat_;
	    vector<vector<Point> > contours_;
	    vector<Axe> axes_;
	    vector<set<Axe> > friends_;
	    vector<RotatedRect> rects_;

};


Axe
points_axe (vector<Point>& v);

Axe
rect_axe (RotatedRect& r);

RotatedRect
rect_bar (vector<Point>& v);

int
distance (Point& p1, Point& p2);
int
distance (Point2f& p1, Point2f& p2);

vector<vector<Point> >
make_vector (map<int, vector<Point> >& m);

vector<Rect>
make_boundings (map<int, vector<Point> > m, vector<Rect>& b);

void
print_point (Point& p, int& i);

void
print_axe (Axe& a);

int
parallel_axes (Axe& a1, Axe& a2);

bool
is_doublon (set<Axe>& s1, set<Axe>& s2);

string
key_str_axe (Axe& a);

RotatedRect
create_rotated_rect(set<Axe>& s);


#endif //TRT_HH
