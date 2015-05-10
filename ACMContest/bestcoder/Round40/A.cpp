#include <cstdio>
#include <cmath>
using namespace std;
int main() {
    int T, n;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        if (n == 0) {
        	printf("0\n");
        	continue;
        }
        int k = sqrt(n);
        int j;
        for (j = k; j > 0; --j) {
            if (n % j == 0) {
                break;
            }
        }
        printf("%d\n", 2 * (j + n/j));
    }
    return 0;
}