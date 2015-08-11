#include <cstdio>
#include <cstring>

using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;
const int N = 1e4 + 10;
ll invv[N],fac[N],inv[N];
int n,t;
int a[N],x,pos;
void init()
{
    fac[0] = 1;
    for (int i = 1;i <= 6000;i++)
        fac[i] = fac[i-1] * i % MOD;
    inv[1] = 1;
    for (int i = 2;i <= 6000;i++)
        inv[i] = (MOD - MOD/i) * inv[MOD%i] % MOD;
    invv[0] = 1;
    invv[1] = 1;
    for (int i = 2;i <= 6000;i++)
        invv[i] = invv[i-1] * inv[i] % MOD;
}
ll C(ll nn,ll mm)
{
    if (mm < 0) return 0;
    if (mm > nn) return 0;
    if (mm == nn) return 1;
    if (mm == 0) return 1;
    return fac[nn] * invv[mm] % MOD * invv[nn-mm] % MOD;
}
int main()
{
  //  freopen("in.txt","r",stdin);
    init();
    scanf("%d %d",&n,&t);
    {
        for (int i = 1;i <= n;i++) scanf("%d",&a[i]);
        scanf("%d %d",&x,&pos);
        int tmp = x;
        x = a[x];
        int left = 0,right = 0,e = 0;
        for (int i = 1;i <= n;i++)
        {
            if (i == tmp) continue;
            if (a[i] < x) left++;
            if (a[i] > x) right++;
            if (a[i] == x) e++;
        }
        ll ans = 0;
        //printf("%d\n",e);
        for (int i = 0;i <= e;i++)
            for (int j = 0;j <= e - i;j++)
            {
                //if (i == 1 && j == 0) printf("%d %I64d\n",e,C(3 ,1));
                ans = (ans + C(left,pos-1-i) * C(right,t-pos-j) % MOD * C(e ,i + j) % MOD) % MOD;
            }
        ans = (ans + MOD) % MOD;
        printf("%lld\n",ans);
    }
}