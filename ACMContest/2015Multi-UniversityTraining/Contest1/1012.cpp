#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <set>
#include <vector>

#define sqr(a) ((a)*(a))
#define EPS 1e-10

using namespace std;
const int N = 2e4 + 10;
double now;
struct P
{
    int up,id,st;
    double x,y,r;

    bool operator <(const P& bb) const
    {
        if (abs(x - bb.x) < EPS)
        {
            if (abs(y - bb.y) < EPS) return up < bb.up;
            return y < bb.y;
        }
        else
            return x < bb.x;
    }
} a[N],b[N*5];
vector <int> G[N];
int f[N],n;
double key(int id,int up)
{
    double t = sqr(a[id].r) - sqr(now - a[id].x);
    if (up == 0)
    {
        t = a[id].y + sqrt(t);
    }
    else if (up == 1)
    {
        t = a[id].y - sqrt(t);
    }
    return t;
}
struct P2
{
    int id;
    int up;
    P2 () {}
    P2 (int _id,int _up) :id(_id),up(_up) {}
    bool operator < (const P2 & bb) const
    {
        if (id == bb.id) return up > bb.up;
        double t1 = key(id,up);
        double t2 = key(bb.id,bb.up);
        return t1<t2;
    }
};

void init()
{
    for (int i = 1; i <= n; i++)
    {
        b[i].x = a[i].x - a[i].r;
        b[i].y = a[i].y;
        b[i].r = a[i].r;
        b[i].up = 0;
        b[i].id = i;
        b[i].st = 0;

        b[i+n].x = a[i].x + a[i].r;
        b[i+n].y = a[i].y;
        b[i+n].r = a[i].r;
        b[i+n].up = 0;
        b[i+n].id = i;
        b[i+n].st = 1;

        b[i+2*n].x = a[i].x - a[i].r;
        b[i+2*n].y = a[i].y;
        b[i+2*n].r = a[i].r;
        b[i+2*n].up = 1;
        b[i+2*n].id = i;
        b[i+2*n].st = 0;

        b[i+3*n].x = a[i].x + a[i].r;
        b[i+3*n].y = a[i].y;
        b[i+3*n].r = a[i].r;
        b[i+3*n].up = 1;
        b[i+3*n].id = i;
        b[i+3*n].st = 1;

        f[i] = -1;
        G[i].clear();
    }
}

void solve1()
{
    set <P2> s;

    for (int i = 1; i <= 4*n; i++)
    {
        now = b[i].x;
        if (b[i].st == 0)
        {
            P2 tmp;
            tmp.id = b[i].id;
            tmp.up = b[i].up;
            if (b[i].up == 0)
            {
                set <P2> :: iterator it;
                it = s.lower_bound(tmp);
                if (it != s.end())
                {

                    P2 tmp2 = *it;
                    if (tmp2.up == 0)
                    {
                        G[tmp2.id].push_back(tmp.id);
                        f[tmp.id] = tmp2.id;
                    }
                    else if (tmp2.up == 1)
                    {
                        if (f[tmp2.id] != -1) G[f[tmp2.id]].push_back(tmp.id);
                        f[tmp.id] = f[tmp2.id];
                    }
                }
                else if (it != s.begin())
                {

                    it--;
                    P2 tmp2 = *it;
                    if (tmp2.up == 1)
                    {
                        G[tmp2.id].push_back(tmp.id);
                        f[tmp.id] = tmp2.id;
                    }
                    else if (tmp2.up == 0)
                    {
                        if (f[tmp2.id] != -1) G[f[tmp2.id]].push_back(tmp.id);
                        f[tmp.id] = f[tmp2.id];
                    }
                }
            }
            s.insert(tmp);

        }
        else if (b[i].st == 1)
        {
            P2 tmp;
            tmp.id = b[i].id;
            tmp.up = b[i].up;

            s.erase(tmp);
        }

    }
}
int dfs(int u,int f)
{
    int res = 0;

    for (int i = 0; i < G[u].size(); i++)
        if (G[u][i] != f)
        {
            res ^= (dfs(G[u][i],u) + 1);
        }
    return res;
}
void solve2()
{
    int st = 0;
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (f[i] == -1)
        {
            st = i;
            ans ^= (dfs(st,0) + 1);
        }
    }
    if (ans)
        puts("Alice");
    else
        puts("Bob");
}
int main()
{
    freopen("in.txt","r",stdin);
    int t;
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d",&n);
        for (int i = 1; i <= n; i++)
        {
            scanf("%lf%lf%lf",&a[i].x,&a[i].y,&a[i].r);
        }
        init();
        sort (b+1,b+4*n+1);
        solve1();
        solve2();
    }
}
