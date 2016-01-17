#include <cstdio>
#include <cstring>
#include<algorithm>
using namespace std;
const int N = 1e5 + 7;
char s[N];
int a[32];
int main() {
    //freopen("d.txt", "r", stdin);
    int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++ cas) {
        for (int i = 0; i < 26; ++ i) {
            a[i] = 0;
        }
        scanf("%s", s);
        int len = strlen(s);
        for (int i = 0; i < len; ++ i) {
            a[s[i] - 'a'] ++;
        }
        int ans = len;
        for (int i = 0; i < 26; ++ i) {
            ans = min(ans, a[i]);
        }
        printf("Case %d: %d\n", cas, ans);
    }
    return 0;
}
