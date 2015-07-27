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
#define REP(i, a, b) for(ll i = a;i < b;i++)
#define REP_D(i, a, b) for(ll i = a;i <= b;i++)

typedef long long ll;

using namespace std;

const ll maxn = 1e5 + 100;
const ll INF = 1e15;

struct info
{
    ll num, x;
};
bool cmp(info a, info b)
{
    return a.x < b.x;
}
info tmp[maxn];
ll n, l, k;
ll a[maxn], tot;

ll f[maxn], g[maxn];

void getA()
{
    sort(tmp+1, tmp+1+n, cmp);
    tot = 0;
    REP_D(i, 1, n)
    {
        if(tmp[i].x==0||tmp[i].x==l)
            continue;
        for(ll j = 1; j<=tmp[i].num; j++)
        {
            tot++;
            a[tot] = tmp[i].x;
        }
    }

}
void dp()
{
    f[0] = 0;
    REP_D(i, 1, tot)
    {
        ll limit = max(0ll, i-k);
        f[i] = f[limit]+a[i]*2;
    }
    g[tot+1] = 0;
    for(ll i = tot;i>=1;i--)
    {
        ll limit = min(tot+1, i+k);
        g[i]= g[limit]+(l-a[i])*2;
    }
    ll ans = INF;
    for(ll i = 0;i<=tot;i++)
    {
        ll j = i+1;
        ans = min(ans, f[i]+g[j]);
        j = i + k + 1;
        ll t = f[i]+l;
        if(j <= tot+1)
        {
            t += g[j];
        }
        ans = min(ans, t);
    }

    int flag = 1;
    printf("%I64d\n", ans);
}

int main()
{
    ll t;
    scanf("%I64d", &t);
    while(t--)
    {
        scanf("%I64d%I64d%I64d", &l, &n, &k);
        REP_D(i, 1, n)
        {
            scanf("%I64d%I64d", &tmp[i].x, &tmp[i].num);
        }
        getA();
        dp();
    }
    return 0;
}
