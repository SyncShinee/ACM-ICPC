#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const int N = 256;
bool invalid[N];
vector <int> gra[N];
int vis[N];
bool dfs(int x, int pre) {
    vis[x] = vis[pre] ^ 1;
    //printf("---%d---%d\n", x, vis[x]);
    for (int i = 0; i < gra[x].size(); ++ i) {
	if (vis[gra[x][i]] != -1) {
	    if (vis[gra[x][i]] != vis[x] ^ 1) return false;
	}
	else {
	    if (invalid[gra[x][i]]) continue;
	    if (!dfs(gra[x][i], x)) return false;
	}
    }
    return true;
}
int n;
bool judge() {
    memset(vis, -1, sizeof vis);
    vis[0] = 0;
    for (int i = 1; i <= n; ++ i) {
	//puts("---");
	if (vis[i] == -1) {
	    //printf("iii=%d\n", i);
	    if (invalid[i]) continue;
	    if (!dfs(i, 0)) return false;
	}
    }
    return true;
}
int main() {
    int len, x;
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w",stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) {
	scanf("%d", &len);
	for (int j = 0; j < len; ++ j) {
	    scanf("%d", &x);
	    gra[i].push_back(x);
	    gra[x].push_back(i);
	}
    }
    memset(invalid, 0, sizeof invalid);
    for (int i = 1; i <= n; ++ i) {
	invalid[i] = true;
	for (int j = i + 1; j <= n; ++ j) {
	    invalid[j] = true;
	    if (judge()) {
		//printf("%d %d\n", i, j);
		puts("Hurrah!");
		return 0;
	    }
	    invalid[j] = false;
	}
	invalid[i] = false;
    }
    puts("Fired.");
    return 0;
}
