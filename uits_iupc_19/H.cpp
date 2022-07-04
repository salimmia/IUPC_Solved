#include<bits/stdc++.h>
using namespace std;
#define mx 1000005
#define ll long long
#define md 1000000007

typedef long double T;
typedef double Tf;
typedef Tf Ti;
const T PI = acos(-1), EPS = 1e-9;
int dcmp(T x) { return abs(x) < EPS ? 0 : (x < 0 ? -1 : 1);}

struct Point {
    T x, y;
    Point(T x = 0, T y = 0) : x(x), y(y) {}

    void read () { scanf("%lf%lf", &x, &y); }
    void write () { printf("%lf %lf\n", x, y); }

    Point operator + (const Point& u) const { return Point(x + u.x, y + u.y); }
    Point operator - (const Point& u) const { return Point(x - u.x, y - u.y); }
    Point operator * (const long long u) const { return Point(x * u, y * u); }
    Point operator*(T d) {return {x * d, y * d};}
    Point operator/(T d) {return {x / d, y / d};} // only for floatingpoint

    bool operator == (const Point& u) const { return dcmp(x - u.x) == 0 && dcmp(y - u.y) == 0; }
    bool operator != (const Point& u) const { return !(*this == u); }
    bool operator < (const Point& u) const { return dcmp(x - u.x) < 0 || (dcmp(x - u.x) == 0 && dcmp(y - u.y) < 0); }

    friend ostream& operator<<(ostream& os, Point p) {
        return os << "(" << p.x << "," << p.y << ")"; /// Some example usage: Point a{3, 4}, b{2, -1};
    }
    friend istream &operator >> (istream &is, Point &p) { return is >> p.x >> p.y; }
};
/// It returns -1 for negative numbers, 0 for zero, and 1 for positive numbers.
template <typename T> int sgn(T x) {
    return (T(0) < x) - (x < T(0));
}

T radian(T a) {return a * PI / 180.0;}
T degree(T a) {return a * 180.0 / PI;}

T sq(Point p) {return p.x * p.x + p.y * p.y;}
double abs(Point p) {return sqrt(sq(p));} /// length

/*To translate an object by a vector #»v , we simply need to add #»v to every point in the object of vector p*/
Point translate(Point v, Point p) {return p + v;}

/*To scale an object by a certain ratio α around a center c, we need to shorten
or lengthen the vector from c to every point by a factor α, while conserving
the direction.*/
Point scale(Point c, double factor, Point p) {
    return c + (p - c) * factor;
}

/*Rotation   In particular, we will often use the (counter-clockwise) rotation centered
on the origin. where theta = a*/
Point rot(Point p, double a) {
    return {p.x * cos(a) - p.y * sin(a), p.x * sin(a) + p.y * cos(a)};
}

/* 90 Degree rotation */
Point perp(Point p) {return { -p.y, p.x};}

T dot(Point v, Point w) {return v.x * w.x + v.y * w.y;}
T cross(Point v, Point w) {return v.x * w.y - v.y * w.x;}

/*f(r) = f(p) + ((r − p) ∗ f(q) − f(p) / (q − p))*/
Point linearTransfo(Point p, Point q, Point r, Point fp, Point fq) {
    Point pq = q - p, num{cross(pq, fq - fp), dot(pq, fq - fp)};
    Point fr;
    return fr = fp + Point{cross(r - p, num), dot(r - p, num)} / sq(pq);
}

/// return true if two vectors v and w are perpendicular
bool isPerp(Point v, Point w) {return dot(v, w) == 0;}

/// angle between vector v and vector w
double angle(Point v, Point w) {
    double cosTheta = dot(v, w) / abs(v) / abs(w);
    return acos(max(-1.0, min(1.0, cosTheta)));
}
double angle(Point v, Point w, bool bk) {
    return atan2(cross(v, w), dot(v, w));
}

/// return 1 if c is left of ab, 0 if on ab && -1 if right of ab
int orient(Point a, Point b, Point c) {return dcmp(cross(b - a, c - a));} /// OK

/// return 1 if point p is in angle CAB
bool inAngle(Point a, Point b, Point c, Point p) {
    assert(orient(a, b, c) != 0);
    if (orient(a, b, c) < 0) swap(b, c);
    return orient(a, b, p) >= 0 && orient(a, c, p) <= 0;
}

/// angle between Orient AB and point C
double orientedAngle(Point a, Point b, Point c) {
    if (orient(a, b, c) >= 0)
        return angle(b - a, c - a);
    else
        return 2 * M_PI - angle(b - a, c - a);
}

