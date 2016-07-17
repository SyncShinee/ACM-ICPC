///max_v, V, get_G, 0 ~ V - 1;
//v*E;
const int MAXN = 2e4 + 100;
const int INF = INT_MAX / 2 - 1;
vector<int> G[MAXN];
int V;
int m, n;
int match[MAXN], used[MAXN];
void add_edge(int from, int to) {
    G[from].push_back(to);
    G[to].push_back(from);
}
int dfs(int v) {
    used[v] = 1;
    for (int i = 0; i < G[v].size(); i++) {
        int u = G[v][i], w = match[u];
        if (w < 0 || (!used[w] && dfs(w))) {
            match[u] = v;
            match[v] = u;
            return 1;
        }
    }
    return 0;
}
int b_match() {
    int res = 0;
    fill(match, match + V, -1);
    for (int i = 0; i < V; i++) { //其实到m就行了.
        if (match[i] < 0) {
            CLR(used);
            if (dfs(i)) {
                res++;
            }
        }
    }
    return res;
}
/*
可以找出是那些点覆盖了边.
方法:x集合中未匹配的大胆标used, 然后与之相连的y集合中的要标成used,之后只有与y相匹配的x中的点才敢标成used,再深搜次x,最终x集合中未标记的和y集合中标记//的选出来.
*/
void find_dfs(int v) {
    used[v] = 1;
    REP(i, 0, G[v].size()) {
        if (!used[G[v][i]]) {
            used[G[v][i]] = 1;
            int new_v = match[G[v][i]];
            if (new_v != -1) {
                find_dfs(new_v);
            }
        }
    }
}
void find_who() {
    CLR(used);
    REP(i, 0, n) {
        if (match[i] == -1 && !used[i]) {
            find_dfs(i);
        }
    }
    REP(i, 0, n) {
        if (!used[i]) { //不是多余的
            printf(" r%d", i + 1);
        }
    }
    REP(i, n, n + m) {
        if (used[i]) { //右边集合要有的.
            printf(" c%d", i - n + 1);
        }
    }
    printf("\n");
}
