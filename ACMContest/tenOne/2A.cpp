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

const int maxn = 50+10;
const int MAX_STA = 1024 + 100;

int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};

struct info
{
    int x, y, sta, high, step;
    info(int _x, int _y, int _sta, int _high, int _step)
    {
        x = _x;
        y = _y;
        sta = _sta;
        high = _high;
        step = _step;
    }
    info()
    {}
};
int vis[maxn][maxn][MAX_STA][3];
int h, w, s[20][maxn][maxn], a[maxn][maxn];
int startx, starty, enddx, enddy;
int swn;

int getA(int x, int y, int sta)
{
    int cnt = 0;
    for(int i = 0; i<swn; i++)
    {
        if((1<<i)&sta)
        {
            if(s[i][x][y])
                cnt++;
        }
    }
    cnt%=2;
    int ans = a[x][y];
    if(cnt==1)
    {
        if(ans==1 || ans==2)
        {
            return 3-ans;
        }
        else if(ans==3)
        {
            return ans;
        }
        else if(ans >= 4&&ans<=13)
        {
            return ans+10;
        }
        else if(ans >=14&&ans<=23)
        {
            return ans-10;
        }
        else if(ans==0)
        {
            return ans;
        }
    }
    else
    {
        return ans;
    }
}

int bfs()
{
    memset(vis, 0, sizeof(vis));
    vis[startx][starty][0][1] = 1;
    queue<info> que;
    que.push(info(startx, starty, 0, 1, 0));
    while(!que.empty())
    {
        info tmp = que.front();
        que.pop();
        int nowx = tmp.x, nowy = tmp.y, nowsta = tmp.sta, nowstep = tmp.step, nowhigh = tmp.high;
        if(nowx==enddx&&nowy==enddy)
        {
            if(nowhigh == getA(enddx, enddy, nowsta))
                return nowstep;
        }
        int nowa = getA(nowx, nowy, nowsta);
        if(nowhigh == 1)
        {
            if(nowa>=4&&nowa<=13)
            {
                int tmpnowa = nowa-4;
                int nextsta = (nowsta^(1<<tmpnowa));
                int nexthigh = nowhigh;
                if(s[tmpnowa][nowx][nowy])
                {
                    nexthigh = 3-nowhigh;
                }
                if(vis[nowx][nowy][nextsta][nexthigh]==0)
                {
                    vis[nowx][nowy][nextsta][nexthigh] = 1;
                    que.push(info(nowx, nowy, nextsta, nexthigh, nowstep+1));
                }
            }
            else if(nowa==3)
            {
                if(vis[nowx][nowy][nowsta][3-nowhigh]==0)
                {
                    vis[nowx][nowy][nowsta][3-nowhigh] = 1;
                    que.push(info(nowx, nowy, nowsta, 3-nowhigh, nowstep+1));
                }
            }

            for(int k = 0; k<4; k++)
            {
                int nextx = nowx+dx[k], nexty = nowy+dy[k];
                int nexta = getA(nextx, nexty, nowsta);
                if(nexta==1||nexta==3||(nexta>=4&&nexta<=13))
                {
                    if(vis[nextx][nexty][nowsta][nowhigh]==0)
                    {
                        vis[nextx][nexty][nowsta][nowhigh] = 1;
                        que.push(info(nextx, nexty, nowsta, nowhigh, nowstep+1));
                    }
                }
            }
        }
        else
        {
            if(nowa>=14&&nowa<=23)
            {
                int tmpnowa = nowa-14;
                int nextsta = (nowsta^(1<<tmpnowa));
                int nexthigh = nowhigh;
                if(s[tmpnowa][nowx][nowy])
                    nexthigh = 3-nowhigh;
                if(vis[nowx][nowy][nextsta][nexthigh]==0)
                {
                    vis[nowx][nowy][nextsta][nexthigh] = 1;
                    que.push(info(nowx, nowy, nextsta, nexthigh, nowstep+1));
                }
            }
            else if(nowa==3)
            {
                if(vis[nowx][nowy][nowsta][3-nowhigh]==0)
                {
                    vis[nowx][nowy][nowsta][3-nowhigh] = 1;
                    que.push(info(nowx, nowy, nowsta, 3-nowhigh, nowstep+1));
                }
            }

            for(int k = 0; k<4; k++)
            {
                int nextx = nowx+dx[k], nexty = nowy+dy[k];
                int nexta = getA(nextx, nexty, nowsta);
                if(nexta==2||nexta==3||(nexta>=14&&nexta<=23))
                {
                    if(vis[nextx][nexty][nowsta][nowhigh]==0)
                    {
                        vis[nextx][nexty][nowsta][nowhigh] = 1;
                        que.push(info(nextx, nexty, nowsta, nowhigh, nowstep+1));
                    }
                }
            }
        }
    }
    return -1;
}
char str[100+10];
void solve()
{
    memset(a, 0, sizeof(a));
    for(int i = 1; i<=h; i++)
    {
        scanf("%s", str+1);
        for(int j = 1; j<=w; j++)
        {
            if(str[j]=='#')
                a[i][j] = 0;
            else if(str[j] == '|')
                a[i][j] = 3;
            else if(str[j]=='_')
                a[i][j] = 1;
            else if(str[j]=='^')
                a[i][j] = 2;
            else if(str[j]>='a'&&str[j]<='j')
                a[i][j] = str[j]-'a'+4;
            else if(str[j]>='A'&&str[j]<='J')
                a[i][j] = str[j]-'A'+14;
            else if(str[j]=='%')
            {
                startx = i;
                starty = j;
                a[i][j] = 1;
            }
            else if(str[j]=='&')
            {
                enddx = i;
                enddy = j;
                a[i][j] = 1;
            }
            else
            {
                printf("23333333\n");
            }
        }
    }
//    for(int i = 1;i<=h;i++)
//    {
//        for(int j =1;j<=w;j++)
//        {
//            printf("%d ", a[i][j]);
//        }
//        printf("\n");
//    }
    scanf("%d", &swn);
    memset(s, 0, sizeof(s));
    for(int k = 0; k<swn; k++)
    {
        for(int i = 1; i<=h; i++)
        {
            scanf("%s", str+1);
            for(int j = 1; j<=w; j++)
            {
                if(str[j]=='*')
                    s[k][i][j] = 1;
            }
        }
    }
//    for(int k = 0; k<swn; k++)
//    {
//        for(int i = 1; i<=h; i++)
//        {
//            for(int j =1; j<=w; j++)
//            {
//                printf("%d ", s[k][i][j]);
//            }
//            printf("\n");
//        }
//        printf("\n");
//    }
    int ans = bfs();
    printf("%d\n", ans);
}

int main()
{
   // freopen("1Ain.txt", "r", stdin);
    //freopen("1Aout.txt", "w", stdout);
    while(scanf("%d%d", &w, &h) != EOF)
    {
        solve();
    }
    return 0;
}