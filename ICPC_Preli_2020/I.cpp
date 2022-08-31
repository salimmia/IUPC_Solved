#include<bits/stdc++.h>
using namespace std;

#define mx 200005
#define ll long long
#define mod 1000000007 //998244353

int a[mx];
char ch[mx];
ll n, m, ii, k, L1, L2, p, q;

void solve()
{
    char c;
    while (1) {
        scanf("%lld%lld %lld %c%lld", &L1, &L2, &p, &c, &q);

        if (L1 == L2 && L1 == 0) break;

        // cout << p << " " << q << endl;

        ll upper = p * p * (L1 - 1) - (L2 - 1) * q * q;

        ll lower = p * (q - p);

        upper *= 2;

        ll B = upper / lower;

        ll area = (2 * L1 + B - 2);

        printf("%lld\n", area);
    }
    return;
}

int main()
{
    int t = 1;
    // scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        // printf("Case %d: ", i);
        solve();
    }
    return 0;
}
