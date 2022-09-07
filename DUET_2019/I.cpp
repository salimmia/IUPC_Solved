/* Tested by https://codeforces.com/contest/1200/problem/E */

#include<bits/stdc++.h>
using namespace std;

#define mx 1000005
#define ll long long

int n, m, ii, k;
char ch[mx], ch1[mx];
/*
backup prime
307,367
1040160883,1066517951
1e9+7,1e9+9,1072857881,1000004249
*/

ll P[mx];

void precal()
{
    P[0] = 1;
    for (int i = 1; i < mx; i++)P[i] = (1949313259 * P[i - 1]) % 2091573227;
}

struct Hash_dui
{
    ll base, mod;
    int sz;
    vector<int>Rev, Forw;
    Hash_dui() {}
    Hash_dui(const char* s, ll b, ll m)
    {
        sz = strlen(s), base = b, mod = m;
        Rev.resize(sz + 2, 0), Forw.resize(sz + 2, 0);
        for (int i = 1; i <= sz; i++)Forw[i] = (Forw[i - 1] * base + (s[i - 1] - 'a' + 1)) % mod; /// digit hole s[i-1]-'0'
        for (int i = sz; i >= 1; i--)Rev[i] = (Rev[i + 1] * base + (s[i - 1] - 'a' + 1)) % mod; ///alphabet hole s[i-1]-'a'
    }

    inline int Range_Hash(int l, int r)
    {
        int re_hash = Forw[r + 1] - ((ll)P[r - l + 1] * Forw[l] % mod);
        if (re_hash < 0)re_hash += mod;
        return re_hash;
    }
    inline int Reverse_Hash(int l, int r)
    {
        int re_hash = Rev[l + 1] - ((ll)P[r - l + 1] * Rev[r + 2] % mod);
        if (re_hash < 0)re_hash += mod;
        return re_hash;
    }
};
struct Hash_Main
{
    Hash_dui h1, h2;
    Hash_Main() {}
    Hash_Main(const char* s)
    {
        h1 = Hash_dui(s, 1949313259, 2091573227);
        // h2 = Hash_dui(s, 1997293877, 2117566807);
    }

    inline ll Range_Hash(int l, int r) /// O base index
    {
        return (ll)h1.Range_Hash(l, r);
    }
};

Hash_Main charhash[16];

void solve()
{
    int n;
    scanf("%s", ch);
    n = strlen(ch);
    string re = ch;
    Hash_Main h_ek(ch);

    vector<ll>hash[17];

    for (int j = 0; j < 17; j++) {
        for (int i = 0; i + (1 << j) - 1 < n; i++) {
            hash[j].push_back(h_ek.Range_Hash(i, i + (1 << j) - 1));
        }
    }

    for (int j = 0; j < 17; j++) {
        sort(hash[j].begin(), hash[j].end());
        // for (int i = 0; i + (1 << j) - 1 < n; i++) {
        //     cout << hash[j][i] << " ";
        // }
        // if (hash[j].size() > 0) cout << endl;
    }

    int q;

    scanf("%d", &q);

    while (q--) {
        scanf("%s", ch);

        int m = strlen(ch);

        ll ans = 0;

        int bit;

        for (int i = 0; i < 17; i++) {
            if ((m >> i) & 1) {
                bit = i;
                break;
            }
        }

        Hash_Main tmp(ch);

        for (int i = 0; i < m; i++) {
            ll prehash = 0, midhash = 0, suffixhash = 0;
            if (i > 0) prehash = tmp.Range_Hash(0, i - 1);
            if (i < m - 1) suffixhash = tmp.Range_Hash(i + 1, m - 1);
            for (int j = 0; j < 16; j++) {
                if (char(j + 'a') == ch[i]) continue;

                midhash = charhash[j].Range_Hash(0, 0);

                ll tothash = ((prehash * 1949313259) % 2091573227 + midhash) % 2091573227;
                // cout << P[m - i - 1] << " ";

                tothash = ((tothash * P[m - i - 1]) % 2091573227 + suffixhash % 2091573227) % 2091573227;

                ans += upper_bound(hash[bit].begin(), hash[bit].end(), tothash) - lower_bound(hash[bit].begin(), hash[bit].end(), tothash);
            }
        }
        ll tothash = tmp.Range_Hash(0, m - 1);

        ans += upper_bound(hash[bit].begin(), hash[bit].end(), tothash) - lower_bound(hash[bit].begin(), hash[bit].end(), tothash);
        printf("%lld\n", ans);
    }
}

int main()
{
    int t = 1;

    precal();

    for (int i = 0; i < 16; i++) {
        char ch[1];
        ch[0] = char(i + 'a');
        Hash_Main tmp(ch);
        charhash[i] = tmp;
        // cout << charhash[i].Range_Hash(0, 0) << endl;
    }

    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        printf("Case %d:\n", i);
        solve();
    }
    return 0;
}

