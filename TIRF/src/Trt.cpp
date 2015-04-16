#include "Trt.hh"
# define MIN_INT(a,b) (a<=b?a:b)
# define MAX_INT(a,b) (a>=b?a:b)

/* *********************************************************************** */
/*				BASICS					   */
/* *********************************************************************** */

/* -------------- */
/* -------------- */
/*  CONSTRUCTORS  */
/* -------------- */
/* -------------- */
Trt::Trt()
    :
	mat_ (),
    contours_ (),
    axes_ (),
    friends_ (),
    rects_ ()
{
}

Trt::Trt(Mat m)
    :
	mat_ (m.clone()),
	contours_ (),
	axes_ (),
	friends_ (),
	rects_ ()
{
}

Trt::Trt(Mat m, vector<vector <Point> > c,
	 //Trt::Trt(vector<vector <Point> > c,
	 vector<Axe> a,
	 vector<set<Axe> > f,
	 vector<RotatedRect> r)
    :
    mat_ (m.clone()),
    contours_ (c),
    axes_ (a),
    friends_ (f),
    rects_ (r)
{
}

/* -------------- */
/* -------------- */
/* DESTRUCTOR */
/* -------------- */
/* -------------- */
Trt::~Trt()
{
}


/* -------------- */
/* -------------- */
/* GETTERS */
/* -------------- */
/* -------------- */
// mat_
Mat
Trt::get_mat() const
{
    return mat_;
}

// contours_
vector<vector<Point> >
Trt::get_contours() const
{
    return contours_;
}

vector<RotatedRect>
Trt::get_rects() const
{
    return rects_;
}



/* -------------- */
/* -------------- */
/* SETTERS */
/* -------------- */
/* -------------- */
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
Trt::set_axes(vector<Axe> a)
{
    axes_ = a;
}

// friends_
void
Trt::set_friends(vector<set<Axe> > f)
{
    friends_ = f;
}

// boundings_
void
Trt::set_rects(vector<RotatedRect> r)
{
    rects_ = r;
}

/* *********************************************************************** */
/*				METHODS					   */
/* *********************************************************************** */

/* ------------------ */
/* ------------------ */
/* COUNTOURS_BOUNDING */
/* ------------------ */
/* ------------------ */
// this function finds contours of shapes defined by preatment
// boundings boxes are calculated for simplified contours
// a first selection is used to only selectionate bounding boxes with
//    parameters between 2 and 5 (that corresponds to a bar of a code bar :
//    2 for a really thin and 5 for a twisted rectangle one)
Mat
Trt::contours_bounding()
{
    Mat mat_contours = mat_.clone();
    vector<vector<Point> > contours; //all contours of white shapes
    vector<Vec4i> hierarchy; //hierarchy of the contours
    Mat res = Mat::zeros(mat_.size(), CV_8UC3); //result image

    // find the contours of white shapes in original picture
    findContours(mat_contours, contours, hierarchy, CV_RETR_EXTERNAL,
	     CV_CHAIN_APPROX_SIMPLE);


    vector<RotatedRect> rects;
    vector<vector<Point> >::iterator it;
    int place = 0;

    for (it = contours.begin(); it < contours.end(); it++)
    {
	drawContours(res, contours, place,
		     BLUE, 0, CV_AA);

	RotatedRect rec = rect_bar(*it);

	Point2f rect_points[4];
	Point2f ref;
	rec.points(rect_points);

	if ((rect_points[1] != ref) && (rect_points[3] != ref))
	{
	    rects.push_back(rec);
	    place++;
	    for (int j = 0; j < 4; j++)
		line(res, rect_points[j], rect_points[(j+1)%4],
		     YELLOW, 1, 8);
	}
	else
	{
	    contours.erase(it);
	    it--;
	}
    }

    // set the new parameters in the object for a future use
    set_contours(contours);
    set_rects(rects);

    return res;
}


