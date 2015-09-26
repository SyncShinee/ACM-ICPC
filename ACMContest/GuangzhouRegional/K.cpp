#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

const int maxn = 100+10;
const int INF = 1e9;

struct  info
{
	int to, w;
	info(int _to = 0, int _w = 0)
	{
		to = _to;
		w = _w;
	}
};

vector<info> G[maxn];
int n, m;
int inq[maxn];
queue<int> q;
int dist[maxn];

int spfa(int s, int t, int k)
{
	memset(inq, 0, sizeof(inq));
	for(int i = 1;i<=n;i++)
		dist[i] = INF;
	inq[s] = 1;
	dist[s] = 0;
	while(!q.empty())
		q.pop();
	q.push(s);
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		inq[u] = 0;
		for(int i = 0;i<G[u].size();i++)
		{
			int v = G[u][i].to, d = G[u][i].w;
			if(v==k)
				continue;
			if(dist[v]>dist[u]+d)
			{
				dist[v] = dist[u]+d;
				if(inq[v]==0)
				{
					inq[v] = 1;
					q.push(v);
				}
			}
		}
	}
	return dist[t];
}
void solve()
{
	int ans = -1;
	for(int i = 2;i<n;i++)
	{
		int tmp = spfa(1, n, i);
		ans = max(ans, tmp);
	}	
	if(ans == INF)
		printf("Inf\n");
	else
		printf("%d\n", ans);
}
int main()
{
	freopen("in.txt", "r", stdin);
	while(scanf("%d%d", &n, &m))
	{
		if(n==0&&m==0)
			break;
		for(int i = 1;i<=n;i++)
			G[i].clear();
		for(int i = 1;i<=m;i++)
		{
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			G[a].push_back(info(b, c));
			G[b].push_back(info(a, c));
		}
		solve();
	}
	return 0;
}