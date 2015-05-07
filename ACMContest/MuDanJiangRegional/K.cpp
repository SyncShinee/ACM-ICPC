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

const int maxn = 1e3 +100;
int m, n, len, pos;
char s[maxn];

void getN()
{
    n = 0;
    for(int i = len - 1;i >= 0;i--)
    {
        if(s[i] == '*')
        {
            pos = i;
            break;
        }
        else
        {
            n++;
        }
    }
}
int solve(int have)
{
    ///zhishaoyou*
    m = 0;
    getN();
    for(int i = 0;i <= pos;i++)
    {
        if(s[i]=='*')
        {
            if(have >= 2)
            {
                have--;
            }
            else
            {
                if(have == 1)
                {
                    m += 1;
                }
            }
        }
        else
        {
            have += 1;
        }
    }
    if(m >= n)
    {
        return m;
    }
    else
    {
        return m+1;
    }
}

int main()
{
    freopen("11Kin.txt", "r", stdin);
    freopen("Kout.txt", "w", stdout);
    int ncase;
    int ans;
    scanf("%d", &ncase);
    while(ncase--)
    {
        scanf("%s", s);
        len = strlen(s);
        int flag = 0;
        for(int i = 0;i < len;i++)
        {
            if(s[i] == '*')
            {
                flag = 1;
                break;
            }
        }
        if(flag==0)
        {
            ans = 0;
        }
        else
        {
            if(s[0]!='*')
            {
                ans = solve(0);
            }
            else
            {
                ans = solve(2) + 2;
                ans = solve(1) + 1;
                for(int i = 1;i < len;i++)
                {
                    if(s[i]!='*')
                    {
                        char tmp = s[i];
                        s[i] = '*';
                        s[0] = tmp;
                        ans = min(ans, solve(0) + 1);
                        s[i] = s[0];
                        s[0] = '*';
                    }
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}