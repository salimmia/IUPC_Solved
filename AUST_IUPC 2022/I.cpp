#include<bits/stdc++.h>
using namespace std;

#define mx 200005
#define ll long long
#define mod 1000000007 //998244353

int a[mx];
char ch[mx];
int n, m, ii, k;

map<tuple<int, int, int>, ll>dp;

ll fnc(int pos, int taken, int diff, vector<int>&candidates, vector<vector<ll>>&v)
{
    if (taken == n - 1) {
        if (diff == 1) return 0;
        else return LONG_LONG_MIN;
    }
    if (pos >= candidates.size()) return LONG_LONG_MIN;

    if (dp.find(make_tuple(pos, taken, diff)) != dp.end()) return dp[make_tuple(pos, taken, diff)];

    ll ret = fnc(pos + 1, taken, diff, candidates, v);

    int idx = candidates[pos];

    ret = max(ret, fnc(pos + 1, taken + 1, diff + 1, candidates, v) + v[idx][2]);
    ret = max(ret, fnc(pos + 1, taken + 1, diff, candidates, v) + v[idx][1]);
    ret = max(ret, fnc(pos + 1, taken + 1, diff - 1, candidates, v) + v[idx][0]);

    return dp[make_tuple(pos, taken, diff)] = ret;
}

void solve()
{
    scanf("%d%d", &n, &k);

    k = n * n / 4;

    vector<vector<ll>>v(k);
    for (int i = 0; i < k; i++) {
        vector<ll>p(4);

        for (int j = 0; j < 4; j++) scanf("%lld", &p[j]);

        sort(p.rbegin(), p.rend());

        for (int j = 1; j < 3; j++) p[j] += p[j - 1];

        v[i] = p;
    }

    vector<int>candidates;

    for (int i = 0; i < 3; i++) {
        vector<pair<ll, int>>p;

        for (int j = 0; j < k; j++) {
            p.push_back({v[j][i], j});
        }
        sort(p.rbegin(), p.rend());

        for (int i = 0; i < n - 1; i++) {
            candidates.push_back(p[i].second);
        }
    }

    sort(candidates.begin(), candidates.end());

    candidates.erase(unique(candidates.begin(), candidates.end()), candidates.end());



    // for (auto vv : v) {
    //     for (auto x : vv) {
    //         cout << x << " ";
    //     }
    //     cout << endl;
    // }

    ll ans = fnc(0, 0, 0, candidates, v);

    dp.clear();

    printf("%lld\n", ans);

    return;
}

int main()
{
    int t = 1;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        // printf("Case %d: ", i);
        solve();
    }
    return 0;
}
