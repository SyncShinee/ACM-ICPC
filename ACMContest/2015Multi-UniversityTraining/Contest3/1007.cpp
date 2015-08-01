//o(1)递推版本.
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
const ll MOD = 998244353;

ll dp[maxn], f[maxn];
ll n;
ll jc[maxn], jcrev[maxn];

ll pow_mod(ll x,ll n)
{
    ll res = 1;
    ll t = x%MOD;
    while(n)
    {
        if(n&1)
            res = (res*t)%MOD;
        t = (t*t)%MOD;
        n >>= 1;
    }
    return res;
}

void getJC()
{
    jc[0] = 1;
    jcrev[0] = 1;
    for(ll i = 1;i<=100000;i++)
    {
        jc[i] = (jc[i-1]*i)%MOD;
        jcrev[i] = (jcrev[i-1]*pow_mod(i, MOD-2))%MOD;
    }
}

void getDp()
{
    dp[0] = 1;
    f[0] = 1;
    ll sum, sum_1, sum_1_1;
    sum = 0;
    sum_1 = 0;
    sum_1_1 = 0;
    REP_D(i, 1, 100000)
    {
        if(i == 1)
        {
            sum_1_1 = f[0];
        }
        else
        {
            sum_1_1 = (sum_1_1 + f[i-1])%MOD;
            sum_1_1 = (sum_1_1 + f[i-2])%MOD;
        }
        sum_1 = (sum_1 + sum_1_1)%MOD;
        sum = (sum + sum_1)%MOD;
        dp[i] = (sum*jc[i-1])%MOD;
        f[i] = (dp[i]*jcrev[i])%MOD;
    }
}

int main()
{
    getJC();
    getDp();
    while(scanf("%I64d", &n) != EOF)
    {
        printf("%I64d\n", dp[n]);
    }
    return 0;
}
//ntt转移卷积加速.
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
typedef long long ll;

using namespace std;

const ll M = 998244353;
const ll maxn = 5e5 + 100;
ll dp[maxn];
ll jc[maxn], jcrev[maxn];
ll x1[maxn],x2[maxn];
/*
* 进行FFT和IFFT前的反转变换。
* 位置i和 （i二进制反转后位置）互换
* len必须去2的幂
*/
void change(ll y[],ll len)
{
    ll i,j,k;
    for(i = 1, j = len/2; i <len-1; i++)
    {
        if(i < j)swap(y[i],y[j]);
//交换互为小标反转的元素，i<j保证交换一次
//i做正常的+1，j左反转类型的+1,始终保持i和j是反转的
        k = len/2;
        while(j >= k)
        {
            j -= k;
            k /= 2;
        }
        if(j < k)j += k;
    }
}
/*
* 做FFT
* len必须为2^k形式，
* on==1时是DFT，on==-1时是IDFT
*/

ll power(ll a, ll n)
{
    ll res = 1, z = a;
    while (n)
    {
        if (n & 1) res = res * z % M;
        z = z * z % M;
        n >>= 1;
    }
    return res;
}

ll inverse(ll x)
{
    return power(x, M - 2);
}

void getJc()
{
    jc[0] = 1;
    jcrev[0] = inverse(1);
    for(ll i = 1;i <= 100000;i++)
    {
        jc[i] = jc[i-1]*i%M;
        jcrev[i] = inverse(jc[i]);
    }
}

void fft(ll y[],ll len,ll on)//from 0 to len - 1;
{
    change(y,len);
    for(ll h = 2; h <= len; h <<= 1)
    {
        ll unit_p0 = power(3, (M-1)/(h));//这个地方是重点
        if(on == -1)
        {
            unit_p0 = inverse(unit_p0);
        }
        for(ll j = 0; j < len; j+=h)
        {
            ll unit = 1;
            for(ll k = j; k < j+h/2; k++)
            {
                ll u = y[k];
                ll t = unit*y[k+h/2]%M;
                y[k] = u+t;
                if(y[k] >= M)
                {
                    y[k] -= M;
                }
                if(u < t)
                {
                    u += M;
                }
                y[k+h/2] = u-t;
                unit = unit*unit_p0%M;
            }
        }
    }

    if(on == -1)
    {
        ll key = inverse(len);
        for(ll i = 0; i < len; i++)
            y[i] = y[i]*key%M;
    }
}


void divid(ll l, ll r)
{
    if(l==r)
    {
        return ;
    }
    ll mid = (l+r)/2;
    divid(l, mid);
    ll len = r-l+1;
    ll len1 = 1;
    while(len1<2*len)
    {
        len1 <<= 1;
    }
    for(ll i = 0;i<len1;i++)
    {
        x1[i] = 0;
        x2[i] = 0;
        if(i+l <= mid)
        {
            x1[i] = dp[i+l]*jcrev[i+l]%M;
        }
        if(i<=len)
        {
            x2[i] = i*i%M;
        }
    }
    fft(x1, len1, 1);
    fft(x2, len1, 1);
    for(ll i = 0;i<len1;i++)
    {
        x1[i] = (x1[i]*x2[i])%M;
    }
    fft(x1, len1, -1);
    for(ll i = mid+1;i<=r;i++)
    {
        dp[i] = (dp[i] + jc[i-1]*x1[i-l]%M)%M;
    }
    divid(mid+1, r);
}
ll n;
int main()
{
    getJc();
    CLR(dp);
    dp[0] = 1;
    divid(0, 100000);
    while(scanf("%I64d", &n) != EOF)
    {
        printf("%I64d\n", dp[n]);
    }
    return 0;
}