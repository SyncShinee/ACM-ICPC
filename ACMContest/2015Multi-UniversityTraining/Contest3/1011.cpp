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

const int maxn = 100+10;
int n, k;
int vis[maxn];
vector<int> G[maxn];
int dp[maxn];
int ans;

void dfs(int u, int fa)
{
    dp[u] = 1;
    REP(i, 0, G[u].size())
    {
        int v = G[u][i];
        if(v!=fa)
        {
            dfs(v, u);
            dp[u] += dp[v];
        }
    }
    if(dp[u]==k+1)
    {
        ans++;
    }
}

int main()
{
    //freopen("11Kin.txt", "r", stdin);
    //freopen("1out.txt", "w", stdout);
    while(scanf("%d%d", &n, &k) != EOF)
    {
        REP_D(i, 1, n)
        {
            G[i].clear();
        }
        CLR(vis);
        REP(i, 1, n)
        {
            int a, b;
            scanf("%d%d", &a, &b);
            G[a].push_back(b);
            vis[b] = 1;
        }
        for(int i = 1;i<=n;i++)
        {
            if(vis[i]==0)
            {
                ans = 0;
                dfs(1, 0);
                break;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}