/* ------------------ */
/* ------------------ */
/* AXES_BOUNDING */
/* ------------------ */
/* ------------------ */
Mat
Trt::axes_bounding()
{
    contours_bounding();

    vector<Axe> axes;
    Mat mat_res = Mat::zeros(mat_.size(), CV_8UC3);

    for (int i = 0; i < contours_.size(); i++)
    {
	axes.push_back(rect_axe(rects_[i]));

	Point2f rect_points[4];
	rects_[i].points(rect_points);

	for (int j = 0; j < 4; j++)
	    line(mat_res, rect_points[j], rect_points[(j+1)%4],
		 YELLOW, 1, 8);

	line(mat_res, axes[i].p1_, axes[i].p2_, PINK, 1, 8, 0);
    }

    set_axes(axes);

    return mat_res;
}


/* ------------------ */
/* ------------------ */
/* FIND_FRIENDS */
/* ------------------ */
/* ------------------ */
Mat
Trt::find_friends()
{
    axes_bounding();

    // creates a black picture to only draw bars
    Mat mat_res = Mat::zeros(mat_.size(), CV_8UC3);
    // vector of several axes sorted in set as friends -> vector of barcodes
    vector<set<Axe> > friends;

    int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
    double fontScale = 0.3;
    int thickness = 1;

    for (int i = 0; i < axes_.size(); i++)
    {

	// Just to see what is tested on picture to debug
	//
	// draw inner line
	line(mat_res, axes_[i].p1_, axes_[i].p2_, PINK, 1, 8, 0);

	Point2f rect_points[4];
	rects_[i].points(rect_points);

	// draw bounding box
	for (int j = 0; j < 4; j++)
	    line(mat_res, rect_points[j], rect_points[(j+1)%4],
		 YELLOW, 1, 8);

	Point p1_1 = axes_[i].p1_;
	Point p1_2 = axes_[i].p2_;

	Point p(p1_1.x, p1_1.y);
	// draw the txt : nb of item
	putText(mat_res, key_str_axe(axes_[i]), p, fontFace, fontScale,
		WHITE, thickness, 8);

	// end of debug

	set<Axe> tmp;
	tmp.insert(axes_[i]);

	for (int j = 0; j < axes_.size(); j++)
	{
	    if (j != i)
	    {
		Point p2_1 = axes_[j].p1_;
		Point p2_2 = axes_[j].p2_;
		int dist1 = distance(p1_1, p2_1);
		int dist2 = distance(p1_2, p2_2);

		if ((abs(dist1 - dist2) <= 40) &&
		    ((dist1 <= 40) || (dist2 <= 80)))
		    tmp.insert(axes_[j]);

		// check distance diago
		// parallèle avec angle < à alpha à déterminer
		// longueurs approx mêmes à 1/6 près
	    }
	}

	if (tmp.size() > 1)
	    friends.push_back(tmp);
    }

    vector<set<Axe> >::iterator it;
    vector<set<Axe> >::iterator jt;

    // remove doublons and regroup sets
    for (jt = friends.begin(); jt != friends.end(); jt++)
    {
	it = friends.begin();
	while (it != friends.end())
	{
	    if (it != jt)
	    {
		if (is_doublon(*jt, *it))
		{
		    jt->insert(it->begin(), it->end());
		    friends.erase(it);
		}
		else
		    it++;
	    }
	    else
		it++;
	}
    }

    vector<RotatedRect> rects;

    vector<RotatedRect>::iterator it_rect;

    for (set<Axe> s : friends)
	rects.push_back(create_rotated_rect(s));

    set_friends(friends);
    set_rects(rects);

    it_rect = rects_.begin();
    it = friends_.begin();

    while (it_rect != rects_.end() && it != friends_.end())
    {
	Point2f rect_points[4];
	it_rect->points(rect_points);

	int width = distance(rect_points[1], rect_points[0]);
	int height = distance(rect_points[1], rect_points[2]);

	if (height > width)
	    swap(width, height);

	if (width * 6 < height)
	{
	    friends_.erase(it);
	    rects_.erase(it_rect);
	}
	else
	{
	    it++;
	    it_rect++;
	}
    }

    return (mat_res);
}

