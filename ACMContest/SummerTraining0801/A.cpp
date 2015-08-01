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

const int maxn = 2e6 + 10;
struct info
{
    int i, k;
};
bool cmp(info a, info b)
{
    return a.k < b.k;
}
info a[maxn];
int ans[maxn];
int n, m, l;
int no[maxn];

void solve()
{
    for(int i = 0;i<n;i++)
    {
        no[i] = i;
    }
    sort(a, a+m, cmp);
    for(int i = 0;i<m;i++)
    {
        //printf("k is  %d\n", a[i].k);
        int x = a[i].i, y = a[i].i + 1;
        if(x < n-1 && x >= 0 && a[i].k < l && a[i].k > 0)
        {
            swap(no[x], no[y]);
        }

    }
    for(int i = 0;i<n;i++)
    {
        ans[no[i]] = i;
        //printf("%d -- %d\n", no[i], i);
    }
    for(int i = 0;i<n;i++)
    {
        printf("%d\n", ans[i]);
    }
}

int main()
{
    //freopen("1Ain.txt", "r", stdin);
    //freopen("1Aout.txt", "w", stdout);
    int ncase;
    scanf("%d", &ncase);
    while(ncase--)
    {
        scanf("%d%d%d", &n, &m ,&l);
        REP(i, 0, m)
        {
            scanf("%d%d", &a[i].i, &a[i].k);
        }
        solve();
    }
    return 0;
}