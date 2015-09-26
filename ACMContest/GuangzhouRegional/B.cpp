#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

const int maxn = 200+10;
int fx[maxn][maxn], fy[maxn][maxn];
int n, x[maxn], y[maxn], have[maxn][maxn];
int bx[maxn], by[maxn], bxn, byn;
vector<int> xl[maxn][maxn];

int check(int i, int j, int k, int z)
{
	if(have[i][k]&&have[i][z]&&have[j][k]&&have[j][z])
		return 1;
	return 0;
}
int check(int i, int j, int k)
{
	if(have[i][k]&&have[j][k])
		return 1;
	return 0;
}

void solve()
{
	memset(have, 0, sizeof(have));
	bxn = byn = 0;
	for(int i = 0;i<n;i++)
	{
		have[x[i]][y[i]] = 1;
		bx[bxn] = x[i];
		bxn++;
		by[byn] = y[i];
		byn++;
	}
	sort(bx, bx+bxn);
	sort(by, by+byn);
	bxn = unique(bx, bx+bxn) - bx;
	byn = unique(by, by+byn) - by;
	for(int i = 0;i<bxn;i++)
		for(int j = i+1;j<bxn;j++)
		{
			xl[i][j].clear();
		}
	memset(fx, 0, sizeof(fx));
	memset(fy, 0, sizeof(fy));
	for(int i = 0;i<bxn;i++)
		for(int j = i+1;j<bxn;j++)
			for(int k = 0;k<byn;k++)
				{for(int z = k+1;z<byn;z++)
				{
					
					int s = (bx[j]-bx[i])*(by[z]-by[k]);
					if(check(bx[i], bx[j], by[k], by[z]))
					{
						fx[i][j] = max(fx[i][j], s);
						fy[k][z] = max(fy[k][z], s);
					}
				}
				if(check(bx[i], bx[j], by[k]))
					{
						xl[i][j].push_back(k);
					}

			}
	int ans = 0;
	for(int i = 0;i<bxn;i++)
		for(int j = i+1;j<bxn;j++)
			for(int k = j+1;k<bxn;k++)
				for(int z = k+1;z<bxn;z++)
				{
					if(fx[i][j]&&fx[k][z])
						ans = max(ans, fx[i][j]+fx[k][z]);
				}
	for(int i = 0;i<byn;i++)
		for(int j = i+1;j<byn;j++)
			for(int k = j+1;k<byn;k++)
				for(int z = k+1;z<byn;z++)
				{
					if(fy[i][j]&&fy[k][z])
						ans = max(ans, fy[i][j]+fy[k][z]);
				}
	for(int i = 0;i<bxn;i++)
		for(int j = i+1;j<bxn;j++)
			for(int k = j+1;k<bxn;k++)
				for(int z = k+1;z<bxn;z++)
				{

					if(xl[i][z].size()>=2&&xl[j][k].size()>=2)
					{
						int kmin = xl[i][z][0], kmax = xl[i][z][xl[i][z].size()-1];
						int ki = upper_bound(xl[j][k].begin(), xl[j][k].end(), kmin) - xl[j][k].begin();
						int kj = lower_bound(xl[j][k].begin(), xl[j][k].end(), kmax) - xl[j][k].begin() - 1;
						//printf("dsafdsa%d  %d  %d  %d\n", kmin, kmax, ki, kj);
						if(ki < kj)
						{
							int s = (bx[z] - bx[i])*(by[kmax] - by[kmin]);
							ans = max(ans, s);
						}
					}
				}
	if(ans == 0)
	{
		printf("imp\n");
	}
	else
	{
		printf("%d\n", ans);
	}
}

int main()
{
	freopen("in.txt", "r", stdin);
	while(scanf("%d", &n))
	{
		if(n==0)
			break;
		for(int i = 0;i<n;i++)
			scanf("%d%d", &x[i], &y[i]);
		solve();
	}
	return 0;
}