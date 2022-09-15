#include<bits/stdc++.h>
using namespace std;

#define mx 200005
#define ll long long
const ll base = 31, mod = 1000003;

int a[mx];
char ch[mx];
int n, m, ii, k;

ll P[mx];

void power_cal()
{
    P[0] = 1;
    for (int i = 1; i < mod; i++)P[i] = (base * P[i - 1]) % mod;
}


ll inv[mx], invfact[mx], fact[mx];

ll add(ll a, ll b)
{
    a += b;
    if (a >= mod)a -= mod;
    return a;
}
ll sub(ll a, ll b)
{
    a -= b;
    if (a < 0)a += mod;
    return a;
}
ll mul(ll a, ll b)
{
    ll re = a;
    re *= b;
    if (re >= mod)re %= mod;
    return re;
}

ll bigmod(ll a, ll b) {
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = mul(res, a);
        a = mul(a, a);
        b >>= 1;
    }
    return res;
}

void Fact()
{
    fact[0] = 1;
    for (int i = 1; i < mx; i++) fact[i] = mul(fact[i - 1], i);

    invfact[mx - 1] = bigmod(fact[mx - 1], mod - 2);

    for (int i = mx - 2; i >= 0; i--) invfact[i] = mul(invfact[i + 1], i + 1);
}

void mod_inverse()
{
    inv[1] = 1;
    for (int i = 2; i < mod; ++i) {
        inv[i] = sub(mod, mul((mod / i), inv[mod % i]));
    }
}

int tree[4 * mx], revtree[4 * mx]; /// be careful with overflow

void build (int cn, int b, int e) {
    if (b == e) {
        tree[cn] = mul((ch[b - 1] - 'A' + 1), P[b]);
        revtree[cn] = mul((ch[b - 1] - 'A' + 1), P[n - b + 1]);
        return;
    }
    int lc = 2 * cn, rc = lc + 1, mid = (b + e) / 2;
    build(lc, b, mid);
    build(rc, mid + 1, e);
    tree[cn] = add(tree[lc], tree[rc]);
    revtree[cn] = add(revtree[lc], revtree[rc]);
}

void upd (int cn , int b , int e , int i , int val) {
    if (b > i or e < i) {
        return;
    }
    int lc = 2 * cn , rc = lc + 1 , mid = (b + e) / 2 ;
    if (b >= i and e <= i) {
        tree[cn] = mul(val, P[b]);
        revtree[cn] = mul(val, P[n - b + 1]);
        return ;
    }
    upd(lc, b, mid, i, val);
    upd(rc, mid + 1, e, i, val);
    tree[cn] = add(tree[lc], tree[rc]);
    revtree[cn] = add(revtree[lc], revtree[rc]);
}


int query (int cn , int b , int e , int i , int j, bool is_front) {
    if (b > j or e < i) return 0;
    if (b >= i and e <= j) {
        if (is_front) return tree[cn];
        return revtree[cn];
    }
    int lc = 2 * cn , rc = lc + 1 , mid = (b + e) / 2;
    return add(query(lc, b, mid, i, j, is_front), query(rc, mid + 1, e, i, j, is_front));
}

int ans = 0, len = 0;

vector<int>g[mx];

void dfs(int u, int p)
{
    upd(1, 1, n, ++len, ch[u - 1] - 'A' + 1);

    // cout << ch[u - 1] << " " << len << endl;

    ll Front = query(1, 1, n, 1, len, 1);
    ll Back = mul(query(1, 1, n, 1, len, 0), inv[P[n - len]]);

    // cout << Front << " " << Back << endl;

    if (Front == Back) ans++;

    for (auto v : g[u]) {
        if (v == p) continue;

        dfs(v, u);

        // len--;
    }
    len--;
}

void solve()
{
    ans = 0, len = 0;
    scanf("%d", &n);

    scanf("%s", ch);

    for (int i = 0; i < n - 1; i++) {
        int u, v;

        scanf("%d%d", &u, &v);

        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, -1);

    int gcd = __gcd(ans, n);

    printf("%d/%d\n", ans / gcd, n / gcd);

    for (int i = 1; i <= n; i++)g[i].clear();

    return;
}

int main()
{
    int t = 1;
    power_cal();
    mod_inverse();
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        printf("Case %d: ", i);
        solve();
    }
    return 0;
}
