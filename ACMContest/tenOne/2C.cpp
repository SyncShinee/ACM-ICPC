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

const int MAX_STA = (1<<16)+100;
const int tot = (1<<16);
const int MAX_N = 128 + 10;
const int MAX_M = 20;
int f[MAX_M][MAX_STA];
char str[MAX_N][MAX_M];
int slen[MAX_N];
int xiao[20];
int num[MAX_STA];
int n, m;

int change(int sta, int x, int y)
{
    int ans = 0;
    int nowsta = (xiao[y]&sta);
    int laststa = sta - nowsta;
    int nownum = num[nowsta];
    if(nownum>=slen[x])
        return -1;
    int lastnum = slen[x-1] - num[laststa];
    if(((1<<y)&sta) && str[x][nownum] == str[x-1][lastnum])
    {
        ans++;
    }
    if(y!=0)
    {
        if(((1<<(y-1))&sta) && str[x][nownum-1] == str[x][nownum])
            ans++;
    }
    return ans;
}

void pre()
{
    for(int i = 0; i<tot; i++)
    {
        num[i] = 0;
        for(int j = 0; j<16; j++)
        {
            if((1<<j)&i)
                num[i]++;
        }
    }
    xiao[0] = 0;
    for(int i = 1; i<16; i++)
    {
        xiao[i] = (xiao[i-1]|(1<<(i-1)));
    }
}
void solve()
{
    int key = (1<<m);
    memset(f, -1, sizeof(f));
    f[0][0] = 0;
    for(int i = 1; i<=n; i++)
    {
        for(int j = 0; j<m; j++)
        {
            for(int s = 0; s<key; s++)
            {
                if(f[j][s]==-1)
                    continue;
                int nxty = j+1;
                int tmp = f[j][s];
                int nxtS = (s&(~(1<<j)));
                f[nxty][nxtS] = max(f[nxty][nxtS], tmp);
                int add = change(s, i, j);
                if(add!=-1)
                {
                    nxtS = (s|((1<<j)));
                    f[nxty][nxtS] = max(f[nxty][nxtS], tmp+add);
                }
            }
        }
        for(int j = 0;j<m;j++)
        {
            for(int s = 0;s<key;s++)
                f[j][s] = -1;
        }
        for(int s = 0; s<key; s++)
        {
            if(f[m][s]!=-1)
            {
                if(num[s]==slen[i])
                    f[0][s] = f[m][s];
            }
        }
        for(int s = 0;s<key;s++)
            f[m][s] = -1;
//        if(i == 3)
//        {
//            for(int j = 0; j<key; j++)
//            {
//                if(f[i][0][j]!=-1)
//                {
//                    printf("s is %d  %d\n", j, f[i][0][j]);
//                }
//            }
//        }
    }
    int ans = 0;
    for(int s = 0; s<key; s++)
    {
        ans = max(ans, f[0][s]);
    }
    printf("%d\n", ans*2);
}

int main()
{
   // freopen("3Cin.txt", "r", stdin);
    //freopen("3Cout.txt", "w", stdout);
    pre();
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        slen[0] = 0;
        for(int i = 1; i<=n; i++)
        {
            scanf("%s", str[i]);
            slen[i] = strlen(str[i]);
        }
        solve();
    }
    return 0;
}