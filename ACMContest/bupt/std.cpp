#include <fstream>
#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#define N 150
using namespace std;

int dp[N][N][17];
int a[N];
int n;

void init()
{
    memset(dp,0,sizeof(dp));

}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("std.out", "w", stdout);
    int T;
    cin>>T;
    while (T--)
    {
        int n,ans=1;
        scanf("%d",&n);
        for (int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        init();
        for (int i=1;i<=n;i++)
            for (int j=i;j<=n;j++)
                for (int k=i;k<=j;k++)
                    dp[i][j][a[k]]=1;
        for (int k=1;k<=15;k++)
            for (int i=1;i<n;i++)
                for (int j=i+1;j<=n;j++)
                    for (int mid=i;mid<j;mid++)
                        {
                            if (dp[i][mid][k-1]==0||dp[mid+1][j][k-1]==0) continue;
                            dp[i][j][k]=max(dp[i][j][k],dp[i][mid][k-1]+dp[mid+1][j][k-1]);
                            if (ans<dp[i][j][k]) ans=dp[i][j][k];
                        }
        printf("%d\n",ans);
    }
}