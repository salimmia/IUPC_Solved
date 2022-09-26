///Created by Salim_JnU

#include<bits/stdc++.h>
using namespace std;

#define mx 50005
#define ll long long
#define mod 1000000007 //998244353

int a[mx], b[mx];
char ch[mx];
int n, m, tt, k,  dp[mx][11], vis[mx][11], dp1[mx][11], vis1[mx][11], idx[mx * 10], mx_taken_idx[mx];

int fnc(int pos, int baki)
{
    if (pos > n) return 0;

    if (vis[pos][baki] == tt) return dp[pos][baki];
    vis[pos][baki] = tt;

    int ret = 1;

    for (int i = pos + 1; i <= n && i <= pos + baki + 1; i++) {
        if (b[i] >= b[pos]) {
            ret = max(ret, fnc(i, pos + baki + 1 - i) + 1);
        }
    }

    return dp[pos][baki] = ret;
}

int fnc1(int pos, int baki)
{
    if (pos < 0) return 0;

    if (vis1[pos][baki] == tt) return dp1[pos][baki];
    vis1[pos][baki] = tt;

    int ret = 1;

    for (int i = pos - 1; i >= 1 && i >= pos - baki - 1; i--) {
        if (a[i] <= a[pos]) {
            ret = max(ret, fnc1(i, i - (pos - baki - 1)) + 1);
        }
    }

    return dp1[pos][baki] = ret;
}

void solve()
{
    scanf("%d%d", &n, &k);

    for (int i = 1; i <= 100000; i++) idx[i] = -1;

    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &b[i]);
        if (idx[b[i]] == -1) idx[b[i]] = i;
    }

    vector<pair<int, int>> arr;

    for (int i = n; i >= 1; i--) {
        int tot = 0;
        int mxx = 0;
        for (int j = 0; j <= k; j++) {
            // cout << i << " " << j << "  " << fnc(i, j) << endl;
            if (tot < fnc(i, j)) {
                mxx = j;
            }
            tot = max(tot, fnc(i, j));
            mx_taken_idx[i] = mxx;
        }
        arr.emplace_back(b[i], tot);
    }
    // cout << endl;

    sort(arr.begin(), arr.end());

    int suf[mx];

    suf[n + 1] = 0;

    for (int i = n; i >= 1; i--) {
        suf[i] = max(suf[i + 1], arr[i - 1].second);
    }

    int ans = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            int ret = fnc1(i, j);

            // cout << i << " " << j << "  " << ret << endl;

            int id = lower_bound(arr.begin(), arr.end(), make_pair(a[i], -1)) - arr.begin();

            if (id == n) continue;

            ans = max(ans, suf[id + 1] + ret);
        }
    }
    // cout << endl;

    printf("%d\n", ans);

    return;
}

int main()
{
    int t = 1;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        tt++;
        printf("Case %d: ", i);
        solve();
    }
    return 0;
}
