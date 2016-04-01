#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 10010;
int n;
int a[N];
void solve(){
    scanf("%d",&n);
    for (int i = 1;i <= n;i++) scanf("%d",&a[i]);
    sort(a + 1, a + n + 1);
    int ans = a[2] - a[1];
    for (int i = 4;i <= n;i+=2) ans = max(ans, a[i] - a[i - 2]);
    for (int i = 3;i <= n;i+=2) ans = max(ans, a[i] - a[i - 2]);
    ans = max(ans, a[n] - a[n - 1]);
    printf("%d\n",ans);
}
int main(){
    int t;
    scanf("%d",&t);
    while (t--){
        solve();
    }
}