/// return 1 if given point is convex polygon
bool isConvex(vector<Point> p) {
    bool hasPos = false, hasNeg = false;
    for (int i = 0, n = p.size(); i < n; i++) {
        int o = orient(p[i], p[(i + 1) % n], p[(i + 2) % n]);
        if (o > 0) hasPos = true;
        if (o < 0) hasNeg = true;
    }
    return !(hasPos && hasNeg);
}

/// return 1 if point p
// bool inDisk(Point a, Point b, Point p) {
//     return dcmp(dot(a - p, b - p)) <= 0;
// }

// bool onSegment(Point a, Point b, Point p) {
//     return dcmp(orient(a, b, p)) == 0 && inDisk(a, b, p);
// }

// /// return 1 if two lines are intersected;
// bool LineLineIntersection(Point a, Point b, Point c, Point d) /// OK /*https://cses.fi/problemset/task/2190*/
// {
//     return (orient(a, b, c) != orient(a, b, d) && orient(c, d, a) != orient(c, d, b)) ||
//            onSegment(a, b, c) || onSegment(a, b, d) ||
//            onSegment(c, d, a) || onSegment(c, d, b);
// }

struct line {
    Point v; T c;
// From direction vector v and offset c
    line(Point v, T c) : v(v), c(c) {}
// From equation ax+by=c
    line(T a, T b, T c) : v( {b, -a}), c(c) {}
// From points P and Q
    line(Point p, Point q) : v(q - p), c(cross(v, p)) {}
// Will be defined later:
// - these work with T = int

    /// return 1 for p is ccw side, 0 for p is in line, -1 for p is in cw
    T side(Point p) {return cross(v, p) - c;}

    /// distance from point p to line l
    T dist(Point p) {return abs(side(p)) / abs(v);}

    /// squared distance from point p to lone l
    T sqDist(Point p) {return side(p) * side(p) / (double)sq(v);}

    /// To find a line perpendicular to line l and which goes through a certain point P
    line perPointhrough(Point p) {return {p, p + perp(v)};}

    /*given points on a line l, to sort them in the order they appear on the line,
    following the direction of #»v .*/

    /*In fact, this comparator is more powerful than we need: it is not limited to
    points on l and can compare two points by their orthogonal projection3 on l.*/
    bool cmpProj(Point p, Point q) {
        return dot(v, p) < dot(v, q);
    }

    /*If we want to translate a line l by vector #»t , the direction vector #»v remains
    the same but we have to adaPoint c.*/
    line translate(Point t) {return {v, c + cross(v, t)};}

    /*A closely related task is shifting line l to the left by a certain distance δ
    (or to the right by −δ).*/
    line shiftLeft(double dist) {return {v, c + dist * abs(v)};}

    /*The orthogonal projection of a point P on a line l is the point on l that is
    closest to P. The reflection of point P by line l is the point on the other side
    of l that is at the same distance and has the same orthogonal projection*/
    Point proj(Point p) {return p - perp(v) * side(p) / sq(v);}

    /*To find the reflection, we need to move P in the same direction but twice
    the distance:*/
    Point refl(Point p) {return p - perp(v) * 2 * side(p) / sq(v);}
};

// lines are represented as a ray from a point: (point, vector)
// returns false if two lines (p, v) && (q, w) are parallel or collinear
// true otherwise, intersection point is stored at o via reference
bool lineLineIntersection(Point p, Point v, Point q, Point w, Point& o) {
    static_assert(is_same<Tf, Ti>::value);
    if (dcmp(cross(v, w)) == 0) return false;
    Point u = p - q;
    o = p + v * (cross(w, u) / cross(v, w));
    return true;
}
// returns false if two lines p && q are parallel or collinear
// true otherwise, intersection point is stored at o via reference
// bool lineLineIntersection(line p, line q, Point& o) {
//  return lineLineIntersection(p.a, p.b - p.a, q.a, q.b - q.a, o);
// }

/// distance between two parallal line l1, l2
T Dist(line l2, line l1) {return (l2.c - l1.c) / abs(l1.v);}

/// There is a unique intersection point between two lines l1 and l2 if and only if # »vl1 != »vl2
bool inter(line l1, line l2, Point &out) {
    T d = cross(l1.v, l2.v);
    if (d == 0) return false;
    out = (l2.v * l1.c - l1.v * l2.c) / d; // requires floating-point coordinates
    return true;
}

/*An important property of bisectors is that their points are at equal distances from the original lines l1 and l2. In fact, if we give a sign to the
    distance depending on which side of the line we are on, we can say that
    lint(l1, l2) is the line whose points are at opposite distances from l1 and l2
    while lext(l1, l2) is the line whose points are at equal distances from l1 and
    l2.*/
