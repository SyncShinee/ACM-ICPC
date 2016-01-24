#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>

using namespace std;

const int maxn = 1000 + 100;
int vis[maxn], p[maxn], n;

void pre() {
    memset(vis, 0, sizeof(vis));
    memset(p, 0, sizeof(p));
    for(int i = 2; i <= 1000; i++) {
        if(vis[i] == 0) {
            p[i] = 1;
        }
        for(int j = i + i; j <= 1000; j += i) {
            vis[j] = 1;
        }
    }
    //printf("**  %d\n", p[21]);
}
void solve() {
    for(int i = 2; i <= n; i++) {
        for(int j = i; j <= n; j++) {
            int k = n - i - j;
            if(k < j) {
                continue;
            }
            if(p[i]&&p[j]&&p[k]) {
                printf("%d %d %d\n", i, j, k);
                return;
            }
        }
    }
    printf("0\n");
}

int main() {
    freopen("J.txt", "r", stdin);
    int ncase;
    pre();
    scanf("%d", &ncase);
    while(ncase--) {
        scanf("%d", &n);
        solve();
    }
    return 0;
}