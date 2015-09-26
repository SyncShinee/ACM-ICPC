#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>

using namespace std;

typedef long long ll;

const int maxn = 400+10;
const int M = 1e9+7.1;
const int key = 360;

int f[maxn][maxn], c[maxn][maxn], sum[maxn][maxn];

int add(int a, int b)
{
	int res = a+b;
	if(res > M)
		res -= M;
	return res;
}

void pre()
{
	memset(c, 0, sizeof(c));
	c[0][0] = 1;
	for(int i = 1;i<=key;i++)
	{
		c[i][0] = 1;
		c[i][i] = 1;
		for(int j = 1;j<i;j++)
		{
			c[i][j] = add(c[i-1][j-1],c[i-1][j]);
		}
	}
	memset(f, 0, sizeof(f));
	f[1][1] = 1;
	for(int i = 2;i<=key;i++)
	{
		f[1][i] = 1;
	}
	for(int i = 2;i<=key;i++)
	{
		for(int d = 1;d<=key;d++)
		{
			f[i][d] = (ll)f[i-1][d-1]*(ll)i%M*(ll)2%M;
			for(int j = 1;i-1-j >=1;j++)
			{
				int temp = (ll)i*((ll)c[i-2][j-1])%M;
				f[i][d] = add(f[i][d],  (int)((ll)f[j][d-1]*(ll)f[i-1-j][d-1]%M*(ll)(temp)%M));
			}
		}
	}
}

int main()
{
	freopen("Jin.txt", "r", stdin);
	pre();
	int ncase;
	scanf("%d", &ncase);
	for(int cas = 1;cas <= ncase;cas++)
	{
		printf("Case #%d: ", cas);
		int n, d;
		scanf("%d%d", &n, &d);
		printf("%d\n", ((f[n][d] - f[n][d-1])%M + M )%M );
	}
	return 0;
}