#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int N = 50010;
char s[N];
int sa[N], height[N], Rank[N], c[N], t1[N], t2[N];
void buildsa(char *s, int n, int m) {
    int i, p, k, a1, a2, *x = t1, *y = t2;
    memset(c, 0, m << 2);
    for (int i = 0; i < n; ++ i) ++ c[x[i] = s[i]];
    for (int i = 1; i < m; ++ i) c[i] += c[i - 1];
    for (int i = n - 1; i >= 0; -- i) sa[-- c[x[i]]] = i;
    for (k = 1, p = 0; k < n; p = 0, k <<= 1) {
        for (i = n - k; i < n; ++ i) y[p ++] = i;
        for (i = 0; i < n; ++ i) if (sa[i] >= k) y[p ++] = sa[i] - k;
        memset(c, 0, m << 2);
        for (i = 0; i < n; ++ i) ++ c[x[y[i]]];
        for (i = 1; i < m; ++ i) c[i] += c[i - 1];
        for (i = n - 1; i >= 0; -- i) sa[-- c[x[y[i]]]] = y[i];
        swap(x, y), p = 1, x[sa[0]] = 0;
        for (i = 1; i < n; ++ i) {
            a1 = sa[i - 1] + k < n ? y[sa[i - 1] + k] : -1;
            a2 = sa[i] + k < n ? y[sa[i] + k] : -1;
            x[sa[i]] = y[sa[i]] == y[sa[i - 1]] && a1 == a2 ? p - 1 : p ++;
        }
        if (p >= n) break; m = p;
    }
    for (i = 0; i < n; ++ i) Rank[sa[i]] = i;
    for (i = 0, k = 0; i < n; ++ i) {
        if (k) -- k; if (!Rank[i]) continue;
        int j = sa[Rank[i] - 1];
        while (s[j + k] == s[i + k]) ++ k;
        height[Rank[i]] = k;
    }
}
int main() {
    int n, T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", s);
        n = strlen(s);
        buildsa(s, n, N);
        int ans = 0;
        for (int i = 0; i < n; ++ i) {
            ans += n - sa[i] - height[i];
        }
        printf("%d\n", ans);
    }
    return 0;
}