/*
#include<bits/stdc++.h>
using namespace std;

#define mx 1000005
#define ll long long

int n, m, ii, k;
char ch[mx], ch1[mx];

struct Hash_dui
{
    ll base, mod;
    int sz;
    vector<int>Rev, Forw, P;
    Hash_dui() {}
    Hash_dui(const char* s, ll b, ll m)
    {
        sz = strlen(s), base = b, mod = m;
        Rev.resize(sz + 2, 0), Forw.resize(sz + 2, 0), P.resize(sz + 2, 1);
        for (int i = 1; i <= sz; i++)P[i] = (base * P[i - 1]) % mod;
        for (int i = 1; i <= sz; i++)Forw[i] = (Forw[i - 1] * base + (s[i - 1] - 'a' + 1)) % mod; /// digit hole s[i-1]-'0'
        for (int i = sz; i >= 1; i--)Rev[i] = (Rev[i + 1] * base + (s[i - 1] - 'a' + 1)) % mod; ///alphabet hole s[i-1]-'a'
    }
    void Single_char_ad(char cc)
    {
        P.push_back((P.back()*base) % mod);
        Forw.push_back((Forw.back()*base + (cc - 'a' + 1)) % mod);
    }
    inline int Range_Hash(int l, int r)
    {
        int re_hash = Forw[r + 1] - ((ll)P[r - l + 1] * Forw[l] % mod);
        if (re_hash < 0)re_hash += mod;
        return re_hash;
    }
    inline int Reverse_Hash(int l, int r)
    {
        int re_hash = Rev[l + 1] - ((ll)P[r - l + 1] * Rev[r + 2] % mod);
        if (re_hash < 0)re_hash += mod;
        return re_hash;
    }
};
struct Hash_Main
{
    Hash_dui h1, h2;
    Hash_Main() {}
    Hash_Main(const char* s)
    {
        h1 = Hash_dui(s, 1949313259, 2091573227);
        // h2 = Hash_dui(s, 1997293877, 2117566807);
    }
    void Char_Add(char cc)
    {
        h1.Single_char_ad(cc);
        // h2.Single_char_ad(cc);
    }
    inline ll Range_Hash(int l, int r) /// O base index
    {
        return (ll)h1.Range_Hash(l, r);
    }

};

Hash_Main charhash[16];

void solve()
{
    int n;
    scanf("%s", ch);
    n = strlen(ch);
    string re = ch;
    Hash_Main h_ek(ch);

    vector<ll>hash[17];

    for (int j = 0; j < 17; j++) {
        for (int i = 0; i + (1 << j) - 1 < n; i++) {
            hash[j].push_back(h_ek.Range_Hash(i, i + (1 << j) - 1));
        }
    }

    for (int j = 0; j < 17; j++) {
        sort(hash[j].begin(), hash[j].end());
        // for (int i = 0; i + (1 << j) - 1 < n; i++) {
        //     cout << hash[j][i] << " ";
        // }
        // if (hash[j].size() > 0) cout << endl;
    }

    int q;

    scanf("%d", &q);

    while (q--) {
        scanf("%s", ch);

        int m = strlen(ch);

        ll ans = 0;

        int bit;

        for (int i = 0; i < 17; i++) {
            if ((m >> i) & 1) {
                bit = i;
                break;
            }
        }

        Hash_Main tmp(ch);

        for (int i = 0; i < m; i++) {
            ll prehash = 0, midhash = 0, suffixhash = 0;
            if (i > 0) prehash = tmp.Range_Hash(0, i - 1);
            if (i < m - 1) suffixhash = tmp.Range_Hash(i + 1, m - 1);
            for (int j = 0; j < 16; j++) {
                if (char(j + 'a') == ch[i]) continue;

                midhash = charhash[j].Range_Hash(0, 0);

                ll tothash = ((prehash * 1949313259) % 2091573227 + midhash) % 2091573227;

                tothash = ((tothash * tmp.h1.P[m - i - 1]) % 2091573227 + suffixhash % 2091573227) % 2091573227;

                ans += upper_bound(hash[bit].begin(), hash[bit].end(), tothash) - lower_bound(hash[bit].begin(), hash[bit].end(), tothash);
            }
        }
        ll tothash = tmp.Range_Hash(0, m - 1);

        ans += upper_bound(hash[bit].begin(), hash[bit].end(), tothash) - lower_bound(hash[bit].begin(), hash[bit].end(), tothash);
        printf("%lld\n", ans);
    }

    // int sz = re.size();
    // for (int i = 2; i <= n; i++)
    // {
    //     scanf("%s", ch1);
    //     Hash_Main h_dui(ch1);
    //     int sz2 = strlen(ch1);

    //     int jabe = 0;
    //     for (int j = 1; j <= min(sz, sz2); j++)
    //     {
    //         if (h_ek.Range_Hash(sz - j, sz - 1) == h_dui.Range_Hash(0, j - 1))jabe = j;
    //     }
    //     for (int j = jabe; j < sz2; j++)h_ek.Char_Add(ch1[j]), sz++, re += ch1[j];
    // }
    // cout << re << "\n";
}

int main()
{
    int t = 1;

    for (int i = 0; i < 16; i++) {
        char ch[1];
        ch[0] = char(i + 'a');
        Hash_Main tmp(ch);
        charhash[i] = tmp;
        // cout << charhash[i].Range_Hash(0, 0) << endl;
    }

    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        printf("Case %d:\n", i);
        solve();
    }
    return 0;
}
*/
