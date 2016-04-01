#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 100010;
char s[N];
typedef long long ll;
struct node {
    int sz, l, r, pre;
    ll sum;
    node () {
        sz = l = r = 0;
        sum = 0;
    }
}p[N];


int main() {
    scanf("%s", s);
    int len = strlen(s);
    int pl = 1;
    int nw = 0, pr = -1;
    p[0].pre = pr;
    p[0].sz = 1;
    p[0].l = 0;
    for (int i = 1; i < len; ++ i) {
        if (s[i] == ')') {
            p[p[nw].pre].sum += 1ll * (p[p[nw].pre].sz - 1) * p[nw].sz;
            p[p[nw].pre].sz += p[nw].sz;
            p[nw].r = i;
            nw = p[nw].pre;
            pr = p[nw].pre;
        }
        else {
            pr = nw;
            nw = pl++;
            p[nw].pre = pr;
            p[nw].l = i;
            p[nw].sz = 1;
        }
    }
    ll ans = 0;
    /*
    for (int i = 0; i < pl; ++ i) {
        printf("%d %d %d\n", p[i].l, p[i].r, p[i].sz);
    }
    */
    for (int i = 0; i < pl; ++ i) {
        ans += 1ll * p[i].sum * (p[i].r - p[i].l + 1);
    }
    printf("%lld\n", ans);
    return 0;
}