#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>
#include <iostream>
using namespace std;

const int MOD = (int)1e9+7;
const int N = 100000+5;

int pri[N], pnum, mu[N], cnt[N], F[N], inv2, a[N], su[N], sum[N], p[N], Inv[N];
bool vis[N];

void mobius(int n) {
    mu[1] = 1;
    vis[1] = 1;
    for(int i = 2;i <= n; i++) {
        if(!vis[i]) pri[pnum++] = i, mu[i] = -1;
        for(int j = 0;j < pnum; j++) {
            if(i*pri[j] > n)    break;
            vis[i*pri[j]] = 1;
            if(i%pri[j] == 0) {
                mu[i*pri[j]] = 0;
                break;
            }
            mu[i*pri[j]] = -mu[i];
        }
    }
    for(int i = 1;i <= n; i++) {
        if(!vis[i]) p[i] = i;
        if(!p[i])   continue;
        if(n/i >= p[i]) p[i*p[i]] = p[i];
        for(int j = i;j <= n;j += i)
            cnt[j] += mu[j/i];
    }
    for(int i = 1;i <= n; i++)  cnt[i] += mu[i];
}

int pow_mod(int x, int n) {
    int ret = 1;
    while(n) {
        if(n&1) ret = 1LL*ret*x%MOD;
        x = 1LL*x*x%MOD;
        n >>= 1;
    }
    return ret;
}

void init(int n) {
    for(int i = 1;i <= n; i++)  Inv[i] = pow_mod(i, MOD-2);
    inv2 = pow_mod(2, MOD-2);
}

inline void Add(int &x, int y) {
    x += y;
    if(x >= MOD)    x -= MOD;
    if(x < 0)   x += MOD;
}
int main() {
    mobius(100000);
    init(100000);
    int n;
    while(scanf("%d", &n) == 1) {
        int mx = 0;
        for(int i = 1;i <= n; i++)  scanf("%d", &a[i]), mx = max(mx, a[i]);
        for(int i = 1;i <= mx; i++) {
            su[i] = sum[i] = 0;
        }
        int fk = 1;
        for(int i = 1;i <= n; i++)  fk = 1LL*fk*a[i]%MOD;
        for(int i = 1;i <= n; i++) {
            int cur = Inv[a[i]];
            Add(su[a[i]], 1LL*cur*cur%MOD);
            Add(sum[1], cur); Add(sum[a[i]+1], -cur);
        }
        for(int i = 1;i <= mx; i++) Add(su[i], su[i-1]);
        for(int i = 1;i <= mx; i++) Add(sum[i], sum[i-1]);
        for(int i = 1;i <= mx; i++) {
            int cur = 0, cur2 = 0;
            for(int j = i;j <= mx; j += i) {
                Add(cur, sum[j]);
                int nxt = min(mx, j+i-1);
                int tmp = 1LL*(j/i)*(j/i)%MOD;
                Add(cur2, 1LL*tmp*(su[nxt]-su[j-1])%MOD);
            }
            cur = 1LL*cur*cur%MOD;
            F[i] = 1LL*(cur - cur2)*inv2%MOD;
            if(F[i] < 0)    F[i] += MOD;
        }
        int ans = 0;
        for(int i = 1;i <= mx; i++) {
            Add(ans, 1LL*F[i]*cnt[i]%MOD);
        }
        printf("%d\n", 1LL*fk*ans%MOD);
    }
    return 0;




}