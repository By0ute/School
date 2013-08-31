#include "Trt.hh"

/* CONSTRUCTORS */
Trt::Trt()
    : mat_ (),
    contours_ (),
    axes_ (),
    boundings_()
{
}

Trt::Trt(Mat m)
    : mat_ (m.clone()),
    contours_ (),
    axes_ (),
    boundings_()
{
}

Trt::Trt(Mat m, vector<vector <Point> > c,
	 vector<vector<Point> > a, vector<Rect> b)
    : mat_ (m.clone()),
    contours_ (c),
    axes_ (a),
    boundings_(b)
{
}

/* DESTRUCTOR */
Trt::~Trt()
{
}

/* GETTERS */
// mat_
Mat
Trt::get_mat()
{
    return mat_;
}

// contours_
vector<vector<Point> >
Trt::get_contours()
{
    return contours_;
}

/* SETTERS */
// mat_
void
Trt::set_mat(Mat m)
{
    mat_ = m;
}

// contours_
void
Trt::set_contours(vector<vector<Point> > c)
{
    contours_ = c;
}

// axes_
void
Trt::set_axes(vector<vector<Point> > a)
{
    axes_ = a;
}

// boundings_
void
Trt::set_boundings(vector<Rect> b)
{
    boundings_ = b;
}

/* METHODS */
// contours_bouding
// this function finds the real contours of the shapes defined by preatment
// a polygon simplification is done on those contours
// then boundings boxes are calculated for simplified contours
// a first selection is used to only selectionate bounding boxes with
//    parameters between 2 and 4 (that corresponds to a bar of a code bar :
//    2 for a really thin and 4 for a rectangle one)
Mat
Trt::contours_bounding()
{
    // all contours of the white shapes
    vector<vector<Point> > contours;
    // hierarchy of the contours
    vector<Vec4i> hierarchy;
    // result image stored in a Mat
    Mat res = Mat::zeros(mat_.size(), CV_8UC3);
    // color for the contours (BLUE)
    Scalar color_contours = Scalar(255, 0, 0);
    // color for the bounding boxes (YELLOW)
    Scalar color_bounding = Scalar(255, 255, 0);

    // find the contours of the white shapes in the original picture
    findContours(mat_, contours, hierarchy, CV_RETR_EXTERNAL,
	     CV_CHAIN_APPROX_SIMPLE);

    // contours for bounding boxes (reduced within this method)
    vector<vector<Point> > contours_poly(contours.size());
    //
    vector<vector<Point> > contours_selected;
    // list of bounding boxes
    vector<Rect> boundRect(contours.size());

    // approximates contours so that looks lire more polygonial
    // and creates bounding boxes around those simplified shapes
    for (int i = 0; i < contours.size(); i++)
    {
	approxPolyDP(Mat(contours[i]), contours_poly[i], 10, true);
	drawContours(res, contours, i, color_contours, 0, CV_AA, hierarchy);
    }

    contours_selected = contours_bar(contours_poly);

    for (int i = 0; i < contours_selected.size(); i++)
    {
	boundRect[i] = boundingRect(Mat(contours_selected[i]));
	rectangle(res, boundRect[i].tl(), boundRect[i].br(), color_bounding,
		  1, 8, 0);
    }

    //for (int i = 0; i < contours_poly.size(); i++)
    //{
	//boundRect[i] = boundingRect(Mat(contours_poly[i]));
	////rectangle(res, boundRect[i].tl(), boundRect[i].br(), color_bounding,
	////1, 8, 0);
    //}


    //for (int i = 405; i <= 415; i++)
    //{
    //rectangle(res, boundRect[i].tl(), boundRect[i].br(), color_bounding,
    //1, 8, 0);
    //}

    //rectangle(res, boundRect[408].tl(), boundRect[408].br(), color_bounding,
	      //1, 8, 0);

    // set the new parameters in the object for a future use
    //set_hierarchy(hierarchy);
    set_contours(contours_selected);
    set_boundings(boundRect);
    //set_contours(contours_poly);
    //print_contours();
    set_mat(res);

    return res;
}

