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

const int maxn = (1<<11) + 100;
const int MOD = 1e9 + 7 + 0.1;
int n, m, s;
int iIsJDeZiShu[20][20];
int p[20], c[20];
int tempMax;

int dp[maxn][110];

int getCi(int no, int key)
{
    int ans = 0;
    int x1 = key + c[no], x2 = c[no] - key;
    if(x1 >= 0 && x1 <= m)
        ans++;
    if(x2 != x1 && x2 >= 0 && x2 <= m)
        ans++;
    return ans;
}

int fa[20];
int getNum(int x)
{
    int ans = 0;
    while(x)
    {
        ans += (x&1);
        x >>= 1;
    }
    return ans;
}
void getDp()
{
    int key = (1<<n) - 1;
    CLR(dp);
    for(int sta = 0; sta <= key; sta++) //key meiju
    {
        dp[sta][0] = 1;
    }
    REP(i, 0, tempMax)
    {
        //dp[i + 1][opt][j] += dp[i][opt][j];
//            if(dp[i][opt][j] == 0)
//            {
//                continue;
//            }


        REP(sta, 0, n)
        {
            REP_D(j, 0, s)
            {
                for(int opt = 0; opt <= key; opt++) //key meiju
                {
                    int tt = (1<<sta);
                    if(dp[opt][j] == 0)
                        continue;
                    //int lastS = key - opt;
                    if(((tt)&opt) == 0 )
                    {
                        int add = getNum((fa[sta]&opt))*p[sta];
                        //printf("add is %d\n", add);
                        if(j + add <= s)
                        {
                            dp[opt|(tt)][j + add] = (dp[opt][j]*getCi(sta, i + 1)%MOD + dp[opt|(tt)][j + add])%MOD;
                            //printf("cicicicicicci------  %lld\n", getCi(sta, i + 1));
                        }
                    }
                }
            }
        }

    }
}

void solve()
{
    int key = (1<<n) - 1;
    getDp();
    printf("%d\n", dp[key][s]);
}


vector<int> G[20];
int vis[20];

void dfs(int i, int start)
{
    vis[i] = 1;
    iIsJDeZiShu[i][start] = 1;
    for(int j = 0; j < G[i].size(); j++)
    {
        if(!vis[G[i][j]])
        {
            dfs(G[i][j], start);
        }
    }
}
int main()
{
    while(scanf("%d%d%d", &n, &m, &s) != EOF)
    {
        int u, w;
        CLR(iIsJDeZiShu);
        REP(i, 0, n)
        {
            G[i].clear();
        }
        REP(i, 0, n - 1)
        {
            scanf("%d%d", &u, &w);
            u--;
            w--;
            G[w].push_back(u);
        }
        for(int i = 0; i < n; i++)
        {
            CLR(vis);
            for(int j = 0; j < G[i].size(); j++)
            {
                dfs(G[i][j], i);
            }
        }
        REP(i, 0, n)
        {
            fa[i] = 0;
            REP(j, 0, n)
            {
                if(iIsJDeZiShu[i][j])
                {
                    fa[i] |= (1<<j);
                }
            }
        }
        tempMax = 0;
        REP(i, 0, n)
        {
            scanf("%d%d", &p[i], &c[i]);
            tempMax = max(tempMax, max(c[i], m - c[i]));
        }
        solve();
    }
    return 0;
}