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

const ll maxn = 1e5 + 100;

ll a[maxn], b[maxn];
ll key, n;

ll m;
struct node
{
    ll x, y;
    node()
    {

    }
    node (ll _x = 0, ll _y = 0)
    {
        x = _x;
        y = _y;
    }
};
vector<node> ans;

void gao()
{
    for(ll i = 1;i<=n-1;i++)
    {
        if(a[i]==key)
        {
            ;
        }
        else if(a[i]==key - 1)
        {
            m++;
            ans.push_back(node(i+1, i));
            a[i]++;
            a[i+1]--;
        }
        else if(a[i] == key + 1)
        {
            m++;
            ans.push_back(node(i, i+1));
            a[i]--;
            a[i+1]++;
        }
        else
        {
            m = -1;
            break;
        }
    }
    if(a[n] == key)
    {
        ;
    }
    else
    {
        m = -1;
    }
}

void solve()
{
    ans.clear();
    m = 0;
    gao();
    if(m != -1)
    {
        printf("YES\n");
        printf("%I64d\n", m);
        for(ll i = 0;i<ans.size();i++)
        {
            printf("%I64d %I64d\n", ans[i].x, ans[i].y);
        }
        return;
    }
    for(ll i = 1;i<=n;i++)
    {
        a[i] = b[i];
    }
    ans.clear();
    ans.push_back(node(n, 1));
    m = 1;
    a[1]++;
    a[n]--;
    gao();
    if(m != -1)
    {
        printf("YES\n");
        printf("%I64d\n", m);
        for(ll i = 0;i<ans.size();i++)
        {
            printf("%I64d %I64d\n", ans[i].x, ans[i].y);
        }
        return;
    }
    for(ll i = 1;i<=n;i++)
    {
        a[i] = b[i];
    }
    ans.clear();
    ans.push_back(node(1, n));
    m = 1;
    a[1]--;
    a[n]++;
    gao();
    if(m != -1)
    {
        printf("YES\n");
        printf("%I64d\n", m);
        for(ll i = 0;i<ans.size();i++)
        {
            printf("%I64d %I64d\n", ans[i].x, ans[i].y);
        }
        return;
    }
    printf("NO\n");
}
ll sum;
int main()
{
    //freopen("1Ain.txt", "r", stdin);
    //freopen("1Aout.txt", "w", stdout);
    ll ncase;
    scanf("%I64d", &ncase);
    while(ncase--)
    {
        sum = 0;
        scanf("%I64d", &n);
        REP_D(i, 1, n)
        {
            scanf("%I64d", &a[i]);
            b[i] = a[i];
            sum += a[i];
        }
        if(sum%n!=0)
        {
            printf("NO\n");
        }
        else
        {
            key = sum/n;
            solve();
        }
    }
    return 0;
}