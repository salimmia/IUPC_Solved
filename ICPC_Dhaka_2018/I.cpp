#include<bits/stdc++.h>
using namespace std;

const double inf = 1e100;
const double eps = 1e-9;
const double PI = acos((double) - 1.0);
int sign(double x) { return (x > eps) - (x < -eps); }

struct PT {
    double x, y;
    PT() { x = 0, y = 0; }
    PT(double x, double y) : x(x), y(y) {}
    PT(const PT &p) : x(p.x), y(p.y)    {}
    void scan() { cin >> x >> y; }
    PT operator + (const PT &a) const { return PT(x + a.x, y + a.y); }
    PT operator - (const PT &a) const { return PT(x - a.x, y - a.y); }
    PT operator * (const double a) const { return PT(x * a, y * a); }
    friend PT operator * (const double &a, const PT &b) { return PT(a * b.x, a * b.y); }
    PT operator / (const double a) const { return PT(x / a, y / a); }
    bool operator == (PT a) const { return sign(a.x - x) == 0 && sign(a.y - y) == 0; }
    bool operator != (PT a) const { return !(*this == a); }
    bool operator < (PT a) const { return sign(a.x - x) == 0 ? y < a.y : x < a.x; }
    bool operator > (PT a) const { return sign(a.x - x) == 0 ? y > a.y : x > a.x; }
    double norm() { return sqrt(x * x + y * y); }
    double norm2() { return x * x + y * y; }
    PT perp() { return PT(-y, x); }
    double arg() { return atan2(y, x); }
    PT truncate(double r) { // returns a vector with norm r and having same direction
        double k = norm();
        if (!sign(k)) return *this;
        r /= k;
        return PT(x * r, y * r);
    }
};
inline double dot(PT a, PT b) { return a.x * b.x + a.y * b.y; }
inline double dist2(PT a, PT b) { return dot(a - b, a - b); }
inline double dist(PT a, PT b) { return sqrt(dot(a - b, a - b)); }
inline double cross(PT a, PT b) { return a.x * b.y - a.y * b.x; }
inline int orientation(PT a, PT b, PT c) { return sign(cross(b - a, c - a)); }
PT perp(PT a) { return PT(-a.y, a.x); }
PT rotateccw90(PT a) { return PT(-a.y, a.x); }
PT rotatecw90(PT a) { return PT(a.y, -a.x); }
PT rotateccw(PT a, double t) { return PT(a.x * cos(t) - a.y * sin(t), a.x * sin(t) + a.y * cos(t)); }
PT rotatecw(PT a, double t) { return PT(a.x * cos(t) + a.y * sin(t), -a.x * sin(t) + a.y * cos(t)); }
double SQ(double x) { return x * x; }
double rad_to_deg(double r) { return (r * 180.0 / PI); }
double deg_to_rad(double d) { return (d * PI / 180.0); }
double get_angle(PT a, PT b) {
    double costheta = dot(a, b) / a.norm() / b.norm();
    return acos(max((double) - 1.0, min((double)1.0, costheta)));
}
struct p3 {
    double x, y, z;
    p3() { x = 0, y = 0; z = 0; }
    p3(double x, double y, double z) : x(x), y(y), z(z) {}
    p3(const p3 &p) : x(p.x), y(p.y), z(p.z)    {}
    void scan() { cin >> x >> y >> z; }
    p3 operator + (const p3 &a) const { return p3(x + a.x, y + a.y, z + a.z); }
    p3 operator - (const p3 &a) const { return p3(x - a.x, y - a.y, z - a.z); }
    p3 operator * (const double a) const { return p3(x * a, y * a, z * a); }
    friend p3 operator * (const double &a, const p3 &b) { return p3(a * b.x, a * b.y, a * b.z); }
    p3 operator / (const double a) const { return p3(x / a, y / a, z / a); }
    bool operator == (p3 a) const { return sign(a.x - x) == 0 && sign(a.y - y) == 0 && sign(a.z - z) == 0; }
    bool operator != (p3 a) const { return !(*this == a); }
    double abs() { return sqrt(x * x + y * y + z * z); }
    double sq() { return x * x + y * y + z * z; }
    p3 unit() { return *this / abs(); }
} zero(0, 0, 0);
double operator | (p3 v, p3 w) { //dot product
    return v.x * w.x + v.y * w.y + v.z * w.z;
}
p3 operator * (p3 v, p3 w) { //cross product
    return {v.y * w.z - v.z * w.y, v.z * w.x - v.x * w.z, v.x * w.y - v.y * w.x};
}
double sq(p3 v) { return v | v; }
double abs(p3 v) { return sqrt(sq(v)); }
p3 unit(p3 v) { return v / abs(v); }
inline double dot(p3 a, p3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
inline double dist2(p3 a, p3 b) { return dot(a - b, a - b); }
inline double dist(p3 a, p3 b) { return sqrt(dot(a - b, a - b)); }
inline p3 cross(p3 a, p3 b) { return p3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }
double orient(p3 p, p3 q, p3 r, p3 s) { return (q - p) * (r - p) | (s - p); }
double orient_by_normal(p3 p, p3 q, p3 r, p3 n) { return (q - p) * (r - p) | n; }
double get_angle(p3 a, p3 b) {
    double costheta = dot(a, b) / a.abs() / b.abs();
    return acos(max((double) - 1.0, min((double)1.0, costheta)));
}
double small_angle(p3 v, p3 w) {
    return acos(min(fabs(v | w) / abs(v) / abs(w), (double)1.0));
}

struct plane {
    p3 n; double d; // (n | p) = d
    // From normal n and offset d
    plane(p3 n, double d) : n(n), d(d) {}
    // From normal n and point P
    plane(p3 n, p3 p) : n(n), d(n | p) {}
    // From three non-collinear points P,Q,R
    plane(p3 p, p3 q, p3 r) : plane((q - p) * (r - p), p) {}
    double side(p3 p) { return (n | p) - d; }
    double dist(p3 p) { return fabs(side(p)) / abs(n); }
    plane translate(p3 t) { return {n, d + (n | t)}; }
    plane shiftUp(double dist) { return {n, d + dist * abs(n)}; }
    p3 proj(p3 p) { return p - n * side(p) / sq(n); }
    p3 refl(p3 p) { return p - n * 2 * side(p) / sq(n); }
};

struct coords {
    p3 o, dx, dy, dz;
    // From three points P, Q, R on the plane:
    // build an orthonormal 3D basis
    coords(p3 p, p3 q, p3 r) : o(p) {
        dx = unit(q - p);
        dz = unit(dx * (r - p));
        dy = dz * dx;
    }
    // From four points P,Q,R,S: take directions PQ, PR, PS as is
    // it allows us to keep using integer coordinates but has some pitfalls.
    coords(p3 p, p3 q, p3 r, p3 s) :
        o(p), dx(q - p), dy(r - p), dz(s - p) {}
    PT pos2d(p3 p) {
        return {(p - o) | dx, (p - o) | dy};
    }
    p3 pos3d(p3 p) {
        return {(p - o) | dx, (p - o) | dy, (p - o) | dz};
    }
    p3 pos3d(PT p) { //original position vector
        return o + dx * p.x + dy * p.y;
    }
};

struct line3d {
    p3 d, o; // p = o + k * d
    // From two points P, Q
    line3d(p3 p, p3 q) : d(q - p), o(p) {}
    // From two planes p1, p2 (requires T = double, planes are not parallel)
    line3d(plane p1, plane p2) {
        d = p1.n * p2.n;
        o = (p2.n * p1.d - p1.n * p2.d) * d / sq(d);
    }
    double dist2(p3 p) { return sq(d * (p - o)) / sq(d); }
    double dist(p3 p) { return sqrt(dist2(p)); }
    bool cmp_proj(p3 p, p3 q) { return (d | p) < (d | q); }
    p3 proj(p3 p) { return o + d * (d | (p - o)) / sq(d); }
    p3 refl(p3 p) { return proj(p) * 2 - p; }
    p3 inter(plane p) { return o - d * p.side(o) / (d | p.n); } // assuming plane and line are not parallel
};

double dist(line3d l1, line3d l2) {
    p3 n = l1.d * l2.d;
    if (n == zero) return l1.dist(l2.o);// parallel
    return fabs((l2.o - l1.o) | n) / abs(n);
}
p3 closest_on_l1(line3d l1, line3d l2) {
    p3 n2 = l2.d * (l1.d * l2.d);
    return l1.o + l1.d * ((l2.o - l1.o) | n2) / (l1.d | n2);
}
double get_angle(line3d l1, line3d l2) {
    return small_angle(l1.d, l2.d);
}
bool is_parallel(line3d l1, line3d l2) {
    return l1.d * l2.d == zero;
}
bool is_perpendicular(line3d l1, line3d l2) {
    return sign((l1.d | l2.d)) == 0;
}
double get_angle(plane p1, plane p2) {
    return small_angle(p1.n, p2.n);
}
bool is_parallel(plane p1, plane p2) {
    return p1.n * p2.n == zero;
}
bool is_perpendicular(plane p1, plane p2) {
    return sign((p1.n | p2.n)) == 0;
}
double get_angle(plane p, line3d l) {
    return PI / 2 - small_angle(p.n, l.d);
}
bool is_parallel(plane p, line3d l) {
    return sign((p.n | l.d)) == 0;
}
bool is_perpendicular(plane p, line3d l) {
    return p.n * l.d == zero;
}

// returns two points on intesection line of two planes formed by points
// a1, b1, c1 and a2, b2, c2 respectively
pair<p3, p3> plane_plane_intersection(p3 a1, p3 b1, p3 c1, p3 a2, p3 b2, p3 c2) {
    p3 n1 = (b1 - a1) * (c1 - a1);
    p3 n2 = (b2 - a2) * (c2 - a2);
    double d1 = n1 | a1, d2 = n2 | a2;
    p3 d = n1 * n2;
    if (d == zero) return make_pair(zero, zero);
    p3 o = (n2 * d1 - n1 * d2) * d / (d | d);
    return make_pair(o, o + d);
}
// returns center of circle passing through three
// non-colinear and co-planer points a, b and c
p3 circle_center(p3 a, p3 b, p3 c) {
    p3 v1 = b - a, v2 = c - a;
    double v1v1 = v1 | v1, v2v2 = v2 | v2, v1v2 = v1 | v2;
    double base = 0.5 / (v1v1 * v2v2 - v1v2 * v1v2);
    double k1 = base * v2v2 * (v1v1 - v1v2);
    double k2 = base * v1v1 * (v2v2 - v1v2);
    return a + v1 * k1 + v2 * k2;
}
// segment ab to point c
double distance_from_segment_to_point(p3 a, p3 b, p3 c) {
    if (sign(dot(b - a, c - a)) < 0) return dist(a, c);
    if (sign(dot(a - b, c - b)) < 0) return dist(b, c);
    return fabs(cross((b - a).unit(), c - a).abs());
}
double distance_from_triangle_to_point(p3 a, p3 b, p3 c, p3 d) {
    plane P(a, b, c);
    p3 proj = P.proj(d);
    double dis = min(distance_from_segment_to_point(a, b, d), min(distance_from_segment_to_point(b, c, d), distance_from_segment_to_point(c, a, d)));
    int o = sign(orient_by_normal(a, b, proj, P.n));
    int inside = o == sign(orient_by_normal(b, c, proj, P.n));
    inside &= o == sign(orient_by_normal(c, a, proj, P.n));
    if (inside) return (d - proj).abs();
    return dis;
}
double distance_from_triangle_to_segment(p3 a, p3 b, p3 c, p3 d, p3 e) {
    double l = 0.0, r = 1.0;
    int cnt = 100;
    double ret = 1e12; //beware!
    while (cnt--) {
        double mid1 = l + (r - l) / 3.0, mid2 = r - (r - l) / 3.0;
        double x = distance_from_triangle_to_point(a, b, c, d + (e - d) * mid1);
        double y = distance_from_triangle_to_point(a, b, c, d + (e - d) * mid2);
        if (x < y) {
            r = mid2;
            ret = x;
        }
        else {
            ret = y;
            l = mid1;
        }
    }
    return ret;
}
double distance_from_triangle_to_triangle(p3 a, p3 b, p3 c, p3 d, p3 e, p3 f) {
    double ret = 1e12; // beware!
    ret = min(ret, distance_from_triangle_to_segment(a, b, c, d, e));
    ret = min(ret, distance_from_triangle_to_segment(a, b, c, e, f));
    ret = min(ret, distance_from_triangle_to_segment(a, b, c, f, d));
    ret = min(ret, distance_from_triangle_to_segment(d, e, f, a, b));
    ret = min(ret, distance_from_triangle_to_segment(d, e, f, b, c));
    ret = min(ret, distance_from_triangle_to_segment(d, e, f, c, a));
    return ret;
}

void solve()
{
    p3 a, b, c, aa, bb, cc;

    a.scan();
    b.scan();
    c.scan();
    aa.scan();
    bb.scan();
    cc.scan();

    long double ans = distance_from_triangle_to_triangle(a, b, c, aa, bb, cc);

    cout << fixed << setprecision(9) << ans << endl;

    return;
}

int main()
{
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        // printf("Case %d: ", i);
        solve();
    }
    return 0;
}
