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
    boundings_ ()
{
}

Trt::Trt(Mat m)
    : mat_ (m.clone()),
    contours_ (),
    axes_ (),
    friends_ (),
    boundings_ ()
{
}

Trt::Trt(Mat m, vector<vector <Point> > c,
	 vector<vector<Point> > a,
	 vector<vector<vector<Point> > > f,
	 vector<Rect> b)
    : mat_ (m.clone()),
    contours_ (c),
    axes_ (a),
    friends_ (f),
    boundings_ (b)
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
Trt::set_axes(vector<vector<Point> > a)
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
Trt::set_boundings(vector<Rect> b)
{
    boundings_ = b;
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


    vector<vector<Point> > contours_poly(contours.size()); //contours for
							   //bounding boxes
    vector<vector<Point> > contours_selected; //contours from contours_poly
					    //reduced with ones
					    // with 2 to 5 points (Bar Shape)


    // approximates contours so that looks like more polygonial
    // and draws them
    for (int i = 0; i < contours.size(); i++)
    {
	approxPolyDP(Mat(contours[i]), contours_poly[i], 10, true);
	drawContours(res, contours, i, color_contours, 0, CV_AA, hierarchy);
    }

    // reduction from contours_poly to only the shapes that have 2-5 points
    // (Bar Shape)
    contours_selected = contours_bar(contours_poly);

    vector<Rect> boundRect(contours_selected.size());// list of bounding boxes

    // finds bounding boxes for those shapes
    // draws them with rectangles
    for (int i = 0; i < contours_selected.size(); i++)
    {
	boundRect[i] = boundingRect(Mat(contours_selected[i]));
	rectangle(res, boundRect[i].tl(), boundRect[i].br(), color_bounding,
		  1, 8, 0);
    }

    // set the new parameters in the object for a future use
    set_contours(contours_selected);
    set_boundings(boundRect);
    //print_contours();
    set_mat(res);

    return res;
}

/* ------------------ */
/* ------------------ */
/* COUNTOURS_BAR */
/* ------------------ */
/* ------------------ */
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


