#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>

using namespace std;

typedef long long ll;
const int maxn = 10000 + 100;
const int MAXNODE = 4 * maxn + 100;
const int M = 10000;

struct edge {
    int to, w;
    edge(int _to = 0, int _w = 0) {
        to = _to;
        w = _w;
    }
};
vector<edge> G[maxn];
int n, deep[maxn], m;
int tp[maxn], fa[maxn], son[maxn], w[maxn], no[maxn], fanno[maxn], cnt;
int tree[MAXNODE], tag[MAXNODE];
int A[maxn * 10], B[maxn * 10];
int tu[maxn * 10], tv[maxn * 10], tw[maxn * 10];
int st[21][maxn], L2[maxn];

void st_initail() {
    for(int s = 1; s <= 20; s++) {
        for(int i = 1;i + (1 << s) - 1 <= cnt; i++) {
            int j = i + (1 << (s - 1));
            st[s][i] = max(st[s - 1][i], st[s - 1][j]);
        }
    }
}
int st_query(int l, int r) {
    int len = (r - l + 1);
    int s = L2[len];
    return max(st[s][l], st[s][r - (1 << s) + 1]);
}

void dfs1(int u, int pa) {
    w[u] = 1;
    son[u] = 0;
    for(int i = 0; i < G[u].size(); i++) {
        int v = G[u][i].to;
        if(v != pa) {
            deep[v] = deep[u] + 1;
            fa[v] = u;
            dfs1(v, u);
            w[u] += w[v];
            if(w[v] > w[son[u]])
                son[u] = v;
        }
    }
}
void dfs2(int u, int top) {
    tp[u] = top;
    cnt++;
    no[u] = cnt;
    fanno[cnt] = u;
    if(son[u] != 0) {
        dfs2(son[u], top);
    }
    for(int i = 0; i < G[u].size(); i++) {
        int v = G[u][i].to;
        if(v != fa[u] && v != son[u]) {
            dfs2(v, v);
        }
    }
}
 void dfs3(int u) {
     for(int i = 0; i < G[u].size(); i++) {
         int v = G[u][i].to, w = G[u][i].w;
         if(v != fa[u]) {
             st[0][no[v]] = w;
             dfs3(v);
         }
     }
 }

void initail(int rt, int l, int r) {
    //printf("aaa  %d %d %d\n", rt, l, r);
    tree[rt] = M;
    tag[rt] = M;
    if(l == r) {
        ;
    }
    else {
        int mid = (l + r) / 2;
        initail(rt * 2, l, mid);
        initail(rt * 2 + 1, mid +1, r);
    }
}

void pushDown(int rt) {
    if(tag[rt] == M)
        return;
    int lrt = 2 * rt, rrt = 2 * rt + 1;
    tag[lrt] = min(tag[lrt], tag[rt]);
    tag[rrt] = min(tag[rrt], tag[rt]);
    tree[lrt] = min(tree[lrt], tag[rt]);
    tree[rrt] = min(tree[rrt], tag[rt]);

    tag[rt] = M;
}
void pushUp(int rt) {
    int lrt = 2 * rt, rrt = 2 * rt + 1;
    tree[rt] = min(tree[lrt], tree[rrt]);
}

void update(int L, int R, int k, int rt, int l, int r) {
    //printf("ccc  %d %d %d\n", rt, l, r);
    if(L <= l && R >= r) {
        tag[rt] = min(tag[rt], k);
        tree[rt] = min(tree[rt], k);
        return;
    }
    pushDown(rt);
    int mid = (l + r) / 2, lrt = 2 * rt, rrt = lrt + 1;
    if(L <= mid) {
        update(L, R, k, lrt, l, mid);
    }
    if(R >= mid + 1) {
        update(L, R, k, rrt, mid + 1, r);
    }
    pushUp(rt);
}
int query(int pos, int rt, int l, int r) {
    if(l == r) {
        return tree[rt];
    }
    pushDown(rt);
    int mid = (l + r) / 2, lrt = 2 * rt, rrt = 2 * rt + 1;
    if(pos <= mid)
        return query(pos, lrt, l, mid);
    return query(pos, rrt, mid + 1, r);
}

