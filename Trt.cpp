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
	 vector<vector<vector<Point> > > f,
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
Trt::set_friends(vector<vector<vector<Point> > > f)
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

	//rectangle(mat_res, boundings_[i].tl(), boundings_[i].br(),
		  //color_bounding, 1, 8, 0);
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
//Mat
//Trt::find_friends()
//{
    //axes_bounding();

    //Mat mat_res = Mat::zeros(mat_.size(), CV_8UC3);
    //Scalar color_bounding = Scalar(100, 100, 0);

    //vector<vector<vector<Point> > > friends;
    //vector<Rect> new_boundings;
    ////vector<vector<Point> > heap;
    //map<int, vector<Point> > heap;
    ////bool conti_nue = false;
    ////int new_i = -1;
    ////int max_dist = 0;

    //////cout << "Size = " << contours_.size() << endl;

    //////for (int i = 0; i < 44; ++i)
    //////{
	//////rectangle(mat_res, boundings_[i].tl(), boundings_[i].br(),
		  //////color_bounding, 1, 8, 0);
	//////cout << i << endl;
    //////}

    //////cout << "LOUL" << endl;

    ////for (int i = 0; i < boundings_.size(); ++i)
    ////{
	////rectangle(mat_res, boundings_[i].tl(), boundings_[i].br(),
		  ////color, 1, 8, 0);
	//////cout << i << endl;
    ////}

    ////for(int i = 0; i < axes_.size(); ++i)
    ////{
	////int dist = distance(axes_[6][0], axes_[i][0]);
	////cout << "Distance(6," << i << ") = " << dist << endl;
    ////}

    ////int dist = distance(axes_[6][0], axes_[34][0]);
    ////cout << "Distance(6,34) = " << dist << endl;

    ////rectangle(mat_res, boundings_[6].tl(), boundings_[6].br(),
	      ////color_bounding, 1, 8, 0);
    ////rectangle(mat_res, boundings_[34].tl(), boundings_[34].br(),
	      ////color_bounding, 1, 8, 0);
    //////rectangle(mat_res, boundings_[39].tl(), boundings_[39].br(),
    //////color_bounding, 1, 8, 0);
    //////rectangle(mat_res, boundings_[6].tl(), boundings_[6].br(),
	      //////color_bounding, 1, 8, 0);

    //////print_point(axes_[6][0], 6);
    //////print_point(axes_[34][0], 34);



    //////////
    //// ****************
    //// /////

    ////heap[6] = axes_[6];

    ////for (int i = 0; i < axes_.size(); ++i)
    ////{
	////int dist = distance(axes_[33][0], axes_[i][0]);
	////cout << "Distance(6," << i << ") = " << dist << endl;

	////if (dist <= 15)
	    ////heap[i] = axes_[i];
    ////}

    ////vector<Rect> bbound = make_boundings(heap, boundings_);

    ////set_boundings(bbound);


    ////for (int i = 0; i < boundings_.size(); i++)
    ////{
	//////axes.push_back(points_axe(contours_[i]));

	////rectangle(mat_res, boundings_[i].tl(), boundings_[i].br(),
		  ////color_bounding, 1, 8, 0);
	//////line(mat_res, axes[i][0], axes[i][1], color_axe, 1, 8, 0);
    ////}




    ////int inc = axes_.size();
    ////int i = 0;
    ////while (inc != 0)
    //for (int i = 0; i < axes_.size(); ++i)
    //{
	////cout << "-- debut en i = " << i << endl;
	////if (!conti_nue)
	////{
	////cout << "****** NEW HASH ******" << endl;
	////cout << i << endl;
	    //heap.clear();
	    //heap[i] = axes_[i];
	    ////}

	    ////new_i = -1;
	    ////max_dist = 0;
	    ////int moment1 = second_area_moment(boundings_[i]);

	//int size = heap.size();
	//int l1 = distance(axes_[i][0], axes_[i][1]);
	////cout << "Size before = " << heap.size() << endl;

	//for (int j = i+1; j < axes_.size(); ++j)
	//{
	    ////if (j != i)
	    ////{
		//int dist = distance(axes_[i][0], axes_[j][0]);
		//int l2 = distance(axes_[j][0], axes_[j][1]);
		//int para = parallel_axes(axes_[i], axes_[j]);

		//if (dist <= 15)
		//{
		    //cout << "--------------------------" << endl;
		    //cout << "longueur i:" << i << " = " << l1 << endl;
		    //cout << "longueur j:" << j << " = " << l2 << endl;
		    //cout << "diff longueurs = " << (l1 - l2) << endl;
		    //cout << "coeff parallel = " << para << endl;
		    //cout << "--------------------------" << endl;

		    ////if ((res_mom >= 0.9) && (res_mom <= 1.1))
		    //if ((para == 0) &&
			//((abs(l1 - l2)) <= (MIN_INT(l1, l2) / 6)))
		    //{
			////cout << j << endl;
			//heap[j] = axes_[j];
		    //}

		    ////if (dist > max_dist)
		    ////{
		    ////max_dist = dist;
		    ////new_i = j;
		    ////}
		//}
		////}
	//}

	////cout << "Size after = " << heap.size() << endl;
	////cout << "Fini de trouver" << endl;

	////if (heap.size() > size)
	////{
	////conti_nue = true;
	////i = new_i;
	////cout << "On continue" << endl;
	////}
	////else
	//if ((heap.size() > 1))// && (heap.size() == size))
	//{
	    //vector<Rect> bbound = make_boundings(heap, boundings_);
	    //new_boundings.insert(new_boundings.end(),
				 //bbound.begin(), bbound.end());
	    //vector<vector<Point> > vec = make_vector(heap);
	    //friends.push_back(vec);
	    ////conti_nue = false;
	    ////cout << "On crée un nouveau vector" << endl;
	    ////i++;
	    ////}
	    ////else
	    ////i++;

	    ////inc--;
	//}

    //}

    //cout << "Size Friends = " << friends.size() << endl;










    ////for (int i = 0; i < axes_.size(); ++i)
    ////{
	////p = i;
	////if (!conti_nue)
	////{
	    ////heap.clear();
	    //////heap.insert(pair<p, axes_[i]>);
	    ////heap[i] = axes_[i];
	////}

	////int size = heap.size();

	////cout << "Size of heap = " << size << endl;

	////Point p1 = axes_[i][0];

	////for (int j = i+1; j < axes_.size(); ++j)
	////{
	    ////int dist = distance(p1, axes_[j][0]);
	    //////int dist = distance(axes_[6][0], axes_[j][0]);

	    //////cout << "Distance(" << i << ", " << j << ") = " << dist << endl;

	    ////if (dist <= 15)
	    ////{
		//////heap.insert(pair<j, axes_[j]);
		////heap[j] = axes_[j];
		//////new_boundings.push_back(boundings_[j]);
	    ////}

	    ////if (new_i == -1)
	    ////{
		////new_i = j;
		//////new_boundings.push_back(boundings_[i]);
	    ////}
	////}

	////if ((heap.size() == size) && (size > 1))
	////{
	    ////vector<Rect> bbound = make_boundings(heap, boundings_);
	    ////new_boundings.insert(new_boundings.end(),
				 ////bbound.begin(), bbound.end());
	    ////vector<vector<Point> > vec = make_vector(heap);

	    ////cout << "Vector = " << vec.size() << endl;

	    ////friends.push_back(vec);
	    ////conti_nue = false;
	    ////new_i = -1;
	////}
	////else if ((heap.size() > size) && (new_i > 0))
	////{
	    ////conti_nue = true;
	    ////i = new_i;
	////}
    ////}

    ////cvFont f;
    ////initFont(&f, CV_FONT_HERSHEY_SIMPLEX, 1.0, 1.0, 0, 8, 8);

    //int loul = 20;
    //for (int i = 0; i < boundings_.size(); i++)
    //{
	////axes.push_back(points_axe(contours_[i]));

	//Scalar color = Scalar(0, 0, loul);
	//Scalar color2 = Scalar(0, loul, 0);
	//rectangle(mat_res, boundings_[i].tl(), boundings_[i].br(),
		  //color, 1, 8, 0);


	//ostringstream oss;
	//oss << i;
	//Point pt(axes_[i][0].x, axes_[i][0].y + i*2);
	//putText(mat_res, oss.str(), pt, FONT_HERSHEY_SCRIPT_SIMPLEX, 0.3, color2);
	//loul += 10;
	////line(mat_res, axes[i][0], axes[i][1], color_axe, 1, 8, 0);
    //}

    //set_boundings(new_boundings);


    //for (int i = 0; i < boundings_.size(); i++)
//{
    ////axes.push_back(points_axe(contours_[i]));

    //rectangle(mat_res, boundings_[i].tl(), boundings_[i].br(),
	      //color_bounding, 1, 8, 0);
    ////line(mat_res, axes[i][0], axes[i][1], color_axe, 1, 8, 0);
//}



    ////cout << "Size friends_ = " << friends.size() << endl;
    //set_friends(friends);
    //set_mat(mat_res);

    //return mat_res;
//}


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
    cout << "Point " << i << " (" << p.x << ", " << p.y << ")" << endl;
}

//int
//second_area_moment(Rect r1)
//{
    //int height = r1.height;
    //int width = r1.width;
    //int h = height*height*height;

    //return ((width*h) / 12);
//}


int
parallel_axes(vector<Point> a1, vector<Point> a2)
{
    int x1 = a1[0].x;
    int y1 = a1[0].y;
    int x2 = a1[1].x;
    int y2 = a1[1].y;
    int x3 = a2[0].x;
    int y3 = a2[0].y;
    int x4 = a2[1].x;
    int y4 = a2[1].y;

    return (((x2 - x1) * (y4 - y3)) - ((y2 - y1) * (x4 - x3)));
}
