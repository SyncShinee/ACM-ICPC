#include <iostream>
#include <time.h>
#include <cstdlib>
#include <cstdio>
using namespace std;
int f[32];
int gf(int x) {
    if (f[x] == x) {
        return x;
    }
    return f[x] = gf(f[x]);
}
int merge(int x, int y) {
    int i = gf(x), j = gf(y);
    f[i] = j;
    f[x] = j;
}
int main()
{
    int t = 0;
    srand((unsigned)time(NULL));
    freopen("2Bin.txt", "w", stdout);
    printf("1\n");
    int n = rand();
    n %= 80;
    n++;
    if (n == 1)
        n++;
    printf("%d\n", n);
    for (int i = 0; i <= n; ++i)
        f[i] = i;
    while (t < n-1) {
        int i = rand(), j = rand();
        i %= n; j %= n;
        i++; j ++;
        if (gf(i) != gf(j)) {
            t++;
            printf("%d %d\n", i, j);
            merge(i,j);
        }
    }
}