void change(int u, int v, int k) {
    int tpu = tp[u], tpv = tp[v];
    while(tpu != tpv) {
        if(deep[tpu] < deep[tpv]) {
            swap(tpu, tpv);
            swap(u, v);
        }
        update(no[tpu], no[u], k, 1, 1, cnt);
        u = fa[tpu];
        tpu = tp[u];
    }
    if(u == v)
        return;
    if(deep[u] < deep[v]) {
        swap(u, v);
    }
    //printf("bbb %d %d %d\n", no[son[v]], no[u], k);
    update(no[son[v]], no[u], k, 1, 1, cnt);
}

 int queryMax(int u, int v) {
     int ans = 0;
     int tpu = tp[u], tpv = tp[v];
     while(tpu != tpv) {
         if(deep[tpu] < deep[tpv]) {
             swap(tpu, tpv);
             swap(u, v);
         }
         ans = max(ans, st_query(no[tpu], no[u]));
         u = fa[tpu];
         tpu = tp[u];
     }
     if(u == v)
         return ans;
     if(deep[u] < deep[v])
        swap(u, v);
     // printf("888 %d  %d\n", u, v);
     ans = max(ans, st_query(no[son[v]], no[u]));
     return ans;
 }

void solve() {
    memset(st[0], 0, sizeof(st[0]));
    memset(deep, 0, sizeof(deep));
    memset(w, 0, sizeof(w));
    dfs1(1, 0);
    //printf("%d %d %d\n", getLCA(2, 3), getLCA(2, 3), getLCA(1, 3));
    tp[1] = 1;
    cnt = 0;
    dfs2(1, 1);
    initail(1, 1, cnt);
    //printf("%d\n", cnt);
    dfs3(1);
    st_initail();
    //printf("777 %d %d\n", queryMax(1, 3), no[2]);
    for(int i = 0; i < m - (n - 1); i++) {
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        A[n - 1 + i] = -1;
        B[n - 1 + i] = c - queryMax(u, v);
        //printf("666 %d\n", B[n - 1 + i]);
        change(u, v, c);
    }
    for(int i = 0; i < n - 1; i++) {
        B[i] = -1;
        int t = tu[i];
        if(deep[tu[i]] > deep[tv[i]])
            t = tu[i];
        else
            t = tv[i];

        A[i] = query(no[t], 1, 1, cnt);
        if(A[i] == M) {
            A[i] = -1;
        }
        else {
            A[i] = A[i] - tw[i];
        }
    }
    ll ans = 0;
    for(int i = 0; i < m; i++) {
        //printf("ddd   %d  %d  %d\n", i, A[i], B[i]);
        ans = ans + (ll)(i + 1) * (ll)A[i] + (ll)(i + 1) * (ll)(i + 1) * (ll)B[i];
    }
    printf("%lld\n", ans);
}

int main() {
    //freopen("c.txt", "r", stdin);
    L2[0] = -1;
    for(int i = 1; i <= 10000; i++) {
        if((i & (i - 1)) == 0)
            L2[i] = L2[i - 1] + 1;
        else
            L2[i] = L2[i - 1];
    }
    int ncase;
    scanf("%d", &ncase);
    for(int _ = 1; _ <= ncase; _++) {
        printf("Case %d: ", _);
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; i++)
            G[i].clear();
        for(int i = 0; i < n - 1; i++) {
            int u, v, c;
            scanf("%d%d%d", &u, &v, &c);
            G[u].push_back(edge(v, c));
            G[v].push_back(edge(u, c));
            tu[i] = u;
            tv[i] = v;
            tw[i] = c;
        }
        solve();
    }
    return 0;
}