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
int const mx = 1e6 + 5;

int n, W, m, k, dp[mx];
priority_queue <pair<int, int> > pq[mx];

int lp[mx];
vector<int>prime;
map<int, int>pf[mx];
ll fact[mx], inv[mx];

void sieve()
{
    for (int i = 2; i < mx - 3; i++)
    {
        if (lp[i] == 0)
        {
            prime.push_back(i);
            lp[i] = i;
        }
        for (int j = 0; j < prime.size() && prime[j] <= lp[i] && i * prime[j] < mx - 3; j++)
            lp[i * prime[j]] = prime[j];
    }

    for (int i = 2; i < mx - 3; i++)
    {
        int p = i / lp[i];
        pf[i] = pf[p];
        pf[i][lp[i]]++;
    }
}

void solve()
{
    scanf("%d%d", &n, &k);

    vector<ll>a(n);

    for (int i = 0; i <= n; i++) dp[i] = (n - 1);

    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    dp[0] = 0;

    for (int i = 0; i < n; i++) {
        for (auto it : pf[a[i]]) {
            auto[prime, cnt] = it;
            while (!pq[prime].empty() && (pq[prime].top().second < i - k)) pq[prime].pop();

            if (!pq[prime].empty()) {
                pair<int, int> p = pq[prime].top();

                int val = -p.first;

                dp[i] = min(dp[i], val + 1);
            }
        }
        if (i > 0) dp[i] = min(dp[i - 1] + 1, dp[i]);
        for (auto it : pf[a[i]]) {
            auto[prime, cnt] = it;

            pq[prime].push({ -dp[i], i});
        }
    }

    for (int i = 0; i < n ; i++) {
        for (auto it : pf[a[i]]) {
            auto[prime, cnt] = it;
            while (!pq[prime].empty()) pq[prime].pop();
        }
    }

    printf("%d\n", dp[n - 1]);

    return;
}

int main()
{
    int t = 1, cs = 1;

    sieve();

    scanf("%d", &t);

    FOR(i, 1, t) {
        printf("Case %d: ", i);
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
