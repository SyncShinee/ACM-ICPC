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

int t;

const int maxn = 2e5 + 100;
ll sum[maxn];
ll s[maxn], n, ans[maxn];
ll l[maxn], r[maxn];
ll lhp[maxn], rhp[maxn];


const long double PI = acos(-1.0);
//复数结构体
struct Complex
{
    long double x,y;//实部和虚部 x+yi
    Complex(long double _x = 0.0,long double _y = 0.0)
    {
        x = _x;
        y = _y;
    }
    Complex operator -(const Complex &b)const
    {
        return Complex(x-b.x,y-b.y);
    }
    Complex operator +(const Complex &b)const
    {
        return Complex(x+b.x,y+b.y);
    }
    Complex operator *(const Complex &b)const
    {
        return Complex(x*b.x-y*b.y,x*b.y+y*b.x);
    }
};

Complex x1[maxn],x2[maxn];
/*
* 进行FFT和IFFT前的反转变换。
* 位置i和 （i二进制反转后位置）互换
* len必须去2的幂
*/
inline void change(Complex y[],ll len)
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
inline void fft(Complex y[],ll len,ll on)
{
    change(y,len);
    for(ll h = 2; h <= len; h <<= 1)
    {
        Complex wn(cos(-on*2*PI/h),sin(-on*2*PI/h));
        for(ll j = 0; j < len; j+=h)
        {
            Complex w(1,0);
            for(ll k = j; k < j+h/2; k++)
            {
                Complex u = y[k];
                Complex t = w*y[k+h/2];
                y[k] = u+t;
                y[k+h/2] = u-t;
                w = w*wn;
            }
        }
    }
    if(on == -1)
        for(ll i = 0; i < len; i++)
            y[i].x /= len;
}
inline void gao(ll l[], ll r[], ll longest)
{
    ll t = longest*2+1;
    ll len = 1;
    while(len < t)
    {
        len*=2;
    }
    for(ll i=0;i<=longest;i++)
    {
        x1[i] = Complex(l[i], 0);
        x2[i] = Complex(r[i], 0);
    }
    for(ll i = longest+1;i<len;i++)
    {
        x1[i] = Complex(0, 0);
        x2[i] = Complex(0, 0);
    }
    fft(x1, len, 1);
    fft(x2, len, 1);
    for(ll i = 0;i<len;i++)
    {
        x1[i] = x1[i]*x2[i];
    }
    fft(x1, len, -1);
    for(ll i = 0;i<len;i++)
    {
        long double temp = x1[i].x;

        ll realans = temp +0.5;
        ans[i] += realans;
    }
}

ll getSum(int a, int b)
{
    if(a==0)
    {
        return sum[b];
    }
    return sum[b]-sum[a-1];
}

inline void f(ll low, ll high)
{
    if(low == high)
    {
        ans[s[low]]++;
        return;
    }
    if(low + 1 == high)
    {
        ans[s[low]]++;
        ans[s[high]]++;
        ans[s[low]+s[high]] += 2;
        return;
    }
    ll mid;
    ll tot = 0;
    for(int i = low;i<= high;i++)
    {
        tot += s[i];
    }
    mid = low;
    ll now = s[low];
    for(int i = low+1;i<= high - 1;i++)
    {
        now += s[i];
        if(now < tot/2)
        {
            mid = i;
        }
        else
        {
            break;
        }
    }
    if(tot == 0)
    {
        mid = (low+high)/2;
    }
    f(low, mid);
    f(mid+1, high);
    ll longest=0;
    for(int i = mid;i>=low;i--)
    {
        longest += s[i];
    }
    ll t = 0;
    for(ll i = mid+1;i<=high;i++)
    {
        t += s[i];
    }
    longest = max(longest, t);
    for(ll i = 0;i<=longest;i++)
    {
        l[i] = 0ll;
        r[i] = 0ll;
        lhp[i] = 0ll;
        rhp[i] = 0ll;
    }
    t = 0;
    for(ll i = mid;i>=low;i--)
    {
        t += s[i];
        l[t]++;
        lhp[t] += (mid-i+1);
    }
    t = 0;
    for(ll i = mid+1;i<=high;i++)
    {
        t += s[i];
        r[t]++;
        rhp[t] += (i - (mid+1)+1);
    }

    gao(l, rhp, longest);
    gao(lhp, r, longest);
}
inline void outPut(ll x)
{
    if(x==0)
    {
        return;
    }
    outPut(x/10);
    char ch = x%10 + '0';
    putchar(ch);
}
int main()
{
    scanf("%d", &t);
    while(t--)
    {
        ll output = 0;
        scanf("%I64d", &n);
        for(int i = 0;i< n;i++)
        {
            scanf("%I64d", &s[i]);
            output += s[i];
        }
        sum[0] = s[0];
        for(int i = 0;i<n;i++)
        {
            sum[i] = sum[i-1]+s[i];
        }
        CLR(ans);
        f(0, n-1);
        REP_D(i, 0, output)
        {
            if(ans[i]!=0)
            {
                outPut(ans[i]);
                putchar('\n');
            }
            else
            {
                printf("0\n");
            }
        }
    }
    return 0;
}