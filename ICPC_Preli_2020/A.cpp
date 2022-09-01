#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

typedef long double Tf;
const double inf = 1e100;
const double eps = 1e-9;
const double PI = acos((double) - 1.0);

int sign(double x) { return (x > eps) - (x < -eps); }
struct PT {
    double x, y;
    void read () { scanf("%lf%lf", &x, &y); }
    void write () { printf("%lf %lf\n", x, y); }
    PT() { x = 0, y = 0; }
    PT(double x, double y) : x(x), y(y) {}
    PT(const PT &p) : x(p.x), y(p.y)    {}
    PT operator + (const PT &a) const { return PT(x + a.x, y + a.y); }
    PT operator-(const PT &a) const { return PT(x - a.x, y - a.y); }
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
    double arg() { double x = atan2(y, x); return x; } /// if (sign(x) < 0) x += 2 * PI;
    PT truncate(double r) { // returns a vector with norm r and having same direction
        double k = norm();
        if (!sign(k)) return *this;
        r /= k;
        return PT(x * r, y * r);
    }
    friend istream &operator >> (istream &is, PT &p) { return is >> p.x >> p.y; }
    friend ostream &operator << (ostream &os, const PT &p) { return os << p.x << " " << p.y; }
};
inline double dot(PT a, PT b) { return a.x * b.x + a.y * b.y; }
inline double dist2(PT a, PT b) { return dot(a - b, a - b); }
inline double dist(PT a, PT b) { return sqrt(dot(a - b, a - b)); }
inline double cross(PT a, PT b) { return a.x * b.y - a.y * b.x; }
inline double cross2(PT a, PT b, PT c) { return cross(b - a, c - a); }
inline int orientation(PT a, PT b, PT c) { return sign(cross(b - a, c - a)); }
PT perp(PT a) { return PT(-a.y, a.x); }
PT rotateccw90(PT a) { return PT(-a.y, a.x); }
PT rotatecw90(PT a) { return PT(a.y, -a.x); }
PT rotateccw(PT a, double t) { return PT(a.x * cos(t) - a.y * sin(t), a.x * sin(t) + a.y * cos(t)); }
PT rotatecw(PT a, double t) { return PT(a.x * cos(t) + a.y * sin(t), -a.x * sin(t) + a.y * cos(t)); }

double area(vector<PT> &p) {
    double ans = 0; int n = p.size();
    for (int i = 0; i < n; i++) ans += cross(p[i], p[i == n - 1 ? 0 : i + 1]);
    return fabs(ans);
}

vector<PT> convex_hull(vector<PT> p) {
    if (p.size() <= 1) return p;
    vector<PT> v = p;
    sort(v.begin(), v.end());
    vector<PT> up, dn;
    for (auto& p : v) {
        while (up.size() > 1 && orientation(up[up.size() - 2], up.back(), p) >= 0) {
            up.pop_back();
        }
        while (dn.size() > 1 && orientation(dn[dn.size() - 2], dn.back(), p) <= 0) {
            dn.pop_back();
        }
        up.push_back(p);
        dn.push_back(p);
    }
    v = dn;
    if (v.size() > 1) v.pop_back();
    reverse(up.begin(), up.end());
    up.pop_back();
    for (auto& p : up) {
        v.push_back(p);
    }
    if (v.size() == 2 && v[0] == v[1]) v.pop_back();
    return v;
}

// -1 if strictly inside, 0 if on the polygon, 1 if strictly outside
// it must be strictly convex, otherwise make it strictly convex first
int is_point_in_convex(vector<PT> &p, const PT& x) { // O(log n)
    int n = p.size();
    if (n <= 2) return 1;
    int a = orientation(p[0], p[1], x), b = orientation(p[0], p[n - 1], x);
    if (a < 0 || b > 0) return 1;
    int l = 1, r = n - 1;
    while (l + 1 < r) {
        int mid = l + r >> 1;
        if (orientation(p[0], p[mid], x) >= 0) l = mid;
        else r = mid;
    }
    int k = orientation(p[l], p[r], x);
    if (k <= 0) return -k;
    if (l == 1 && a == 0) return 0;
    if (r == n - 1 && b == 0) return 0;
    return -1;
}

typedef long long ll;

ll add(ll a, ll b, ll md)
{
    a += b;
    if (a >= md)a -= md;
    return a;
}

ll mul(ll a, ll b, ll md)
{
    ll re = a;
    re *= b;
    if (re >= md)re %= md;
    return re;
}

long long seed1, seed2;
int get_random() {
    seed1 = (add(mul(seed1, 1103515243, 2012345671), 12345, 2012345671));
    seed2 = (add(mul(seed2, 1092104927, 2094828103), 54321, 2094828103));
    int r = mul(seed1, seed2, 100000);
    return r;
}


void solve()
{
    int n;

    vector<PT>v;

    long long ans = 0;

    set<pair<ll, ll>>st;

    scanf("%d %lld %lld", &n, &seed1, &seed2);

    long long last = 0;
    int i;

    for (i = 1; i <= n; i++) {
        int x = get_random();
        int y = get_random();

        if (is_point_in_convex(v, PT(x, y)) > 0) {
            v.push_back(PT(x, y));
            v = convex_hull(v);
            last = area(v);
        }
        ans += last;
    }

    printf("%lld\n", ans);
}

int main() {
    int t, cs, i;
    scanf("%d", &t);

    for (int i = 1; i <= t; i++) {
        printf("Case %d: ", i);
        solve();
    }

    return 0;
}
