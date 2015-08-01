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

///max_v, V, get_G, 0 ~ V - 1;
//v*E;
const int MAXN = 1e4 + 100;
const int INF = INT_MAX/2 - 1;
vector<int> G[MAXN];
int V;
int m, n;
int match[MAXN], used[MAXN];
void add_edge(int from, int to)
{
    G[from].push_back(to);
    G[to].push_back(from);
}
int dfs(int v)
{
    used[v] = 1;
    for(int i = 0; i < G[v].size(); i++)
    {
        int u = G[v][i], w = match[u];
        if(w < 0 || (!used[w] && dfs(w)))
        {
            match[u] = v;
            match[v] = u;
            return 1;
        }
    }
    return 0;
}
int b_match()
{
    int res = 0;
    fill(match, match + V, -1);
    for(int i = 0; i < V; i++)//其实到m就行了.
    {
        if(match[i] < 0)
        {
            CLR(used);
            if(dfs(i))
            {
                res++;
            }
        }
    }
    return res;
}
char s[60][60];
int check(int x, int y)
{
    if(x >= 0 && x < n && y>=0 && y<m)
        return 1;
    return 0;
}
void solve()
{
    V = 2*n*m;
    int sum = 0;
    REP(i, 0, V)
    {
        G[i].clear();
    }
    REP(i, 0, n)
    {
        REP(j, 0, m)
        {
            if(s[i][j]=='G' || s[i][j]=='R')
            {
                sum++;
                int newI = i-1, newJ = j-1;
                if(check(newI, newJ) && (s[newI][newJ]=='G'||s[newI][newJ]=='R'))
                {
                    add_edge(newI*m+newJ, n*m+i*m+j);
                }

            }
        }
    }
    int ans = sum - b_match();
    sum = 0;
    REP(i, 0, V)
    {
        G[i].clear();
    }
    REP(i, 0, n)
    {
        REP(j, 0, m)
        {
            if(s[i][j]=='G' || s[i][j]=='B')
            {
                sum++;
                int newI = i-1;

                int newJ = j + 1;
                if(check(newI, newJ) && (s[newI][newJ]=='G'||s[newI][newJ]=='B'))
                {
                    add_edge(newI*m+newJ, n*m+i*m+j);
                }
            }
        }
    }
    ans += sum-b_match();
    printf("%d\n", ans);
}


int main()
{
    //freopen("13Min.txt", "r", stdin);
    //freopen("1out.txt", "w", stdout);
    int ncase;
    scanf("%d", &ncase);
    while(ncase--)
    {
        scanf("%d", &n);
        REP(i, 0, n)
        {
            scanf("%s", s[i]);
        }
        m = strlen(s[0]);
        solve();
    }
    return 0;
}