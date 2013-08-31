#ifndef TRT_HH
# define TRT_HH

# include <opencv2/core/core.hpp>
# include <cv.h>
# include <opencv2/highgui/highgui.hpp>

# include <iostream>
# include <string>
# include <vector>

using namespace cv;
using namespace std;

class Trt
{
    public:
	    // constructor and co
	    Trt();
	    Trt(Mat m);
	    Trt(Mat m, vector<vector <Point> > c,
		vector<vector<Point> > a, vector<Rect> b);

	    ~Trt();

	    // Treatment methods
	    Mat contours_bounding();
	    vector<vector<Point> > contours_bar(vector<vector<Point> >
						contours_origin);
	    Mat axes_bounding();

	    // utils
	    //void print_hierarchy();
	    void print_contours();

	    // getters setters
	    Mat get_mat();
	    vector<vector<Point> > get_contours();
	    vector<Vec4i> get_hierarchy();

	    void set_mat(Mat m);
	    void set_contours(vector<vector<Point> > c);
	    void set_axes(vector<vector<Point> > a);
	    //void set_hierarchy(vector<Vec4i> h);
	    void set_boundings(vector<Rect> b);

    private:
	    Mat mat_;
	    vector<vector<Point> > contours_;
	    vector<vector<Point> > axes_;
	    vector<Rect> boundings_;

};


//bool two_points_bar(vector<Point> v);
//bool four_points_bar(vector<Point> v);
bool points_bar(vector<Point> v);

vector<Point> points_axe(vector<Point> v);
//vector<Point> four_points_axe(vector<Point> v);
//vector<Point> three_five_points_axe(vector<Point> v);

#endif //TRT_HH
