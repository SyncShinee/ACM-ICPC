#pragma comment(linker,"/STACK:102400000,102400000")
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int N = 1e5 + 10;
int n,m;
struct edge
{
    int from,to;
    int id;
    int To(int x)
    {
        if (x == from) return to;
        return from;
    }
}a[N*5];
int vis[N*5];
int visn[N],in[N];
int s[N*5],iter[N*5],tot;
int ans[N*5],cut;
int pflag;
vector <edge> go[N];
void dfs(int u,int id)
{
    //printf("%d ",u);

    //if (u == 3) printf("%d\n",cut);
    if (!visn[u] && (in[u] & 1) == 0)
    {
        cut ++;
    }
    if (cut == 2)
    {
       // printf("dd %d %d %d\n",cut,u,in[u]);
        pflag = 1;
    }
    visn[u] = 1;
    //if (u == 1) printf("debug %d\n",iter[u]);
    for (int& i = iter[u];i < go[u].size() && pflag == 0;i++)
    {
        edge e = go[u][i];

        if (vis[e.id] == 1) continue;
        int v = e.To(u);
        //printf("v = %d\n",v);
        vis[e.id] = 1;
        in[u]--;in[v]--;
        //ans[e.id] = (e.from == u ? 1 : 0);
        dfs(e.To(u),e.id);
    }
    //if (u == 1) printf("debug %d\n",re);
    //iter[u] = re;
    ans[id] = (a[id].from == u ? 1 : 0);
    s[++tot] = u;
}

int main()
{
   // freopen("in.txt","r",stdin);
    int t;scanf("%d",&t);
    while (t--)
    {
        tot = 0;
        memset(vis,0,sizeof vis);
        memset(a,0,sizeof a);
        memset(visn,0,sizeof visn);
        memset(iter,0,sizeof iter);
        memset(ans,-1,sizeof ans);
        scanf("%d %d",&n,&m);
        for (int i = 1;i <= n;i++) go[i].clear();
        for (int i = 1;i <= m;i++)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            a[i] = edge{x,y,i};
            in[x]++;in[y]++;
            go[x].push_back(edge{x,y,i});
            go[y].push_back(edge{x,y,i});
        }
        int flag = 1;

        for (int i = 1;i <= n;i++)
        {
            if ( in[i] & 1)
            {
                tot = 0;
                cut = 1;
                pflag = 0;
                //pre = i;
                //printf("dd %d\n",i);
                dfs(i,0);
                //printf("\n");
                //for (int i = 1;i <= tot;i++) printf("%d%c",s[i]," \n"[i==tot]);
            }
        }
        memset(visn,0,sizeof visn);
        for (int i = 1;i <= n;i++)
        {
            if (in[i] != 0)
            {
                cut = 0;
                tot = 0;
                pflag = 0;
                //printf("ddd %d\n",i);
                dfs(i,0);
            }
        }
        for (int i = 1;i <= m;i++)
        {
            if (!vis[i])
            {
                flag = 0;
                break;
            }
        }
        if (flag == 0)
        {
            puts("-1");
            continue;
        }
        //printf("\n");
        for (int i = 1;i <= m;i++) printf("%d\n",ans[i]);


    }
}