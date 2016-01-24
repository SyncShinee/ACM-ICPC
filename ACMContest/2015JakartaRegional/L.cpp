#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int N = 60;
int num[N], a[N][N], n;
ll ans;
ll gcd(ll a, ll b){
    if (b == 0) return a;
    return gcd(b, a % b);
}
void dfs(int now, ll res ){
    if (now == n + 1){
	ans = gcd(res, ans);
	return ;
    }
    for (int i = 1;i <= num[now];i++){
	dfs(now+1, res + a[now][i]);
    }
}
void solve(){
    scanf("%d",&n);

    for (int i = 1;i <= n;i++){
	scanf("%d",&num[i]);
	for (int j = 1;j <= num[i];j++){
	    scanf("%d",&a[i][j]);
	}
    }
    ans = 0;
    dfs(1, 0);
    static int ca = 0;
    printf("Case #%d: %lld\n",++ca,ans);
}

int main(){
    int t;
    scanf("%d",&t);
    while (t--){
	solve();
    }
}
