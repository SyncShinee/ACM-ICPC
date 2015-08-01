#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define lson l,m,k<<1
#define rson m+1,r,k<<1|1
#define INF -2000000000
typedef long long ll;
const int N = 1e5 + 10;
struct T
{
    ll a[4];
}f[N<<2];

/*
奇奇
奇偶
偶偶
偶奇
*/
int n,q;
int x[N];
T put(T a, T b)
{
    T c;
    c.a[0] = max(a.a[0] + b.a[3] ,a.a[1] + b.a[0]);
    c.a[1] = max(a.a[0] + b.a[2] ,a.a[1] + b.a[1]);
    c.a[2] = max(a.a[2] + b.a[1] ,a.a[3] + b.a[2]);
    c.a[3] = max(a.a[2] + b.a[0] ,a.a[3] + b.a[3]);
    c.a[0] = max(a.a[0],c.a[0]);
    c.a[0] = max(b.a[0],c.a[0]);

    c.a[1] = max(a.a[1],c.a[1]);
    c.a[1] = max(b.a[1],c.a[1]);

    c.a[2] = max(a.a[2],c.a[2]);
    c.a[2] = max(b.a[2],c.a[2]);

    c.a[3] = max(a.a[3],c.a[3]);
    c.a[3] = max(b.a[3],c.a[3]);

    return c;
}
void mk(int l,int r,int k)
{
    for (int i = 0;i < 4;i++) f[k].a[i] = INF;

    if (l == r)
    {

        if (l & 1)
        {
            f[k].a[0] = x[l];
        }
        else
        {
            f[k].a[2] = x[l];
        }
        return ;
    }
    int m = (l + r) >> 1;
    mk(lson);
    mk(rson);
    f[k] = put(f[k<<1],f[k<<1|1]);
}
void update(int pos,int l,int r,int k,ll d)
{
    if (l == pos && r == pos)
    {
        for (int i = 0;i < 4;i++) f[k].a[i] = INF;
        if (l & 1)
        {
            f[k].a[0] = d;
        }
        else
        {
            f[k].a[2] = d;
        }
        return;
    }

    int m = (l + r) >> 1;

    if (pos <= m) update(pos,lson,d);
    if (pos > m) update(pos,rson,d);

    f[k] = put(f[k<<1],f[k<<1|1]);
}
T query(int la,int ra,int l,int r,int k)
{
    if (la <= l && r <= ra)
    {
        return f[k];
    }

    int m = (l + r) >> 1;

    if (ra <= m) return query(la,ra,lson);
    if (la > m) return query(la,ra,rson);
    if (la <= m && ra > m)
    {
        T tmp1 = query(la,ra,lson);
        T tmp2 = query(la,ra,rson);
        return put(tmp1,tmp2);
    }
}
int main()
{
  //  freopen("in.txt","r",stdin);
    int t;
    scanf("%d",&t);
    while (t--)
    {
        scanf("%d %d",&n,&q);

        for (int i = 1;i <= n; i++) scanf("%d",&x[i]);

        mk(1,n,1);
        //query(2,4,1,n,1,0);

        for (int i = 1;i <= q;i++)
        {
            int a,b,c;
            scanf("%d%d%d",&a,&b,&c);

            if (a == 0)
            {
                T ans = query(b,c,1,n,1);
                ll aans = INF;
                aans = max(ans.a[0],aans);
                aans = max(ans.a[1],aans);
                aans = max(ans.a[2],aans);
                aans = max(ans.a[3],aans);
                printf("%I64d\n",aans);
            }
            else
            {
                update(b,1,n,1,c);
            }
        }
    }
}