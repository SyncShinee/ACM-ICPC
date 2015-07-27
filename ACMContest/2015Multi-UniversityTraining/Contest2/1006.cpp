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

const int maxn = 100 + 10;
struct Edge
{
    int a, b;
};

int h1[9], l0[9];

vector<Edge> edge;

int key;
int G[maxn][maxn];
int n,m;

void solve()
{
    int ans = 0;
    CLR(G);

    edge.clear();

    REP_D(i, 1, m)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        G[a][b] = 1;
        G[b][a] = 1;
    }
    int temp = 0;
    int tot_n;
    for(int i = 1; i<=n; i++)
    {
        int t = 0;
        for(int j = 1; j<=n; j++)
        {
            if(G[i][j])
            {
                t++;
            }
        }
        if(t%2!=0)
        {
            printf("0\n");
            return;
        }
        if(t > temp)
        {
            temp = t;
            tot_n = i;
        }
    }

    for(int i = 1; i<=n; i++)
    {
        for(int j = i+1; j<=n; j++)
        {
            if(G[i][j])
            {
                if(i!=tot_n && j!=tot_n)
                {
                    Edge t;
                    t.a = i;
                    t.b = j;
                    edge.push_back(t);
                }
            }
        }
    }

    int tot = edge.size();
    key = (1<<tot);
    for(int s = 0; s<key; s++)
    {
        CLR(h1);
        CLR(l0);
        for(int i = 0; i<tot; i++)
        {
            if( ((1<<i)&s) )
            {
                h1[edge[i].a]++;
                h1[edge[i].b]++;
            }
            else
            {
                l0[edge[i].a]++;
                l0[edge[i].b]++;
            }
        }
        int flag = 1;
        for(int i = 1; i<=n; i++)
        {
            if(i==tot_n)
                continue;
            if(G[tot_n][i])
            {
                if(h1[i]==l0[i] + 1)
                {
                    l0[tot_n]++;
                }
                else if(h1[i]==l0[i]-1)
                {
                    h1[tot_n]++;
                }
                else
                {
                    flag = 0;
                    break;
                }
            }
            else
            {
                if(h1[i]!=l0[i])
                {
                    flag = 0;
                    break;
                }
            }
        }
        if(flag)
        {
            if(h1[tot_n]!=l0[tot_n])
            {
                flag = 0;
            }
        }
        ans += flag;
    }
    printf("%d\n", ans);
}

int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d%d", &n, &m);
        if(n==1 || m==0)
        {
            printf("1\n");
            continue;
        }
        solve();
    }
    return 0;
}