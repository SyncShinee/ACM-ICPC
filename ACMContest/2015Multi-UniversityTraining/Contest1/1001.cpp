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
const ll MOD = 1e9 + 7.1;
ll p[maxn], n, a[maxn], l[maxn], r[maxn];
ll key;


void getP()
{
    key = 10000 + 100;
    CLR(p);
    CLR(l);
    for(ll i = 1;i<=n;i++)
    {
        r[i] = n+1;
    }
    REP_D(i, 1, n)
    {
        key = sqrt(a[i])+1e-9;
        ll tmp = a[i];
        l[i] = p[1];
        for(ll j=1;j<=key;j++)
        {
            if(tmp%j==0)
            {
                l[i] = max(l[i], p[j]);
                l[i] = max(l[i], p[tmp/j]);
            }
        }
        p[a[i]] = i;
    }
    key = 10000 + 100;
    for(ll i = 1;i<=key;i++)
    {
        p[i] = n+1;
    }
    for(ll i = n;i >=1;i--)
    {
        key = sqrt(a[i])+1e-9;
        ll tmp = a[i];
        r[i] = p[1];
        for(ll j=1;j<=key;j++)
        {
            if(tmp%j==0)
            {
                r[i] = min(r[i], p[j]);
                r[i] = min(r[i], p[tmp/j]);
            }
        }
        p[a[i]] = i;
    }
}

void solve()
{
    getP();
    ll ans = 0;
    REP_D(i, 1, n)
    {
        ll tmp = (i - l[i])*(r[i]-i)%MOD;
        ans = (ans + tmp)%MOD;
    }
    printf("%I64d\n", ans);
}

int main()
{
    while(scanf("%I64d", &n) != EOF)
    {
        REP_D(i, 1,n)
        {
            scanf("%I64d", &a[i]);
        }
        solve();
    }
    return 0;
}