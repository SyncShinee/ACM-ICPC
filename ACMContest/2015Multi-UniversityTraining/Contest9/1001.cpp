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

const ll maxn = 100 + 10;
const ll MOD = 1e9+7.1;

ll a[maxn], n;
char s[maxn];
ll dp[maxn][maxn], jc[maxn], jcrev[maxn];

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

void getJc()
{
    jc[0] = 1;
    jcrev[0] = 1;
    for(ll i = 1;i<=100;i++)
    {
        jc[i] = (jc[i-1]*i)%MOD;
        jcrev[i] = pow_mod(jc[i], MOD-2);
//        if(i <= 10)
//        {
//            printf("i is %I64d  %I64d\n", i, jcrev[i]);
//        }
    }
}
void solve()
{
    CLR(dp);
    REP_D(i, 1, n)
    {
        dp[i][i] = a[i];
    }
    for(ll l = 1;l<=n-1;l++)
    {
        for(ll i = 1;i+l <= n;i++)
        {
            ll j = i+l;
            for(ll k = i;k<=j-1;k++)
            {
                ll tmp = jc[j-i - 1]*jcrev[k-i]%MOD*jcrev[j-(k+1)]%MOD;
                if(s[k]=='*')
                {
                    dp[i][j] = (dp[i][j] + dp[i][k]*dp[k+1][j]%MOD*tmp%MOD)%MOD;
                }
                else if(s[k]=='+')
                {
                    dp[i][j] = (dp[i][j] + (dp[i][k]*jc[j-(k+1)]%MOD + dp[k+1][j]*jc[k-i]%MOD)*tmp%MOD )%MOD;
                }
                else if(s[k]=='-')
                {
                    dp[i][j] = ((dp[i][j] + (dp[i][k]*jc[j-(k+1)]%MOD - dp[k+1][j]*jc[k-i]%MOD)*tmp%MOD )%MOD + MOD)%MOD;
                }
            }
        }
    }
    printf("%I64d\n", dp[1][n]);
}

int main()
{
    //freopen("1Ain.txt", "r", stdin);
    //freopen("1Aout.txt", "w", stdout);
    getJc();
    while(scanf("%I64d", &n)!=EOF)
    {
        REP_D(i, 1, n)
        {
            scanf("%I64d", &a[i]);
        }
        scanf("%s", s+1);
        solve();
    }
    return 0;
}