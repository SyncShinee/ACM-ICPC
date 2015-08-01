#include <cstdio>
#include <cstring>
#include <algorithm>


using namespace std;
typedef long long ll;
const ll MOD = 258280327;
const int N = 101000;
int a[N],n;
ll cnt[N],u[N],inv[N],invv[N],fac[N],F[N],F2[N];
void init()
{
    u[1] = 1;
    for (int i = 1;i <= 100000;i++)
        for (int j = i + i;j <= 100000;j += i)
            u[j] -= u[i];
    fac[0] = 1;
    for (int i = 1;i <= 100000;i++)
        fac[i] = fac[i-1] * i % MOD;
    inv[0] = 1;
    inv[1] = 1;
    for (int i = 2;i <= 100000;i++)
        inv[i] = (MOD - MOD/i) * inv[MOD%i] % MOD;
    invv[0] = 1;
    for (int i = 1;i <= 100000;i++)
        invv[i] = invv[i-1] * inv[i] % MOD;
}
ll Pow(ll x,ll nn)
{
    ll res = 1;
    while (nn)
    {
        if (nn & 1) res = res * x % MOD;
        x = x * x % MOD;
        nn >>= 1;
    }
    return res;
}
ll C(int nn,int mm)
{
    return fac[nn] * invv[mm] % MOD * invv[nn-mm] % MOD;
}
void solve_F()
{
    for (int i = 1;i <= 100000;i++)
    {
        F[i] = 0;
        for (int j = 1;j <= cnt[i];j++)
        {
            F[i] += fac[n-j+1] * invv[cnt[i]-j] % MOD;
            F[i] %= MOD;
        }
        //if (i == 1) printf("%d %I64d\n",cnt[1],F[1]);
        F[i] = F[i] * fac[cnt[i]] % MOD;
    }

    for (int i = 1;i <= 100000;i++)
    {
        F2[i] = 0;
        if (cnt[i])
            F2[i] = cnt[i]*Pow(2,cnt[i] - 1) % MOD;
    }
}
int main()
{
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    //freopen("test.txt","r",stdin);
    init();

    while (~scanf("%d",&n))
    {
        memset(cnt,0,sizeof cnt);
        for (int i = 1;i <= n;i++) scanf("%d",&a[i]);
        for (int i = 1;i <= n;i++)
        {
            for (int j = 1;j * j <= a[i];j++)
            {
                if (a[i] % j == 0)
                {
                    cnt[j]++;
                    if (a[i] != j * j )cnt[a[i]/j]++;
                }
            }
        }
        ll ans1 = 0,ans2 = 0;
        solve_F();
        for (int i = 1;i <= 100000;i++)
        {
            ll tmp = 0;
            for (int j = 1;j <= 100000/i;j++)
            {
                tmp += u[j] * F[i*j] % MOD;
            }
            //if (tmp != 0) printf("%d\n",i);
            ans1 = (ans1 + tmp * i % MOD) % MOD;
        }
        //printf("%I64d %I64d %I64d\n",F[1],F[2],F[3]);
        ////////////////////
        for (int i = 1;i <= 100000;i++)
        {
            ll tmp = 0;
            for (int j = 1;j <= 100000/i;j++)
            {
                tmp += u[j] * F2[i*j] % MOD;
            }
            ans2 = (ans2 + tmp * i % MOD) % MOD;
        }
        //printf("%I64d %I64d\n",ans1,ans2);
        if (ans1 == ans2)
        {
            printf("Equal %I64d\n",ans1);
        }
        if (ans1 > ans2)
        {
            printf("Mr. Zstu %I64d\n",ans1);
        }
        if (ans1 < ans2)
        {
            printf("Mr. Hdu %I64d\n",ans2);
        }
    }
}
