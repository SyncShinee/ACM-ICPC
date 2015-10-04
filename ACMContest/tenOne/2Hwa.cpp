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

const double eps = 1e-10;
const double PI = acos(-1.0);
const int maxn = 1e5 + 100;

int dcmp(double x)
{
    if(fabs(x)<eps)
        return 0;
    if(x > 0)
        return 1;
    return -1;
}
struct Point
{
    double x, y;
    int id, tag;
    Point(double _x = 0, double _y = 0, int _id = 0, int _tag = 0)
    {
        x = _x;
        y = _y;
        id = _id;
        tag = _tag;
    }
    Point operator -(const Point &b)const
    {
        return Point(x - b.x,y - b.y);
    }
    double operator ^(const Point &b)const
    {
        return x*b.y - y*b.x;
    }
    int operator ==(const Point &b)const
    {
        if(dcmp(x-b.x)==0&&dcmp(y-b.y)==0)
            return 1;
        return 0;
    }
    double operator *(const Point &b)const
    {
        return x*b.x + y*b.y;
    }
    double mo()
    {
        double ans = 0;
        ans = sqrt(x*x+y*y);
        return ans;
    }
    void change(double r)
    {
        double k = r/mo();
        x *= k;
        y *= k;
    }
    bool operator < (Point b) const
    {
        if(dcmp(x-b.x)==0)
            return dcmp(y-b.y) < 0;
        return dcmp(x-b.x)<0;
    }
};

