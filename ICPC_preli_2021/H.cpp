#include<bits/stdc++.h>
using namespace std;

#define mx 200005
#define ll long long
#define mod 1000000007 //998244353

char ch[2][mx];
int n, m, ii, k;

const int N = 200005;
int Tree[2][N * 4][26];
int Lazy[2][N * 4][26];
int ar[N];

void Relax(int node, int be, int en, int ti)
{
    for (int i = 0; i < 26; i++) {
        if (Lazy[ti][node][i] != -1) Tree[ti][node][i] = (en - be + 1) * Lazy[ti][node][i];
    }

    if (be != en)
    {
        for (int i = 0; i < 26; i++) {
            if (Lazy[ti][node][i] != -1) {
                Lazy[ti][node * 2][i] = Lazy[ti][node][i];
                Lazy[ti][node * 2 + 1][i] = Lazy[ti][node][i];
            }
        }
    }

    for (int i = 0; i < 26; i++) {
        Lazy[ti][node][i] = -1;
    }

    return;
}

void Merge(int node, int left, int right, int ti)
{
    for (int i = 0; i < 26; i++) {
        Tree[ti][node][i] = Tree[ti][left][i] + Tree[ti][right][i];
    }
    return;
}

void init(int node, int be, int en, int ti)
{
    for (int i = 0; i < 26; i++) {
        Lazy[ti][node][i] = -1;
    }
    if (be == en)
    {
        for (int i = 0; i < 26; i++) {
            Tree[ti][node][i] = 0;
        }
        Tree[ti][node][ch[ti][be] - 'a'] = 1;
        return;
    }
    int mid = (be + en) / 2;
    init(node * 2, be, mid, ti);
    init(node * 2 + 1, mid + 1, en, ti);
    Merge(node, node * 2, node * 2 + 1, ti);
}

void Rupdate(int node, int be, int en, int i, int j, int c, int ti)
{
    Relax(node, be, en, ti);
    if (be > j || en < i)return;
    if (be >= i && en <= j)
    {
        for (int i = 0; i < 26; i++) {
            Lazy[ti][node][i] = 0;

        }
        Lazy[ti][node][c] = 1;
        Relax(node, be, en, ti);
        return;
    }
    int mid = (be + en) / 2;
    Rupdate(node * 2, be, mid, i, j, c, ti);
    Rupdate(node * 2 + 1, mid + 1, en, i, j, c, ti);
    Merge(node, node * 2, node * 2 + 1, ti);
}

int query(int node, int be, int en, int i, int j, int c, int ti)
{
    Relax(node, be, en, ti);
    if (be > j || en < i)return 0;
    if (be >= i && en <= j)return Tree[ti][node][c];
    int mid = (be + en) / 2;
    return query(node * 2, be, mid, i, j, c, ti) + query(node * 2 + 1, mid + 1, en, i, j, c, ti);
}

// void dbg_test(int node, int be, int en)
// {
//     if (be == en)return;
//     int mid = (be + en) / 2;
//     dbg_test(node * 2, be, mid);
//     dbg_test(node * 2 + 1, mid + 1, en);
// }

void solve()
{
    scanf("%s", &ch[0]);
    scanf("%s", &ch[1]);

    // printf("%s\n", ch[0]);

    n = strlen(ch[0]), m = strlen(ch[1]);

    int q;

    init(1, 0, n - 1, 0);
    init(1, 0, m - 1, 1);

    scanf("%d", &q);

    while (q--) {
        int type, l1, r1, l2, r2;
        char c;
        scanf("%d", &type);

        if (type == 1) {
            scanf("%d%d %c", &l1, &r1, &c);

            Rupdate(1, 0, n - 1, l1 - 1, r1 - 1, c - 'a', 0);
        }
        else if (type == 2) {
            scanf("%d%d %c", &l2, &r2, &c);
            Rupdate(1, 0, m - 1, l2 - 1, r2 - 1, c - 'a', 1);
        }
        else {
            scanf("%d%d%d%d", &l1, &r1, &l2, &r2);

            ll ans = (r1 - l1 + 2) * (r2 - l2 + 2);

            for (int i = 0; i < 26; i++) {

                // cout << ans << endl;
                ll x = query(1, 0, n - 1, l1 - 1, r1 - 1, i, 0);
                ll y = query(1, 0, m - 1, l2 - 1, r2 - 1, i, 1);

                // cout << char(i + 'a') << " " << x << " " << y << endl;

                ans -= x * y;
            }

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
        // printf("Case %d: ", i);
        solve();
    }
    return 0;
}
