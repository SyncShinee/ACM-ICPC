#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;
#define lson l,m,k<<1
#define rson m+1,r,k<<1|1
const int N = 1e5 + 10;
struct Q
{
    int x,y,id;
    Q(int _x = 0,int _y = 0,int _id = 0)
    {
        x = _x;
        y = _y;
        id = _id;
    }
}q[N];
int com(Q q1,Q q2)
{
    if (q1.y == q2.y) return q1.x < q2.x;
    return q1.y < q2.y;
}
vector <int> g[N],pos[N];
map <int ,int> mp;
int sum[N<<2],n,a[N],m,b[N];
int ans[N],dfs_clock,k,in[N],out[N];
void up(int k)
{
    sum[k] = sum[k<<1] + sum[k<<1|1];
}
void build(int l,int r,int k)
{
    sum[k] = 0;
    if (l == r)
    {
        return ;
    }
    int m = l + r >> 1;
    build(lson);
    build(rson);
}
void update(int pos,int l,int r,int k,int del)
{
    if (l == pos && l == r)
    {
        sum[k] += del;
        return;
    }
    int m = l + r >> 1;
    if (pos <= m) update(pos,lson,del);
    if (pos > m) update(pos,rson,del);
    up(k);
}
int query(int la,int ra,int l,int r,int k)
{
    if (la <= l && r <= ra)
    {
        return sum[k];
    }
    int m = l + r >> 1;
    int res = 0;
    if (la <= m) res += query(la,ra,lson);
    if (ra > m) res += query(la,ra,rson);
    return res;
}
void dfs(int u,int f)
{
    in[u] = ++dfs_clock;
    b[in[u]] = a[u];
    for (int i = 0;i < g[u].size();i++)
    {
        int v = g[u][i];
        if (v == f) continue;
        dfs(v,u);
    }
    out[u] = dfs_clock;
}
int main()
{
 //   freopen("in.txt","r",stdin);
    int t;
    scanf("%d",&t);
    while (t--)
    {
        static int ca = 0;
        printf("Case #%d:\n",++ca);
        mp.clear();
        scanf("%d%d",&n,&k);
        for (int i = 1;i <= n;i++)
            g[i].clear(),
            pos[i].clear();
        for (int i = 1;i <= n;i++)
            scanf("%d",&a[i]);
        for (int i = 1;i < n;i++)
        {
            int x,y;
            scanf("%d %d",&x,&y);
            g[x].push_back(y);
            g[y].push_back(x);
        }
        dfs_clock = 0;
        dfs(1,0);
        //puts("here");
        int Qn;
        scanf("%d",&Qn);
        for (int i = 1;i <= Qn;i++)
        {
            int u;
            scanf("%d",&u);
            q[i].x = in[u];
            q[i].y = out[u];
            q[i].id = i;
            //printf("%d %d\n",q[i].x,q[i].y);
        }
        sort(q+1,q+n,com);
        int now = 1;
        build(1,n,1);
        for (int i = 1;i <= n;i++)
        {
            //printf("dd %d\n",b[i]);
            mp[b[i]]++;
            pos[b[i]].push_back(i);
            int tmp = mp[b[i]];
            if (tmp >= k)
            {
                if (tmp > k)
                    update(pos[b[i]][tmp - k - 1],1,n,1,-2);
                if (tmp > k + 1)
                    update(pos[b[i]][tmp - k - 2],1,n,1,1);
                //printf("now %d\n",pos[b[i]][tmp - k]);
                update(pos[b[i]][tmp - k],1,n,1,1);
            }
            while (now <= Qn && q[now].y == i)
            {
                //printf("%d %d %d\n",i,q[now].x,q[now].y);
                //printf("kk %d %d\n",i,sum[2]);
                ans[q[now].id] = query(q[now].x,q[now].y,1,n,1);
                now++;
            }
        }
        for (int i = 1;i <= Qn;i++)
            printf("%d\n",ans[i]);
    }
}