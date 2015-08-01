#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll N = 200000000000000;
int l,r;
ll ans;
void dfs(ll l,ll r) {
    if (l == 0) {
        ans = min(r,ans);
        return;
    }
    if (r >= ans ||l > r || l < 0 || r - l + 1 > l) return;
    dfs(l,r*2-l), dfs(l,r*2+1-l), dfs((l-1)*2-r,r), dfs((l-1)*2+1-r,r);
}
int main() {
    while (~scanf("%d %d",&l,&r)) {
        ans = N;
        if (l == r) {
            printf("%d\n",l);
            continue;
        }
        dfs(l,r);
        if (ans == N)
            puts("-1");
        else
            printf("%I64d\n",ans);
    }
}