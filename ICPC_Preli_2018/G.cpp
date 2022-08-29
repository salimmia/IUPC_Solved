#include<bits/stdc++.h>
using namespace std;

#define mx 200005
#define ll long long
#define mod 1000000007 //998244353

int a[mx];
char ch[mx];
int n, m, ii, k;

void solve()
{
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    scanf("%d", &m);

    while (m--) {
        ll x;

        scanf("%d", &x);

        int gcd = 0;
        bool f = false;

        for (int i = 0; i < n; i++) {
            if (a[i] % x == 0) {
                gcd = __gcd(gcd, a[i]);
                if (gcd <= x) {
                    if (gcd == x) printf("Y\n"), f = true;
                    break;
                }
            }
        }
        if (!f) printf("N\n");
    }

    return;
}

int main()
{
    int t = 1;
    // scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        // printf("Case %d: \n", i);
        solve();
    }
    return 0;
}
