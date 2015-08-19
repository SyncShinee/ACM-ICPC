#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 1e5 + 10;
struct edge
{
    int x,y;
    int w;
}e[N];
int f[N],n,tot;
int com(edge a,edge b)
{
    return a.w > b.w;
}
int gcd(int a,int b)
{
    if (b == 0) return a;
    return gcd(b,a%b);
}
int findx(int x)
{
    if (f[x] == x) return x;
    return f[x] = findx(f[x]);
}
int main()
{
    freopen("out.txt","w",stdout);
    for (int n = 6;n <= 6;n++)
    {
        tot = 0;
        for (int i = 1;i <= n;i++) f[i] = i;
        for (int i = 1;i <= n;i++)
            for (int j = 1;j <= n;j++)
                if (i != j)
                {
                    tot++;
                    e[tot].x = i;
                    e[tot].y = j;
                    e[tot].w = gcd(i,j);
                }
        sort(e+1,e+tot+1,com);
        int ans = 0;
        for (int i = 1;i <= tot;i++)
        {
            int fa = findx(e[i].x);
            int fb = findx(e[i].y);
            if (fa != fb)
            {
                printf("%d %d %d\n",e[i].x,e[i].y,e[i].w);
                ans += e[i].w;
                f[fa] = fb;
            }
        }
        printf("%d %d\n",n, ans);
    }
}
