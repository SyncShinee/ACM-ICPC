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
#define REP(i, a, b) for(ll i = a;i < b;i++)
#define REP_D(i, a, b) for(ll i = a;i <= b;i++)

typedef long long ll;

using namespace std;

const ll maxn = 60 + 10;
const ll M = 1e9 + 7.1;
ll a[maxn], b[maxn], c[maxn], d[maxn], l[maxn];
ll num[maxn], sum[maxn];
//ll keyD[maxn];
ll m;
map<ll, map<ll, ll> > mp;
map<ll,map<ll, map<ll, map<ll,map<ll,ll> > > > > mp2;

ll getDist(ll A, ll B, ll xa, ll xb, ll C)
{
    if (mp2[A][B][xa][xb].count(C))
        return mp2[A][B][xa][xb][C];
    if(C == 0)
    {
        return mp2[A][B][xa][xb][C] = 0;
    }
    if(xa == xb)
        return mp2[A][B][xa][xb][C] = 0;
    if(xa < num[A] && xb < num[A])
    {
        return mp2[A][B][xa][xb][C] = getDist(a[A], b[A], xa, xb, A);
    }
    if(xa >= num[A] && xb >= num[A])
    {
        return mp2[A][B][xa][xb][C] = getDist(a[B], b[B], xa - num[A], xb - num[A], B);
    }
    if(xa > xb)
        swap(xa, xb);
    return mp2[A][B][xa][xb][C] = (getDist(a[A], b[A], xa, c[C], A) + l[C] + getDist(a[B], b[B], xb-num[A], d[C], B))%M;
}

ll gao(ll C, ll x)
{
    if(mp[C].count(x))
    {
        return mp[C][x];
    }
    if(C==0)
        return 0;
    ll A = a[C], B = b[C];
    ll xa = c[C], xb = d[C];
    ll ans;
    if(x < num[A])
    {
        ans = 0;
        ans = gao(B, xb);
        ll tmpD = getDist(A, B, x, xb+num[A], C);
        ans = (ans + tmpD*(num[B]%M)%M)%M;
        ans = (ans + gao(A, x))%M;
    }
    else
    {
        ans = 0;
        ans = gao(A, xa);
        ll tmpD = getDist(A, B, x, xa, C);
        ans = (ans + tmpD*(num[A]%M)%M)%M;
        ans = (ans + gao(B, x - num[A]))%M;
    }
    mp[C][x] = ans;
    return ans;
}

void solve()
{
    mp.clear();
    mp2.clear();
    num[0] = 1;
    sum[0] = 0;
    //keyD[0] = 0;
    for(ll i = 1;i<=m;i++)
    {
        ll A = a[i], B = b[i], xa = c[i], xb = d[i];
        num[i] = num[A]+num[B];
        sum[i] = (sum[A]+sum[B])%M;
        sum[i] = (sum[i] + l[i]*(num[A]%M)%M*(num[B]%M)%M)%M;
        sum[i] = (sum[i] + gao(A, xa)*(num[B]%M)%M + gao(B, xb)*(num[A]%M)%M)%M;
        printf("%I64d\n", sum[i]);
    }
}

int main()
{
    //freopen("in.txt", "r", stdin);
    //freopen("6Fout.txt", "w", stdout);
    while(scanf("%I64d", &m) != EOF)
    {
        REP_D(i, 1, m)
        {
            scanf("%I64d%I64d%I64d%I64d%I64d", &a[i], &b[i], &c[i], &d[i], &l[i]);
        }
        solve();
    }
    return 0;
}