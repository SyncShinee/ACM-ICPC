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

ll n, m;
ll sum, a[maxn][maxn];
ll b[2][maxn];
ll jc[maxn];

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
    for(ll i = 1; i<=100; i++)
    {
        jc[i] = (jc[i-1]*i)%MOD;
//        if(i <= 10)
//        {
//            printf("i is %I64d  %I64d\n", i, jcrev[i]);
//        }
    }
}

void solve()
{
    if(sum != 0)
    {
        int flag = 1;
        for(int i = 1; i<=m; i++)
        {
            if(a[i][1] == -1)
                continue;
            CLR(b[0]);
            for(int j = 1; j<=n; j++)
            {
                b[0][a[i][j]]++;
            }
            for(int j = 1; j<=n; j++)
            {
                if(b[0][j] != 1)
                {
                    flag = 0;
                    break;
                }
            }
            if(flag == 0)
                break;
        }
        if(flag == 0)
        {
            printf("0\n");
        }
        else
        {
            ll key = jc[n];
            printf("%I64d\n", pow_mod(key, sum-1));
        }
    }
    else
    {
        ll y = 0, x = 1;
        REP_D(i,1,n)
        {
            b[x][i] = i;
        }
        for(ll i = m; i>=1; i--)
        {
            for(ll j = 1; j<=n; j++)
            {
                b[y][j] = a[i][b[x][j]];
            }
            swap(x, y);
        }
        ll flag = 1;
        for(ll i = 1; i<=n; i++)
        {
            if(b[x][i]!=i)
            {
                flag = 0;
                break;
            }
        }
        printf("%I64d\n", flag);
    }
}

int main()
{
    //freopen("4Din.txt", "r", stdin);
    //freopen("4Dout.txt", "w", stdout);
    getJc();
    while(scanf("%I64d%I64d", &n, &m) != EOF)
    {
        sum = 0;
        REP_D(i ,1, m)
        {
            scanf("%I64d", &a[i][1]);
            if(a[i][1] == -1)
            {
                sum++;
            }
            else
            {
                for(ll j = 2; j<=n; j++)
                {
                    scanf("%I64d", &a[i][j]);
                }
            }
        }
        solve();
    }
    return 0;
}