/// angle bisector line, if iteratior is 1 then return internal line otherwise external line...
line bisector(line l1, line l2, bool interior) {
    assert(cross(l1.v, l2.v) != 0); // l1 and l2 cannot be parallel!
    double sign = interior ? 1 : -1;
    return {l2.v / abs(l2.v) + l1.v / abs(l1.v) * sign,
            l2.c / abs(l2.v) + l1.c / abs(l1.v) * sign};
}

/*For this we will first define a useful subroutine inDisk() that checks if
a point P lies on the disk of diameter [AB]. */
bool inDisk(Point a, Point b, Point p) {
    return dot(a - p, b - p) <= 0;
}

/// return true if point p is on segment AB
bool onSegment(Point a, Point b, Point p) {
    return orient(a, b, p) == 0 && inDisk(a, b, p);
}

/// segment segment intersection
bool properInter(Point a, Point b, Point c, Point d, Point &out) {
    double oa = orient(c, d, a),
           ob = orient(c, d, b),
           oc = orient(a, b, c),
           od = orient(a, b, d);
    // Proper intersection exists iff opposite signs
    if (oa * ob < 0 && oc * od < 0) {
        out = (a * ob - b * oa) / (ob - oa);
        return true;
    }
    return false;
}

// To create sets of points we need a comparison function
struct cmpX {
    bool operator()(Point a, Point b) const {
        return make_pair(a.x, a.y) < make_pair(b.x, b.y);
    }
};

/// return all segment segment intersection point
set<Point, cmpX> inters(Point a, Point b, Point c, Point d) {
    Point out;
    if (properInter(a, b, c, d, out)) return {out};
    set<Point, cmpX> s;
    if (onSegment(c, d, a)) s.insert(a);
    if (onSegment(c, d, b)) s.insert(b);
    if (onSegment(a, b, c)) s.insert(c);
    if (onSegment(a, b, d)) s.insert(d);
    return s;
}

/// segment Point Distance from point p to segment AB
double segPoint(Point a, Point b, Point p) {
    if (a != b) {
        line l(a, b);
        if (l.cmpProj(a, p) && l.cmpProj(p, b)) // if closest to projection
            return l.dist(p); // output distance to line
    }
    return min(abs(p - a), abs(p - b)); // otherwise distance to A or B
}

/// Distance between to segment
double segSeg(Point a, Point b, Point c, Point d) {
    Point dummy;
    if (properInter(a, b, c, d, dummy))
        return 0;
    return min({segPoint(a, b, c), segPoint(a, b, d),
                segPoint(c, d, a), segPoint(c, d, b)
               });
}

/// area of a triangle
T areaTriangle(Point a, Point b, Point c) {
    return abs(cross(b - a, c - a)) / 2.0;
}

bool half(Point p) { // true if in blue half
    if (p.x != 0 || p.y != 0) return true; // the argument of (0,0) is undefined
    return p.y > 0 || (p.y == 0 && p.x < 0);
}
void polarSort(vector<pair<Point, int>> &v) {
    sort(v.begin(), v.end(), [](pair<Point, int> v, pair<Point, int> w) {
        return make_tuple(half(v.first), 0) <
               make_tuple(half(w.first), cross(v.first, w.first));
    });
}

/* It
is good practice to always put your polygons in counter-clockwise order,
by reversing the array of vertices if necessary, because some algorithms on
polygons use this property.
picks theorem Area = (I + (B / 2) - 1);
*/
/// area of polygon... input is taken by vector
T areaPolygon(vector<Point> p) {
    T area = 0.0;
    for (int i = 0, n = p.size(); i < n; i++) {
        area += cross(p[i], p[(i + 1) % n]); // wrap back to 0 if i == n-1
    }
    return abs(area) / 2.0;
}

// true if P at least as high as Ray A (blue part)
bool above(Point a, Point p) {
    return p.y >= a.y;
}

// check if [PQ] crosses ray from A
bool crossesRay(Point a, Point p, Point q) {
    return (above(a, q) - above(a, p)) * orient(a, p, q) > 0;
}

// if strict, returns false when A is on the boundary
/// strict means Consider him inside if he is on the boundary of the polygon.
bool inPolygon(vector<Point> p, Point a, bool strict = true) {
    int numCrossings = 0;
    for (int i = 0, n = p.size(); i < n; i++) {
        if (onSegment(p[i], p[(i + 1) % n], a))
            return !strict;
        numCrossings += crossesRay(a, p[i], p[(i + 1) % n]);
    }
    return numCrossings & 1; // inside if odd number of crossings
}

struct Circle {
    Point o;
    T r;
    Circle(Point o = Point(0, 0), T r = 0) : o(o), r(r) {}

