#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 1e5 + 100;
int n,  ans[maxn], m, b[maxn];
struct node
{
  int a, id;
  node(int _a = 0, int _id = 0)
  {
    a = _a;
    id = _id;
  }
};
node d[maxn];
struct Edge
{
  int u, v, id;
  Edge(int _u = 0, int _v = 0, int _id = 0)
  {
    u = _u;
    v = _v;
    id = _id;
  }
};
Edge edge[maxn];
bool cmp(node a, node b)
{
  return a.a < b.a;
}

void solve()
{
 for(int i = 1; i <= n; i++)
    {
      d[i].a = 0;
      d[i].id = i;
    }
 
  int cnt = 0;
  for(int i = 1; i <= m; i++)
    {
    if(edge[i].u != 1 && edge[i].v != 1)
      {
	ans[i] = ++cnt;
	d[edge[i].u].a += cnt;
	d[edge[i].v].a += cnt;
      }
    else
      {
	if(edge[i].u != 1)
	  b[edge[i].u] = i;
	else
	  b[edge[i].v] = i;
      }
    }
  sort(d + 1, d + 1 + n, cmp);
  for(int i = 1; i <= n; i++)
    {
      if(d[i].id != 1)
	{
	  ans[b[d[i].id]] = ++cnt;
	}
    }
  printf("Yes\n");
  for(int i = 1; i <= m; i++)
    {
      printf("%d ", ans[i]);
    }
  printf("\n");
}
int main()
{
  freopen("flights.in", "r", stdin);
  freopen("flights.out", "w", stdout);
  while(scanf("%d%d", &n, &m) != EOF && (n | m))
    {
      for(int i = 1; i <= m; i++)
	{
	  scanf("%d%d", &edge[i].u, &edge[i].v);
	}
      solve();
    }
    return 0;
}
