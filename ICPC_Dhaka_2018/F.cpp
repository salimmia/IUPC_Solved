///Creater by Salim_JnU

#include<bits/stdc++.h>
using namespace std;

#define mx 20005
#define ll long long
#define mod 1000000007 //998244353

int a[mx];
char ch[mx];
int n, m, tt, k;

int par[mx][18], depth[mx] ;
vector <int> g[mx];
bitset<mx>path[mx];

void dfs (int u , int p , int lvl) {
    par[u][0] = p ;
    depth[u] = lvl;
    if (p != -1) {
        path[u] = path[p];
    }
    path[u][u] = true;

    for (int i = 0 ; i < g[u].size() ; i++) {
        int v = g[u][i] ;
        if (v == p) continue ;
        dfs (v, u, lvl + 1) ;
    }
}


void init(int root , int n) {
    dfs(root, -1, 1) ;
    for (int k = 1 ; k < 18 ; k++) {
        for (int i = 1 ; i <= n ; i++) {
            if (par[i][k - 1] != -1)
                par[i][k] = par[par[i][k - 1]][k - 1] ;
            else
                par[i][k] = -1 ;
        }
    }
}


int lca (int u , int v) {
    if (depth[u] < depth[v]) {  /// u nichey
        swap(u, v) ;
    }
    int diff = depth[u] - depth[v] ;
    for (int i = 18 - 1 ; i >= 0 ; i--) {
        if (diff >= (1 << i)) {
            diff -= (1 << i) ;
            u = par[u][i] ;
        }
    }
    if (u == v) return u ;
    for (int i = 18 - 1; i >= 0 ; i--) {
        if (par[u][i] != par[v][i]) {
            u = par[u][i];
            v = par[v][i];
        }
    }
    return par[v][0];
}

int kth_par(int u , int k) {
    for (int i = 18 - 1; i >= 0; i--) {
        if (k >= (1 << i)) {
            k -= (1 << i);
            u = par[u][i];
        }
        if (u == -1) return u;
    }
    return u ;
}


void solve()
{
    scanf("%d", &n);

    for (int i = 0; i < n - 1; i++) {
        int u, v;

        scanf("%d%d", &u, &v);

        g[u].push_back(v);
        g[v].push_back(u);
    }

    init(1, n);

    // for (int i = 1; i <= n; i++) {
    //     cout << i << "-> ";
    //     for (int j = 1; j <= n; j++) {
    //         cout << path[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    int q;

    scanf("%d", &q);

    while (q--) {
        scanf("%d", &k);

        bitset<mx>ans;

        ans.set();

        while (k--) {
            int u, v;

            scanf("%d%d", &u, &v);

            int _lca = lca(u, v);

            bitset<mx>bs = path[u] | path[v];

            bs ^= (path[_lca]);
            bs[_lca] = 1;

            ans &= bs;
        }

        printf("%d\n", (int)ans.count());
    }

    for (int i = 0; i <= n; i++) {
        g[i].clear();
        path[i] = false;
    }

    return;
}

int main()
{
    int t = 1;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        tt++;
        printf("Case %d:\n", i);
        solve();
    }
    return 0;
}
