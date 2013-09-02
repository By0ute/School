#include "Box.hh"

Box::Box()
    : p1_ (),
    p2_ (),
    p3_ (),
    p4_ ()
{
}


Box::Box(Point pt1, Point pt2, Point pt3, Point pt4)
    : p1_ (pt1),
    p2_ (pt2),
    p3_ (pt3),
    p4_ (pt4)
{
}

Box::Box(int x1, int y1, int x2, int y2,
	 int x3, int y3, int x4, int y4)
    : p1_ (Point(x1, y1)),
    p2_ (Point(x2, y2)),
    p3_ (Point(x3, y3)),
    p4_ (Point(x4, y4))
{
}

Box::~Box()
{
}
