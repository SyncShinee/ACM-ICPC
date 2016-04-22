#include <bits/stdc++.h>

using namespace std;
const int N = 1100;
const int M = 5e4 + 100;
struct P{
    int id, x;
    P (int _id = 0, int _x = 0){
	id = _id;
	x = _x;
    }
    bool operator <(const P & o) const{
	return id < o.id || id == o.id && x < o.x;
    }
}a[N];
int n, s;
int f[M], g[M];
int main(){
    // freopen("in.txt", "r", stdin);
    scanf("%d %d", &n, &s);
    for (int i = 1; i <= n; ++ i){
	scanf("%d %d", &a[i].id, &a[i].x);
    }
    memset(f, -1, sizeof f);
    sort(a + 1, a + n + 1);
    f[0] = 0;
    for (int i = 1; i <= n; ++ i){
	for (int j = s; j >= a[i].x; -- j){
	    if (f[j - a[i].x] == -1) continue;
	    if (a[i].id == g[j - a[i].x] &&
		f[j] < f[j - a[i].x]){
		f[j] = f[j - a[i].x];
		g[j] = a[i].id;
	    }else if (a[i].id != g[j - a[i].x] &&
		      f[j] < f[j - a[i].x] + 1){
		f[j] = f[j - a[i].x] + 1;
		g[j] = a[i].id;
	    }
	}
    }
    //printf("%d\n", g[16]);
    if (f[s] == -1) puts("Impossible");
    else
	printf("%d\n", f[s]);
}
