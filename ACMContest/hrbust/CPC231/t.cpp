#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
int state[100010],father[100010],num[100010],N,M,x,y;
int find(int x)
{
    if (x == father[x]) return x;
    else return father[x] = find(father[x]);
}
int cas;
int main()
{
    while (scanf("%d %d",&N,&M),N||M)
    {
        cas++;
        for (int i = 0 ; i < M ; i++)
        {
            father[i] = i;
            state[i] = 0;
            num[i] = 1;
        }
        for (int i = 0 ; i < N ; i++)
        {
            scanf("%d %d",&x,&y);
            if (x == y)
            {
                int temp = find(x);
                if (state[temp] == 0)
                {
                    state[temp] = 1;
                    num[temp] = 1;
                }
                else
                {
                    state[temp] = 1;
                    num[temp] = 0;
                }
            }
            else
            {
                int temp1 = find(x);
                int temp2 = find(y);
                if (temp1 == temp2)
                {
                    if (state[temp1])  num[temp1] = 0;
                    else
                    {
                        state[temp1] = 2;
                        num[temp1] = 2;
                    }
                }
                else
                {
                    if (state[temp1] == 0 && state[temp2] == 0)
                    {
                        father[temp2] = temp1;
                        num[temp1] += num[temp2];
                    }
                    else if (state[temp1] == 0)
                    {
                        if (num[temp2] != 0)
                        {
                            father[temp2] = temp1;
                            state[temp1] = state[temp2];
                            if (state[temp2] == 1)  num[temp1] = 1;
                            else    num[temp1] = 2;
                        }
                        else
                        {
                            father[temp2] = temp1;
                            state[temp1] = state[temp2];
                            num[temp1] = 0;
                        }
                    }
                    else if (state[temp2] == 0)
                    {
                        father[temp2] = temp1;
                    }
                    else
                    {
                        father[temp2] = temp1;
                        num[temp1] = 0;
                    }
                }
            }
        }
        long long ans = 1;
        for (int i = 0 ; i < M ; i++)
            if (find(i) == i)
            {
                ans *= (long long)num[i];
                if (ans == 0)   break;
                ans %= 1000000007;
            }
        printf("Case %d: %I64d\n",cas,ans);
    }
    return 0;
}