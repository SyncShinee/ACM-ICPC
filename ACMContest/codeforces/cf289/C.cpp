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

const int maxn = 500;

int b[maxn];
int sum[maxn];
char a[maxn][maxn];
int n;

int ti(char a[], int sum, int key)
{
    if(sum >= 0 && sum <= 9*key)
    {
        for(int i = 0;i < key;i++)
        {
            if(sum >= 9)
            {
                a[i] = '9';
                sum -= 9;
            }
            else
            {
                a[i] = sum + '0';
                sum = 0;
            }
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

void getOk(char a[], char b[], int key)
{
    int n = strlen(a);
    sum[0] = a[0] - '0';
    REP(i, 1, n)
    {
        sum[i] = sum[i - 1] + a[i] - '0';
    }
    for(int i = 0; i < n; i++)
    {
        int t = key;
        t -= (sum[n - 1] - sum[i]);
        for(int j = a[i] - '0' + 1; j <= 9; j++)
        {
            if(ti(b, t - j, i))
            {
                b[i] = j + '0';
                for(int k = i + 1; k < n; k++)
                {
                    b[i] = a[i];
                }
                return;
            }
        }
    }
    int tmp = n + 1;
    while(tmp*9 < key)
    {
        tmp++;
    }
    for(int i = 1;i <= 9;i++)
    {
        if(ti(b, key - i, tmp - 1))
        {
            b[tmp - 1] = i + '0';
            return;
        }
    }
}

void solve()
{
    CLR(a);
    a[0][0] = '0';
    REP_D(i, 1, n)
    {
        getOk(a[i - 1], a[i], b[i]);
    }
    REP_D(i, 1, n)
    {
        int t = strlen(a[i]);
        for(int j = t-  1;j >= 0;j--)
        {
            printf("%c", a[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    freopen("3Cin.txt", "r", stdin);
    //freopen("3Cout.txt", "w", stdout);
    while(scanf("%d", &n) != EOF)
    {
        REP_D(i, 1, n)
        {
            scanf("%d", &b[i]);
        }
        solve();
    }
    return 0;
}
