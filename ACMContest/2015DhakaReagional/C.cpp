#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 10010;
const int M = 1000010;

struct Edge {
    int to, nxt, val;
}e[N << 1];

int side;
int head[N];
int n, m;

struct Eg {
    int x, y, val;
}eg[M];

void build(int x, int y, int z) {
    e[side].to = y;
    e[side].val = z;
    e[side].nxt = head[x];
    head[x] = side++;
}

int dist[N];
int deep[N], anc[N][20];

int fa[N], subtree_size[N], son[N], top[N];

void dfs(int x, int pre, int v) {
    dist[x] = v;
    fa[x] = pre;
    subtree_size[x] = 1;
    for (int i = head[x]; ~i; i = e[i].nxt) {
        if (e[i].to == pre) {
            continue;
        }
        anc[e[i].to][0] = x;
        deep[e[i].to] = deep[x] + 1;
        get_dist(e[i].to, x, v + e[i].val);
        subtree_size[x] += subtree_size[e[i].to];
        if (son[x] == -1 || subtree_size[son[x]] < subtree_size[e[i].to]) {
            son[x] = e[i].to;
        }
    }
}

void get_pos(int x, int pre, int value) {
    top[x] = pre;
    if (son[x] != -1) {
        
    }
    else {
        
    }
}

void prepare() {
    for (int i= 1; i <= n; ++ i) {
        for (int j = 1; (i << j) <= n; ++ j) {
            anc[i][j] = -1;
        }
    }
    for (int j = 1; (1 << j) <= n; ++ j) {
        for (int i = 1; i <= n; ++ i) {
            if (anc[i][j - 1] != -1) {
                int a = anc[i][j - 1];
                anc[i][j] = anc[a][j - 1];
            }
        }
    }
}

int Lca(int p, int q) {
    int lo;
    if (deep[p] < deep[q]) {
        swap(p, q);
    }
    for (lo = 1; (1 << lo) <= deep[p]; ++ lo);
    lo--;
    for (int i = lo; i >= 0; -- i) {
        if (deep[p] - (1 << i) >=  deep[q]) {
            p = anc[p][i];
        }
    }
    if (p == q) {
        return p;
    }
    for (int i = lo; i >= 0; -- i) {
        if (anc[p][i] != -1 && anc[q][i] != anc[p][i]) {
            p = anc[p][i];
            q = anc[q][i];
        }
    }
    return anc[p][0];
}

int A[N], B[N];

int main() {
    int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++ cas) {
        scanf("%d%d", &n, &m);
        memset(head, -1, sizeof head);
        memset(son, -1, sizeof son);
        side = deep[1] = pos = 0;
        deep[0] = -1;
        for (int i = 0; i < m; ++ i) {
            scanf("%d%d", &eg[i].x, &eg[i].y, &eg[i].val);
            if (i < n - 1) {
                build(eg[i].x, eg[i].y, eg[i].val);
            }
        }
        dfs(1, 0, 0);
        prepare();
        for (int i = n - 1; i < m; ++ i) {
            A[i] = -1;
            B[i] = eg[i].val - (dist[eg[i].x] + dist[eg[i].y] - dist[Lca(eg[i].x, eg[i].y)]);
        }
        get_pos(1, -1, INF);
        
    }
    return 0;
}