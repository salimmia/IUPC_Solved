///Created by Salim_JnU

#include<bits/stdc++.h>
using namespace std;

#define mx 200005
#define ll long long
#define mod 1000000007 //998244353

char ch[mx];
int n, m, tt, k;
int col[mx], ans[mx], t_col[mx];

ll a[mx];
bool taken[mx];

void solve()
{
    scanf("%d%d", &n, &m);

    vector<pair<ll, int>>v(n * m);

    ll tot = 0;

    for (int i = 0; i < n * m; i++) {
        scanf("%lld", &a[i]);

        taken[i] = false;

        tot += a[i];

        v[i] = {a[i], i};
    }

    if (n == 1) {
        printf("%lld\n", tot);

        for (int i = 1; i < m; i++) printf("%d ", i);
        printf("%d\n", m);
        return;
    }
    if (m == 1) {
        printf("%lld\n", tot);

        for (int i = 1; i < n; i++) printf("1 ");
        printf("1\n");

        return;
    }

    tot = 0;

    sort(v.rbegin(), v.rend());

    int takecol = m + 1, bad_col = 1;

    for (int i = 0; i < n + m - 1; i++) {
        taken[v[i].second] = true;
        tot += (ll)v[i].first;
    }

    printf("%lld\n", tot);

    col[0] = n;

    for (int i = 0; i < n * m; i++) {
        if (taken[i]) {
            int diff = takecol - bad_col;

            if (diff > 1) {
                takecol--;
            }
            else if (diff == 1) {
                if (t_col[takecol] == col[bad_col] + 1) {
                    takecol--;
                    bad_col++;
                    // cout << "eee" << endl;
                }
            }
            else {
                if (t_col[takecol] + col[takecol] == n) takecol--;
            }
            ans[i] = takecol;
            t_col[takecol]++;
        }
        else {
            int diff = takecol - bad_col;

            if (diff > 1) {
                if (col[bad_col] == n - 1) bad_col++;
            }
            else if (diff == 1) {
                if (col[bad_col] == n - 1) {
                    bad_col += 2;
                }
            }
            else {
                if (col[bad_col] + t_col[bad_col] == n) bad_col++;
            }
            ans[i] = bad_col;
            col[bad_col]++;
        }
        // cout << taken[i] << "    " << takecol << " " << bad_col << endl;
        // cout << t_col[takecol] << " " << col[bad_col] << endl;
    }

    for (int i = 0; i < n * m - 1; i++) printf("%d ", ans[i]);
    printf("%d\n", ans[n * m - 1]);

    for (int i = 0; i <= m; i++) col[i] = 0, t_col[i] = 0;

    return;
}

int main()
{
    int t = 1;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        tt++;
        // printf("Case %d: ", i);
        solve();
    }
    return 0;
}
