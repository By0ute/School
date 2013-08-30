#include "Trt.hh"

/* CONSTRUCTORS */
Trt::Trt()
    : mat_ (),
    contours_ (),
    hierarchy_ ()
{
}

Trt::Trt(Mat m)
    : mat_ (m.clone()),
    contours_ (),
    hierarchy_ ()
{
}

Trt::Trt(Mat m, std::vector<std::vector <Point> > c, std::vector<Vec4i> h)
    : mat_ (m),
    contours_ (c),
    hierarchy_ (h)
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
std::vector<std::vector<Point> >
Trt::get_contours()
{
    return contours_;
}

// hierarchy_
std::vector<Vec4i>
Trt::get_hierarchy()
{
    return hierarchy_;
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
Trt::set_contours(std::vector<std::vector<Point> > c)
{
    contours_ = c;
}

// hierarchy_
void
Trt::set_hierarchy(std::vector<Vec4i> h)
{
    hierarchy_ = h;
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
Trt::contours_bouding()
{
    // all contours of the white shapes
    std::vector<std::vector<Point> > contours;
    // hierarchy of the contours
    std::vector<Vec4i> hierarchy;
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
    std::vector<std::vector<Point> > contours_poly(contours.size());
    // list of bounding boxes
    std::vector<Rect> boundRect(contours.size());

    // approximates contours so that looks lire more polygonial
    // and creates bounding boxes around those simplified shapes
    for (int i = 0; i < contours.size(); i++)
    {
	approxPolyDP(Mat(contours[i]), contours_poly[i], 10, true);
	boundRect[i] = boundingRect(Mat(contours_poly[i]));
    }

    // draws all the contours of the white shapes
    for (int i = 0; i < contours.size(); i++)
	drawContours(res, contours, i, color_contours, 0, CV_AA, hierarchy);

    // selects only the coor of the bounding boxes that have
    // 2 to 4 points in contours_poly
    for (int i = 0; i < contours_poly.size(); i++)
    {
	if ((contours_poly[i].size() < 2) &&
	    (contours_poly[i].size() > 4))
	    contours_poly.erase(contours_poly.begin()+i);
    }

    // finally draws bounding boxes with the reduced list
    for (int i = 0; i < contours_poly.size(); i++)
    {
	rectangle(res, boundRect[i].tl(), boundRect[i].br(), color_bounding,
		  1, 8, 0);
    }

    // set the new parameters in the object for a future use
    set_hierarchy(hierarchy);
    set_contours(contours_poly);
    set_mat(res);

    return res;
}

// contours_bar
Mat
Trt::contours_bar()
{
    // result image
    Mat res = Mat::zeros(mat_.size(), CV_8UC3);
    // color for the bounding boxes (YELLOW)
    Scalar color_bounding = Scalar(255, 255, 0);
    //
    bool res_vec = false;
    int i  = 0;
    std::vector<std::vector<Point> > contours_simplified;

    for (int i = 0; i < contours_.size(); i++)
    {
	vector<Point> vec = contours_[i];
	if (vec.size() == 4)
	    res_vec = four_points_bar(vec);
	else if (vec.size() == 2)
	    res_vec = two_points_bar(vec);

	if (res_vec)
	    contours_simplified.push_back(vec);
    }

    for (int i = 0; i < contours_simplified.size(); i++)
    {
	if (contours_simplified[i].size() == 2)
	    rectangle(res, contours_simplified[i][0],
		  contours_simplified[i][1], color_bounding, 1, 8, 0);
	else
	    rectangle(res, contours_simplified[i][0],
		  contours_simplified[i][2], color_bounding, 1, 8, 0);

    }

    set_contours(contours_simplified);
    set_mat(res);

    return res;
}


/* UTILS */
void
Trt::print_hierarchy()
{
    cout << "hierarchy : ";
    for (auto vec : hierarchy_)
    {
	for (int i = 0; i < 4; i++)
	    cout << vec[i] << ' ';
       cout << endl;
    }
}

void
Trt::print_contours()
{
    cout << "Contours : ";
    int i = 1;
    for (auto vec : contours_)
    {
	cout << i << " : ";
	for (auto v : vec)
	    cout << v << ' ';
	//int s = vec.size();
	i++;
	cout << endl;
    }
}

bool
four_points_bar(vector<Point> v)
{
    //  p1 --- p3
    //  |	|
    //  |	|
    //  p2 ---  +
    Point p1 = v[0];
    Point p2 = v[1];
    Point p3 = v[3];

    int Y = p2.y - p1.y;
    int X = p3.x - p1.x;

    if ((X*10 < Y) || (Y*10 < X))
	return true;

    return false;
}

bool
two_points_bar(vector<Point> v)
{
    //  p1 --- p3
    //  |	|
    //  |	|
    //  p2 ---  +
    Point p1 = v[0];
    Point p2 = v[1];

    int Y = p2.y - p1.y;
    int X = p2.x - p1.x;

    if ((X*20 < Y) || (Y*20 < X))
	return true;

    return false;
}
