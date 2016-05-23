#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
using namespace std;
int num[16];
int main() {
    int T, a, b, d, n;
    scanf("%d", &T);
    while (T--) {
        memset(num, 0, sizeof num);
        scanf("%d%d%d%d", &a, &b, &d, &n);
        int k1 = a * b / 10;
        int k2 = a * b % 10;
        if (n == 1) {
            num[k2] ++;
            if (k1 > 0)
                num[k1]++;
            printf("%d\n", num[d]);
            continue;
        }
        if (k1 == 0) {
            if (d == k2) {
                printf("%d\n", n);
            } else {
                printf("0\n");
            }
        } else {
            if (k1 + k2 > 9) {
                num[k2] ++;
                num[(k1 + k2) % 10]++;
                num[(k1 + k2) % 10 + (k1 + k2) / 10] += n - 2;
                num[k1 + (k1 + k2) / 10] ++;
            } else {
                num[k1 + k2] = n - 1;
                num[k1]++;
                num[k2]++;
            }
            printf("%d\n", num[d]);
        }
    }
    return 0;
}
