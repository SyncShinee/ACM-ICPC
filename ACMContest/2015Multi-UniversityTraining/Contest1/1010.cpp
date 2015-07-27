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

const ll maxn = 1e9;
ll p[1000];
ll vis[1000];
ll pn;

void getP()
{
    CLR(vis);
    pn = 0;
    for(ll i = 2;i <= 100;i++)
    {
        if(vis[i]==0)
        {
            p[pn] = i;
            pn++;
            for(ll j = i+i;j<=100;j+= i)
            {
                vis[j] = 1;
            }
        }
    }
}
ll key = 62;

ll ans;
ll r, n;
ll getF(ll x, ll res)
{
    if(res==1)
        return 0;
    ll t;
    t = (pow(x, 1.0/(res*1.0))+1e-9);
    return t - 1;
}
void calcu(ll x, ll pos, ll res, ll fu)
{
    if(res >= key)
        return;
    if(p[pos] > r)
    {
        ans += fu*(getF(x, res));
        return;
    }
    calcu(x, pos+1, res*p[pos], -fu);
    calcu(x, pos+1, res, fu);
}

ll f_old(ll n)
{
    ll l = 1, r = 2*n;
    while(r - 1 >= l)
    {
        ll mid = (l+r)/2;
        ans = 0;
        calcu(mid, 0, 1, 1);
        if(ans >= n)
        {
            r = mid;
        }
        else
        {
            l = mid + 1;
        }
    }
    return r;
}
ll getCha(ll tn)
{
    ans = 0;
    calcu(tn, 0, 1, -1);
    return ans + 1;
}
ll f(ll n)
{
    ll out = n + getCha(n);
    ll t;
    while((t = n+getCha(out)) != out)
    {
        out = n + getCha(t);
    }
    return out;
}

void solve()
{
    printf("%I64d\n", f(n));
}

int main()
{
    getP();
    int t;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%I64d%I64d", &n, &r);
        solve();
    }
    return 0;
}