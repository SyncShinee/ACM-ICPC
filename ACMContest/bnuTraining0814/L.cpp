#include <cstdio>
#include <cstring>
using namespace std;
int main() {
    int n, sum, m;
    while (~scanf("%d", &n)) {
        m = n;
        n /= 2;
        sum = 0;
        for (int i = 2; i * i <= m; ++ i) {
            if (m % i == 0) {
                sum ++;
                if (m / i <= m/2) {
                    sum++;
                }
            }
        }
        printf("%d\n", n - sum);
    }
    return 0;
}