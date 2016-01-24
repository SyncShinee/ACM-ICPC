#pragma comment(linker,"/STACK:102400000,102400000")
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

const int N = 40010;
const int M = 256;

struct Edge {
    int to, nxt, val;
}e[N << 1];

int head[N], side, n, m;

int f[N], rk[N];

int dist[N], anc[N];

vector <int> q_v[N];

bool vis[N];

void build(int x, int y, int z) {
    e[side].to = y;
    e[side].val = z;
    e[side].nxt = head[x];
    head[x] = side ++;
}

int gf(int x) {
    return x == f[x] ? x : f[x] = gf(f[x]);
}

int merge(int x, int y) {
    x = gf(x), y = gf(y);
    if (rk[x] < rk[y]) {
        f[x] = y;
    }
    else {
        f[y] = x;
        rk[x] += rk[x] == rk[y];
    }
}

struct Query {
    int a, b, lca;
}query[M];

struct Tarjan {
    void initial() {
        memset(head, -1, sizeof head);
        side = 0;
        memset(vis, 0, sizeof vis);
        memset(rk, 0, sizeof rk);
        for (int i = 1; i <= n; ++ i) {
            q_v[i].clear();
        }
    }
    void add_query(int id, int x, int y) {
        query[id].a = x;
        query[id].b = y;
        q_v[x].push_back(id);
        q_v[y].push_back(id);
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
        vis[x] = true;
        for (int i = 0; i < q_v[x].size(); ++ i) {
            int tmp = q_v[x][i], v = query[tmp].a;
            if (v == x) {
                v = query[tmp].b;
            }
            if (vis[v]) {
                query[tmp].lca = anc[gf(v)];
            }
        }
    }
}g;

void dfs(int x, int pre, int value) {
    dist[x] = value;
    for (int i = head[x]; ~i; i = e[i].nxt) {
        if (e[i].to == pre) {
            continue;
        }
        dfs(e[i].to, x, e[i].val + value);
    }
}

int main() {
    int T, x, y, z;
    scanf("%d", &T);
    while (T --) {
        scanf("%d%d", &n, &m);
        g.initial();
        for (int i = 1; i < n; ++ i) {
            scanf("%d%d%d", &x, &y, &z);
            build(x, y, z);
            build(y, x, z);
        }
       
        for (int i = 0; i < m; ++ i) {
            scanf("%d%d", &x, &y);
            g.add_query(i, x, y);
        }
        g.tarjan(1, -1);
        dfs(1, -1, 0);

        for (int i = 0; i < m; ++ i) {
            printf("%d\n", dist[query[i].a] + dist[query[i].b] - 2 * dist[query[i].lca]);
        }
    }
}