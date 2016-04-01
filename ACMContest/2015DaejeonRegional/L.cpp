#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 120;
int n, m;
int a[N],b[N],c[N];
int check(int st){
    for (int i = 1;i <= m;i++){
        int pos = i + st - 1;
        if (pos > n){
            pos -= n;
        }
        if (a[pos] > b[i]) break;
        if (a[pos] < b[i]) return 0;
    }
    for (int i = 1;i <= m;i++){
        int pos = i + st - 1;
        if (pos > n){
            pos -= n;
        }
        if (a[pos] < c[i]) break;
        if (a[pos] > c[i]) return 0;
    }
    return 1;
}
void solve(){
    scanf("%d %d",&n, &m);
    for (int i = 1;i <= m;i++) scanf("%d",&b[i]);
    for (int i = 1;i <= m;i++) scanf("%d",&c[i]);
    for (int i = 1;i <= n;i++) scanf("%d",&a[i]);
    int ans = 0;
    for (int i = 1;i <= n;i++){
        if (check(i)){
            ans++;
        }
    }
    printf("%d\n",ans);
}
int main(){
    int t;
    scanf("%d",&t);
    while (t--){
        solve();
    }
}