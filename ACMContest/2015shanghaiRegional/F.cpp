#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int INF = 100010;
char s[1024];
int main() {
    int T, ans;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++ cas) {
        scanf("%s", s);
        ans = INF;
        int len = strlen(s);
        for (int i = 0; i < len; ++ i) {
            for (int j = i + 1; j < len; ++ j) {
                if (s[i] != s[j]) continue;
                ans = min(ans, j - i);
            }
        }
        if (ans == INF) ans = -1;
        printf("Case #%d: %d\n", cas, ans);
    }
    return 0;
}