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

const int INF = 1e9;

int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};

int n, m, x, y;

int check(int x, int y)
{
    if(x >= 1 && x <= n&&y>=1&&y<=m)
    {
        return 1;
    }
    return 0;
}

void solve()
{
    int ans = 0;
    if(n%2==1 && m%2==1 && x==(n+1)/2 && y==(m+1)/2)
    {

        int newi = x-1;
        int newj = y;
        if(check(newi, newj))
        {
            int t = INF;
            t = min(t, newi);
            t = min(t, (m+1)/2);
            ans = max(ans, t);
        }
        newi = x;
        newj = y-1;
        if(check(newi, newj))
        {
            int t = INF;
            t = min(t, newj);
            t = min(t, (n+1)/2);
            ans = max(ans, t);
        }

    }
    else
    {
        ans = min((n+1)/2, (m+1)/2);
        int newi = x-1;
        int newj = y;
        if(check(newi, newj))
        {
            int t = INF;
            int tt = min(newj, m-newj+1);
            t = min(t, newi);
            t = min(t, tt);
            ans = max(ans, t);
        }
        newi = x;
        newj = y-1;
        if(check(newi, newj))
        {
            int t = INF;
            t = min(t, newj);
            int tt = min(newi, n-newi+1);
            t = min(t, tt);
            ans = max(ans, t);
        }
        newi = x+1;
        newj = y;
        if(check(newi, newj))
        {
            int t = INF;
            int tt = min(newj, m-newj+1);
            t = min(t, n - newi + 1);
            t = min(t, tt);
            ans = max(ans, t);
        }
        newi = x;
        newj = y+1;
        if(check(newi, newj))
        {
            int t = INF;
            int tt = min(newi, n - newi+1);
            t = min(t, m - newj + 1);
            t = min(t, tt);
            ans = max(ans, t);
        }
    }
    printf("%d\n", ans);
}

int main()
{
    while(scanf("%d%d%d%d", &n, &m, &x, &y) != EOF)
    {
        solve();
    }
    return 0;
}