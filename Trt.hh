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
		vector<vector<Point> > a,
		vector<vector<vector<Point> > > f,
		vector<Rect> b);

	    ~Trt();

	    // Treatment methods
	    Mat contours_bounding();
	    vector<vector<Point> > contours_bar(vector<vector<Point> >
						contours_origin);
	    Mat axes_bounding();
	    Mat find_friends();

	    // utils
	    void print_contours();

	    // getters setters
	    Mat get_mat();
	    vector<vector<Point> > get_contours();

	    void set_mat(Mat m);
	    void set_contours(vector<vector<Point> > c);
	    void set_axes(vector<vector<Point> > a);
	    void set_friends(vector<vector<vector<Point> > > f);
	    void set_boundings(vector<Rect> b);

    private:
	    Mat mat_;
	    vector<vector<Point> > contours_;
	    vector<vector<Point> > axes_;
	    vector<vector<vector<Point> > > friends_;
	    vector<Rect> boundings_;

};


bool points_bar(vector<Point> v);

vector<Point> points_axe(vector<Point> v);

int distance(Point p1, Point p2);

vector<vector<Point> > make_vector(map<int, vector<Point> > m);

vector<Rect> make_boundings(map<int, vector<Point> > m, vector<Rect> b);

//int second_area_moment(Rect r1);

void print_point(Point p, int i);

int parallel_axes(vector<Point> a1, vector<Point> a2);



#endif //TRT_HH
