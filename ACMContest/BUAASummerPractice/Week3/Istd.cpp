#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define N 110
#define lint __int64
lint dp[N][N], maxLcm[N];
lint factor[N], fnum;
int p[25] ={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31,
37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

inline lint gcd ( lint a, lint b )
{
    lint c;
    while ( b != 0 )
    {
        c = a % b;
        a = b;
        b = c;
    }
    return a;
}

void split ( int n )
{
    int i, j, k, lcm;
    memset(dp,0,sizeof(dp));
    for ( i = 1; i <= n; i++ )
        dp[i][1] = i;

    for ( i = 2; i <= n; i++ )
        for ( j = 2; j <= i; j++ )
            for ( k = 1; k < i && i-k >= j-1; k++ )
            {
                lcm = dp[i-k][j-1] * k / gcd(dp[i-k][j-1], k);
                if ( lcm > dp[i][j] ) dp[i][j] = lcm;
            }

    for ( i = 1; i <= n; i++ )
    {
        maxLcm[i] = 0;
        for ( j = 1; j <= n; j++ )
            if ( dp[i][j] >= maxLcm[i] )
                maxLcm[i] = dp[i][j];
    }
}

void split ( lint num )
{
    fnum = 0;
    for ( int i = 0; i < 25; i++ )
    {
        if ( num % p[i] ) continue;
        factor[fnum] = 1;
        while ( num % p[i] == 0 )
        {
            factor[fnum] *= p[i];
            num /= p[i];
        }
        fnum++;
    }
}

int main()
{
    int t, n;
    split(100);
    scanf("%d",&t);
    while ( t-- )
    {
        scanf("%d",&n);
        split ( maxLcm[n] );
        sort(factor,factor+fnum);

        int i, j, k, tmp = 0;
        for ( i = 0; i < fnum; i++ )
            tmp += factor[i];

        printf("%I64d",maxLcm[n]);
        for ( i = 1; i <= n - tmp; i++ )
            printf(" %d",i);

        k = n - tmp;
        for ( i = 0; i < fnum; i++ )
        {
            for ( j = 2; j <= factor[i]; j++ )
                printf(" %d",k+j);
            printf(" %d",k+1);
            k += factor[i];
        }
        printf("\n");
    }
    return 0;
}
