#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int N = 1e6 + 100;
int n;
ll a[N];
void solve(){
    scanf("%d",&n);
    for (int i = 1;i <= n;i++) scanf("%lld",&a[i]);
    a[n + 1] = 0;
    ll ans = 0;
    for (int i = n;i >= 1;i--){
        if (a[i] <= a[i+1]){
            ans += a[i + 1] - a[i];
        }
        a[i] = max(a[i], a[i + 1]);
    }
    printf("%lld\n",ans);
}
int main(){

    int t;
    scanf("%d",&t);
    while (t--){
        solve();
    }
}