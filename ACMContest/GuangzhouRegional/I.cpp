#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <cmath>

using namespace std;

const int maxn = 100+10;
const int maxS = (1<<12)+100;
const double EPS = 1e-10;

double a[maxn], f[maxS];
int n;

int check(double a, double b, double c)
{
	if(a+b>c+EPS&&a+c>b+EPS&&b+c>a+EPS)
		return 1;
	return 0;
}
double calcu(double a, double b, double c)
{
	double p = (a+b+c)/2;
	double ans;
	ans = sqrt(p*(p-a)*(p-b)*(p-c));
	return ans;
}
int solve()
{
	int key = (1<<n);
	for(int s = 0;s<key;s++)
	{
		f[s] = -1;
	}
	f[0] = 0;
	for(int s = 0;s<key;s++)
	{
		if(fabs(f[s]-(-1)) < EPS)
			continue;
		for(int i = 0;i<n;i++)
		{
			if((1<<i)&s)
				continue;
			for(int j = i+1;j<n;j++)
			{
				if((1<<j)&s)
					continue;
				for(int k = j+1;k<n;k++)
				{
					if((1<<k)&s)
						continue;
					if(check(a[i], a[j], a[k]))
					{
						f[s|(1<<i)|(1<<j)|(1<<k)] = max(f[s|(1<<i)|(1<<j)|(1<<k)], f[s]+calcu(a[i], a[j], a[k]));
					}
				}
			}
		}
	}
	double ans = 0;
	for(int i = 0;i<key;i++)
		ans = max(ans, f[i]);
	printf("%.2f\n", ans);
}

int main()
{
	freopen("in.txt", "r", stdin);
	while(scanf("%d", &n))
	{
		if(n==0)
			break;
		for(int i = 0;i<n;i++)
		{
			scanf("%lf", &a[i]);
		}
		solve();
	}
	return 0;
}