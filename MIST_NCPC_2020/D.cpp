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
int const N = 2e5 + 5;

int n, tt, W, m, k, prefix[N], st[2 * N], en[2 * N], is_fill[N], enn[N];

vector<int> g[N];
set<int> stt;

void dfs(int u, int p)
{
    st[u] = tt++;

    for (auto v : g[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
    stt.insert(tt);
    enn[u] = tt;
    en[tt++] = u;
}

void solve()
{
    scanf("%d", &n);

    tt = 1;
    for (int i = 1; i < n; i++) {
        int x, y;

        scanf("%d%d", &x, &y);

        g[x].push_back(y);
        g[y].push_back(x);
    }

    for (int i = 1; i <= n; i++) sort(g[i].begin(), g[i].end());

    dfs(1, -1);

    int q;

    scanf("%d", &q);

    int cnt = 0;

    while (q--) {
        int type, u, x;

        scanf("%d%d", &type, &u);

        if (type == 1) {
            scanf("%d", &x);

            while (cnt < n && x--) {
                auto it = stt.lower_bound(st[u]);

                if (*it > enn[u]) break;

                // cout << *it << endl;

                is_fill[en[*it]] = 1;

                stt.erase(it);
                cnt++;
            }
        }
        else {
            printf("%d\n", is_fill[u]);
        }
    }

    stt.clear();

    for (int i = 0; i <= n; i++) {
        g[i].clear();
        is_fill[i] = 0;
    }

    for (int i = 1; i <= 2 * n; i++) {
        st[i] = en[i] = 0;
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

/*///Created by Salim_JnU

#include<bits/stdc++.h>
using namespace std;

#define mx 200005
#define ll long long
#define mod 1000000007 //998244353

int a[mx];
char ch[mx];
int n, m, tt, k;
vector<int>g[mx];
int st[mx], en[mx], timer;
set<pair<int, int>>s;
bool done[mx];

void dfs(int u, int p)
{
	st[u] = ++timer;

	for (auto v : g[u]) {
		if (v != p) dfs(v, u);
	}
	en[u] = ++timer;

	s.insert({en[u], u});
}

void solve()
{
	scanf("%d", &n);

	for (int i = 1; i < n; i++) {
		int u, v;

		scanf("%d%d", &u, &v);

		g[u].push_back(v);
		g[v].push_back(u);
	}

	for (int i = 1; i <= n; i++) sort(g[i].begin(), g[i].end());

	dfs(1, -1);

	int q;

	scanf("%d", &q);

	while (q--) {
		int type;

		scanf("%d", &type);

		if (type == 1) {
			int u, water;

			scanf("%d%d", &u, &water);

			if (done[u] || water == 0) continue;

			auto it = s.lower_bound({st[u], -1});

			while (water > 0) {
				if (it->first == st[u]) break;

				done[it->second] = 1;

				it = s.erase(it);

				water--;
			}
		}
		else {
			int u;
			scanf("%d", &u);
			printf("%d\n", done[u]);
		}
	}

	return;
}

int main()
{
	int t = 1;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++) {
		tt++;
		timer = 0;
		printf("Case %d:\n", i);
		solve();
	}
	return 0;
}
*/