vector<int>
Trt::extract_deskew(RotatedRect& r, Mat& Cropped)
{
    Mat Extract, Deskew;//, Cropped;

    float angle = r.angle;
    Size r_size = r.size;

    if (r.angle < -45.)
    {
	angle += 90.0;
	swap(r_size.width, r_size.height);
    }

    Extract = getRotationMatrix2D(r.center, angle, 1.0);
    warpAffine(mat_, Deskew, Extract, mat_.size(), INTER_CUBIC);

    getRectSubPix(Deskew, r_size, r.center, Cropped);

    r_size = Cropped.size();

    if (r_size.width < r_size.height)
    {
	Point2f center(Cropped.rows / 2.0f, Cropped.cols / 2.0f);
	Mat rot_mat = getRotationMatrix2D(center, -90, 0.7);
	Mat dst;
	Size size_swap(Cropped.size().height, Cropped.size().width);
	warpAffine(Cropped, dst, rot_mat, size_swap);
	Cropped = dst;
    }

    Mat soluce;

    threshold(Cropped, soluce, 127, 255, THRESH_BINARY);
    Cropped = soluce;
    vector<int> results = barCodeTrt(soluce);

    return results;
}

Mat&
Trt::print_results(Mat& src, Mat& Cropped)
{
    find_friends();

    int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
    double fontScale = 1;
    int thickness = 2;

    for (RotatedRect r : rects_)
    {
	if (r.size.width > 1 && r.size.height > 1)
	{
	    Point2f rect_points[4];
	    r.points(rect_points);

	    Point p(rect_points[2].x,
		    rect_points[2].y +
		    ((rect_points[1].y - rect_points[2].y) / 3 * 2));

	    //vector<int> res = extract_deskew(r, Cropped);

	    //cout << "width = " << r.size.width;
	    //cout << " height = " << r.size.height << endl;


	    vector<int> res = extract_deskew(r, Cropped);
	    vector<int>::iterator it = res.begin();

	    string text = "";

	    for (int i = 0; i < res.size(); i++)
	    {
		ostringstream oss;
		oss << res[i];
		text += oss.str();
	    }

	    cout << "Decode : " << text << endl;


	    for (it = res.begin(); it != res.end(); it++)
	    {
		if (*it == -1)
		    break;
	    }

	    if (it == res.end())
	    {
		// draw bounding box
		for (int j = 0; j < 4; j++)
		    line(src, rect_points[j], rect_points[(j+1)%4],
			 GREEN, 10, 8);

		putText(src, text, p, fontFace, fontScale,
			GREEN, thickness, 8);
	    }
	    else
	    {
		for (int j = 0; j < 4; j++)
		    line(src, rect_points[j], rect_points[(j+1)%4],
			 RED, 10, 8);
	    }
	}
    }

    return src;
}


/* *********************************************************************** */
/*				UTILS METHODS				   */
/* *********************************************************************** */

/* ------------------ */
/* ------------------ */
/* PRINT_CONTOURS */
/* ------------------ */
/* ------------------ */
void
Trt::print_contours()
{
    cout << "Contours : ";
    int i = 0;
    for (auto vec : contours_)
    {
	cout << i << " : ";
	for (auto v : vec)
	    cout << v << ' ';
	i++;
	cout << endl;
    }
}



/* ------------------ */
/* ------------------ */
/* PRINT_FRIENDS */
/* ------------------ */
/* ------------------ */
void
Trt::print_friends()
{
    cout << "Friends : " << endl;
    for (int i = 0; i < friends_.size(); i++)
    {
	cout << "   Set : " << i << " [ ";

	//for (int j = 0; j < friends_[i].size(); j++)
	for (auto a : friends_[i])
	    print_axe(a);

	cout << " ] " << endl;
    }
}


/* *********************************************************************** */
/*				UTILS FUNCTIONS				   */
/* *********************************************************************** */

/* ------------------ */
/* ------------------ */
/* POINTS_AXE */
/* ------------------ */
/* ------------------ */
// 2 4 3-5 AXE
Axe
points_axe(vector<Point>& v)
{
    int max_y = 0;
    int max_x = 0;
    int min_y = numeric_limits<int>::max();
    int min_x = numeric_limits<int>::max();
    Point p0;
    Point p1;
    int mid = 0;

    for (int i = 0; i < v.size(); i++)
    {
	int x = v[i].x;
	int y = v[i].y;

	max_y = MAX_INT(y, max_y);//(y > max_y)?y:max_y;
	max_x = MAX_INT(x, max_x);//(x > max_x)?x:max_x;
	min_y = MIN_INT(y, min_y);//(y < min_y)?y:min_y;
	min_x = MIN_INT(x, min_x);//(x < min_x)?x:min_x;
    }

    int Y = max_y - min_y;
    int X = max_x - min_x;

    if (X > Y)
    {
	mid = (max_y + min_y) / 2;
	p0 = Point(min_x, mid);
	p1 = Point(max_x, mid);
    }
    else
    {
	mid = (max_x + min_x) / 2;
	p0 = Point(mid, min_y);
	p1 = Point(mid, max_y);
    }

    return (Axe(p0, p1));
}

