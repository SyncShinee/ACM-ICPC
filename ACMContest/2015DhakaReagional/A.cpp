#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long ll;

const int maxn = 50000 + 100;
int l[20], nl[20];
int ncase, n;

void solve() {
    memset(l, 0, sizeof(l));
    memset(nl, 0, sizeof(nl));
    for(int i = 0; i < n; i++) {
        int d, sta;
        char s[2];
        scanf("%d%d%s", &d, &sta, s);
        if(sta == 0 && s[0] == 'i') {
            nl[d]++;
        }
        if(sta == 1 && s[0] == 'c') {
            l[d]++;
        }
    }
    ll ans = 0;
    for(int i = 1; i <= 10; i++) {
        ll tmp = 0;
        for(int j = 1; j < i; j++)
            tmp = tmp + (ll)nl[j];
        ans = ans + (ll)l[i] * tmp;
    }
    printf("%lld\n", ans);
}

int main() {
    freopen("a.txt", "r", stdin);
    scanf("%d", &ncase);
    while(ncase--) {
        scanf("%d", &n);
        solve();
    }
    return 0;
}
