#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long ll;

const int maxn = 1024 + 100;
const int M = 1e9 + 7.1;
int fac[20], n, g[maxn], f[maxn], d[20][1024 * 1024 + 100];
int  s[20];

int add(int a, int b) {
    int c = a + b;
    if(c >= M)
        c -= M;
    return c;
}
int sub(int a, int b) {
    if(a < b)
        a += M;
    return a - b;
}
int dfs(int pos, int limit, int sta, int first) {
    //printf("222    %d\n", sta);
     if(pos < 0) {
        if(first)
            return 0;
        int flag = 1;
        for(int i = 0; i < 10; i++) {
            if((1 << (2 * i + 1)) & sta) {
                flag = 0;
                break;
            }
        }
        return flag;
    }
    if(limit == 0 && first == 0 && d[pos][sta] != -1)
        return d[pos][sta];
    int ans = 0;
    for(int i = 0; i < 10; i++) {
        if(((1 << (2 * i) ) & sta) == 0 && !(i == 0 && first))
            continue;
        if(first && i == 0) {
            ans = add(ans, dfs(pos - 1, 0, sta, 1));
            continue;
        }
        int tmp = sta;
        if((1 << (2 * i + 1)) & sta)
            tmp = sta ^ (1 << (2 * i + 1));
        if(limit) {
            if(i > s[pos])
                continue;
            if(i == s[pos]) {
                ans = add(ans, dfs(pos - 1, 1, tmp, 0));
            }
            else {
                ans = add(ans, dfs(pos - 1, 0, tmp, 0));
            }
        }
        else {
            ans = add(ans, dfs(pos - 1, 0, tmp, 0));
        }
    }
    if(!limit && !first)
        d[pos][sta] = ans;
    return ans;
}

void solve() {
    int sn = 0, tmp = n;
    while(tmp != 0) {
        s[sn] = tmp % 10;
        tmp /= 10;
        sn++;
    }
    // printf("333 %d\n", sn);
    g[0] = 0;
    g[1] = 0;
    for(int sta = 2; sta < (1 << 10); sta++) {
        int num = 0;
        for(int i = 0; i < 10; i++) {
            if((1 << i) & sta)
                num = num + (1<<(2 * i)) + (1 << (2 * i + 1));
        }
        g[sta] = dfs(sn - 1, 1, num, 1);
        // if(sta <= 8) printf("111  %d   %d\n", sta, g[sta]);
        // if(g[sta] != 0) printf("111 %d  %d\n", sta, g[sta]);
    }
    memset(f, 0, sizeof(f));
    f[0] = 1;
    for(int sta = 1; sta < (1 << 10); sta++) {
        int number;
        for(int k = 0; k < 10; k++) {
            if((1 << k) & sta) {
                number = k;
                break;
            }
        }
        for(int ss = ((sta - 1) & sta);ss != sta; ss = ((ss - 1) & sta)) {
            if((1 << number) & (sta - ss))
                f[sta] = add(f[sta], (ll)f[ss] * (ll)g[sta - ss] % M);
        }
        // if(sta <= 8) printf("222 %d  %d\n", sta, f[sta]);
    }
    int ans = 0;
    for(int sta = 1; sta < (1 << 10); sta++) {
        ans = add(ans, f[sta]);
    }
    printf("%d\n", ans);
}

int main() {
    freopen("i.txt", "r", stdin);
    memset(d, -1, sizeof(d));
    int ncase;
    scanf("%d", &ncase);
    for(int _ = 1; _ <= ncase; _++) {
        // memset(d, -1, sizeof(d));
        printf("Case %d: ", _);
        scanf("%d", &n);
        solve();
    }
    return 0;
}
