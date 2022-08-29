#include<bits/stdc++.h>
using namespace std;

#define mx 200005
#define ll long long
#define mod 1000000007 //998244353

int a[mx];
char ch[mx];
int n, m, ii, k;

ll fnc(ll val)
{
    ll lo = 0, hi = 1e9;

    while (lo < hi) {
        ll mid = (lo + hi + 1) >> 1;

        if (mid * mid <= val) lo = mid;
        else hi = mid - 1;
    }

    ll re = lo;

    lo = 0, hi = 1e9;

    while (lo < hi) {
        ll mid = (lo + hi + 1) >> 1;

        if (mid * mid * 2 <= val) lo = mid;
        else hi = mid - 1;
    }

    return re + lo;
}

void solve()
{
    ll l, r;
    scanf("%lld%lld", &l, &r);

    ll ans = fnc(r) - fnc(l - 1);

    printf("%lld\n", ans);

    return;
}

int main()
{
    int t = 1;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        printf("Case %d: ", i);
        solve();
    }
    return 0;
}
