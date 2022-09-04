#include<bits/stdc++.h>
using namespace std;

#define mx 200005
#define ll long long
#define mod 1000000007 //998244353

int a[mx];
char ch[mx];
int n, m, ii, k;

void solve()
{
    scanf("%d%d%d", &n, &m, &k);
    int kk = 1;

    //cout << n << " " << m << " " << k <<

    int x = (n + m + k);


    if (x % 3 == 0) {
        x = x / 3;

        int dif1 = abs(n - x), dif2 = abs(m - x), dif3 = abs(k - x);

        bool ok = false;

        // cout << dif1 << " " << dif2 << " " << dif3 << endl;
        // cout << "kk : " << kk << endl;

        if ((dif1 % kk == 0) and (dif2 % kk) == 0 and (dif3 % kk) == 0)
        {
            ok = true;
        }

        if (ok)
        {
            printf("Peaceful\n");
        }
        else
        {
            printf("Fight\n");
        }


    }
    else printf("Fight\n");

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
