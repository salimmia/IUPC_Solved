///Creater by Salim_JnU

#include<bits/stdc++.h>
using namespace std;

#define mx 200005
#define ll long long
#define mod 1000000007 //998244353

int a[mx];
char ch[mx];
int n, m, tt, k;

struct segtree {
    vector<ll>tree, lazy, a;
    void init(int x) {
        tree.resize(4 * (x + 5));
        lazy.resize(4 * (x + 5));
        a.resize(x + 5);
    }
    ll Merge(ll l, ll r)
    {
        return l | r;
    }

    void build (int cn, int b, int e) {
        if (b == e) {
            tree[cn] = a[b];
            return;
        }
        int lc = 2 * cn, rc = lc + 1, mid = (b + e) / 2;
        build(lc, b, mid);
        build(rc, mid + 1, e);
        tree[cn] = Merge(tree[lc], tree[rc]);
    }
    void relax (int cn, int b, int e) {
        if (lazy[cn]) {
            tree[cn] += (e - b + 1) * lazy[cn] ;
            if (b != e) {
                lazy[2 * cn] += lazy[cn] ;
                lazy[2 * cn + 1] += lazy[cn] ;
            }
            lazy[cn] = 0;
        }
    }
    void upd (int cn, int b, int e, int i, int j, int add) {
        relax(cn, b, e);
        if (b > j or e < i) {
            return;
        }
        int lc = 2 * cn , rc = lc + 1 , mid = (b + e) / 2;
        if (b >= i and e <= j) {
            lazy[cn] += add;
            relax(cn, b, e);
            return;
        }
        upd(lc, b, mid, i, j, add);
        upd(rc, mid + 1, e, i, j, add);
        tree[cn] = Merge(tree[lc], tree[rc]);
    }
    ll query (int cn, int b, int e, int i, int j) {
        relax(cn, b, e);
        if (b > j or e < i) return 0;
        if (b >= i and e <= j) {
            return tree[cn];
        }
        int lc = 2 * cn, rc = lc + 1, mid = (b + e) / 2;
        ll p = query(lc, b, mid, i, j);
        ll q = query(rc, mid + 1, e, i, j);

        return Merge(p, q);
    }
};

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

void solve()
{
    scanf("%d%d", &n, &k);

    segtree sg;

    sg.init(n);

    for (int i = 1; i <= n; i++) scanf("%lld", &sg.a[i]);

    sg.build(1, 1, n);

    while (k--) {
        int l, r;

        scanf("%d%d", &l, &r);

        ll len = bigmod(2, r - l);

        ll _or = sg.query(1, 1, n, l, r);

        // cout << _or << endl;

        ll ans = mul(_or, len);

        printf("%lld\n", ans);
    }

    return;
}

int main()
{
    int t = 1;
    // scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        tt++;
        // printf("Case %d: ", i);
        solve();
    }
    return 0;
}
