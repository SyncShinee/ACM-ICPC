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

const int maxn = 300000 + 100;
const int INF = 0;
const int MAX_NODE = maxn*4 + 10;

int tree[MAX_NODE], late[MAX_NODE];
char s[maxn];
int a[maxn];
int n, rtn, q;
set<int> you;

void pushUp(int rt)
{
    int lRt = (rt<<1), rRt = ((rt<<1)|1);
    tree[rt] = min(tree[lRt], tree[rRt]);
}

void initail()
{
    CLR(late);
    rtn = 1;
    while(rtn < n)
    {
        rtn <<= 1;
    }
    for(int i = 1;i<=n;i++)
    {
        tree[i+rtn-1] = a[i];
    }
    for(int i = rtn+n;i<rtn*2;i++)
    {
        tree[i] = 1e9;
    }
    for(int i = rtn-1;i>=1;i--)
    {
        pushUp(i);
    }
}

void pushDown(int rt)
{
    if(late[rt] == INF)
        return;
    int lRt = (rt<<1), rRt = ((rt<<1)|1);
    int key = late[rt];
    late[rt] = INF;
    late[lRt] += key;
    tree[lRt] += key;
    late[rRt] += key;
    tree[rRt] += key;
}


void change(int L, int R, int key, int rt, int l, int r)
{
    if(L <= l && R >= r)
    {
        late[rt] += key;
        tree[rt] += key;
        return;
    }
    pushDown(rt);
    int mid = ((l + r)>>1), lRt = (rt<<1), rRt = ((rt<<1)|1);
    if(L <= mid)
    {
        change(L, R, key, lRt, l, mid);
    }
    if(R >= mid + 1)
    {
        change(L, R, key, rRt, mid + 1, r);
    }
    pushUp(rt);
}
int query(int rt, int l, int r)
{
    if(l==r)
    {
        return l;
    }
    pushDown(rt);
    int mid = ((l + r)>>1), lRt = (rt<<1), rRt = ((rt<<1)|1);
    if(tree[rRt] >= 2)
    {
        return query(lRt, l, mid);
    }
    else
    {
        return query(rRt, mid+1, r);
    }
}



int query(int L, int R, int rt, int l, int r)
{
    if(L <= l && R >= r)//全包括
    {
        return tree[rt];
    }
    pushDown(rt);//下一次层延迟
    int ans = INF, mid = ((l + r)>>1), lRt = (rt<<1), rRt = ((rt<<1)|1);
    if(L <= mid)
    {
        ans = min(ans, query(L, R, lRt, l, mid));
    }
    if(R >= mid + 1)
    {
        ans = min(ans, query(L, R, rRt, mid + 1, r));
    }
    return ans;
}

void solve()
{
    you.clear();
    a[0] = 0;
    for(int i = 1;i<=n;i++)
    {
        a[i] = a[i-1];
        if(s[i]=='(')
        {
            a[i]++;
        }
        else
        {
            you.insert(i);
            a[i]--;
        }
    }
    initail();
    int ans;
    while(q--)
    {
        int x;
        scanf("%d", &x);
        if(s[x] == '(')
        {
            s[x] = ')';
            change(x, n, -2, 1, 1, rtn);
            you.insert(x);
            ans = (*you.begin());
            printf("%d\n", ans);
            s[ans] = '(';
            change(ans, n, 2, 1, 1, rtn);
            you.erase(you.begin());
        }
        else
        {
            s[x] = '(';
            change(x, n, 2, 1, 1, rtn);
            you.erase(x);
            ans = query(1, 1, rtn);
            ans++;
            printf("%d\n", ans);
            s[ans] = ')';
            change(ans, n, -2, 1, 1, rtn);
            you.insert(ans);
        }
    }
}

int main()
{
   // freopen("7Gin.txt", "r", stdin);
    //freopen("7Gout.txt", "w", stdout);
    while(scanf("%d%d", &n, &q)!=EOF)
    {
        scanf("%s", s+1);
        solve();
    }
    return 0;
}