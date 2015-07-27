#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define lson l,(l+r)>>1,k<<1
#define rson ((l+r)>>1)+1,r,k<<1|1
typedef long long ll;
////////////////////////////////////////////////////////////////////////
char *ch, *ch1, buf[40*1024000+5], buf1[40*1024000+5];

void read(int &x) {
	for (++ch; *ch <= 32; ++ch);
	for (x = 0; '0' <= *ch; ch++)	x = x * 10 + *ch - '0';
}

void out(int x) {
	if (!x)	*(++ch1) = '0';
	else {
		char *ch0 = ch1, *ch = ch1 + 1;
		while (x) {
			*(++ch0) = x % 10 + '0';
			x /= 10;
		}
		ch1 = ch0;
		while (ch <= ch0)	swap(*(ch++), *(ch0--));
	}
	*(++ch1) = '\n';
}

void out(long long x) {
	if (!x)	*(++ch1) = '0';
	else {
		char *ch0 = ch1, *ch = ch1 + 1;
		while (x) {
			*(++ch0) = x % 10 + '0';
			x /= 10;
		}
		ch1 = ch0;
		while (ch <= ch0)	swap(*(ch++), *(ch0--));
	}
	*(++ch1) = '\n';
}
////////////////////////////////////////////////////////////////////////
const int N = 1e6 + 10;
struct T
{
    int Maxtag,Max,Tag,s,cover;
    int Tagtag;
    ll sum;
}f[N << 2];
int n,m,a[N];
T put(T c,int t)
{
    if (t == 0) return c;
    if (c.s != c.cover) c.Max = t;
    c.Maxtag = t;
    c.Tag = t;
    c.sum += 1LL * (c.s - c.cover) * t;
    c.cover = c.s;
    return c;
}
T calc(T a,T b)
{
    T c;
    c.Tag = 0;
    c.Tagtag = 0;
    c.s = a.s + b.s;
    c.cover = a.cover + b.cover;
    c.Maxtag = max(a.Maxtag,b.Maxtag);
    c.Max = max(a.Max,b.Max);
    c.sum = a.sum + b.sum;
    return c;
}
T calc(T a,T b,int t)
{
    T c;
    c.Tag = t;
    c.Tagtag = 1;
    c.s = a.s + b.s;
    c.cover = a.cover + b.cover;
    c.Maxtag = max(a.Maxtag,b.Maxtag);
    c.Max = max(a.Max,b.Max);
    c.sum = a.sum + b.sum;
    return put(c,t);
}
void Clear(int k,int t)
{
    if (t > f[k].Maxtag) return;

    if (f[k].Tag >= t)
        f[k].Tagtag = 0,
        f[k].Tag = 0;


    if (f[k].s != 1)
    {
        Clear(k<<1,t);
        Clear(k<<1|1,t);
        if (f[k].Tagtag ) f[k] = calc(f[k<<1],f[k<<1|1],f[k].Tag);
        else
            f[k] = calc(f[k<<1],f[k<<1|1]);
    }
    else
    {
        f[k].sum = f[k].Maxtag = f[k].Max = f[k].Tag;
        f[k].cover = (f[k].Tagtag > 0);
    }
}

void maketree(int l,int r,int k)
{
    f[k].Tag = 0;
    f[k].Tagtag = 0;
    f[k].s = r - l + 1;

    if (l == r)
    {
        f[k].s = 1;
        f[k].cover = 1;
        f[k].Tagtag = 1;
        f[k].sum = f[k].Tag = f[k].Maxtag = f[k].Max = a[l];
        return ;
    }
    maketree(lson);
    maketree(rson);

    f[k] = calc(f[k<<1],f[k<<1|1]);
}
void modify(int la,int ra,int l,int r,int k,int t)
{
    if (f[k].Tagtag && t > f[k].Tag) return;
    if (l >= la && r <= ra)
    {
        Clear(k,t);
        f[k].Tag = t;
        f[k].Tagtag = 1;

        if (l == r)
        {
            f[k].Maxtag = f[k].sum = f[k].Max = f[k].Tag;
            //f[k].cover = (f[k].Tag > 0);
            f[k].cover = (f[k].Tagtag > 0);
        }
        else
        {
            if (f[k].Tagtag ) f[k] = calc(f[k<<1],f[k<<1|1],f[k].Tag);
            else
                f[k] = calc(f[k<<1],f[k<<1|1]);
        }
        return;
    }
    int m = (l + r) >> 1;
    if (la <= m) modify(la,ra,lson,t);
    if (ra > m) modify(la,ra,rson,t);

    if (f[k].Tagtag ) f[k] = calc(f[k<<1],f[k<<1|1],f[k].Tag);
    else
        f[k] = calc(f[k<<1],f[k<<1|1]);
}
T query(int la,int ra,int l,int r,int k)
{
    if (l >= la && r <= ra)
    {
        return f[k];
    }
    int m = (l + r) >> 1;
    if (la > m) return put(query(la,ra,rson),f[k].Tag);
    if (ra <= m) return put(query(la,ra,lson),f[k].Tag);

    if (f[k].Tagtag ) return calc(query(la,ra,lson),query(la,ra,rson),f[k].Tag);
    else
        return calc(query(la,ra,lson),query(la,ra,rson));
}

int main()
{
    ///////////////////////////////////
    ch = buf - 1;
	ch1 = buf1 - 1;
	fread(buf, 1, 1000 * 35 * 1024, stdin);
    ///////////////////////////////////
    int t;
    //scanf("%d",&t);
    read(t);
    while (t--)
    {
        //printf("%d\n",t);
        //scanf("%d%d",&n,&m);
        read(n);read(m);
        //printf("%d %d\n",n,m);
        for (int i = 1;i <= n;i++)
            //scanf("%d",&a[i]);
            read(a[i]);
        maketree(1,n,1);

        for (int i = 1;i <= m;i++)
        {
            int x,y,z,q;
            //scanf("%d",&q);scanf("%d %d",&x,&y);
            read(q);read(x);read(y);
            if (q == 0)
            {
                //scanf("%d",&z);
                read(z);
                modify(x,y,1,n,1,z);
            }
            if (q == 1)
            {
                //printf("%d\n",query(x,y,1,n,1).Max);
                out(query(x,y,1,n,1).Max);
            }
            if (q == 2)
            {
                //printf("%I64d\n",query(x,y,1,n,1).sum);
                out(query(x,y,1,n,1).sum);
            }
        }
    }
    fwrite(buf1, 1, ch1 - buf1 + 1, stdout);
}
