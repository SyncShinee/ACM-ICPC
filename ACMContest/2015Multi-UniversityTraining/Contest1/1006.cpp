//这个是标序算链的和.
#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
#include <ctype.h>
#include <limits.h>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <stack>
#include <set>
#include <bitset>
#define CLR(a) memset(a, 0, sizeof(a))
#define REP(i, a, b) for(int i = a;i < b;i++)
#define REP_D(i, a, b) for(int i = a;i <= b;i++)

typedef long long ll;

using namespace std;

const int maxn = 1e5 + 100;
const int maxRMQ = 4e5 + 100;
const int maxIND = 2e5 + 1000;
const int maxTree = 1e6 + 100;
int nn, m;
struct Edge
{
    int a, b, val;
};
vector<Edge> edge[maxn];
vector<int> G[maxn];
int st[maxRMQ][50], L2[maxRMQ], P2[50];

int dfn, index[maxn], fa_index[maxn], first_u[maxn];
int a_st[maxRMQ], an;

int dfx, getin[maxn], getout[maxn];
int d[maxn], sum[maxn];

void dfs_dfn(int u, int fa)//这是lca
{
    dfn++;
    index[u] = dfn;
    fa_index[dfn] = u;
    an++;
    a_st[an] = dfn;
    first_u[u] = an;
    REP(i, 0, G[u].size())
    {
        int v = G[u][i];
        if(v!=fa)
        {
            dfs_dfn(v, u);
            an++;
            a_st[an] = index[u];
        }
    }
}
void getL2()
{
    L2[1] = 0;
    for(int i = 2; i<=400000; i++)
    {
        if((i&(i-1))==0)
        {
            L2[i] = L2[i-1]+1;
        }
        else
        {
            L2[i] = L2[i-1];
        }
    }
}
void initail()
{
    P2[0] = 1;
    for(int i = 1; i<=30; i++)
    {
        P2[i] = 2*P2[i-1];
    }

    for(int i = 1; i <= an; i++)
    {
        st[i][0] = a_st[i];
    }
    for(int s = 1; s<=30; s++)
    {
        for(int i = 1; i+P2[s] - 1 <=an; i++)
        {
            int j = i+P2[s-1];
            st[i][s] = min(st[i][s-1], st[j][s-1]);
        }
    }
}
int st_query(int a, int b)
{
    int len = (b-a+1);
    int s = L2[len];
    return min(st[a][s], st[b-P2[s]+1][s]);
}
int getLca(int a, int b)//lca结束
{
    int l = first_u[a], r = first_u[b];
    if(l > r)
    {
        swap(l, r);
    }
    return fa_index[st_query(l, r)];
}

int tree[maxn << 1];//树状数组
int getsum(int x)
{
    int ret = 0;
    while (x)
    {
        ret += tree[x];
        x -= (x & (-x));
    }
    return ret;
}
void update(int x, int y)
{
    while (x <= dfx)
    {
        tree[x] += y;
        x += (x & (-x));
    }
}


void dfs_xu(int u, int fa)
{
    dfx++;
    getin[u] = dfx;
    REP(i, 0, G[u].size())
    {
        int v = G[u][i];
        if(v!=fa)
        {
            dfs_xu(v, u);
        }
    }
    dfx++;
    getout[u] = dfx;
}

int getT(int a, int b)
{
    if(a==1)
    {
        return getsum(b);
    }
    return getsum(b)-getsum(a-1);
}

int getSum_t(int a, int b, int lca)
{
    int l = getin[lca];
    int r = getin[a];
    int ans = 0;
    ans += getT(l, r);
    r = getin[b];
    ans += getT(l, r);
    return ans;
}

void dfs(int u, int fa)//树形dp,求和链上.
{
    sum[u] = 0;
    REP(i, 0, G[u].size())
    {
        int v = G[u][i];
        if(v!=fa)
        {
            dfs(v, u);
            sum[u] += d[v];
        }
    }
    d[u] = sum[u];
    REP(i, 0, edge[u].size())
    {
        Edge e = edge[u][i];
        int a = e.a, b = e.b, val = e.val;
        int tmp = getSum_t(a, b, u);
        d[u] = max(d[u], tmp + sum[u] + val);
    }
    update(getin[u], sum[u]-d[u]);
    update(getout[u], d[u]-sum[u]);

}
void solve()
{
    REP_D(i, 1, nn)
    {
        G[i].clear();
        edge[i].clear();
    }
    REP_D(i, 1, nn - 1)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        G[a].push_back(b);
        G[b].push_back(a);
    }
    dfn = 0;
    an = 0;
    dfs_dfn(1, 0);
    initail();
    REP_D(i, 1, m)
    {
        int a, b, val;
        scanf("%d%d%d", &a, &b, &val);
        int lca = getLca(a, b);
        Edge t;
        t.a = a;
        t.b = b;
        t.val = val;
        edge[lca].push_back(t);
    }
    CLR(tree);
    CLR(sum);
    CLR(d);
    dfx = 0;
    dfs_xu(1,0);
    dfs(1, 0);
    printf("%d\n", d[1]);
}

int main()
{
    int t;
    getL2();
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d%d", &nn,&m);
        solve();
    }
    return 0;
}