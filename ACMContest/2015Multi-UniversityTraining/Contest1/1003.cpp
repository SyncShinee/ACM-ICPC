#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
#include <ctype.h>
#include <limits.h>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <stack>
#include <set>
#include <bitset>
#define CLR(a) memset(a, 0, sizeof(a))
#define REP(i, a, b) for(int i = a;i < b;i++)
#define REP_D(i, a, b) for(int i = a;i <= b;i++)

typedef long long ll;

using namespace std;

const int maxn = 1e5 + 10;
const int maxDist = 100+10;
const int INF = 1e8+100;
int n, w[maxn];
vector<int> G[maxn];
int f[maxn][maxDist], g[maxn][maxDist];

void dfs(int u, int fa)
{
    REP(i, 0, G[u].size())
    {
        int v = G[u][i];
        if(v!=fa)
        {
            dfs(v, u);
        }
    }
    for(int i = 0;i<=100;i++)
    {
        f[u][i] = INF;
        int a, b;
        if(w[u]>=i)
        {
            b = 1;
        }
        else
        {
            b = INF;
        }
        a = 0;
        REP(j, 0, G[u].size())
        {
            int v = G[u][j];
            if(v!=fa)
            {
                int t = f[v][i+1];//简单的横叉转移
                if(t!=INF)
                {
                    b = min(b+g[v][i] , a+t);
                }
                else
                {
                    b = b + g[v][i];
                }
                a += g[v][i];
            }
        }
        f[u][i] = b;

        g[u][i] = INF;//g的转移也很简单
        if(i>=1)
        {
            a = 0;
        }
        else
        {
            a = 1;
        }
        REP(j, 0, G[u].size())
        {
            int v = G[u][j];
            if(v!=fa)
            {
                int limit = max(0, i-1);
                int t = g[v][limit];
                a += t;
            }
        }
        g[u][i] = a;
    }

    f[u][101] = INF;
    g[u][101] = INF;
    for(int i = 100;i>=0;i--)//关键理解:我们定义的f和g有实际意义.
    {
        f[u][i] = min(f[u][i], f[u][i+1]);
    }
    g[u][0] = min(g[u][0], f[u][0]);
    for(int i = 1;i<=100;i++)
    {
        g[u][i] = min(g[u][i], g[u][i-1]);
    }
}
void solve()
{
    dfs(1, 0);
    printf("%d\n", g[1][0]);
}

int main()
{
    while(scanf("%d", &n) != EOF)
    {
        REP_D(i, 1, n)
        {
            scanf("%d", &w[i]);
        }
        REP_D(i,1,n)
        {
            G[i].clear();
        }
        REP_D(i, 1, n-1)
        {
            int a, b;
            scanf("%d%d", &a, &b);
            G[a].push_back(b);
            G[b].push_back(a);
        }
        solve();
    }
    return 0;
}