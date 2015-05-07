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

const ll MOD = 1e9 + 7;

const ll maxn = 2e3 + 10;
ll n, d, x;
ll res;
ll dp[maxn][maxn], sum[maxn][maxn], C[maxn];

ll pow_mod(ll x, ll p)
{
    if(p==0)
        return 1;
    ll xx = (x*x)%MOD;
    ll pp = (p >> 1);
    ll ans = pow_mod(xx, pp);
    if(p&1)
    {
        ans = (ans*x)%MOD;
    }
    return ans;
}
void getC()
{
    ll t = min(d, n);
    C[0] = 1;
    for(ll i = 1; i <= t; i++)
    {
        C[i] = (C[i-1]*(d-i+1))%MOD;
        ll k = pow_mod(i, MOD - 2);
        C[i] = (C[i]*k)%MOD;
    }
}
void getDp()
{
    CLR(dp);
    CLR(sum);
    for(ll j = 1; j <= min(n, x); j++)
    {
        dp[1][j] = 1;
    }
    for(ll j = 1; j <= n; j++)
    {
        sum[1][j] = (sum[1][j-1]+dp[1][j])%MOD;
    }
    REP_D(i, 2, n)
    {
        for(ll j = i; j <= n; j++)
        {
            ll i_left = j - x - 1;
            i_left = max(0ll, i_left);
            ll t = ((sum[i-1][j-1]-sum[i-1][i_left])%MOD+MOD)%MOD;
            dp[i][j] = (t)%MOD;
            //printf("%lld %lld %lld\n", i, j, dp[i][j]);
        }
        for(ll j = 1; j <= n; j++)
        {
            sum[i][j] = (sum[i][j-1]+dp[i][j])%MOD;
        }
    }
}
void solve()
{
    getDp();
    getC();
    res = 0;
    ll tt = min(n, d);
    for(ll i = 1; i <= tt; i++)
    {
        ll ans = dp[i][n];
        ans = (ans*C[i])%MOD;
        res = (res + ans)%MOD;
        //printf("%lld %lld\n",dp[i][n], ans);
    }
    printf("%lld\n", res);
}

int main()
{
    //freopen("8Hin.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    while(scanf("%lld%lld%lld", &n, &d, &x) != EOF)
    {
        if(n==0&&d==0&&x==0)
        {
            break;
        }
        x--;
        solve();
    }
    return 0;
}