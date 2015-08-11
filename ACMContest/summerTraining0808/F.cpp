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

const int maxn = 1e6 + 10;
char str[maxn];
int n;
int sum[maxn];

int gao(int start, int endd, int have, int numa)
{
    int nowendd = endd;
    int flag = 0;
    int num = numa;
    for(int i = start; i<=nowendd; i++)
    {
        if(str[i]=='a')
        {
            num++;
        }
        else
        {
            if(num >= 2)
            {
                num--;
            }
            else
            {
                if(str[i+1]=='a')
                {
                    flag++;
                    have++;
                    str[i+1] = '+';
                    str[i] = 'a';
                    num++;
                }
                else
                {
                    if(flag >= 1)
                    {
                        flag--;
                        have++;
                    }
                    else
                    {
                        have += 2;
                    }
                }
            }
        }
    }

    return have;
}

void solve()
{
    int ans = 0;
    int numa=0, numb=0;
    int n = strlen(str + 1);
    for(int i = 1; i<=n; i++)
    {
        if(str[i]=='a')
        {
            numa++;
        }
        else
        {
            numb++;
        }
    }
    if(numa < numb + 1)
    {
        ans = gao(1, n, numb+1-numa, numb+1-numa);
    }
    else
    {
        if(str[1]=='+'&&str[2]=='a')
        {
            str[1] = 'a';
            str[2] = '+';
            ans = gao(1, n, 1 + numa-1-numb, 0);
            str[1] = '+';
            str[2] = 'a';
            ans = min(ans, gao(1, n, 2, 1) );
        }
        else if(str[1]=='+')
        {
            ans = gao(1, n, 4 + numa - 1 - numb, 2);
        }
        else
        {
            ans = gao(1, n, numa-1-numb, 0);
        }
    }
    printf("%d\n", ans);
}

int main()
{
    //freopen("6Fin.txt", "r", stdin);
    //freopen("6Fout.txt", "w", stdout);
    //////////dayudengyu  22222222
    int ncase;
    scanf("%d", &ncase);
    for(int _ = 1; _<=ncase; _++)
    {
        printf("Case %d: ", _);
        scanf("%s", str + 1);
        int n = strlen(str+1);
        if(n == 1)
        {
            if(str[1] == 'a')
            {
                printf("0\n");
            }
            else
            {
                printf("2\n");
            }
        }
        else
        {
            solve();
        }
    }
    return 0;
}