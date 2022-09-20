///Creater by Salim_JnU

#include<bits/stdc++.h>
using namespace std;

#define mx 1000005
#define ll long long
#define mod 10000007 //998244353

int a[mx];
char ch[mx];
int n, m, tt, k;

bitset<mx>is_composite;
vector<int>prime;
int phi[mx];

void seive()
{
    phi[1] = 1;

    n = mx - 3;

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

void solve()
{
    while (1) {
        scanf("%d", &n);

        if (n == 0) break;

        ll ans = 1;

        for (int i = 0; prime[i] <= n; i++) {
            ll x = n;

            ll cnt = 1;

            while (x) {
                cnt += (x / prime[i]);
                x /= prime[i];
            }
            ans = mul(ans, (cnt * (cnt + 1) / 2));
        }

        printf("%lld\n", ans);
    }

    return;
}

int main()
{
    int t = 1;

    seive();

    mod_inverse();

    // scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        tt++;
        // printf("Case %d: ", i);
        solve();
    }
    return 0;
}
