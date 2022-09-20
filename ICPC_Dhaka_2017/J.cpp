///Creater by Salim_JnU

#include<bits/stdc++.h>
using namespace std;

#define mx 200005
#define ll long long
#define mod 1000000007 //998244353

int a[mx];
char ch[mx];
int n, m, tt, k;

int wa[mx], wb[mx], wv[mx], Ws[mx];
//(1-indexed) sa[i] = st_lcparting position (0...n-1) of ith lexicographically smallest_lcp suffix in s
//(0-indexed) Rank[i] = lexicographical rank of s[i....n-1] ((i+1)th suffix by position)
//LCP[i] = longest_lcp common prefix of sa[i] & sa[i-1]
int sa[mx], Rank[mx], LCP[mx];

int cmp(int *r, int a, int b, int l) {return r[a] == r[b] && r[a + l] == r[b + l];}

//Suffix Array (O(nlogn))
//m = maximum possible ASCII value of a string character (alphabet size)
//also, m = maximum number of dist_lcpinct character in string (when compressed)
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

/// this is for LCP from index i to index j.
/// just_lcp run a query from min(Rank[i-1],Rank[j-1])+1 to max(Rank[i-1],Rank[j-1])
int st_lcp[mx][22], st_sa[mx][22];
int Jump_LOG[mx];

void Build_Sparse(int n)
{
    for (int i = 1; i <= n; i++)st_lcp[i][0] = LCP[i], st_sa[i][0] = sa[i];

    for (int i = 2; i <= n; i++)Jump_LOG[i] = Jump_LOG[i - 1] + !(i & (i - 1));

    for (int j = 1; (1 << j) <= n; j++)
    {
        for (int i = 1; (i + (1 << j) - 1) <= n; i++)
        {
            st_lcp[i][j] = min(st_lcp[i][j - 1], st_lcp[i + (1 << (j - 1))][j - 1]);
            st_sa[i][j] = min(st_sa[i][j - 1], st_sa[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int query_lcp(int i, int j)
{
    int boro_lav = Jump_LOG[j - i + 1];
    return min(st_lcp[i][boro_lav], st_lcp[j - (1 << boro_lav) + 1][boro_lav]);
}

int query_sa(int i, int j)
{
    int boro_lav = Jump_LOG[j - i + 1];
    return min(st_sa[i][boro_lav], st_sa[j - (1 << boro_lav) + 1][boro_lav]);
}

vector<int>Tree1[mx * 4], Tree2[4 * mx];

void init(int node, int be, int en) {
    Tree1[node].clear();
    Tree2[node].clear();
    if (be == en) {
        Tree1[node].push_back(LCP[be]);
        Tree2[node].push_back(n - sa[be]);
        return;
    }
    int mid = (be + en) / 2;
    init(node * 2, be, mid);
    init(node * 2 + 1, mid + 1, en);
    merge(Tree1[node * 2].begin(), Tree1[node * 2].end(), Tree1[node * 2 + 1].begin(), Tree1[node * 2 + 1].end(), back_inserter(Tree1[node]));
    merge(Tree2[node * 2].begin(), Tree2[node * 2].end(), Tree2[node * 2 + 1].begin(), Tree2[node * 2 + 1].end(), back_inserter(Tree2[node]));
}

int query_sa_baad(int node, int be, int en, int i, int j, int val) {
    if (be > j or en < i)return 0;
    if (be >= i and en <= j) {
        int small = lower_bound(Tree2[node].begin(), Tree2[node].end(), val) - Tree2[node].begin();
        return small;
    }
    int mid = (be + en) / 2;
    return query_sa_baad(node * 2, be, mid, i, j, val) + query_sa_baad(node * 2 + 1, mid + 1, en, i, j, val);
}

int query_lcp_baad(int node, int be, int en, int i, int j, int val) {
    if (be > j or en < i)return 0;
    if (be >= i and en <= j) {
        int sz = en - be + 1;
        int small = lower_bound(Tree1[node].begin(), Tree1[node].end(), val) - Tree1[node].begin();
        return sz - small;
    }
    int mid = (be + en) / 2;
    return query_lcp_baad(node * 2, be, mid, i, j, val) + query_lcp_baad(node * 2 + 1, mid + 1, en, i, j, val);
}

void solve()
{
    scanf("%s", ch);
    string s = ch;
    n = s.size();
    buildSA(s, sa, n + 1, 130); //Important
    buildLCP(s, sa, n);
    Build_Sparse(n);
    // for (int i = 1; i <= n; i++) cout << sa[i] << " "; cout << endl;
    // for (int i = 0; i < n; i++) cout << Rank[i] << " "; cout << endl;
    // for (int i = 1; i <= n; i++) cout << LCP[i] << " "; cout << endl;
    int q;

    init(1, 1, n);

    scanf("%d", &q);
    for (int i = 1; i <= q; i++)
    {
        int len, Mth;

        scanf("%d%d", &len, &Mth);

        int lo = 1, hi = n, got = -1;

        while (lo <= hi) {
            int mid = (lo + hi) / 2;

            int baad = query_sa_baad(1, 1, n, 1, mid, len) + query_lcp_baad(1, 1, n, 1, mid, len);

            if (mid - baad >= Mth) {
                got = mid;
                hi = mid - 1;
            }
            else lo = mid + 1;
        }
        if (got == -1) {
            printf("Not found\n");
        }
        else {
            int lo = got + 1, hi = n, next = got;

            while (lo <= hi) {
                int mid = (lo + hi) / 2;

                if (query_lcp(got + 1, mid) >= len) {
                    next = mid;
                    lo = mid + 1;
                }
                else hi = mid - 1;
            }
            printf("%d\n", query_sa(got, next));
        }
    }
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
