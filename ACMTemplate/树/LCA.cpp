/** 
 * 首先执行initial()，之后建图，然后执行prepare()
 * 最后就可以通过Lca(a, b)求a和b的LCA了
 * head[], side, build(x, y, z)定义与之前相同
 */
int deep[N], anc[N][20];
struct LCA_online {
    void initial(){
        side = deep[1] = 0;
        memset(head, -1, sizeof head);
    }
    void dfs(int x, int pre) {
        for (int i = head[x]; ~i; i = e[i].nxt) {
            int v = e[i].to;
            if (v != pre) {
                anc[v][0] = x;
                deep[v] = deep[x] + 1;
                dfs(v, x);
            }
        }
    }
    void prepare() {
        dfs(1, -1);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; (1 << j) <= n; j++) anc[i][j] = -1;
        }
        for (int j = 1; (1 << j) <= n; j++) {
            for (int i = 1; i <= n; i++) {
                if (anc[i][j - 1] != -1) {
                    int a = anc[i][j - 1];
                    anc[i][j] = anc[a][j - 1];
                }
            }
        }
    }
    int Lca(int p, int q) {
        int lo;
        if (deep[p] < deep[q]) swap(p, q);
        for (lo = 1; (1 << lo) <= deep[p]; lo++); lo--;
        for (int i = lo; i >= 0; i--)
            if (deep[p] - (1 << i) >= deep[q])
                p = anc[p][i];
        if (p == q)
            return p;
        for (int i = lo; i >= 0; i--)
            if (anc[p][i] != -1 && anc[p][i] != anc[q][i]) {
                p = anc[p][i];
                q = anc[q][i];
            }
        return anc[p][0];
    }
}g;