/* ------------------ */
/* ------------------ */
/* AXES_BOUNDING */
/* ------------------ */
/* ------------------ */
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
	axes.push_back(points_axe(contours_[i]));

	//rectangle(mat_res, boundings_[i].tl(), boundings_[i].br(),
	//color_bounding, 1, 8, 0);
	line(mat_res, axes[i][0], axes[i][1], color_axe, 1, 8, 0);
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
    Scalar color_bounding = Scalar(100, 100, 0);

    vector<vector<vector<Point> > > friends;
    vector<Rect> new_boundings;
    //vector<vector<Point> > heap;
    map<int, vector<Point> > heap;
    //bool conti_nue = false;
    //int new_i = -1;
    //int max_dist = 0;

    ////cout << "Size = " << contours_.size() << endl;

    ////for (int i = 0; i < 44; ++i)
    ////{
	////rectangle(mat_res, boundings_[i].tl(), boundings_[i].br(),
		  ////color_bounding, 1, 8, 0);
	////cout << i << endl;
    ////}

    ////cout << "LOUL" << endl;

    //for (int i = 0; i < boundings_.size(); ++i)
    //{
	//rectangle(mat_res, boundings_[i].tl(), boundings_[i].br(),
		  //color, 1, 8, 0);
	////cout << i << endl;
    //}

    //for(int i = 0; i < axes_.size(); ++i)
    //{
	//int dist = distance(axes_[6][0], axes_[i][0]);
	//cout << "Distance(6," << i << ") = " << dist << endl;
    //}

    //int dist = distance(axes_[6][0], axes_[34][0]);
    //cout << "Distance(6,34) = " << dist << endl;

    //rectangle(mat_res, boundings_[6].tl(), boundings_[6].br(),
	      //color_bounding, 1, 8, 0);
    //rectangle(mat_res, boundings_[34].tl(), boundings_[34].br(),
	      //color_bounding, 1, 8, 0);
    ////rectangle(mat_res, boundings_[39].tl(), boundings_[39].br(),
    ////color_bounding, 1, 8, 0);
    ////rectangle(mat_res, boundings_[6].tl(), boundings_[6].br(),
	      ////color_bounding, 1, 8, 0);

    ////print_point(axes_[6][0], 6);
    ////print_point(axes_[34][0], 34);



    ////////
    // ****************
    // /////

    //heap[6] = axes_[6];

    //for (int i = 0; i < axes_.size(); ++i)
    //{
	//int dist = distance(axes_[33][0], axes_[i][0]);
	//cout << "Distance(6," << i << ") = " << dist << endl;

	//if (dist <= 15)
	    //heap[i] = axes_[i];
    //}

    //vector<Rect> bbound = make_boundings(heap, boundings_);

    //set_boundings(bbound);


    //for (int i = 0; i < boundings_.size(); i++)
    //{
	////axes.push_back(points_axe(contours_[i]));

	//rectangle(mat_res, boundings_[i].tl(), boundings_[i].br(),
		  //color_bounding, 1, 8, 0);
	////line(mat_res, axes[i][0], axes[i][1], color_axe, 1, 8, 0);
    //}




    //int inc = axes_.size();
    //int i = 0;
    //while (inc != 0)
    for (int i = 0; i < axes_.size(); ++i)
    {
	//cout << "-- debut en i = " << i << endl;
	//if (!conti_nue)
	//{
	//cout << "****** NEW HASH ******" << endl;
	//cout << i << endl;
	    heap.clear();
	    heap[i] = axes_[i];
	    //}

	    //new_i = -1;
	    //max_dist = 0;
	    //int moment1 = second_area_moment(boundings_[i]);

	int size = heap.size();
	int l1 = distance(axes_[i][0], axes_[i][1]);
	//cout << "Size before = " << heap.size() << endl;

	for (int j = i+1; j < axes_.size(); ++j)
	{
	    //if (j != i)
	    //{
		int dist = distance(axes_[i][0], axes_[j][0]);
		int l2 = distance(axes_[j][0], axes_[j][1]);
		int para = parallel_axes(axes_[i], axes_[j]);

		if (dist <= 15)
		{
		    cout << "--------------------------" << endl;
		    cout << "longueur i:" << i << " = " << l1 << endl;
		    cout << "longueur j:" << j << " = " << l2 << endl;
		    cout << "diff longueurs = " << (l1 - l2) << endl;
		    cout << "coeff parallel = " << para << endl;
		    cout << "--------------------------" << endl;

		    //if ((res_mom >= 0.9) && (res_mom <= 1.1))
		    if ((para == 0) &&
			((abs(l1 - l2)) <= (MIN_INT(l1, l2) / 6)))
		    {
			//cout << j << endl;
			heap[j] = axes_[j];
		    }

		    //if (dist > max_dist)
		    //{
		    //max_dist = dist;
		    //new_i = j;
		    //}
		}
		//}
	}

	//cout << "Size after = " << heap.size() << endl;
	//cout << "Fini de trouver" << endl;

	//if (heap.size() > size)
	//{
	//conti_nue = true;
	//i = new_i;
	//cout << "On continue" << endl;
	//}
	//else
	if ((heap.size() > 1))// && (heap.size() == size))
	{
	    vector<Rect> bbound = make_boundings(heap, boundings_);
	    new_boundings.insert(new_boundings.end(),
				 bbound.begin(), bbound.end());
	    vector<vector<Point> > vec = make_vector(heap);
	    friends.push_back(vec);
	    //conti_nue = false;
	    //cout << "On crée un nouveau vector" << endl;
	    //i++;
	    //}
	    //else
	    //i++;

	    //inc--;
	}

    }

    cout << "Size Friends = " << friends.size() << endl;










    //for (int i = 0; i < axes_.size(); ++i)
    //{
	//p = i;
	//if (!conti_nue)
	//{
	    //heap.clear();
	    ////heap.insert(pair<p, axes_[i]>);
	    //heap[i] = axes_[i];
	//}

	//int size = heap.size();

	//cout << "Size of heap = " << size << endl;

	//Point p1 = axes_[i][0];

	//for (int j = i+1; j < axes_.size(); ++j)
	//{
	    //int dist = distance(p1, axes_[j][0]);
	    ////int dist = distance(axes_[6][0], axes_[j][0]);

	    ////cout << "Distance(" << i << ", " << j << ") = " << dist << endl;

	    //if (dist <= 15)
	    //{
		////heap.insert(pair<j, axes_[j]);
		//heap[j] = axes_[j];
		////new_boundings.push_back(boundings_[j]);
	    //}

	    //if (new_i == -1)
	    //{
		//new_i = j;
		////new_boundings.push_back(boundings_[i]);
	    //}
	//}

	//if ((heap.size() == size) && (size > 1))
	//{
	    //vector<Rect> bbound = make_boundings(heap, boundings_);
	    //new_boundings.insert(new_boundings.end(),
				 //bbound.begin(), bbound.end());
	    //vector<vector<Point> > vec = make_vector(heap);

	    //cout << "Vector = " << vec.size() << endl;

	    //friends.push_back(vec);
	    //conti_nue = false;
	    //new_i = -1;
	//}
	//else if ((heap.size() > size) && (new_i > 0))
	//{
	    //conti_nue = true;
	    //i = new_i;
	//}
    //}

    //cvFont f;
    //initFont(&f, CV_FONT_HERSHEY_SIMPLEX, 1.0, 1.0, 0, 8, 8);

    int loul = 20;
    for (int i = 0; i < boundings_.size(); i++)
    {
	//axes.push_back(points_axe(contours_[i]));

	Scalar color = Scalar(0, 0, loul);
	Scalar color2 = Scalar(0, loul, 0);
	rectangle(mat_res, boundings_[i].tl(), boundings_[i].br(),
		  color, 1, 8, 0);


	ostringstream oss;
	oss << i;
	Point pt(axes_[i][0].x, axes_[i][0].y + i*2);
	putText(mat_res, oss.str(), pt, FONT_HERSHEY_SCRIPT_SIMPLEX, 0.3, color2);
	loul += 10;
	//line(mat_res, axes[i][0], axes[i][1], color_axe, 1, 8, 0);
    }

    set_boundings(new_boundings);


    for (int i = 0; i < boundings_.size(); i++)
{
    //axes.push_back(points_axe(contours_[i]));

    rectangle(mat_res, boundings_[i].tl(), boundings_[i].br(),
	      color_bounding, 1, 8, 0);
    //line(mat_res, axes[i][0], axes[i][1], color_axe, 1, 8, 0);
}



    //cout << "Size friends_ = " << friends.size() << endl;
    set_friends(friends);
    set_mat(mat_res);

    return mat_res;
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

	max_y = MAX_INT(y, max_y);//(y > max_y)?y:max_y;
	max_x = MAX_INT(x, max_x);//(x > max_x)?x:max_x;
	min_y = MIN_INT(y, min_y);//(y < min_y)?y:min_y;
	min_x = MIN_INT(x, min_x);//(x < min_x)?x:min_x;
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



/* ------------------ */
/* ------------------ */
/* POINTS_BAR */
/* ------------------ */
/* ------------------ */
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

	max_y = MAX_INT(y, max_y);
	max_x = MAX_INT(x, max_x);//(x > max_x)?x:max_x;
	min_y = MIN_INT(y, min_y);//(y < min_y)?y:min_y;
	min_x = MIN_INT(x, min_x);//(x < min_x)?x:min_x;
    }

    int Y = max_y - min_y;
    int X = max_x - min_x;

    if ((X*8 < Y) || (Y*8 < X))
	return true;

    return false;
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