// contours_bar
std::vector<std::vector<Point> >
Trt::contours_bar(std::vector<std::vector<Point> > contours_origin)
{
    // color for the bounding boxes (YELLOW)
    Scalar color_bounding = Scalar(255, 255, 0);
    //
    int i  = 0;
    std::vector<std::vector<Point> > contours_simplified;

    for (auto vec : contours_origin)
    {
	int size = vec.size();

	if ((size >= 2) && (size <= 5))
	{
	    if (points_bar(vec))
		contours_simplified.push_back(vec);
	}
    }

    return contours_simplified;
}

Mat
Trt::axes_bounding()
{
    contours_bounding();

    vector<vector<Point> > axes;
    // YELLOW
    Scalar color_bounding = Scalar(255, 255, 0);
    // PINK
    Scalar color_axe= Scalar(100, 0, 255);
    Mat mat_res = Mat::zeros(mat_.size(), CV_8UC3);

    for (int i = 0; i < contours_.size(); i++)
    {
	int size = contours_[i].size();

	axes.push_back(points_axe(contours_[i]));

	rectangle(mat_res, boundings_[i].tl(), boundings_[i].br(),
		  color_bounding, 1, 8, 0);
	line(mat_res, axes[i][0], axes[i][1], color_axe, 1, 8, 0);
    }

    set_axes(axes);
    return mat_res;
}


/* UTILS */
void
Trt::print_contours()
{
    cout << "Contours : ";
    int i = 0;
    for (auto vec : contours_)
    //for (int i = 0; i < 500; i++)
    {
	//vector<Point> vec = contours_[i];
	cout << i << " : ";
	for (auto v : vec)
	    cout << v << ' ';
	//int s = vec.size();
	i++;
	cout << endl;
    }
}


/* UTILS FUNCTIONS */


// 2 4 3-5 AXE
vector<Point>
points_axe(vector<Point> v)
{
    int max_y = 0;
    int max_x = 0;
    int min_y = numeric_limits<int>::max();
    int min_x = numeric_limits<int>::max();
    vector<Point> res;

    for (int i = 0; i < v.size(); i++)
    {
	int x = v[i].x;
	int y = v[i].y;

	max_y = (y > max_y)?y:max_y;
	max_x = (x > max_x)?x:max_x;
	min_y = (y < min_y)?y:min_y;
	min_x = (x < min_x)?x:min_x;
    }

    int Y = max_y - min_y;
    int X = max_x - min_x;

    if (X > Y)
    {
	int mid = (max_y + min_y) / 2;
	Point p0(min_x, mid);
	Point p1(max_x, mid);
	res.push_back(p0);
	res.push_back(p1);
    }
    else
    {
	int mid = (max_x + min_x) / 2;
	Point p0(mid, min_y);
	Point p1(mid, max_y);
	res.push_back(p0);
	res.push_back(p1);
    }

    return res;
}




// 2 4 3-5 BAR
bool
points_bar(vector<Point> v)
{
    // 2 POINTS
    //  p1 ---  +
    //  |	|
    //  |	|
    //  +  --- p2


    // 4 POINTS
    //  p1 --- p4
    //  |	|
    //  |	|
    //  p2 --- p3


    // 3-5 POINTS
    //  p2 ----  p1
    //  |	 |
    //  |	 |
    //  (p3)-p4-(p5)
    //
    //  or p4 on the top as p2 and so on

    int max_y = 0;
    int max_x = 0;
    int min_y = numeric_limits<int>::max();
    int min_x = numeric_limits<int>::max();

    for (int i = 0; i < v.size(); i++)
    {
	int x = v[i].x;
	int y = v[i].y;

	max_y = (y > max_y)?y:max_y;
	max_x = (x > max_x)?x:max_x;
	min_y = (y < min_y)?y:min_y;
	min_x = (x < min_x)?x:min_x;
    }

    int Y = max_y - min_y;
    int X = max_x - min_x;

    if ((X*8 < Y) || (Y*8 < X))
	return true;

    return false;
}

