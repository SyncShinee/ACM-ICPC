#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long ll;
ll p, pre, x, y, a, b;
void exgcd(ll x, ll y, ll &a, ll &b) {
    if (y == 0) {
        a = 1, b = 0;
        return;
    }
    exgcd(y, x % y, a, b);
    ll t = a;
    a = b;
    b = t - x / y * b;
}
int main() {
    int T;
    scanf("%d\n", &T);
    while (T --){
        scanf("%lld", &p);
        pre = 1;
        while (!(p & 1)) {
            p >>= 1;
            pre <<= 1;
        }
        if (p == 1) {
            p <<= 1;
            pre >>= 1;
        }
        x = 1, y = 1;
        while (x * x <= p) {
            x <<= 1;
        }
        x >>= 1;
        while (y * y <= p) {
            y *= 3;
        }
        y /= 3;
        printf("begin\n");
        exgcd(x, y, a, b);
        a = (a % y + y) % y;
        b = (p - a * x) / y;
        a *= p, b *= p;
        printf("---%lld %lld\n",a, b);
        a = (a % y + y) % y;
        b = (p - a * x) / y;
        if (a <= 0) {
            a += y;
            b -= x;
        }
        printf("%lld %lld----%lld===%lld\n" ,a,b, a * x + b * y, p);
        //if (a < 0 || b < 0) while (1);
        if (a == 0 || b == 0) {
            printf("NO\n");
            continue;
        }
        printf("%lld %lld\n", a * x * pre, b * y * pre);
//        for (int i = )
    }
    return 0;
}