 #include <cstdio>
 #include <cstring>
 #include <algorithm>
 #include <cmath>
 using namespace std;
 int gcd(int x, int y) {
    if (y == 0)
        return x;
    return gcd(y, x % y);
 }
 int n, m, a[100010], b[100010], mxa, mxb, mna, mnb, gc;
 int main() {
    int i, cas = 0;
    while (scanf("%d%d", &n, &m), n | m) {
        cas++;
        mxa = mxb = 0;
        mna = mnb = 1000000007;
        gc = 0;
        for(i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
            mxa = max(a[i], mxa);
            mna = min(a[i], mna);
            gc = gcd(gc, abs(a[i] - a[0]));
        }
        for(i = 0; i < m; ++i) {
            scanf("%d", &b[i]);
            mxb = max(b[i], mxb);
            mnb = min(b[i], mnb);
            gc = gcd(gc, abs(b[i] - b[0]));
        }
        gc = gcd(gc, abs(a[0] - b[0]));
        printf("Case %d: ", cas);
        if(mxa <= mnb || mxb <= mna){
            printf("YES\n");
        }
        else {
            if(gc == 1 || (gc == 2 && a[0] % 2 == 1)){
                printf("NO\n");
            }
            else
                printf("YES\n");
        }
    }
    return 0;
 }