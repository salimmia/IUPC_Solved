// Created by ash_98
#include<bits/stdc++.h>
using namespace std;
#define mx 1000005

int wa[mx], wb[mx], wv[mx], Ws[mx];
//(1-indexed) sa[i] = starting position (0...n-1) of ith lexicographically smallest suffix in s
//(0-indexed) Rank[i] = lexicographical rank of s[i....n-1] ((i+1)th suffix by position)
//LCP[i] = longest common prefix of sa[i] & sa[i-1]
int sa[mx], Rank[mx], LCP[mx];

int cmp(int *r, int a, int b, int l) {return r[a] == r[b] && r[a + l] == r[b + l];}

//Suffix Array (O(nlogn))
//m = maximum possible ASCII value of a string character (alphabet size)
//also, m = maximum number of distinct character in string (when compressed)
void buildSA(string s, int* sa, int n, int m) {
    int i, j, p, *x = wa, *y = wb, *t;
    for (i = 0; i < m; i++) Ws[i] = 0;
    for (i = 0; i < n; i++) Ws[x[i] = s[i]]++;
    for (i = 1; i < m; i++) Ws[i] += Ws[i - 1];
    for (i = n - 1; i >= 0; i--) sa[--Ws[x[i]]] = i;
    for (j = 1, p = 1; p < n; j <<= 1, m = p) {
        for (p = 0, i = n - j; i < n; i++) y[p++] = i;
        for (i = 0; i < n; i++) if (sa[i] >= j) y[p++] = sa[i] - j;
        for (i = 0; i < n; i++) wv[i] = x[y[i]];
        for (i = 0; i < m; i++) Ws[i] = 0;
        for (i = 0; i < n; i++) Ws[wv[i]]++;
        for (i = 1; i < m; i++) Ws[i] += Ws[i - 1];
        for (i = n - 1; i >= 0; i--) sa[--Ws[wv[i]]] = y[i];
        for (t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i++)
            x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
    }
}

//Kasai's LCP algorithm (O(n))
void buildLCP(string s, int *sa, int n) {
    int i, j, k = 0;
    for (i = 1; i <= n; i++) Rank[sa[i]] = i;
    for (i = 0; i < n; LCP[Rank[i++]] = k)
        for (k ? k-- : 0, j = sa[Rank[i] - 1]; s[i + k] == s[j + k]; k++);
    return;
}

// Pattern Subtring hisbe ace kina
bool Pattern(string &text, string &pat)
{
    int lo = 1, hi = text.size();
    while (lo <= hi)
    {
        int mid = (lo + hi) / 2;
        int ok = 0;
        for (int i = 0; i < pat.size(); i++)
        {
            if (text[i + sa[mid]] > pat[i]) {ok = 1; break;}
            if (text[i + sa[mid]] < pat[i]) {ok = -1; break;}
        }
        if (!ok) return true;
        if (ok > 0) hi = mid - 1;
        else lo = mid + 1;
    }
    return false;
}
pair<int, int> Patterntern_occurence(string Text , string Pattern)
{
    int n = Text.size();
    int m = Pattern.size();
    int be = 1, en = n;

    while (be < en)
    {
        int mid = (en + be) / 2;
        int ok = 0;
        for (int i = 0; i < m; i++)
        {
            if (Text[i + sa[mid]] > Pattern[i]) {ok = 1; break;}
            if (Text[i + sa[mid]] < Pattern[i]) {ok = -1; break;}
        }
        if (ok + 1) en = mid;
        else be = mid + 1;
    }

    bool ok = 1;
    for (int i = 0; i < m; i++) if (Text[i + sa[be]] != Pattern[i]) {ok = 0; break;}
    if (!ok) return { -1, -1};

    pair<int, int> re;
    re.first = be;
    be = 1, en = n;
    while (be < en)
    {
        int mid = (en + be) / 2;
        int ok = 0;
        for (int i = 0; i < m; i++)
        {
            if (Text[i + sa[mid]] > Pattern[i]) {ok = 1; break;}
            if (Text[i + sa[mid]] < Pattern[i]) {ok = -1; break;}
        }
        if (ok > 0) en = mid;
        else be = mid + 1;
    }

    ok = 1;
    for (int i = 0; i < m; i++) if (Text[i + sa[en]] != Pattern[i]) {ok = 0; break;}
    if (!ok) en--;
    re.second = en;

    return re;
}
/// this is for LCP from index i to index j.
/// just run a query from min(Rank[i-1],Rank[j-1])+1 to max(Rank[i-1],Rank[j-1])
int ST[mx][22];
int Jump_LOG[mx];

