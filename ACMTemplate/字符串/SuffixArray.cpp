int sa[N], t1[N], t2[N], c[N], Rank[N], height[N];
void buildsa(char *s, int n, int m) {
    int i, k, p, a1, a2, *x = t1, *y = t2;
    memset(c, 0, m << 2);
    for (i = 0; i < n; ++ i) ++ c[x[i] = s[i]];
    for (i = 1; i < m; ++ i) c[i] += c[i - 1];
    for (i = n - 1; i >= 0; -- i) sa[-- c[x[i]]] = i;
    for (k = 1, p = 0; k < n; k <<= 1, p = 0) {
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
            x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && a1 == a2 ? p - 1 : p ++;
        }
        if (p >= n) break; m = p;
    }
    for (i = 0; i < n; ++ i) Rank[sa[i]] = i;
    for (i = 0, k = 0; i < n; ++ i) {
        if (k) -- k; if (!Rank[i]) continue;
        int j = sa[Rank[i] - 1];
        while (s[i + k] == s[j + k]) ++ k;
        height[Rank[i]] = k;
    }
}
