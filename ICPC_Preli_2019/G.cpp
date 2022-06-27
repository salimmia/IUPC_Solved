#include<bits/stdc++.h>

using namespace std;

#define MOD 1000000007
#define INF 1e18
#define nl "\n"
#define PI 3.141592653589793238462

typedef long long int ll;
typedef unsigned long long ull;
typedef long double lld;
#define ff first
#define ss second
#define all(x) x.begin(), x.end()

#define mt make_tuple
#define eb emplace_back
#define pb push_back

int const mx = 1e7 + 5;

ll n, W, m, k;

bitset<mx>is_composite;
vector<int>prime;
int phi[mx];
ll prefix[mx];


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

void solve()
{
    scanf("%lld%lld", &n, &k);

    ll lo = 1, hi = n, ans = -1;

    while (lo <= hi) {
        int mid = (lo + hi) >> 1;

        if (prefix[mid] >= k) {
            ans = mid;
            hi = mid - 1;
        }
        else lo = mid + 1;
    }

    if (ans != -1) ans = n / ans;

    printf("%lld\n", ans);

    return;
}

int main()
{
    int t = 1, cs = 1;

    seive();

    for (int i = 1; i < mx; i++) {
        prefix[i] = prefix[i - 1] + phi[i];
    }

    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        printf("Case %d: ", i);
        solve();
    }
}
/*
0. Enough array size? Enough array size? Enough array size? Integer overflow?

1. Think TWICE, Code ONCE!
Are there any counterexamples to your algo?

2. Be careful about the BOUNDARIES!
N=1? P=1? Something about 0?

3. Do not make STUPID MISTAKES!
Time complexity? Memory usage? Precision error?
*/
