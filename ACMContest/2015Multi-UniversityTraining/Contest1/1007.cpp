#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>
#include <stack>
#include <map>
#include <set>
#define N 100010

#define MOD 1000000007

using namespace std;
int n, m;
struct edge
{
    int to, val;
} e;
vector <edge> gra[4096];
int deep[4096], len[4096], ans, dist[4096], iinf;
vector <int> pre[4096];
bool inq[4096];
queue <int> q;



const int MAXN = 2000 + 110;
const int INF = 1000000000;

struct Edge
{
    int from, to, cap, flow;
};


struct Dinic
{
    int s, t;
    vector<Edge> edges;    // 边数的两倍
    vector<int> G[MAXN];   // 邻接表，G[i][j]表示结点i的第j条边在e数组中的序号
    bool vis[MAXN];        // BFS使用
    int d[MAXN];           // 从起点到i的距离
    int cur[MAXN];         // 当前弧指针

    void init()
    {
        edges.clear();
    }

    void clearNodes(int a, int b)
    {
        for(int i = a; i <= b; i++) G[i].clear();
    }

    void AddEdge(int from, int to, int cap)
    {
        edges.push_back((Edge)
        {
            from, to, cap, 0
        });
        edges.push_back((Edge)
        {
            to, from, 0, 0
        });
        int m = edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    bool BFS()
    {
        memset(vis, 0, sizeof(vis));
        queue<int> Q;
        Q.push(s);
        vis[s] = 1;
        d[s] = 0;
        while(!Q.empty())
        {
            int x = Q.front();
            Q.pop();
            for(int i = 0; i < G[x].size(); i++)
            {
                Edge& e = edges[G[x][i]];
                if(!vis[e.to] && e.cap > e.flow)
                {
                    vis[e.to] = 1;
                    d[e.to] = d[x] + 1;
                    Q.push(e.to);
                }
            }
        }
        return vis[t];
    }

    int DFS(int x, int a)
    {
        if(x == t || a == 0) return a;
        int flow = 0, f;
        for(int& i = cur[x]; i < G[x].size(); i++)
        {
            Edge& e = edges[G[x][i]];
            if(d[x] + 1 == d[e.to] && (f = DFS(e.to, min(a, e.cap-e.flow))) > 0)
            {
                e.flow += f;
                edges[G[x][i]^1].flow -= f;
                flow += f;
                a -= f;
                if(a == 0) break;
            }
        }
        return flow;
    }

    // 求s-t最大流。如果最大流超过limit，则只找一个流量为limit的流
    int Maxflow(int s, int t, int limit)
    {
        this->s = s;
        this->t = t;
        int flow = 0;
        while(BFS())
        {
            memset(cur, 0, sizeof(cur));
            flow += DFS(s, limit - flow);
            if(flow == limit) break; // 达到流量限制，直接退出
        }
        return flow;
    }
};
Dinic g;

void getG()
{
    int s, t;
    s = 1;
    t = n;
    g.init();
    g.clearNodes(s, t);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j < gra[i].size(); ++j)
        {
            int v = gra[i][j].to, w = gra[i][j].val;
            if (dist[v] == dist[i] + w)
            {
                g.AddEdge(i, v, 1);
            }
        }
    }
    printf("%d", g.Maxflow(s, t, INF));
}

int dfs(int x) {
    if (deep[x] < iinf)
        return deep[x];
    for (int i = 0; i < gra[x].size(); ++i) {
        int v = gra[x][i].to, w = gra[x][i].val;
        if (dist[x] + w == dist[v])
        deep[x] = min(deep[x], dfs(v) + 1);
    }
    return deep[x];
}

int main()
{
    int x, y, z;
    while (~scanf("%d%d", &n, &m))
    {
        for (int i = 1; i <= n; ++i)
        {
            gra[i].clear();
        }
        for (int i = 0; i < m; ++i)
        {
            scanf("%d%d%d", &x, &y, &z);
            e.to = y;
            e.val = z;
            gra[x].push_back(e);
            e.to = x;
            gra[y].push_back(e);
        }
        memset(dist, 0x7f, sizeof dist);
        memset(inq, 0, sizeof inq);
        q.push(1);
        inq[1] = true;
        dist[1] = 0;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            inq[u] = false;
            for (int i = 0; i < gra[u].size(); ++i)
            {
                int v = gra[u][i].to, w = gra[u][i].val;
                if (dist[v] > dist[u] + w)
                {
                    dist[v] = dist[u] + w;
                    if (!inq[v])
                    {
                        inq[v] = true;
                        q.push(v);
                    }
                }
            }
        }
        memset(deep, 0x7f, sizeof deep);
        iinf = deep[0];
        deep[n] = 0;
        ans = dfs(1);
        getG();
        printf(" %d\n",  m - ans);
    }
    return 0;
}