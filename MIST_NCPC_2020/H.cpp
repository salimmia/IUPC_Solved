#include<bits/stdc++.h>
using namespace std;

#define mx 50005
#define ll long long
#define mod 1000000007 //998244353

int a[mx];
char ch[mx];
int n, m, ii, k;

bool visit[mx], f;

vector<pair<int, int>>g[mx];

int par[mx], tree_prefix[mx], prefix_xor[mx], ans[mx], par_tree[mx], node_xor[mx];

int Find(int u)
{
    return par[u] = (u == par[u] ? u : Find(par[u]));
}

void Union(int u, int v)
{
    par[u] = par[v];
}

void dfs(int u)
{
    visit[u] = true;

    for (auto pii : g[u]) {
        int v = pii.first, x = pii.second;
        if (visit[v]) continue;

        else tree_prefix[v] = tree_prefix[u] ^ x;

        dfs(v);
    }
}

void solve()
{
    scanf("%d%d", &n, &k);

    for (int i = 0; i <= n; i++) par[i] = i, ans[i] = -1, par_tree[i] = -1, node_xor[i] = 0;

    f = true;

    set<pair<pair<int, int>, int>> same_comp;

    while (k--) {
        int l, r, x;

        scanf("%d%d%d", &l, &r, &x);

        l--;

        node_xor[r] = x;

        int par_l = Find(l), par_r = Find(r);

        if (par_l == par_r) {
            same_comp.insert({{l, r}, x});
        }
        else {
            g[l].push_back({r, x});
            g[r].push_back({l, x});
            Union(par_r, par_l);
            par_tree[r] = l + 1;
        }
    }

    for (int i = 0; i < n; i++) {
        if (!visit[i]) {
            dfs(i);
            ans[i] = 0;
        }
    }

    for (auto pii : same_comp) {
        auto [u, v] = pii.first;
        int x = pii.second;
        if ((tree_prefix[v] ^ x ^ tree_prefix[u]) != 0) f = false;
    }

    ll csum[mx];
    csum[0] = 0;

    if (!f) printf("Impossible\n");
    else {
        for (int i = 1; i <= n; i++) {
            if (ans[i] == -1) {
                if (par_tree[i] != -1) {
                    ans[i] = csum[i - 1] ^ csum[par_tree[i] - 1] ^ node_xor[i];
                }
                else ans[i] = 0;
            }
            csum[i] = csum[i - 1] ^ ans[i];
        }
    }

    for (int i = 1; i < n; i++) printf("%d ", ans[i]);
    printf("%d\n", ans[n]);

    for (int i = 0; i <= n; i++) {
        g[i].clear();
        tree_prefix[i] = 0;
        prefix_xor[i] = 0;
        visit[i] = false;
    }
    same_comp.clear();

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
