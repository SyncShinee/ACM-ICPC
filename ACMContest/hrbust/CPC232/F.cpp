#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define oo 2014083016
using namespace std;
int f[1024][128][10], a[1024], n, p, ans;
int calc(int x, int d1, int d2) 
{
	if ((a[x-1] >> d1) == (a[x] >> d2))
		return a[x] >> d2;
	else
		return 0;
}
int main() 
{
	int T;
	scanf("%d", &T);
	while (T--) 
	{
		scanf("%d%d", &n, &p);
		memset(f, 0, sizeof(f));
		for (int i = 1; i <= n; i ++) 
		{
			scanf("%d", &a[i]);
			for (int j = 0; j <= p; j ++)
			{
				for (int k = 0; k <= 8; k ++) 
				{
					f[i][j][k] = oo;
					if (k > j)
						break;
					for (int t = 0; t <= 8; t ++) 
					{
						if (t > j-k)
							break;
						if (f[i][j][k] > f[i-1][j-k][t] + (a[i] >> k) + calc(i, t, k))
							f[i][j][k] = f[i-1][j-k][t] + (a[i] >> k) + calc(i, t, k);
					}
				}
			}
		}
		ans = oo;
		for (int i = 0; i <= p; i ++)
			for (int j = 0; j <= 8; j ++)
			{
				if (j > i)
					break;
				ans = min(ans, f[n][i][j]);
			}
		printf("%d\n", ans);
	}	
	return 0;
}