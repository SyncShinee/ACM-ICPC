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

const int maxn = 3e4 + 1000;//开大一点
const int INF = INT_MAX/2 - 1;


const int MAX_K = 10010;
int q_front, q_tail;
struct node
{
    int no, number;
};
node q[MAX_K];
int n;

int tot, val[110], num[110], dp_buy[maxn], dp_change[maxn];
int key;
void getDpChange()
{
    fill(dp_change, dp_change + 1 + key, INF);
    //memset(dp_change, -1, sizeof(dp_change));
    dp_change[0] = 0;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 0; j <= key; j++)
        {
            if(j - val[i] >= 0 && dp_change[j - val[i]] >= 0 && dp_change[j - val[i]] + 1 < dp_change[j])
            {
                dp_change[j] = dp_change[j - val[i]] + 1;
            }
        }
    }
}

void zeroOneP(int n, int v)//cost是v，val是n，01背包的逆序更新
{
    for(int j = key; j >= v; j--)
    {
        dp_buy[j] = min(dp_buy[j], dp_buy[j - v] + n);
    }
}
void getDpBuy_old()//多重背包
{
    fill(dp_buy, dp_buy + key + 1, INF);
    dp_buy[0] = 0;
    for(int i = 1; i <= n; i++)
    {
        int k = 1;//k先1
        while(k < num[i])//小的时候
        {
            zeroOneP(k, k*val[i]);
            num[i] -= k;
            k *= 2;
        }
        zeroOneP(num[i], num[i]*val[i]);//剩下的都弄
    }
}

void pack_old(int tot, int cost, int val, int num)
{
    for(int i = tot;i >= 0;i--)
    {
        for(int j = 1;j <= num;j++)
        {
            if(i - j*cost >= 0 && dp_buy[i-j*cost] != INF)
                dp_buy[i] = min(dp_buy[i], dp_buy[i-j*cost]+j*val);
        }
    }
}
void get_pack(int tot, int cost, int val, int num)
{
    if(cost==0)
        return;
    for(int j = 0;j < cost;j++)
    {
       
        q_front = 1;
        q_tail = 0;
        int i = 0;
        for(int k = j;k <= tot;k = k + cost)
        {
            if (cost == 90) {
             printf("%d %d  %d\n", j, k, n);
             if (n == 199) {
                    return;
                }
            }
            
            while(q_front <= q_tail&&q[q_front].no < i - num)
            {
                q_front++;
            }
            if (cost == 90 && k == 17910) {
             printf("111111%d %d  %d\n", j, k, n);
             if (n == 199) {
                    return;
                }
            }
            if(dp_buy[k]!=INF)
            {
                int tt = dp_buy[k] - i*val;
                while(q_front<=q_tail&&q[q_tail].number>=tt)
                {
                    q_tail--;
                }
               
                q_tail++;
                q[q_tail].number = tt;
                q[q_tail].no = i;

             if (cost == 90 && k == 17910) {
             printf("7777777%d %d  %d-----------dp[%d\n", j, k, n, dp_buy[k]);
             if (n == 199) {
                    return;
                }
            }

            }
            
            if(q_front<=q_tail)
            {
                dp_buy[k] = q[q_front].number + i*val;
            }
            else
            {
                dp_buy[k] = INF;
            }
            if (cost == 90 && k == 17910) {
             printf("33333333333%d %d  %d\n", j, k, n);
             if (n == 199) {
                    return;
                }
            }
            i++;
            if (cost == 90 && k == 17910) {
             printf("444444%d %d  %d\n", j, k, n);
             if (n == 199) {
                    return;
                }
            }
        }
    }
//    for(int i = 0;i <= 50;i++)
//    {
//        printf("%d ---  %d --- %d\n", cost, i, dp_buy[i]);
//    }
}

void getDpBuy()
{
    fill(dp_buy, dp_buy + key + 1, INF);
    dp_buy[0] = 0;
    for(int i = 1; i <= n; i++)
    {
        get_pack(key, val[i], 1, num[i]);
    }
}
void solve(int m)
{
    getDpChange();
    getDpBuy();
    int ans = INF;
    for(int i = m; i <= key; i++) //选取一个个数最少的
    {
        if(dp_buy[i] < INF && dp_change[i - m] < INF && dp_buy[i] + dp_change[i-m] < ans)
        {
            ans = dp_buy[i] + dp_change[i-m];
        }
    }
    if(ans >= INF)
    {
        printf("-1\n");
    }
    else
    {
        printf("%d\n", ans);
    }
}

int main()
{
    //freopen("2Bin.txt", "r", stdin);
    //freopen("8Hout.txt", "w", stdout);
    while(scanf("%d%d", &n, &tot) != EOF)
    {
        key = 0;
        REP_D(i, 1, n)
        {
            scanf("%d", &val[i]);
            key = max(key, val[i]);
        }
        REP_D(i, 1, n)
        {
            scanf("%d", &num[i]);
        }
        key = tot + key*key;
        key = 3e4 + 10;
        solve(tot);
    }
    return 0;
}