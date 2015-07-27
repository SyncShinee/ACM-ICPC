#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;
const int N = 5e5 + 10;
int n,m,k;
int a[N];
int cnt[N];
bool vis[N];
int f[N];

struct L
{
    int l,r;
    L () {}
    L (int _l,int _r):l(_l),r(_r) {}
    bool operator <(const L & b) const
    {
        if (l == b.l) return r > b.r;
        return l < b.l;
    }
};
vector <L> b;
vector <L> c;
bool check(int x)
{
    int id = c.size() - 1;
    cnt[c[id].r+1] = 0;
    for (int i = c[id].r;i >= c[id].l;i--)
    {
        f[i] = 1;
        cnt[i] = cnt[i+1] + f[i];
    }

    for (int i = c[c.size() - 1].l - 1;i >= 1;i--)
    {
        if (id > -1 && i < c[id].l)
        {
            id--;
        }

        if (i + x <= n && i + x <= c[id+1].r)
            f[i] = ((cnt[i + x] - cnt[c[id+1].r + 1]) > 0) ? 1 : 0;
        else
            f[i] = 0;
        cnt[i] = f[i] + cnt[i+1];
    }

    for (int i = 1;i <= c[0].r;i++) if (f[i] > 0) return 1;
    return 0;
}

int main()
{
    while (~scanf("%d %d %d",&n,&m,&k))
    {
        static int ca = 0;

        memset(vis,0,sizeof vis);
        b.clear();
        c.clear();
        for (int i = 1;i <= n;i++)
        {
            int x;scanf("%d",&x);
            a[i] = a[i-1] + x;
        }
        bool die = 0;
        for (int i = 1;i <= n;i++)
        {
            int now = m - a[i];
            if (now > 0) continue;
            int D = 1 - now;
            int l = (D + k - 1)/k;
            if (l > i-1)
            {
                die = 1;
                break;
            }
            b.push_back(L(l,i-1));
        }

        if (die)
        {
            puts("Poor Hero!");
            continue;
        }
        sort(b.begin(),b.end());
        int MM = 2e9;
        for (int i = b.size() - 1;i >= 0;i--)
        {
            if (b[i].r >= MM)
            {
                vis[i] = 1;
                continue;
            }
            MM = b[i].r;
        }
        for (int i = 0;i < b.size();i++)
        if (vis[i] == 0)
            c.push_back(b[i]);

        int MX1 = c[0].r,MX2 = c[c.size() - 1].l;
        for (int i = 1;i < c.size();i++)
        {
            MX1 = min(c[i].r,MX1);
        }

        if (MX1 >= MX2 || c.size() == 0)
        {
            puts("Poor JRY!");
            continue;
        }

        int l = 1,r = n+1;

        while (l < r - 1)
        {
            int m = (l + r) >> 1;
            if (check(m))
                l = m;
            else
                r = m;
        }

        vector <int> ans;
        check(l);
        printf("%d\n",l);


        int now = 1;
        for (int i = 1;i <= c[c.size() - 1].r;i++)
        if (f[i])
        {
            ans.push_back(i);
            if (i >= c[c.size() - 1].l) break;
            i += l - 1;
        }

        printf("%d\n",ans.size());
        for (int i = 0;i < ans.size();i++)
            printf("%d%c",ans[i]," \n"[i == (ans.size() - 1)]);
    }
}