double dist(Point a, Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

struct Line
{
    Point s,e;
    Line() {}
    Line(Point _s,Point _e)
    {
        s = _s;
        e = _e;
    }
};
/*
*p点在L上面返回1
*p点不在L上面返回0
*/
bool OnSeg(Point P,Line L)
{
    return
        dcmp((L.s-P)^(L.e-P)) == 0 &&
        dcmp((P.x - L.s.x) * (P.x - L.e.x)) <= 0 &&
        dcmp((P.y - L.s.y) * (P.y - L.e.y)) <= 0;
}
/*
线段相交
*相交返回1
*不相交返回0
*/
bool inter(Line l1,Line l2)
{
    return
        max(l1.s.x,l1.e.x) >= min(l2.s.x,l2.e.x) &&
        max(l2.s.x,l2.e.x) >= min(l1.s.x,l1.e.x) &&
        max(l1.s.y,l1.e.y) >= min(l2.s.y,l2.e.y) &&
        max(l2.s.y,l2.e.y) >= min(l1.s.y,l1.e.y) &&
        dcmp((l2.s-l1.e)^(l1.s-l1.e))*dcmp((l2.e-l1.e)^(l1.s-l1.e)) <= 0 &&
        dcmp((l1.s-l2.e)^(l2.s-l2.e))*dcmp((l1.e-l2.e)^(l2.s-l2.e)) <= 0;
}
Point inter_Point(Line l1, Line l2)
{
    double a1, b1, a2, b2, a3, b3, a4, b4;
    if (l1.s == l2.s || l1.s == l2.e) {
        return l1.s;
    }
    if (l1.e == l2.s || l1.e == l2.e) {
        return l1.e;
    }
    a1 = l1.s.x;
    b1 = l1.e.x - l1.s.x;
     a2 = l1.s.y;
    b2 = l1.e.y - l1.s.y;
    a3 = l2.s.x;
    b3 = l2.e.x - l2.s.x;
    a4 = l2.s.y;
    b4 = l2.e.y - l2.s.y;
    double t2 = (a1*b2-a2*b1-a3*b2+a4*b1)/(b3*b2-b4*b1);
    return Point(l2.s.x + b3*t2, l2.s.y + b4*t2);
}

Line l[300+10];
Point p[1000+10];
vector<Point> llink[300+10];
int n, m, tot;
vector<int> G[maxn];
int vis[maxn], cannot[maxn];
int endd, start;
Point newp[maxn];
Point zhap[maxn];
int zhapn;

int iszha(Point x, int &ans)
{
    int pos = lower_bound(zhap, zhap+zhapn, x) - zhap;
    if(zhap[pos] == x)
    {
        ans = zhap[pos].id;
        return 1;
    }
    return 0;
}

void bfs_first()
{
    memset(vis, 0, sizeof(vis));
    memset(cannot, 0, sizeof(cannot));
    queue<int> que;
    vis[endd] = 1;
    cannot[endd] = 1;
    que.push(endd);
    while(!que.empty())
    {
        int u = que.front();
        que.pop();
        int tmpans;
        if(newp[u].tag==2 || iszha(newp[u], tmpans))
            continue;
        for(int i = 0; i<G[u].size(); i++)
        {
            int v = G[u][i];
            if(!vis[v])
            {
                cannot[v] = 1;
                int tmpans;
                if (iszha(newp[v], tmpans)) {
                    v = tmpans;
                }
                cannot[v] = 1;
                vis[v] = 1;
                que.push(v);
            }
        }
    }
}
double bfs_second()
{
    memset(vis, 0, sizeof(vis));
    queue<int> que;
    vis[start] = 1;
    que.push(start);
    double ans = 0;
    while(!que.empty())
    {
        int u = que.front();
        que.pop();
        int tmpans = -1;
        if(iszha(newp[u], tmpans))
        {
            if(tmpans != -1 && cannot[tmpans])
                continue;
        }
        if(cannot[u])
            continue;
        for(int i = 0; i<G[u].size(); i++)
        {
            int v = G[u][i];
            if(!vis[v])
            {
                ans += dist(newp[u], newp[v]);
                vis[v] = 1;
                que.push(v);
            }
        }
    }
    return ans;
}

void solve()
{
    for(int i = 1; i<=n; i++)
    {
        llink[i].clear();
    }
    tot = 0;
    for(int i = 1; i<=n; i++)
    {
        l[i].s.id = tot;
        l[i].s.tag = 1;
        newp[tot] = l[i].s;
        llink[i].push_back(newp[tot]);
        tot++;
        l[i].e.id = tot;
        l[i].e.tag = 1;
        newp[tot] = l[i].e;
        llink[i].push_back(newp[tot]);
        tot++;
        for(int j = i+1; j<=n; j++)
        {
            if(inter(l[i], l[j]))
            {
                Point tmp = inter_Point(l[i], l[j]);
                tmp.id = tot;
                tmp.tag = 1;
                newp[tot] = tmp;
                tot++;
                tmp.tag = 1;
                llink[i].push_back(tmp);
                llink[j].push_back(tmp);
            }
        }
    }
    for(int i = 1; i<=m; i++)
    {
        p[i].id = tot;
        p[i].tag = 2;
        newp[tot] = p[i];
        tot++;
        for(int j = 1; j<=n; j++)
        {
            if(OnSeg(p[i], l[j]))
            {
                llink[j].push_back(p[i]);
            }
        }
    }
    for(int i = m+1; i<=m+2; i++)
    {
        p[i].id = tot;
        p[i].tag = 3;
        newp[tot] = p[i];
        tot++;
        for(int j = 1; j<=n; j++)
        {
            if(OnSeg(p[i], l[j]))
            {
                llink[j].push_back(p[i]);
            }
        }
    }

    start = p[m+1].id;
    endd = p[m+2].id;
    zhapn = 0;
    for(int i = 0;i<tot;i++)
    {
        if(newp[i].tag==2)
        {
            zhap[zhapn] = newp[i];
            zhapn++;
        }
    }
    sort(zhap, zhap+zhapn);
    for(int i = 1; i<=n; i++)
    {
        sort(llink[i].begin(), llink[i].end());
    }
    //     for (int i = 1; i <= n; ++ i) {
    //  for (int j = 0; j < llink[i].size(); ++ j) {
    //      printf("%.2f %.2f--", llink[i][j].x, llink[i][j].y);
    //                }
    //   printf("\n");
    //   }
    for(int i = 0; i<tot; i++)
        G[i].clear();
    for(int i = 1; i<=n; i++)
    {
        for(int j = 0; j<llink[i].size()-1; j++)
        {
            int k = j+1;
            int idu = llink[i][j].id, idv = llink[i][k].id;
            G[idu].push_back(idv);
            G[idv].push_back(idu);
        }
    }
    bfs_first();
    if(cannot[start])
        printf("-1\n");
    else
    {
        double ans = bfs_second();
        double sum = 0;
        for(int i = 1; i<=n; i++)
        {
            sum += dist(l[i].s, l[i].e);
        }
        printf("%.10f\n", sum - ans);
    }
}

int main()
{
    freopen("in.txt", "r", stdin);
    //freopen("8Hout.txt", "w", stdout);
    while(scanf("%d%d", &n, &m) != EOF)
    {
        for(int i = 1;i<=n;i++)
            scanf("%lf%lf%lf%lf", &l[i].s.x, &l[i].s.y, &l[i].e.x, &l[i].e.y);
        for(int i = 1;i<=m+2;i++)
        {
            scanf("%lf%lf", &p[i].x, &p[i].y);
        }
        solve();
    }
    return 0;
}