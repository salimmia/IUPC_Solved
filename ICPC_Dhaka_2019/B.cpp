#include<bits/stdc++.h>
using namespace std;

#define mx 200005
#define ll long long
#define mod 1000000007 //998244353

int a[mx];
char ch[mx];
ll n, m, ii, k, p, prefix[mx], dp[mx];

void solve()
{
    scanf("%lld%lld%lld", &n, &p, &k);

    for (int i = 0; i <= n; i++) prefix[i] = 0;

    ll root = -1;

    if (p > n) {
        printf("Invalid\n");
        return;
    }

    for (int i = p; i <= n; i++) {
        int st = i - p;

        ll tot = prefix[i - 1] + prefix[max(0, st - 1)];

        dp[i] = tot + i - st;

        prefix[i] = prefix[i - 1] + dp[i];

        if (dp[i] + n - i >= k) {
            k -= n - i;
            root = i;
            break;
        }
    }

    if (root == -1) {
        printf("Invalid\n");
        return;
    }

    int nxt = root - 1;

    while (k > 0) {
        int hi = root - 1, lo = max(0LL, root - p);
        ll now = 0;

        for (int i = hi; i >= lo; i--) {
            now = dp[i] + 1;

            if (now < k) {
                k -= now;
            }
            else {
                k--;
                nxt = i;
                if (k == 0) break;
                else {
                    root = i;
                    nxt = i - 1;
                    break;
                }
            }
        }
    }

    printf("%lld %d\n", root, nxt);

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
