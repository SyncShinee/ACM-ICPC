#include <cstdio>
#include <cstring>

using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int a[N],l[N],r[N];
int d1,d2,n;
void init()
{
    for (int i = 1;i <= n;i++)
        l[i] = r[i] = i;
    for (int i = 2;i <= n;i++)
    if (a[i-1] + d1 == a[i])
        l[i] = l[i-1];
    for (int i = n - 1;i >= 1;i --)
    if (a[i+1] - d2 == a[i])
        r[i] = r[i+1];
}
void solve1()
{
    ll ans = 0;
    for (int i = 1;i <= n;i++)
    if (r[i] == i)
    {
        ll lent = i - l[i] + 1;
        ans += (lent + 1) * lent / 2;
    }
    printf("%I64d\n",ans);
}
void solve2()
{
    ll ans = 0;
    for (int i = 1;i <= n;i++)
        ans += (ll)(i - l[i] + 1) * (r[i] - i + 1);
    printf("%I64d\n",ans);
}
int main()
{
   // freopen("in.txt","r",stdin);
    while (~scanf("%d %d %d",&n,&d1,&d2))
    {
        for (int i = 1;i <= n;i++)
            scanf("%d",&a[i]);
        init();
        if (d1 == d2)
            solve1();
        else
            solve2();
    }
}