    // returns true if point p is in || on the circle
    bool contains(Point p) {
        return dcmp(sq(p - o) - r * r) <= 0;
    }

    // returns a point on the circle rad radians away from +X CCW
    Point point(Tf rad) {
        static_assert(is_same<Tf, Ti>::value);
        return Point(o.x + cos(rad) * r, o.y + sin(rad) * r);
    }

    // area of a circular sector with central angle rad
    T area(T rad = PI + PI) { return rad * r * r / 2; }

    /// area of the circular sector cut by a chord with central angle alpha
    /// https://math.libretexts.org/Bookshelves/Precalculus/Book%3A_Elementary_Trigonometry_(Corral)/04%3A_Radian_Measure/4.03%3A_Area_of_a_Sector
    T sector(T alpha) { return r * r * 0.5 * (alpha - sin(alpha)); }
};

/// given 3 points and return the center of of the new CircumCircle
Point circumCenter(Point a, Point b, Point c) { /// OK
    b = b - a, c = c - a; // consider coordinates relative to A
    assert(cross(b, c) != 0); // no circumcircle if A,B,C aligned
    return a + perp(b * sq(c) - c * sq(b)) / cross(b, c) / 2;
}

/// return the intersection point of circle and a line
int circleLine(Circle C, line l, pair<Point, Point> &out) {
    double h2 = C.r * C.r - l.sqDist(C.o);
    if (h2 >= 0) { // the line touches the circle
        Point p = l.proj(C.o); // point P
        Point h = l.v * sqrt(h2) / abs(l.v); // vector parallel to l, of length h
        out = {p - h, p + h};
    }
    return 1 + sgn(h2);
}

/*two circles (O1, r1) and (O2, r2) can have
either 0, 1, 2 or an infinity of intersection points (in case the circles are
identical).*/
int circleCircle(Point o1, double r1, Point o2, double r2, pair<Point, Point> &out) {
    Point d = o2 - o1; double d2 = sq(d);
    if (d2 == 0) { return 0;} // concentric circles
    double pd = (d2 + r1 * r1 - r2 * r2) / 2; // = |O_1P| * d
    double h2 = r1 * r1 - pd * pd / d2; // = hˆ2
    if (h2 >= 0) {
        Point p = o1 + d * pd / d2, h = perp(d) * sqrt(h2 / d2);
        out = {p - h, p + h};
    }
    return 1 + sgn(h2);
}
/// return circle circle intersection points
int circleCircle(Circle C1, Circle C2, pair<Point, Point> &out) {
    Point o1 = C1.o, o2 = C2.o;
    T r1 = C1.r, r2 = C2.r;

    return circleCircle(o1, r1, o2, r2, out);
}

typedef vector<Point> Polygon;
int convexHull(Polygon p, Polygon & ch) { /// OK
    sort(p.begin(), p.end());
    int n = p.size();
    ch.resize(n + n);
    int m = 0;    // preparing lower hull
    for (int i = 0; i < n; i++) {
        while (m > 1 && dcmp(cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 1])) < 0) m--; /// sometime <
        ch[m++] = p[i];
    }
    int k = m;    // preparing upper hull
    for (int i = n - 2; i >= 0; i--) {
        while (m > k && dcmp(cross(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2])) < 0) m--; /// sometime <
        ch[m++] = p[i];
    }
    if (n > 1) m--;
    ch.resize(m);
    return m;
}
Polygon p[105], cv[105];

void solve()
{
    int n;

    T d;

    cin >> n;

    int m[n + 5];

    for (int i = 0; i < n; i++) {
        int xx;
        cin >> xx;
        for (int j = 0; j < xx; j++) {
            Point x;
            cin >> x;

            p[i].push_back(x);
        }
        m[i] = convexHull(p[i], cv[i]);
    }
    T ans = 0.0;
    for (int ii = 0; ii < n; ii++) {
        T now = 10000000000.0;
        for (int i = 0; i < m[ii]; i++) {
            Point fr = cv[ii][i], se = cv[ii][(i + 1) % m[ii]];
            line l = line(fr, se);
            T now1 = 0.0;
            for (int j = 0; j < m[ii]; j++) {
                Point pt = cv[ii][j];

                now1 = max(now1, l.dist(pt));
            }
            now = min(now, now1);
        }
        ans = max(ans, now);
    }

    cout << fixed << setprecision(2) << ans << endl;

    for (int i = 0; i < n; i++) p[i].clear(), cv[i].clear();
}

int main()
{
    int t = 1, cs = 1;

    cin >> t;

    for (int i = 1; i <= t; i++) {
        cout << "Case " << i << ": ";
        solve();
    }
}