void Build_Sparse(int n)
{
    for (int i = 1; i <= n; i++)ST[i][0] = LCP[i];

    for (int i = 2; i <= n; i++)Jump_LOG[i] = Jump_LOG[i - 1] + !(i & (i - 1));

    for (int j = 1; (1 << j) <= n; j++)
    {
        for (int i = 1; (i + (1 << j) - 1) <= n; i++)
        {
            ST[i][j] = min(ST[i][j - 1], ST[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int query(int i, int j)
{
    int boro_lav = Jump_LOG[j - i + 1];
    return min(ST[i][boro_lav], ST[j - (1 << boro_lav) + 1][boro_lav]);
}

vector<int>g[100005];
char ch[mx];
typedef long long ll;

ll dp[mx], Visit[mx], n, tt;

ll fnc(int pos)
{
    // cout << pos << " ";
    if (pos >= n) {
        // cout << pos << " ";
        if (pos == n) return 0;
        return INT_MAX;
    }
    if (Visit[pos] == tt) return dp[pos];
    Visit[pos] = tt;

    ll ret = INT_MAX;

    if (g[pos].size() == 0) return dp[pos] = ret;

    for (int i = 0; i < g[pos].size(); i++) {
        ret = min(ret, fnc(g[pos][i]) + 1);
    }

    return dp[pos] = ret;
}

void solve()
{
    string s;

    int q;

    scanf("%d", &q);

    string pat[q + 5];

    for (int i = 0; i < q; i++) {
        scanf("%s", ch);
        pat[i] = ch;
        // cout << pat[i] << endl;
    }

    scanf("%s", ch);

    s = ch;

    // cout << s << endl;

    n = s.size();
    buildSA(s, sa, n + 1, 130); //Important
    buildLCP(s, sa, n);
    // for (int i = 1; i <= n; i++) cout << sa[i] << " "; cout << endl;
    // for (int i = 0; i < n; i++) cout << Rank[i] << " "; cout << endl;
    // for (int i = 1; i <= n; i++) cout << LCP[i] << " ";
    // printf("\n");

    for (int i = 0; i < q; i++)
    {
        pair<int, int>re = Patterntern_occurence(s, pat[i]);
        if (re.second == -1) continue;

        for (int j = re.first; j <= re.second; j++) {
            g[sa[j]].push_back(sa[j] + pat[i].size());
        }
    }

    // for (int i = 0; i < n; i++) {
    //     cout << i << "   ";
    //     for (auto v : g[i]) {
    //         cout << v << " ";
    //     }
    //     cout << endl;
    // }

    // queue<int>Q;

    // Q.push(0);

    // vector<int>dis(n + n, 1e9);
    // vector<bool>vis(n + 1, false);

    // vis[0] = true;

    // dis[0] = 0;

    // while (!Q.empty()) {
    //     int u = Q.front();
    //     Q.pop();

    //     for (auto v : g[u]) {
    //         if (!vis[v]) {
    //             vis[v] = true;
    //             Q.push(v);
    //             dis[v] = dis[u] + 1;
    //         }
    //     }
    // }

    ll ans = fnc(0);

    if (ans >= INT_MAX) {
        printf("impossible\n");
        return;
    }

    printf("%d\n", ans);

    for (int i = 0; i <= n; i++) {
        g[i].clear();
    }
}

int main()
{
    int t = 1;
    tt = 1;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        printf("Case %d: ", i);
        solve();
        tt++;
    }
    return 0;
}
