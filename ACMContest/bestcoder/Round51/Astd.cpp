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

typedef unsigned long long ll;

using namespace std;

const ll maxn = 3e6 + 100;
const ll key = 3000000;
const ll MOD = 3221225473ll;

ll p[maxn], pn;
ll a[maxn], num[maxn];
ll vis[maxn], n;
vector<ll> ans;

ll pow_mod(ll x, ll n)
{
    ll res = 1;
    ll tmp = x%MOD;
    while(n)
    {
        if(n&1)
        {
            res = res*tmp%MOD;
        }
        tmp = tmp*tmp%MOD;
        n >>= 1;
    }
    return res;
}

void getP()
{
    CLR(vis);
    pn = 0;
    for(ll i = 2;i<=key;i++)
    {
        if(vis[i]==0)
        {
            p[pn] = i;
            pn++;
        }
        for(ll j = i+i;j<=key;j+=i)
        {
            vis[j]=1;
        }
    }
}

ll dfs(ll x)
{
    vis[x] = 1;
    if(vis[a[x]]==0)
    {
        return dfs(a[x])+1;
    }
    else
    {
        return 1;
    }
}
void solve()
{
    CLR(vis);
    REP_D(i, 1, n)
    {
        if(vis[i]==0)
        {
            ll t = dfs(i);
            ans.push_back(t);
        }
    }
//    for(int i = 0;i<ans.size();i++)
//    {
//        printf("%I64d ", ans[i]);
//    }
//    printf("\n");
    CLR(num);
    REP(i, 0, ans.size())
    {
        ll t = ans[i];
        for(ll j = 0;j<pn;j++)
        {
            if(p[j]>t)
                break;
            ll v = p[j];
            if(t%v==0)
            {
                ll cnt = 0;
                while(t%v==0)
                {
                    cnt++;
                    t/=v;
                }
                num[v] = max(num[v], cnt);
            }
        }
    }
    ll res = 1;
    for(ll i = 1;i<=key;i++)
    {
        if(num[i] != 0)
            res = res*pow_mod(i, num[i])%MOD;
    }
    printf("%I64u\n", res);
}

int main()
{
    freopen("in.txt", "r", stdin);
    getP();
    ll ncase;
    scanf("%I64u", &ncase);
    while(ncase--)
    {
        scanf("%I64u", &n);
        REP_D(i, 1, n)
        {
            scanf("%I64u", &a[i]);
        }
        solve();
    }
    return 0;
}
