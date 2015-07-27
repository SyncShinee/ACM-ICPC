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

const ll maxn = 100000 + 100;
struct info
{
    ll num, p;
    bool operator < (const info & other) const
    {
        return num > other.num;
    }
};
info s[maxn];
ll sn;
ll n, a[maxn], k;

ll l[maxn], r[maxn], fL[maxn], sL[maxn], fR[maxn], sR[maxn];

void getFL()
{
    sn = 0;
    s[0].num = 2e9 + 1000;
    s[0].p = 0;
    REP_D(i, 1, n)
    {
        ll key = a[i] + k;
        info tt;
        tt.num = key - 1;
        ll pos = lower_bound(s, s + sn + 1, tt) - s - 1;
        fL[i] = s[pos].p;
        ll tttt = s[pos].num;
        while(s[sn].num <= a[i])
        {
            sn--;
        }
        sn++;
        s[sn].num = a[i];
        s[sn].p = i;
    }
}
void getSL()
{
    sn = 0;
    s[0].num = -1;
    s[0].p = 0;
    REP_D(i, 1, n)
    {
        ll key = a[i];
        while(s[sn].num > key)
        {
            sn--;
        }
        sL[i] = s[sn].p;
        sn++;
        s[sn].num = a[i];
        s[sn].p = i;
    }
}

void getFR()
{
    sn = 0;
    s[0].num = 2e9 + 1000;
    s[0].p = n + 1;
    for(ll i = n;i >= 1;i--)
    {
        ll key = a[i] + k;
        info tt;
        tt.num = key - 1;
        ll pos = lower_bound(s, s + sn + 1, tt) - s - 1;
        fR[i] = s[pos].p;
        while(s[sn].num <= a[i])
        {
            sn--;
        }
        sn++;
        s[sn].num = a[i];
        s[sn].p = i;
    }
}
void getSR()
{
    sn = 0;
    s[0].num = -1;
    s[0].p = n + 1;
    for(ll i = n;i>=1;i--)
    {
        ll key = a[i];
        while(s[sn].num >= key)
        {
            sn--;
        }
        sR[i] = s[sn].p;
        sn++;
        s[sn].num = a[i];
        s[sn].p = i;
    }
}

void solve()
{
    ll ans = 0;
    getFL();
    getSL();
    getFR();
    getSR();
    REP_D(i, 1, n)
    {
        l[i] = max(fL[i], sL[i]);
        r[i] = min(fR[i], sR[i]);
        ans += (i - l[i])*(r[i]-i);
    }
    printf("%I64d\n", ans);
}


int main()
{
    ll t;
    scanf("%I64d", &t);
    while(t--)
    {
        scanf("%I64d%I64d", &n, &k);
        REP_D(i, 1, n)
        {
            scanf("%I64d", &a[i]);
        }
        solve();
    }
    return 0;
}