#pragma comment(linker,"/STACK:102400000,102400000")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define N 40010
#define M 256
using namespace std;
typedef vector <int> :: iterator IT;
struct edge {
    int to, nxt, val;
}e[N << 1];
struct node {
    int a, b, lca, id;
}qq[M];
vector <int> q_v[N];
int n, m, head[N], side, f[N], rk[N], anc[N], dist[N];
bool vit[N];
void build(int x, int y, int z) {
    e[side].to = y;
    e[side].val = z;
    e[side].nxt = head[x];
    head[x] = side ++;
}
int gf(int x) {
    if (f[x] == x) return x;
    return f[x] = gf(f[x]);
}
void merge(int x, int y) {
    x = gf(x), y = gf(y);
    if (rk[x] < rk[y]) {
        f[x] = y;
    }
    else {
        f[y] = x;
        rk[y] == rk[x] ? rk[x] ++ : 0;
    }
}
void tarjan(int x, int pre) {
    anc[x] = f[x] = x;
    for (int i = head[x]; ~i; i = e[i].nxt) {
        if (e[i].to == pre) {
            continue;
        }
        tarjan(e[i].to, x);
        merge(e[i].to, x);
        anc[gf(x)] = x;
    }
    vit[x] = true;
    for (IT i = q_v[x].begin(); i != q_v[x].end(); ++ i) {
        int t = *i, v = qq[t].a;
        if (v == x) {
            v = qq[t].b;
        }
        if (vit[v]) {
            qq[t].lca = anc[gf(v)];
        }
    }
}
void dfs(int x, int pre, int value) {
    dist[x] = value;
    for (int i = head[x]; ~i; i = e[i].nxt) {
        if (e[i].to == pre) {
            continue;
        }
        dfs(e[i].to, x, value + e[i].val);
    }
}
int main() {
    int T, x, y, z;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        side = 0;
        memset(head, -1, sizeof head);
        memset(vit, 0, sizeof vit);
        memset(rk, 0, sizeof rk);
        for (int i = 1; i <= n; ++ i) {
            q_v[i].clear();
        }
        for (int i = 1; i < n; ++i) {
            scanf("%d%d%d", &x, &y, &z);
            build(x, y, z);
            build(y, x, z);
        }
        for (int i = 0; i < m; ++i) {
            scanf("%d%d", &qq[i].a, &qq[i].b);
            q_v[qq[i].a].push_back(i);
            q_v[qq[i].b].push_back(i);
        }
        tarjan(1, 0);
        dfs(1, -1, 0);
        for (int i = 0; i < m; ++i) {
            printf("%d\n", dist[qq[i].a] + dist[qq[i].b] - (dist[qq[i].lca] << 1));
        }
    }
    return 0;
}