/* ------------------ */
/* ------------------ */
/* RECT_AXE */
/* ------------------ */
/* ------------------ */
Axe
rect_axe(RotatedRect& r)
{
    Point2f r_pts[4];
    r.points(r_pts);

    int width = distance(r_pts[1], r_pts[2]);
    int height = distance(r_pts[0], r_pts[1]);

    Point p1;
    Point p2;

    if (width > height)
    {
	p1 = Point((r_pts[0].x + r_pts[1].x) / 2,
		   (r_pts[0].y + r_pts[1].y) / 2);
	p2 = Point((r_pts[2].x + r_pts[3].x) / 2,
		   (r_pts[2].y + r_pts[3].y) / 2);
    }
    else
    {
	p1 = Point((r_pts[1].x + r_pts[2].x) / 2,
		   (r_pts[1].y + r_pts[2].y) / 2);
	p2 = Point((r_pts[0].x + r_pts[3].x) / 2,
		   (r_pts[0].y + r_pts[3].y) / 2);
    }

    return (Axe(p1, p2));
}

/* ------------------ */
/* ------------------ */
/* RECT_BAR */
/* ------------------ */
/* ------------------ */
RotatedRect
rect_bar(vector<Point>& vec)
{
    RotatedRect rect = minAreaRect(vec);

    Point2f rect_points[4];
    rect.points(rect_points);

    int height = distance(rect_points[0], rect_points[1]);
    int width = distance(rect_points[1], rect_points[2]);

    if (((height*10 < width) && (width > 20)) ||
	((width*10 < height) && (height > 20)))
	return rect;

    return RotatedRect();
}



/* ------------------ */
/* ------------------ */
/* DISTANCE */
/* ------------------ */
/* ------------------ */
int
distance(Point& p1, Point& p2)
{
    int x1 = p1.x;
    int y1 = p1.y;
    int x2 = p2.x;
    int y2 = p2.y;
    int res1 = x2 - x1;
    int res2 = y2 - y1;

    return (sqrt ((res1*res1) + (res2*res2)));
}

int
distance(Point2f& p1, Point2f& p2)
{
    int x1 = p1.x;
    int y1 = p1.y;
    int x2 = p2.x;
    int y2 = p2.y;
    int res1 = x2 - x1;
    int res2 = y2 - y1;

    return (sqrt ((res1*res1) + (res2*res2)));
}


/* ------------------ */
/* ------------------ */
/* MAKE_VECTOR */
/* ------------------ */
/* ------------------ */
vector<vector<Point> >
make_vector(map<int, vector<Point> >& m)
{
    vector<vector<Point> > vec;
    map<int, vector<Point> >::iterator it;

    for (it = m.begin(); it != m.end(); ++it)
	vec.push_back(it->second);

    return vec;
}


vector<Rect>
make_boundings(map<int, vector<Point> >& m, vector<Rect>& b)
{
    vector<Rect> res;
    map<int, vector<Point> >::iterator it;

    for (it = m.begin(); it != m.end(); ++it)
	res.push_back(b[it->first]);

    return res;
}

void
print_point(Point& p, int& i)
{
    cout << "Point " << i << " (" << p.x;
    cout << ", " << p.y << ")";// << endl;
}

void
print_point(Point2f& p, int& i)
{
    cout << "Point " << i << " (" << p.x;
    cout << ", " << p.y << ")";// << endl;
}

void
print_axe(Axe& a)
{
    int x1 = a.p1_.x;
    int x2 = a.p2_.x;
    int y1 = a.p1_.y;
    int y2 = a.p2_.y;

    cout << "{ (" << x1 << ", " << y1 << ") , (";
    cout << x2 << ", " << y2 << ") } ";
}


