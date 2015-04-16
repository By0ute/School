#include "Axe.hh"

Axe::Axe()
    : p1_ (),
    p2_ ()
{
}


Axe::Axe(Point pt1, Point pt2)
    : p1_ (pt1),
    p2_ (pt2)
{
}

Axe::Axe(int x1, int y1, int x2, int y2)
    : p1_ (Point(x1, y1)),
    p2_ (Point(x2, y2))
{
}

Axe::~Axe()
{
}
