#include<bits/stdc++.h>

using namespace std;

#define MOD 1000000007
#define INF 1e18
#define nl "\n"
#define PI 3.141592653589793238462

typedef long long int ll;
typedef unsigned long long ull;
typedef long double lld;
#define ff first
#define ss second
#define FOR(i, a, b) for(int i = a; i <= b; i++)
#define ROF(i, a, b) for(int i = a; i >= b; i--)
#define all(x) (x).begin(), (x).end()
#define rep(i, begin, end) for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))

#define mt make_tuple
#define eb emplace_back
#define pb push_back

#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x <<": "; _print(x); cerr << endl;
#else
#define debug(x)
#endif

void _print(ll t) {cerr << t;}
void _print(int t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(lld t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(ull t) {cerr << t;}

auto sum() { return 0; }

template<typename T, typename... Args>
auto sum(T a, Args... args) { return a + sum(args...); }

#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cerr << *it << " = " << a << endl;
    err(++it, args...);
}

void read () { }
template <typename T, typename... Args>
void read (T& t, Args&... args) {
    cin >> t;
    read(args...);
}

template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T, class V> void _print(map <T, V> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(pair <T, V> p) {cerr << "{"; _print(p.ff); cerr << ","; _print(p.ss); cerr << "}";}
template <class T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(set <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(multiset <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
int const N = 1e6 + 5;

int n, W, m, k, prefix[N], need[N], a[N];

void solve()
{
    scanf("%d%d", &n, &m);

    // vector<int>a(n + 2);
    a[0] = 0;
    a[n + 1] = m;

    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    sort(a, a +  n + 1);
    // reverse(a.begin(), a.end());

    for (int i = 0; i <= m; i++) need[i] = 0;

    for (int i = 1; i <= n + 1; i++) {
        int diff = a[i] - a[i - 1];

        for (int j = 1; j < diff; j++) {
            need[j] += (diff + j - 1) / j - 1;
        }
    }

    // for (int i = 1; i <= m; i++) cout << need[i] << " ";
    // cout << endl;

    int q;

    scanf("%d", &q);

    while (q--) {
        int s;
        scanf("%d", &s);
        int lo = 1, hi = m;

        while (lo < hi) {
            int mid = (lo + hi) >> 1;

            if (need[mid] <= s) hi = mid;
            else lo = mid + 1;
        }
        printf("%d\n", lo);
    }

    return;
}

int main()
{
    int t = 1, cs = 1;

    cin >> t;

    for (int i = 1; i <= t; i++) {
        printf("Case %d:\n", i);
        solve();
    }
}
/*
0. Enough array size? Enough array size? Enough array size? Integer overflow?

1. Think TWICE, Code ONCE!
Are there any counterexamples to your algo?

2. Be careful about the BOUNDARIES!
N=1? P=1? Something about 0?

3. Do not make STUPID MISTAKES!
Time complexity? Memory usage? Precision error?
*/
