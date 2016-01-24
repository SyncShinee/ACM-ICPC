#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
const int N = 210;
int hash[N * N];
int n, tot;
int f[2][N * N];
int x[N], y[N];
int see[N][N];
void hash_init(){
    sort(hash + 1, hash + tot + 1);
    tot = unique(hash+1, hash + tot + 1) - hash - 1;
}
int Hash(int x){
    return lower_bound(hash+1, hash + tot + 1, x) - hash;
}
void solve(){
    memset(f, 0, sizeof f);
    scanf("%d",&n);
    for (int i = 1;i <= n;i++) scanf("%d",&x[i]);
    for (int i = 1;i <= n;i++) scanf("%d",&y[i]);

    for (int i = 1;i <= n;i++){
	for (int j = 1;j <= n;j++){
	    scanf("%d",&see[i][j]);
	}
    }
    tot = 0;
    for (int i = 1;i <= n;i++){
	for (int j = 1;j <= n;j++){
	    int dist = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
	    hash[++tot] = dist;
	}
    }
    hash_init();
    int tot1 = 0;
    for (int i = 1;i <= n;i++){
	for (int j = 1;j <= n;j++){
	    int dist = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
	    int pos = Hash(dist);
	    if (see[i][j] == 1){
		f[1][pos]++;
		tot1++;
	    }else{
		f[0][pos]++;
	    }
	}
    }
    for (int i = 1;i <= tot;i++){
	f[1][i] += f[1][i-1];
	f[0][i] += f[0][i-1];
    }
    int ansn = 100000, ans = 1;
    for (int i = 1;i <= tot;i++){
	int now = f[0][i] - f[1][i] + tot1;
	if (now < ansn){
	    ansn = now;
	    ans = i;
	}
    }
    static int ca = 0;
    printf("Case #%d: %d %d\n",++ca, hash[ans], ansn);
}
int main(){
    freopen("d.txt","r",stdin);
    int t;
    scanf("%d",&t);
    while (t--){
	solve();
    }
}
