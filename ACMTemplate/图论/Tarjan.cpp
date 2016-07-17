/* vis[N]记录该点是否被访问到 dfn[N]记录该点的时序
 * low[N]记录该点可追溯到的最小时序 now作为时间戳
 * num记录强连通分量的个数 size[N]记录每个强连通分量中包含的点的个数
 * index[N]记录每个点属于哪个强连通分量
 * gra[N]是图 sta是tarjan算法中的栈
 */
int vis[N], dfn[N], low[N], now = 0, num = 0, size[N], index[N];
vector<int> gra[N]; stack<int> sta;
void tarjan(int x) {
    vis[x] = 2;
    dfn[x] = low[x] = ++now;
    sta.push(x);
    for (int i = 0; i < gra[x].size(); ++i) {
        if (vis[gra[x][i]] == 0) {
            tarjan(gra[x][i]);
            low[x] = min(low[gra[x][i]], low[x]);
        }
        else if (vis[gra[x][i]] == 2)
            low[x] = min(dfn[gra[x][i]], low[x]);
    }
    if (low[x] == dfn[x]) {
        num++;
        while (1) {
            int t = sta.top();
            index[t] = num;
            vis[t] = 1;
            sta.pop();
            size[num]++;
            if (t == x)
                break;
        }
    }
}
int main() {
    //BuildGragh
    for (int i = 1; i <= n; ++i) {
        if (vis[i] == 0)
            tarjan(i);
    }
    //Print
    return 0;
}
