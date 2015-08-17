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

const int maxn = 52;
int have[maxn][maxn];
int dx[10] = {0, -1, 0, 0, 1}, dy[10] = {0, 0, 1, -1, 0};
int a[maxn][maxn][5];
int vis[maxn][maxn][100 + 10][11][5];
int ans[maxn][maxn];
int tot_t, directN[100 + 10], directD[100 + 10];
int m, n, x_0, y_0, street;
void dfs(int x, int y, int t, int b, int f)
{
    //printf("%d %d %d %d %d----\n", x, y, t, b, f);
    if(t==0)
    {
        REP_D(i, 1, 4)
        {
            if(a[x][y][i])
            {
                int newx=x+dx[i], newy=y+dy[i], newt = t + 1, newb = 1, newf = i;
                if(!vis[newx][newy][newt][newb][newf])
                {
                    vis[newx][newy][newt][newb][newf] = 1;
                    dfs(newx, newy, newt, newb, newf);
                }
            }
        }
        return;
    }
    if(t==tot_t&&directN[t]==b)
    {
        if(f==directD[t])
        {
            REP_D(i, 1, 4)
            {
                if(i!=5-f&&a[x][y][i])
                {
                    ans[x][y] = 1;
                }
            }
        }
        else if(f==5-directD[t])
        {
            ;
        }
        else
        {
            if(a[x][y][directD[t]])
            {
                ans[x][y] = 1;
            }
        }
        return;
    }
    if(b == directN[t])
    {
        if(f == directD[t])
        {
            REP_D(i, 1, 4)
            {
                if(5-i!=f&&a[x][y][i])
                {
                    int newx=x+dx[i], newy=y+dy[i], newt = t + 1, newb = 1, newf = i;
                    if(!vis[newx][newy][newt][newb][newf])
                    {
                        vis[newx][newy][newt][newb][newf] = 1;
                        dfs(newx, newy, newt, newb, newf);
                    }
                }
            }
        }
        else if(f == 5 - directD[t])
        {
            ;
        }
        else
        {
            int i = directD[t];
            if(a[x][y][i])
            {
                int newx=x+dx[i], newy=y+dy[i], newt = t + 1, newb = 1, newf = i;
                if(!vis[newx][newy][newt][newb][newf])
                {
                    vis[newx][newy][newt][newb][newf] = 1;
                    dfs(newx, newy, newt, newb, newf);
                }
            }
        }
    }
    else
    {
        REP_D(i, 1, 4)
        {
            if(5-i!=f&&a[x][y][i])
            {
                int newx=x+dx[i], newy=y+dy[i], newt = t, newb = b+1, newf = i;
                if(!vis[newx][newy][newt][newb][newf])
                {
                    vis[newx][newy][newt][newb][newf] = 1;
                    dfs(newx, newy, newt, newb, newf);
                }
            }
        }
    }
}
void getA()
{
    m = 1;
    n = 1;
    REP_D(i, 1, street)
    {
        int a1, b1, a2, b2;
        scanf("%d%d%d%d", &a1, &b1, &a2, &b2);

        m = max(m, a1);
        m = max(m, a2);
        n = max(n, b1);
        n = max(n, b2);
        if(a1==a2)
        {
            if(b1 >= b2)
            {
                swap(b1, b2);
            }
//            REP_D(j, b1, b2)
//            {
//                have[a1][j] = 1;
//            }
            for(int j = b1;j <= b2 - 1;j++)
            {
                a[a1][j][2] = 1;
            }
            for(int j = b2;j >= b1 +1;j--)
            {
                a[a1][j][3] = 1;
            }
        }
        else
        {
            if(a1 >= a2)
            {
                swap(a1, a2);
            }
//            REP_D(j, a1, a2)
//            {
//                have[j][b1] = 1;
//            }
            for(int j = a1;j <= a2 - 1;j++)
            {
                a[j][b1][4] = 1;
            }
            for(int j = a2;j >= a1 + 1;j--)
            {
                a[j][b1][1] = 1;
            }
        }
    }
//    REP_D(i, 0, m)
//    {
//        REP_D(j, 0, n)
//        {
//            REP_D(k, 1, 4)
//            {
//                int newx = i+dx[k], newy = j+dy[k];
//                if(newx>=0&&newx<=m&&newy>=0&&newy<=n&&have[newx][newy])
//                {
//                    a[i][j][k] = 1;
//                }
//            }
//        }
//    }
}
void getDirect()
{
    REP_D(i, 1, tot_t)
    {
        int bu;
        char s[2];
        scanf("%d%s", &bu, s);
        if(s[0]=='N')
        {
            directD[i] = 2;
        }
        else if(s[0]=='S')
        {
            directD[i] = 3;
        }
        else if(s[0] == 'W')
        {
            directD[i] = 1;
        }
        else
        {
            directD[i] = 4;
        }
        directN[i] = bu;
    }
}
void solve()
{
    CLR(have);
    CLR(vis);
    CLR(ans);
    CLR(a);
    getA();
    getDirect();
    dfs(x_0, y_0, 0, 0, 0);
    for(int i = 0;i <= m;i++)
    {
        for(int j = 0;j <= n;j++)
        {
            if(ans[i][j]==1)
            {
                printf("%d %d\n", i, j);
            }
        }
    }
}


int main()
{
    //freopen("5Ein.txt", "r", stdin);
    //freopen("5Eout.txt", "w", stdout);
    while(scanf("%d%d%d%d", &street, &x_0, &y_0, &tot_t) != EOF)
    {
        solve();
    }
    return 0;
}