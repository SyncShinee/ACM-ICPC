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

const int maxn = 500000+100;
int dp[maxn][2];
int n;
int w[maxn];
vector<int> G[maxn];

void dfs(int u, int fa)
{
    dp[u][0] = 1;
    dp[u][1] = 0;
    REP(i, 0, G[u].size())
    {
        int v = G[u][i];
        if(v!=fa)
        {
            dfs(v, u);
        }
    }
    int t = 0;
    REP(i, 0, G[u].size())
    {
        int v = G[u][i];
        if(v!=fa)
        {
            if(w[v] > w[u])
            {
              t += dp[v][0];
            }
        }
    }
    t++;
    dp[u][0] = t;
    int a = t;
    REP(i, 0, G[u].size())
    {
        int v = G[u][i];
        if(v!=fa)
        {
            if(w[v]<w[u])
            {
                int tt = max(dp[v][0], dp[v][1]);
                if(t + tt>a)
                {
                    a = t+tt;
                }
            }
        }
    }
    dp[u][1] = a;
}

void solve()
{
    dfs(1, 0);
    int ans = 0;
    REP_D(i, 1, n)
    {
        ans = max(dp[i][0], ans);
        ans = max(dp[i][1], ans);
    }
    printf("%d\n", ans);
}

int main()
{
    while(scanf("%d", &n) != EOF)
    {
        REP_D(i, 1, n)
        {
            scanf("%d", &w[i]);
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