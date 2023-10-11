// Salim_JnU

#include<bits/stdc++.h>
using namespace std;

#define mx 10005
#define ll long long
#define mod 1000000007 //998244353


ll dp[mx];
ll pre[mx];
int n, m, ii, p;
ll k;

void solve()
{
    scanf("%d%d%lld", &n, &p, &k);
    int id = -1;
    if (p > n)
    {
        printf("Case %d: Invalid\n", ++ii );
        return;
    }

    if (n - k >= p)
    {
        printf("Case %d: %lld %lld\n", ++ii, n - k + 1, n - k);
        return;
    }

    for (int i = 0; i < p; i++)dp[i] = 0, pre[i] = 0;
    for (int i = p; i <= n; i++)
    {
        int be = i - p;
        ll tot = pre[i - 1] - pre[max(1, be - 1)];

        dp[i] = tot + i - be;
        pre[i] = pre[i - 1] + dp[i];

        if (dp[i] + n - i >= k)
        {
            k -= n - i;
            if (k == 0)
            {
                printf("Case %d: %d %d\n", ++ii, i + 1, i);
                return;
            }
            id = i;
            break;
        }
    }

    if (id == -1)
    {
        printf("Case %d: Invalid\n", ++ii );
        return;
    }

    int cur = id;
    int nxt = id - 1;
    while (k > 0)
    {
        int jabe = max(0, cur - p);
        for (int i = cur - 1; i >= jabe; i--)
        {
            ll tot = dp[i] + 1;
            //cout<<cur<<" "<<i<<" "<<tot<<" "<<k<<endl;
            if (tot < k)
            {
                k -= tot;
            }
            else
            {
                k--;
                if (k == 0)
                {
                    nxt = i;
                    break;
                }
                else
                {
                    cur = i;
                    nxt = i - 1;
                    break;
                }
            }
        }

    }
    printf("Case %d: %d %d\n", ++ii, cur, nxt);
}

int main()
{
    int t = 1;
    scanf("%d", &t);
    while (t--)solve();
    return 0;
}
