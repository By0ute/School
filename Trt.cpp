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
    : mat_ (),
    contours_ (),
    axes_ (),
    friends_ (),
    rects_ ()
{
}

Trt::Trt(Mat m)
    : mat_ (m.clone()),
    contours_ (),
    axes_ (),
    friends_ (),
    rects_ ()
{
}

Trt::Trt(Mat m, vector<vector <Point> > c,
	 vector<Axe> a,
	 vector<set<Axe> > f,
	 vector<RotatedRect> r)
    : mat_ (m.clone()),
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
// a polygon simplification is done on those contours
// then boundings boxes are calculated for simplified contours
// a first selection is used to only selectionate bounding boxes with
//    parameters between 2 and 5 (that corresponds to a bar of a code bar :
//    2 for a really thin and 5 for a twisted rectangle one)
Mat
Trt::contours_bounding()
{
    vector<vector<Point> > contours; //all contours of white shapes
    vector<Vec4i> hierarchy; //hierarchy of the contours
    Mat res = Mat::zeros(mat_.size(), CV_8UC3); //result image

    // find the contours of white shapes in original picture
    findContours(mat_, contours, hierarchy, CV_RETR_EXTERNAL,
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
    //print_contours();
    //set_mat(res);

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
	//axes.push_back(points_axe(contours_[i]));
	axes.push_back(rect_axe(rects_[i]));

	Point2f rect_points[4];
	rects_[i].points(rect_points);

	for (int j = 0; j < 4; j++)
	    line(mat_res, rect_points[j], rect_points[(j+1)%4],
		 YELLOW, 1, 8);

	line(mat_res, axes[i].p1_, axes[i].p2_, PINK, 1, 8, 0);
    }

    set_axes(axes);
    //set_mat(mat_res);
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

		if ((abs(dist1 - dist2) <= 20) &&
		    ((dist1 <= 50) || (dist2 <= 50)))
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

    //for (it_rect = rects_.begin(), it = friends_.begin();
    //it_rect != rects_.end(), it != friends_.end();
    //it_rect++, it++)
    //while ()
    //{
    //	
    //}



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

	if (height < width)
	    swap(width, height);

	if ((width * 6 < height))// ||
	    //(width * 2 > height))
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

    //cout << "Size : " << friends_.size() << endl;
    //cout << "Size rects " << rects_.size() << endl;


    //for (RotatedRect r : rects_)
    //{
	//Point2f rect_points[4];
	//r.points(rect_points);

	//// draw bounding box
	//for (int j = 0; j < 4; j++)
	    //line(mat_res, rect_points[j], rect_points[(j+1)%4],
		 //GREEN, 1, 8);
    //}



    //
    //
    //for (set<Axe> s : friends)
    //cout << "-> " << s.size() << endl;


    //print_friends();

    return (mat_res);
}

Mat
Trt::extract_deskew(RotatedRect& r)
{
    Mat Extract, Deskew, Cropped;

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

    return Cropped;
}



//// TEMPORARY



Mat
Trt::extract_deskew2(Mat& in)
{
    if (rects_.size() > 0)
    {
	RotatedRect r = rects_[0];

	Mat Extract, Deskew, Cropped;

	float angle = r.angle;
	Size r_size = r.size;

	if (r.angle < -45.)
	{
	    angle += 90.0;
	    swap(r_size.width, r_size.height);
	}

	Extract = getRotationMatrix2D(r.center, angle, 1.0);
	warpAffine(in, Deskew, Extract, in.size(), INTER_CUBIC);

	getRectSubPix(Deskew, r_size, r.center, Cropped);

	//Cropped = subtreatment(Cropped, r);

	return Cropped;
    }

    return in;
}

Mat
Trt::subtreatment(Mat& cropped, RotatedRect& box)
{
    Mat lol = cropped.clone();
    vector<Vec4i> lines;
    Size size = cropped.size();

    HoughLinesP(cropped, lines, 1, CV_PI / 180, size.width / 2.f, 20);
    Mat disp_lines(size, CV_8UC1, BLACK);

    double angle = 0;

    unsigned nb_lines = lines.size();

    for (int i = 0; i < nb_lines; i++)
    {
	line(disp_lines, Point(lines[i][0], lines[i][1]),
	     Point(lines[i][2], lines[i][3]), BLUE);

	angle += atan2((double)lines[i][3] - lines[i][1],
		       (double)lines[i][2] - lines[i][0]);
    }

    angle /= nb_lines;

    // redo the rotation
    //RotatedRect box = minAreaRect(cropped);
    Mat rot_mat = getRotationMatrix2D(box.center, angle, 1);

    Mat rotated;
    warpAffine(cropped, rotated, rot_mat, cropped.size(), INTER_CUBIC);

    Size box_size = box.size;

    if (box.angle < -45.)
	swap(box_size.width, box_size.height);

    Mat res;

    getRectSubPix(rotated, box_size, box.center, res);


    cout << "angle = " << angle * 180 / CV_PI << endl;

    return res;
}


// TEMPORARY




Mat&
Trt::print_results(Mat& src)
{
    find_friends();

    int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
    double fontScale = 3;
    int thickness = 5;

    for (RotatedRect r : rects_)
    {
	Point2f rect_points[4];
	r.points(rect_points);

	Point p(rect_points[2].x,
		rect_points[2].y +
		((rect_points[1].y - rect_points[2].y) / 3 * 2));

	// draw bounding box
	//if (decode(r))
	//{
	//for (int j = 0; j < 4; j++)
	//line(src, rect_points[j], rect_points[(j+1)%4],
	//GREEN, 10, 8);
	//}
	//else
	//{
	    for (int j = 0; j < 4; j++)
		line(src, rect_points[j], rect_points[(j+1)%4],
		     RED, 10, 8);


	    putText(src, "FAUX CODE", p, fontFace, fontScale,
		    RED, thickness, 8);
	    //}

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

    //vector<Vec4i> lines;
    //
    //HoughLinesP(res, lines, 1, CV_PI / 180, 100, res.size.width / 2.f, 20);

    return (res);
}



