#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

const int maxn = 5e4 + 100;
double x[maxn], w[maxn];
int n;

double calcu(double key)
{
	double ans = 0;
	for(int i = 1;i<=n;i++)
	{
		double t = fabs(x[i] - key);
		t = t*t*t*w[i];
		ans += t;
	}
	return ans;
}

void solve()
{
	double l = -1e6, r = 1e6, mid, midmid, ansMid, ansMidMid;
	while(fabs(r - l) > 1e-6)
	{
		 mid = (l+r)/2;
		 midmid = (l+mid)/2;
		 ansMid = calcu(mid);
		 ansMidMid = calcu(midmid);
		if(ansMid > ansMidMid)
		{
			r = mid;
		}
		else
		{
			l = midmid;
		}
	}
	//double ans = (ansMid + 0.5 + 1e-9);
	//ans = 2.6;
	printf("%.0f\n", ansMid);
}
int main()
{
	int t;
	scanf("%d", &t);
	for(int _ = 1;_<=t;_++)
	{
		printf("Case #%d: ", _);
		scanf("%d", &n);
		for(int i = 1;i<=n;i++)
		{
			scanf("%lf%lf", &x[i], &w[i]);
		}
		solve();
	}
}