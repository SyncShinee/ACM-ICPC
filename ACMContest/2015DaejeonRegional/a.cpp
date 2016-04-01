#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int maxn = 500 + 100;
const int INF = 1e6;
int w[maxn][maxn];
int lx[maxn], ly[maxn], linky[maxn], visx[maxn], visy[maxn], slack[maxn], nx, ny;
int f[maxn][maxn], n, color[maxn], coin[maxn], m;
vector<int> l, r;

int find(int x) {
    visx[x] = 1;
    for(int y = 0; y < ny; y++) {
        if(visy[y])
        continue;
        int t = lx[x] + ly[y] - w[x][y];
        if(t == 0) {
            visy[y] = 1;
            if(linky[y] == -1 || find(linky[y])) {
                linky[y] = x;
                return 1;
            }
        }
        else if(slack[y] > t) {
            slack[y] = t;
        }
    }
    return 0;
}
int KM() {
    memset(linky, -1, sizeof(linky));
    memset(ly, 0, sizeof(ly));
    for(int i = 0; i < nx; i++) {
        lx[i] = -INF;
        for(int j = 0; j < ny; j++) {
            if(w[i][j] > lx[i]) {
                lx[i] = w[i][j];
            }
        }
    }
    for(int x = 0; x < nx; x++) {
        for(int i = 0; i < ny; i++) {
            slack[i] = INF;
        }
        while(1) {
            memset(visx, 0, sizeof(visx));
            memset(visy, 0, sizeof(visy));
            if(find(x))
            break;
            int d = INF;
            for(int i = 0; i < ny; i++) {
                if(!visy[i] && d > slack[i])
                d = slack[i];
            }
            for(int i = 0; i < nx; i++) {
                if(visx[i])
                lx[i] -= d;
            }
            for(int i = 0; i < ny; i++) {
                if(visy[i])
                ly[i] += d;
                else
                slack[i] -= d;
            }
        }
    }
    int res = 0;
    for(int i = 0; i < ny; i++) {
        if(linky[i] > -1) {
            res += w[linky[i]][i];
        }
    }
    return res;
}

void solve() {
    for(int i = 0; i < n; i++) {
        for(int u = 0; u < n; u++) {
            if(u == i)
            continue;
            for(int v = 0; v < n; v++) {
                if(v == i || v == u)
                continue;
                f[u][v] = min(f[u][v], f[u][i] + f[i][v]);
            }
        }
    }
    int sum = 0;
    for(int i = 0; i < n; i++) {
        if(color[i] == 1)
        sum++;
    }
    if(sum >= 250) {
        for(int i = 0; i < n; i++) {
            color[i] = 1 - color[i];
            coin[i] = 1 - coin[i];
        }
    }
    l.clear();
    r.clear();
    for(int i = 0; i < n; i++) {
        if(color[i] == 1) {
            l.push_back(i);
        }
        if(coin[i] == 1) {
            r.push_back(i);
        }
    }
    for(int i = 0; i < l.size(); i++) {
        for(int j = 0; j < r.size(); j++) {
            w[i][j] = INF;
        }
    }
    for(int i = 0; i < l.size(); i++) {
        for(int j = 0; j < r.size(); j++) {
            w[i][j] = -f[l[i]][r[j]];
        }
    }
    nx = ny = l.size();
    int ans = -KM();
    printf("%d\n", ans);
}

int main() {
    freopen("a.txt", "r", stdin);
    int ncase;
    scanf("%d", &ncase);
    while(ncase--) {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n;j++) {
                if(j == i)
                f[i][j] = 0;
                else
                f[i][j] = INF;
            }
        }
        for(int i = 0; i < m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            a--;
            b--;
            f[a][b] = 1;
            f[b][a] = 1;
        }
        for(int i = 0; i < n; i++) {
            scanf("%d", &color[i]);
        }
        for(int i = 0; i < n; i++) {
            scanf("%d" ,&coin[i]);
        }
        solve();
    }
    return 0;
}