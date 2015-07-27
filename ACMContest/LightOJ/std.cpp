#include <cstdio>
#include <bitset>
using namespace std;
typedef long long ll;

const int N = 100000000+2;
const ll MOD = 1LL<<32;

unsigned int vis[(N+31)/32 + 5];
int pri[5770000], pnum;
unsigned int sum[5770000];

bool Get(int i) {
    int x = i/32, y = i%32;
    return 1<<y & vis[x];
}

void Set(int i) {
    int x = i/32, y = i%32;
    vis[x] |= 1<<y;
}

void get_prime(int n) {
    pnum = 0;
    for(int i = 2;i <= n; i++) {
        if(!Get(i)) pri[pnum++] = i;
        for(int j = 0;j < pnum; j++) {
            if(i*pri[j] > n)    break;
            Set(i*pri[j]);
            if(i%pri[j] == 0)   break;
        }
    }
    sum[0] = pri[0];
    for(int i = 1;i < pnum; i++)    sum[i] = (ll)sum[i-1]*pri[i]%MOD;
}

int n;

bool ok(int cnt, int m) {
    ll now = 1;
    for(int i = 0;i < cnt; i++) {
        now *= pri[m];
        if(now > n) return false;
    }
    return true;
}

int bin(int cnt) {
    int l = 0, r = pnum-1, ret = -1;
    while(l <= r) {
        int mid = l+r>>1;
        ll now = 1;
        if(ok(cnt, mid)) {
            ret = mid;
            l = mid+1;
        }
        else
            r = mid-1;
    }
    return ret;
}

int main() {
    get_prime(100000000);
    int t, cas = 1;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        ll ans = 1;
        int cur = 1;
        while(true) {
            int ret = bin(cur);
            if(ret == -1)   break;
            ans = (ll)ans*sum[ret]%MOD;
            cur++;
        }
        printf("Case %d: %u\n", cas++, ans);
    }
    return 0;
}