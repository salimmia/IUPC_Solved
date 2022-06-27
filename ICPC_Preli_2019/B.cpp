#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using    namespace __gnu_pbds;

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
int const mx = 1e5 + 5;

// typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

/// multiset hisebe use korte///
typedef tree<pair<ll, int>, null_type, less<pair<ll, ll>>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

int n, W, m, k, q;
int parent[mx];
ordered_set os[mx];

int Find(int u)
{
    return parent[u] = (u == parent[u]) ? u : Find(parent[u]);
}

void solve()
{
    scanf("%d%d", &n, &q);
    int cnt = 0;

    for (int i = 0; i <= n; i++) {
        os[i].clear();
        parent[i] = i;
    }

    for (int i = 0; i < q; i++) {
        int type;

        scanf("%d", &type);

        if (type == 0) {
            int u, v;
            scanf("%d%d", &u, &v);

            int paru = Find(u);
            int parv = Find(v);

            if (paru != parv) {
                if (os[paru].size() < os[parv].size()) {
                    swap(paru, parv);
                }
                parent[parv] = paru;

                for (auto x : os[parv]) {
                    os[paru].insert(x);
                }
                os[parv].clear();
            }
        }
        else if (type == 1) {
            int u, T;
            scanf("%d%d", &u, &T);

            os[Find(u)].insert({T, ++cnt});
        }
        else {
            int u, l, r;
            scanf("%d%d%d", &u, &l, &r);

            ll ans = (os[Find(u)].order_of_key({r , cnt + 2})) - (os[Find(u)].order_of_key({l , -1}));

            printf("%lld\n", ans);
        }
    }

    return;
}

int main()
{
    int t = 1, cs = 1;

    scanf("%d", &t);

    FOR(i, 1, t) {
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
