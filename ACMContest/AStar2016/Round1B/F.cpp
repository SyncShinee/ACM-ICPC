#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <cmath>
using namespace std;
const int N = 10010;
int a[N], b[N], num[N + N];
int main() {
    int n;
    while (~scanf("%d", &n)) {
        for (int i = 1; i <= n; ++ i) {
            scanf("%d", &a[i]);
        }
        for (int i = 1; i <= n; ++ i) {
            for (int j = 1; j <= n; ++ j) {
                if (a[j] == a[i]) b[j] = 0;
                else if (a[j] > a[i]) b[j] = 1;
                else b[j] = -1;
            }
            for (int j = 0; j <= n + n; ++ j) num[j] = 0;
            int nw = 0; num[n] = 1;
            for (int j = i - 1; j > 0; -- j) {
                nw += b[j];
                num[nw + n] ++;
            }
            int ans = 0;
            nw = 0;
            for (int j = i; j <= n; ++ j) {
                nw += b[j];
                ans += num[n - nw];
            }
            printf("%d%c", ans, " \n"[i == n]);
        }
    }
    return 0;
}
