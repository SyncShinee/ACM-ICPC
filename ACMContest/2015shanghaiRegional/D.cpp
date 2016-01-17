#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>
#include <vector>

using namespace std;

const int maxn = 2e6 + 100;
const int MAXV = 2e9;
int d[maxn];
struct info {
    int x, y, z, id, tag, num0, num1, have;
    info(int _x = 0, int _y = 0, int _z = 0, int _id = 0, int _tag = 0) {
        x = _x;
        y = _y;
        z = _z;
        id = _id;
        tag = _tag;
    }
    bool operator < (const info b) const {
        return z < b.z;
    }
    bool operator == (const info b) const {
        if(z == b.z && id == b.id)
        return 1;
        return 0;
    }
};
bool cmp_a(info a, info b) {
    if(a.x == b.x) {
        if(a.y == b.y) {
            if(a.z == b.z) {
                return a.have < b.have;
            }
            return a.z < b.z;
        }
        return a.y < b.y;
    }
    return a.x < b.x;
}
vector<int> G[maxn];
info query[maxn];
info a[2*maxn];
int an;
info b[2*maxn];
int bn;
int l[maxn], r[maxn];
int m, n;
int f[maxn][2];
struct z_info {
    int h, id, tag;
    z_info(int _h = 0, int _id = 0) {
        h = _h;
        id = _id;
    }
};
int stn;
z_info st[maxn];
int fa[maxn], vis[maxn];

void dfs(int u, int pa) {
    vis[u] = 1;
    for(int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if(v != pa) {
            dfs(v, u);
        }
    }
    f[u][1] = b[u].num1;
    for(int i = 0;i < G[u].size(); i++) {
        int v = G[u][i];
        if(v != pa) {
            f[u][1] += f[v][1];
        }
    }
    f[u][0] = b[u].num0;
    for(int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if(v != pa)
        f[u][0] += max(f[v][1], f[v][0]);
    }
}

bool cmp(info a, info b) {
    return a.x < b.x;
}
bool cmp_b(info a, info b) {
    if(a.x == b.x) {
        return a.tag > b.tag;
    }
    return a.x < b.x;
}

int b_search(int low, int high, int key) {
    high--;
    while(low < high) {
        int mid = (low + high + 1)/2;
        if(st[mid].h > key) {
            low = mid;
        }
        else {
            high = mid - 1;
        }
    }
    return st[low].id;
}

void solve() {
    sort(query, query + m, cmp);
    d[0] = d[n] = MAXV;
    stn = 1;
    st[0].h = d[0];
    st[0].id = 0;
    int now = 1;
    for(int i = 0; i < m; i++) {
        while(now  < query[i].x) {
            while(stn != 0 && st[stn - 1].h <= d[now])
            stn--;
            st[stn].h = d[now];
            st[stn].id = now;
            stn++;
            now++;
        }
        l[i] = b_search(0, stn, query[i].y);
    }
    stn = 1;
    st[0].h = d[n];
    st[0].id = n;
    now = n - 1;
    for(int i = m - 1; i >= 0; i--) {
        while(now >= 0 && now >= query[i].x) {
            while(stn != 0 && st[stn - 1].h <= d[now]) {
                stn--;
            }
            st[stn].h = d[now];
            st[stn].id = now;
            stn++;
            now--;
        }
        r[i] = b_search(0, stn, query[i].y);
    }
    an = 0;
    printf("--- %d\n", m);
    for(int i = 0; i < m; i++) {
        a[i].x = l[i];
        a[i].y = r[i];
        a[i].z = min(d[l[i]], d[r[i]]);
        a[i].have = query[i].z;
        a[i].tag = 0;
    }
    sort(a, a + m, cmp_a);
    for(int i = 0; i < m; i++) {
        printf("***%d %d %d %d %d %d\n", i, a[i].x, a[i].y, a[i].z);
    }
    bn = 0;
    b[0] = a[0];
    b[0].num1 = b[0].num0 = 0;
    bn++;
    for(int i = 0; i < m; i++) {
        if(a[i].x == b[bn - 1].x && a[i].y == b[bn - 1].y && a[i].z == b[bn - 1].z) {
            if(a[i].have == 0) {
                b[bn - 1].num0++;
            }
            else {
                b[bn - 1].num1++;
            }
        }
        else {
            b[bn] = a[i];
            b[bn].num0 = b[bn].num1 = 0;
            if(a[i].have == 0) {
                b[bn].num0++;
            }
            else {
                b[bn].num1++;
            }
            bn++;
        }
    }
    for(int i = 0; i < bn; i++) {
        b[bn + i] = b[i];
        b[bn + i].x = b[i].y;
        b[bn + i].tag = 1;
    }
    bn *= 2;
    printf("bbbb  %d\n", bn);
    sort(b, b + bn, cmp_b);
    set<info> ms;
    for(int i = 0; i < m; i++) {
        G[i].clear();
    }
    for(int i = 0; i < bn; i++) {
        if(b[i].tag == 1) {
            ms.erase(b[i]);
        }
        else {
            fa[b[i].id] = (*ms.upper_bound(b[i])).id;
            G[fa[b[i].id]].push_back(b[i].id);
        }
    }
    int ans = 0;
    memset(vis, 0, sizeof(vis));
    for(int i = 0; i < m; i++) {
        if(vis[i] == 0) {
            dfs(i, i);
            ans += max(f[i][0], f[i][1]);
        }
    }
    printf("%d\n", ans);
}

int main() {
    freopen("D.txt", "r", stdin);
    int ncase;
    scanf("%d", &ncase);
    for(int _ = 1; _ <= ncase; _++) {
        printf("Case #%d: ", _);
        scanf("%d%d", &n, &m);
        for(int i = 1; i < n; i++)
        scanf("%d", &d[i]);
        for(int i = 0; i < m; i++) {
            scanf("%d%d%d", &query[i].x, &query[i].y, &query[i].z);
        }
        solve();
    }
    return 0;
}