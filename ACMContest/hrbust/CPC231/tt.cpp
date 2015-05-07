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
typedef long long ll;

using namespace std;

const int maxn = 1000 + 10;
const int INF = INT_MAX/2 - 1;
vector<int> sx, sy;
int x[maxn], y[maxn], c[maxn];
int blue_num, red_num;
int key;
int ans;
int n;
int temp;
int is_ok(int le, int ri, int low, int high)
{
    blue_num = 0;
    red_num = 0;
    for(int i = 0; i < n; i++)
    {
        if(x[i] >= le && x[i] <= ri && y[i] >= low && y[i] <= high)
        {
            if(c[i] == 0)
            {
                red_num++;
            }
            else
            {
                blue_num++;
            }
        }
    }
    if(blue_num == 0 && 2*red_num == key)
    {
        return (ri - le)*(high - low);
    }
    else
    {
        return -1;
    }
}
void solve()
{
    ans = INF;
    key = 0;
    sx.clear();
    sy.clear();
    for(int i = 0; i < n; i++)
    {
        scanf("%d %d %d", &x[i], &y[i], &c[i]);
        sx.push_back(x[i]);
        sy.push_back(y[i]);
        if(c[i] == 0)
            key++;
    }
    sort(sx.begin(), sx.end());
    sx.erase(unique(sx.begin(), sx.end()), sx.end());
    sort(sy.begin(), sy.end());
    sy.erase(unique(sy.begin(), sy.end()), sy.end());
    int le, ri, low, high;
    for(int i = 0; i < sx.size(); i++)
    {
        for(int j = i; j < sx.size(); j++)
        {
            le = sx[i];
            ri = sx[j];
            for(int k = 0; k < sy.size(); k++)
            {
                for(int z = k; z < sy.size(); z++)
                {
                    low = sy[k];
                    high = sy[z];
                     temp = is_ok(le, ri, low, high);
                    if(temp != -1 && temp < ans)
                    {
                        ans = temp;
                    }
                }
            }
        }
    }
    if(ans != INF)
        printf("%d\n", ans);
    else
        printf("-1\n");
}
int main()
{
    freopen("in.txt", "r", stdin);
    freopen("std.out", "w", stdout);
    int ncase = 0;
    while(scanf("%d", &n))
    {
        if(n == 0)
            break;
        ncase++;
        //printf("Case %d: ", ncase);
        printf("Case %d: ", ncase);
        solve();
    }
    return 0;
}
