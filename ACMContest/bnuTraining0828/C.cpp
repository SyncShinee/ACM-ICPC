#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

typedef long long ll;

const int maxn = 1024 + 100;
ll f[20][20][maxn];
int vis[20][20][maxn];
int s[20];

int getNewSta(int sta, int x)
{
	int tmp = -1;
	int newSta;
	for(int i = 9;i>=x;i--)
	{
		if((1<<i)&sta)
		{
			tmp = i;
		}
	}
	if(tmp == -1)
	{
		newSta = (sta|(1<<x));
	}
	else
	{
		newSta = sta - (1<<tmp);
		newSta = (newSta|(1<<x));
	}
	return newSta;
}
ll dfs(int pos, int k, int sta, int first, int limit)
{
	if(pos < 0)
	{
		//printf("sta is %d k is %d\n", sta, k);
		if(first)
			return 0;
		int cnt = 0;
		for(int i = 0;i<10;i++)
		{
			if((1<<i)&sta)
			{
				cnt++;
			}
		}
		if(cnt==k)
			return 1;
		return 0;
	}
	if(!limit&&!first&&vis[pos][k][sta])
		return f[pos][k][sta];
	int key = 9;
	if(limit)
		key = s[pos];
	ll ans = 0;
	for(int i = 0;i<=key;i++)
	{
		int newSta;
		if(first && i == 0)
		{
			newSta = 0;
		}
		else
		{
			newSta = getNewSta(sta, i);
		}
		ans += dfs(pos-1, k, newSta, (first&&i==0), (limit&&i == key) );
	}
	if(!limit && !first)
	{
		vis[pos][k][sta] = 1;
		f[pos][k][sta] = ans;
	}
	return ans;
}

ll solve(ll x, int k)
{
	memset(s, 0, sizeof(s));
	int sn = 0;
	while(x != 0)
	{
		s[sn] = x%10;
		sn++;
		x /= 10;
	}
	sn--;
	ll ans = dfs(sn, k, 0, 1, 1);
	return ans;
}
ll l, r, k, ans;
int main()
{
	freopen("Cin.txt", "r", stdin);
	memset(vis, 0, sizeof(vis));
	int ncase;
	scanf("%d", &ncase);
	for(int cas = 1;cas<=ncase;cas++)
	{
		printf("Case #%d: ", cas);
		scanf("%I64d%I64d%I64d", &l, &r, &k);
		ans = 0;
		ans = solve(r, k);
		if(l!=1)
		{
			ans -= solve(l-1, k);
		}
		printf("%I64d\n", ans);
	}
	return 0;
}