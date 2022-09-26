#include<bits/stdc++.h>
using namespace std;

#define mx 30005
#define ll long long
#define mod 1000000007 //998244353

int a[mx];
char ch[mx];
int n, m, ii, k, parent[mx][15], comp_par[mx], depth[mx], par[mx], node[mx], dist[mx];

vector<pair<int, int>>g[mx];
bool vis[mx], is_graph[mx];

ll comp_cost[mx];

void init() {
    for (int k = 1 ; k < 15 ; k++) {
        for (int i = 1 ; i <= n ; i++) {
            if (parent[i][k - 1] != -1)
                parent[i][k] = parent[parent[i][k - 1]][k - 1] ;
            else
                parent[i][k] = -1 ;
        }
    }
}


int lca (int u , int v) {
    if (depth[u] < depth[v]) {  /// u nichey
        swap(u, v) ;
    }
    int diff = depth[u] - depth[v] ;
    for (int i = 14; i >= 0 ; i--) {
        if (diff >= (1 << i)) {
            diff -= (1 << i) ;
            u = parent[u][i] ;
        }
    }
    if (u == v) return u ;
    for (int i = 14; i >= 0 ; i--) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i] ;
            v = parent[v][i] ;
        }
    }
    return parent[v][0] ;
}


void dfs(int u, int p, int d, int cost)
{
    vis[u] = true;

    parent[u][0] = p;

    node[u] = ii;

    dist[u] = cost;

    depth[u] = d;

    for (auto [v, w] : g[u]) {
        if (v != p) {
            if (vis[v] == true) {
                if (is_graph[ii] == false) comp_cost[ii] += w;
                is_graph[ii] = true;
            }
            else {
                comp_cost[ii] += w;
                dfs(v, u, d + 1, cost + w);
            }
        }
    }
}

int Find(int u)
{
    return par[u] = (u == par[u] ? u : Find(par[u]));
}

void Union(int paru, int parv)
{
    par[parv] = paru;
}

void Clear(int n)
{
    for (int i = 0; i <= n; i++) {
        par[i] = i;
        g[i].clear();
        vis[i] = false;
        comp_cost[i] = 0;
        dist[i] = 0;
        is_graph[i] = false;
    }
}

void solve()
{
    scanf("%d%d", &n, &m);

    Clear(n);

    for (int i = 0; i < m; i++) {
        int u, v, w;

        scanf("%d%d%d", &u, &v, &w);

        g[u].push_back({v, w});
        g[v].push_back({u, w});

        int paru = Find(u);
        int parv = Find(v);

        if (paru != parv) Union(paru, parv);
    }

    ii = 0;

    int cmp = 0;

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            ++ii;
            comp_par[ii] = i;
            dfs(i, -1, 0, 0);
            // cout << comp_cost[ii] << endl;
        }
    }

    init();

    int q;

    scanf("%d", &q);

    while (q--) {
        int u, v;

        scanf("%d%d", &u, &v);

        int paru = Find(u), parv = Find(v);

        if (paru != parv) {
            printf("-1\n");
        }
        else {
            int cmp = node[u];

            int parent_cmp = comp_par[cmp];

            // cout << parent_cmp << " ";

            int _lca = lca(u, v);

            ll ans = dist[u] + dist[v];

            if (_lca > 0) ans -= 2 * dist[_lca];

            // cout << "Lca: " << _lca << endl;

            if (is_graph[cmp]) ans = min(ans, comp_cost[ii] - ans);

            // if (is_graph[cmp]) cout << "|  " << endl;

            printf("%lld\n", ans);
        }
    }

    return;
}

int main()
{
    int t = 1;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        printf("Case %d:\n", i);
        solve();
    }
    return 0;
}
