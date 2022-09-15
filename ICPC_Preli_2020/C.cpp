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
        tree[cn] = mul((ch[b - 1] - 'a' + 1), P[b]);
        revtree[cn] = mul((ch[b - 1] - 'a' + 1), P[n - b + 1]);
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

void solve()
{
    scanf("%s", ch);

    n = strlen(ch);

    set<int>st;
    st.insert(0);

    for (int i = 1; i < n; i++) {
        if (ch[i] != ch[i - 1]) st.insert(i);
    }

    build(1, 1, n);

    int q;

    scanf("%d", &q);

    while (q--) {
        int type;

        scanf("%d", &type);

        if (type == 1) {
            int l, r;

            scanf("%d%d", &l, &r);

            ll Front = mul(query(1, 1, n, l, r, 1), inv[P[l]]);

            ll Back = mul(query(1, 1, n, l, r, 0), inv[P[n - r + 1]]);

            // cout << l << " " << r << " " << Front << " " << Back << endl;

            if (Front == Back) {
                printf("0\n");
                continue;
            }

            int len = r - l + 1;

            int lo = 0, hi = (len + 1) / 2, re = -1;

            while (lo <= hi) {
                int mid = (lo + hi) / 2;

                Front = mul(query(1, 1, n, l, l + mid - 1, 1), inv[P[l]]);
                Back = mul(query(1, 1, n, n - mid + 1, r, 0), inv[P[n - r + 1]]);

                if (Front == Back) {
                    re = mid;
                    lo = mid + 1;
                }
                else hi = mid - 1;
            }
            // printf("%d\n", re);

            int fs = l + re, ls = r - re;

            // cout << fs << " fs, ls " << ls << endl;

            Front = mul(query(1, 1, n, fs + 1, ls, 1), inv[P[fs + 1]]);
            Back = mul(query(1, 1, n, fs + 1, ls, 0), inv[P[n - ls + 1]]);

            if (Front == Back) {
                /// print low index of fs
                auto it = st.lower_bound(fs - 1);
                printf("%d\n", *it + 1);
                continue;
            }

            Front = mul(query(1, 1, n, fs, ls - 1, 1), inv[P[fs]]);
            Back = mul(query(1, 1, n, fs, ls - 1, 0), inv[P[n - ls]]);

            if (Front == Back) {
                /// print low index of ls;
                auto it = st.lower_bound(fs - 1);
                printf("%d\n", *it + 1);

                continue;
            }


            printf("-1\n");
        }
        else {
            int idx;
            char c;

            scanf("%d %c", &idx, &c);

            if (n == 1) continue;

            if (ch[idx - 1] == c) continue;

            if (idx == 1) {
                if (ch[1] != c) st.insert(1);
            }
            else if (idx == n) {
                if (ch[n - 2] != c) st.insert(n - 1);
            }
            else {
                if (ch[idx] == c) st.erase(st.find(idx));
                if (ch[idx - 1] != c) st.insert(idx - 1);
            }

            upd(1, 1, n, idx, c - 'a' + 1);

            ch[idx - 1] = c;
        }
    }

    return;
}

int main()
{
    int t = 1;
    power_cal();
    mod_inverse();
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        printf("Case %d:\n", i);
        solve();
    }
    return 0;
}