int
parallel_axes(Axe& a1, Axe& a2)
{
    int x1 = a1.p1_.x;
    int y1 = a1.p1_.y;
    int x2 = a1.p2_.x;
    int y2 = a1.p2_.y;
    int x3 = a2.p1_.x;
    int y3 = a2.p1_.y;
    int x4 = a2.p2_.x;
    int y4 = a2.p2_.y;

    return (((x2 - x1) * (y4 - y3)) - ((y2 - y1) * (x4 - x3)));
}

bool
is_doublon(set<Axe>& s1, set<Axe>& s2)
{
    set<Axe>::iterator it;

    for (Axe a1 : s1)
    {
	for (Axe a2 : s2)
	{
	    if (a1.p1_.x == a2.p1_.x &&
		a1.p1_.y == a2.p1_.y &&
		a1.p2_.x == a2.p2_.x &&
		a1.p2_.y == a2.p2_.y)
		return true;
	}
    }

    return false;
}

string
key_str_axe(Axe& a)
{
    ostringstream oss;
    oss << (a.p1_.x + a.p1_.y + a.p2_.x + a.p2_.y);
    return oss.str();
}

RotatedRect
create_rotated_rect(set<Axe>& s)
{
    vector<Point> points;

    for (Axe a : s)
    {
	points.push_back(a.p1_);
	points.push_back(a.p2_);
    }

    RotatedRect res = minAreaRect(points);
    res.size.height += (res.size.height * 0.05);
    res.size.width += (res.size.width * 0.05);

    return (res);
}

//RotatedRect
//create_rotatedrect(vector<RotatedRect>& rects)
//{
    //vector<Point2f> _0s;
    //vector<Point2f> _1s;
    //vector<Point2f> _2s;
    //vector<Point2f> _3s;

    //for (RotatedRect r : rects)
    //{
	//Point2f rect_points[4];
	//r.points(rect_points);

	//_0s.push_back(rect_points[0]);
	//_1s.push_back(rect_points[1]);
	//_2s.push_back(rect_points[2]);
	//_3s.push_back(rect_points[3]);
    //}

    //Point2f _0 = _0s[0];
    //Point2f _1 = _1s[0];
    //Point2f _2 = _2s[0];
    //Point2f _3 = _3s[0];

    //for (Point2f p : _0s)
    //{
	//if (p.x > _0.x)
	    //_0 = p;
    //}

    //for (Point2f p : _1s)
    //{
	//if (p.x > _1.x)
	    //_1 = p;
    //}

    //for (Point2f p : _2s)
    //{
	//if (p.x > _2.x)
	    //_2 = p;
    //}

    //for (Point2f p : _3s)
    //{
	//if (p.x > _3.x)
	    //_3 = p;
    //}

    //Point2f mid((_0.x + _2.x) / 2., (_0.y + _2.y) / 2.);
    //double width = distance(_0, _1);
    //width += width * 0.05;
    //double height = distance(_1 , _2);

    //Point2f p1((_2.x + _3.x) / 2., (_2.y + _3.y) / 2.);
    //Point2f p2((_0.x + _1.x) / 2., (_0.y + _1.y) / 2.);

    //double angle = pythagore(p1, p2);

    //return (RotatedRect(mid, Size(width, height), angle));
//}

//double
//pythagore (Point2f p1, Point2f p2)
//{
    //double angle = 0;

    //if (p2.x > p1.x)
    //{
	//Point2f p3(p1.x, p2.y);
	//double hypothenuse = distance(p1, p2);
	//double adjacent = distance(p2, p3);
	//angle = -(acos(adjacent / hypothenuse));
	//angle = angle / CV_PI * 180;
	//cout << "angle = " << angle << endl;
    //}
    //else
    //{
	//Point2f p3(p2.x, p1.y);
	//double hypothenuse = distance(p1, p2);
	//double adjacent = distance(p2, p3);
	//angle = acos(adjacent / hypothenuse);
	//angle = angle / CV_PI * 180;
	//cout << "angle = " << angle << endl;
    //}

    //return angle;
//}


