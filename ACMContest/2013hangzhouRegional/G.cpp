#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
const int N = 100010;
typedef long long ll;
struct Edge {
    int to, nxt, val;
}e[N << 1];

int head[N], side;

ll a[N];

void build(int x, int y, int z) {
    e[side].to = y;
    e[side].val = z;
    e[side].nxt = head[x];
    head[x] = side ++;
}

struct Trie {
    int son[N << 6][2];
    ll val[N << 6];
    int sz[N << 6];
    int tot;
    void init() {
        tot = 1;
        memset(son, -1, sizeof son);
        memset(sz, 0, sizeof sz);
    }
    void insert(ll x) {
        int u = 0;
        for (int i = 60; i >= 0; -- i) {
            int v = (x & bIT[i]) > 0;
            if (!son[u][v]) {
                son[u][v] = tot ++;
            }
            u = ch[u][v];
            sz[u] ++;
        }
        val[u] = x;
    }
    int kth_max(int k, int v) {
        if (k >= n) {
            return -1;
        }
        int u = 0;
        for (int i = 60; i >= 0; -- i) {
            int r = !((v & BIT[i]) > 0);
            if (son[u][r]) {
                if (sz[son[u][r]] >= k) {
                    u = son[u][r];
                }
                else {
                    k -= sz[son[u][r]];
                    u = son[u][r ^ 1];
                }
            }
            else {
                u = son[u][r ^ 1];
            }
        }
        return v ^ val[u];
    }
}trie;

struct Node {
    int v;
    ll vmax, k;
};

bool operator < (const node &A, const node &B) {
    return A.vmax < B.vmax;
}

struct Query {
    int k, id;
}query[N];

bool operator < (const node &A, const node &B) {
    return A.k < B.k;
}

priority_queue<Node> q;

void dfs(int x, int pre, ll val) {
    ac.insert(val);
    a[x] = val;
    for (i = head[x]; ~i; i = e[i].nxt) {
        int v = e[i].to;
        if (pre == v) {
            continue;
        }
        dfs(v, x, val ^ e[i].val);
    }
}

int main() {
    while (~scanf("%d", &n)) {
        while (!q.empty()) {
            q.pop();
        }
        memset(head, -1, sizeof head);
        side = 0;
        for (int i = 1; i < n; ++ i) {
            scanf("%d%d%d", &x, &y, &z);
            build(x, y, z);
            build(y, x, z);
        }
        dfs(1, -1, 0);
        scanf("%d", &m);
        for (int i = 1; i <= m; ++ i) {
            scanf("%d", &query[i].k);
            query[i].id = i;
        }
        sort(query + 1, query + m + 1);
        for (int i = 1; i <= n; ++ i) {
            Node now;
            now.k = 1;
            now.v = a[i];
            now.vmax = ac.kth_max(now.k, now.v);
            q.push(now);
        }
        int Rank = 1;
        for (int i = 1; i <= m; ++ i) {
            while (!q.empty() && Rank < query[i].k) {
                Rank ++;
                Node now = q.top();
                q.pop();
                now.vmax = ac.kth_max(now.k, now,v);
                q.push(now);
            }
        }
    }
    return 0;
}