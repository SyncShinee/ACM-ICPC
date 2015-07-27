#include <cstdio>
#include <cstring>
#include <algorithm>

#define base 40005

using namespace std;
typedef long long ll;
const int W = 8e4 + 20;
const ll MOD = 1e9 + 7;

ll f[2][W];
ll cnt[W];

int a[210];
int n;
void update1(int st,int sum,ll key)
{
    cnt[st + 2] -= key * 2;
    cnt[st - sum * 2 + 2] += key;
    cnt[st + sum * 2 + 2] += key;
}
void update2(int st,int sum,ll key)
{
    cnt[st - 1 - sum * 2 + 2] += key;
    cnt[st + 1] -= key ;
    cnt[st + 1 + 2] -= key;
    cnt[st + 1 + 2 * sum + 2] += key;
}

int main()
{
    freopen("in.txt","r",stdin);
    int t;
    scanf("%d",&t);
    while (t--)
    {
        memset(f,0,sizeof f);
        memset(cnt,0,sizeof cnt);
        scanf("%d",&n);
        for (int i = 1;i <= n;i++) scanf("%d",&a[i]);
        int tot = 0;
        int s = 0, t = 1;
        f[s][base] = 1;
        for (int i = 1;i <= n;i++)
        {
            if (a[i] == 0) continue;
            tot += a[i];

            for (int j = base - tot - 4;j <= base + tot + 4;j++)
                f[t][j] = cnt[j] = 0;
            for (int j = base - tot - 4;j <= base + tot + 4;j++)
            {
                if (f[s][j] == 0) continue;
                update1(j,a[i]/2 + 1,f[s][j]);
                update2(j,(a[i] - 1)/2 + 1,f[s][j]);
            }


            ll now = 0,del = 0;
            for (int j = base - tot - 4;j <= base + tot + 4;j+=2)
            {
                del = (del + cnt[j] % MOD) % MOD;
                now = (now + del) % MOD;
                f[t][j] = (f[t][j] + now) % MOD;
            }
            now = del = 0;
            for (int j = base - tot + 1 - 4;j <= base + tot + 4;j+=2)
            {
                del = (del + cnt[j] % MOD) % MOD;
                now = (now + del) % MOD;
                f[t][j] = (f[t][j] + now) % MOD;
            }
            swap(s,t);
        }
        int ans;
        ans = s;
        f[ans][base] = (f[ans][base] % MOD + MOD) % MOD;
        printf("%I64d\n",f[ans][base]);
    }
}
