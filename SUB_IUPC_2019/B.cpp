///Created by Salim_JnU

#include<bits/stdc++.h>
using namespace std;

#define mx 1000005
#define ll long long
#define mod 1000000007 //998244353

int a[mx];
char ch[mx];
int n, m, tt, k;
ll ans[mx];

vector<pair<int, ll>> ar[mx];
vector<int> ache[mx];

bitset<mx>is_composite;
vector<ll>prime;
int phi[mx];


void seive(int n)
{
    phi[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        if (!is_composite[i])
        {
            prime.push_back(i);
            phi[i] = i - 1;          ///i is prime
        }

        for (int j = 0; j < prime.size() && i * prime[j] <= n; j++)
        {
            is_composite[i * prime[j]] = true;

            if (i % prime[j] == 0)
            {
                phi[i * prime[j]] = phi[i] * prime[j]; ///prime[j] divides i
                break;
            }
            else
            {
                phi[i * prime[j]] = phi[i] * phi[prime[j]]; ///prime[j] do not divide i
            }
        }
    }
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

void mod_inverse()
{
    inv[1] = 1;
    for (int i = 2; i < mx; ++i) {
        inv[i] = sub(mod, mul((mod / i), inv[mod % i]));
    }
}


auto factorization(ll x)
{
    vector<pair<ll, int>>v;

    for (int i = 0; prime[i] * prime[i] <= x; i++) {
        int cnt = 0;

        while (x % prime[i] == 0) {
            x /= prime[i];
            cnt++;
        }
        if (cnt > 0) {
            v.emplace_back(prime[i], cnt);
        }
    }

    if (x > 1) v.emplace_back(x, 1);

    return v;
}

void solve()
{
    scanf("%d%d", &n, &k);

    for (int i = 1; i <= n; i++) ans[i] = 1;

    while (k--) {
        int l, r, x;

        scanf("%d%d%d", &l, &r, &x);

        ar[l].push_back({1, x});
        ar[r + 1].push_back({ -1, x});
    }

    ll now = 1;

    for (int i = 1; i <= n + 1; i++) {
        for (auto[type, x] : ar[i]) {
            if (type == 1) {
                auto v = factorization(x);

                for (auto [div, cnt] : v) {
                    if (ache[div].size() > 0) {
                        if (ache[div].back() < cnt) {
                            now = mul(now, inv[bigmod(div, ache[div].back())]);
                            now = mul(now, bigmod(div, cnt));
                        }
                        // ache[div].pop_back();
                    }
                    else {
                        now =  mul(now, bigmod(div, cnt));
                    }

                    ache[div].push_back(cnt);
                    sort(ache[div].begin(), ache[div].end());
                    // cout << now << endl;
                }
            }

            else {
                auto v = factorization(x);

                for (auto [div, cnt] : v) {

                    if (cnt == ache[div].back()) {
                        // cout << i << " " << div << " " << cnt << endl;
                        now = mul(now, inv[bigmod(div, cnt)]);
                        ache[div].pop_back();
                    }

                    if (ache[div].size() > 0) {
                        now = mul(now, bigmod(div, ache[div].back()));
                    }
                }
            }

            // cout << i << endl;
        }
        ans[i] = now;
    }

    for (int i = 1; i <= n; i++) printf("%lld ", ans[i]);
    printf("\n");

    return;
}

int main()
{
    int t = 1;

    seive(mx - 1);
    mod_inverse();

    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        tt++;
        printf("Case %d: ", i);
        solve();
    }
    return 0;
}
