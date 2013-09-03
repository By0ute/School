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
    Scalar color_contours = Scalar(255, 0, 0); //color for the contours (BLUE)
    Scalar color_bounding = Scalar(255, 255, 0); //color for the
						//bounding boxes (YELLOW)

    // find the contours of white shapes in original picture
    findContours(mat_, contours, hierarchy, CV_RETR_EXTERNAL,
	     CV_CHAIN_APPROX_SIMPLE);


    vector<RotatedRect> rects;
    vector<vector<Point> >::iterator it;
    int place = 0;

    for (it = contours.begin(); it < contours.end(); it++)
    {
	drawContours(res, contours, place,
		     color_contours, 0, CV_AA);

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
		     color_bounding, 1, 8);
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
    set_mat(res);

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
    // YELLOW
    Scalar color_bounding = Scalar(255, 255, 0);
    // PINK
    Scalar color_axe= Scalar(100, 0, 255);
    Mat mat_res = Mat::zeros(mat_.size(), CV_8UC3);

    for (int i = 0; i < contours_.size(); i++)
    {
	axes.push_back(points_axe(contours_[i]));
	//axes.push_back(rect_axe(rects_[i]));

	Point2f rect_points[4];
	rects_[i].points(rect_points);

	for (int j = 0; j < 4; j++)
	    line(mat_res, rect_points[j], rect_points[(j+1)%4],
		 color_bounding, 1, 8);

	line(mat_res, axes[i].p1_, axes[i].p2_, color_axe, 1, 8, 0);
    }

    set_axes(axes);
    set_mat(mat_res);
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

    Mat mat_res = Mat::zeros(mat_.size(), CV_8UC3);
    Scalar color_axe= Scalar(100, 0, 255);
    Scalar color_bounding = Scalar(255, 255, 0);
    Scalar color_text = Scalar(255, 255, 255);
    vector<set<Axe> > friends;
    vector<set<Axe> >::iterator it;
    bool in = false;
    int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
    double fontScale = 0.3;
    int thickness = 1;

    for (int i = 0; i < axes_.size(); i++)
    {
	//line(mat_res, axes_[i].p1_, axes_[i].p2_, color_axe, 1, 8, 0);

	Point2f rect_points[4];
	rects_[i].points(rect_points);

	for (int j = 0; j < 4; j++)
	    line(mat_res, rect_points[j], rect_points[(j+1)%4],
		 color_bounding, 1, 8);



	cout << "---------------------" << endl;
	//print_friends();
	Point p1 = axes_[i].p1_;
	Point p(p1.x, p1.y + i);
	ostringstream oss;

	oss << i;

	putText(mat_res, oss.str(), p, fontFace, fontScale,
		color_text, thickness, 8);

	set<Axe> tmp;
	//set<Axe>::iterator a_it;
	//in = false;

	//for (it = friends.begin(); it != friends.end(); it++)
	//{
	    //a_it = it->find(axes_[i]);

	    //if (a_it != it->end())
	    //{
		//cout << "Oui on a trouvé un ancien" << endl;
		//tmp = *it;
		//in = true;
		//break;
	    //}
	    //else
		tmp.insert(axes_[i]);
		//}

	for (int j = 0; j < axes_.size(); j++)
	{
	    if (j != i)
	    {
		Point p2 = axes_[j].p1_;
		int dist = distance(p1, p2);

		cout << " [ ";
		print_point(p1, i);
		cout << ", ";
		print_point(p2, j);
		cout << " ] = " << dist;


		if (dist <= 50)
		{
		    tmp.insert(axes_[j]);
		    //cout << "(" << i << ", " << j << ") " << endl;
		    cout << " : j'insère" << endl;
		}
		else
		    cout << endl;
	    }
	}

	//if (!in && (tmp.size() > 1))
	//friends.push_back(tmp);

	//set_friends(friends);
	//cout << "---------------------" << endl;

	if (tmp.size() > 1)
	{
	    set<Axe>::iterator sit;
	    bool insert = false;

	    for (set<Axe> s : friends)
	    {
		if (insert)
		    break;

		//for (inc = 0; inc < tmp.size(); inc++)
		for (Axe a : tmp)
		{
		    sit = s.find(a);

		    if (sit != s.end())
		    {
			cout << endl << "j'ai trouvé un copain" << endl;
			print_axe(a);
			insert = true;
			s.insert(tmp.begin(), tmp.end());
			break;
		    }
		}

	    }

	    if (!insert)
		friends.push_back(tmp);
	}

    }

    cout << "Size : " << friends.size() << endl;

    set_friends(friends);

    //print_friends();

    return (mat_res);
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
points_axe(vector<Point> v)
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
rect_axe(RotatedRect r)
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
rect_bar(vector<Point> vec)
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
distance(Point p1, Point p2)
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
make_vector(map<int, vector<Point> > m)
{
    vector<vector<Point> > vec;
    map<int, vector<Point> >::iterator it;

    for (it = m.begin(); it != m.end(); ++it)
	vec.push_back(it->second);

    return vec;
}


vector<Rect>
make_boundings(map<int, vector<Point> > m, vector<Rect> b)
{
    vector<Rect> res;
    map<int, vector<Point> >::iterator it;

    for (it = m.begin(); it != m.end(); ++it)
	res.push_back(b[it->first]);

    return res;
}

void
print_point(Point p, int i)
{
    cout << "Point " << i << " (" << p.x;
    cout << ", " << p.y << ")";// << endl;
}

void
print_axe(Axe a)
{
    int x1 = a.p1_.x;
    int x2 = a.p2_.x;
    int y1 = a.p1_.y;
    int y2 = a.p2_.y;

    cout << "{ (" << x1 << ", " << y1 << ") , (";
    cout << x2 << ", " << y2 << ") } ";
}


int
parallel_axes(Axe a1, Axe a2)
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
