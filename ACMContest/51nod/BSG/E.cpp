#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
using namespace std;
typedef long long ll;
const int N = 100010;
int a[N];
int b[N];
int n;
ll k;
int C[N << 1][2];
void update(int x, int tag) {
    while (x < N + N) {
        C[x][tag] ++;
        x += x & -x;
    }
}
ll getsum(int x, int tag) {
    ll ret = 0;
    while (x) {
        ret += C[x][tag];
        x -= x & -x;
    }
    return ret;
}
bool check(int x) {
    for (int i = 1; i <= n; ++ i) {
        b[i] = a[i] < x ? -1 : 1;
    }
    for (int i = 1; i <= n; ++ i) {
        b[i] += b[i - 1];
    }
    /*
    printf("%d\n", x);
    for (int i = 1; i <= n; ++ i) {
        printf("%d ", b[i]);
    }
    puts("");
    */
    memset(C, 0, sizeof C);
    update(N, 0);
    ll sum = 0;
    for (int i = 1; i <= n; ++ i) {
        sum += getsum(b[i], (i & 1) ^ 1);
        update(b[i], i & 1);
    }
    if (sum >= k) return true;
    return false;
}
int main() {
    scanf("%d%lld", &n, &k);
    int l = 0, r = 0;
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", &a[i]);
        r = max(r, a[i]);
    }
    b[0] = N;
    
    while (l <= r) {
        int mid = l + r >> 1;
        if (check(mid)) {
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }
    printf("%d\n", r);
    return 0;
}
