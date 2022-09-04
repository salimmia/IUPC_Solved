#include<bits/stdc++.h>
using namespace std;

#define mx 200005
#define ll long long
#define mod 1000000007 //998244353
typedef double Tf;

int a[mx];
char ch[mx];
int n, m, ii, k;

void solve()
{
	while (1) {
		Tf l, w;
		scanf("%lf%lf", &l, &w);

		if ((int)l == 0 && (int)w == 0) break;

		Tf ce = w, ac = l;

		Tf now = l + w;

		Tf lo = l / 2, hi = l;

		for (int i = 0; i < 100; i++) {
			Tf mid = (lo + hi) / 2;

			Tf bd = mid;
			Tf ab = mid;
			Tf bc = l - ab;
			Tf cd = sqrt(bd * bd - bc * bc);

			Tf de = w - cd;


			Tf tot = ab + bd + de;

			if (tot < now) {
				hi = mid;
				now = tot;
			}
			else lo = mid;
		}

		// printf("%lf\n", w);

		printf("%.4lf\n", now);
	}

	return;
}

int main()
{
	int t = 1;
	// scanf("%d", &t);
	for (int i = 1; i <= t; i++) {
		// printf("Case %d: ", i);
		solve();
	}
	return 0;
}
