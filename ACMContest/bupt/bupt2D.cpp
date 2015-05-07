#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
vector<int> gra[100010];
bool b[100010], flag;
int sg[100010], f[100010];
void dfs(int x) {
	int  mx = -1,mn = 1000000000;
	flag = false;
	f[x] = 0;
	sg[x] = 0;
	if (gra[x].size() == 0)
		return;
	for(int i = 0; i < gra[x].size(); ++i) {
		dfs(gra[x][i]);
		if (sg[gra[x][i]] == 0) {
			if (mx < f[gra[x][i]]+1)
				mx = f[gra[x][i]]+1;
		}
		else {
			if (mn > f[gra[x][i]] + 1)
				mn = f[gra[x][i]] + 1;
		}
	}
	if (mx > -1){
		f[x] = mx;
		sg[x] = 1;
	}
	else {
		f[x] = mn;
		sg[x] = 0;
	}
}
int main() {
	int T, n, m, tmp, max1, max2;
	scanf("%d", &T);
	while (T--) {
		max1 = max2 = -1;
		scanf("%d%d", &n, &m);
		memset(b, 0, sizeof(b));
		for (int i = 1; i <= n; ++i)
			gra[i].clear();
		for (int i = 2; i <= n; ++i) {
			scanf("%d", &tmp);
			gra[tmp].push_back(i);
		}
		for (int i = 0; i < m; ++i) {
			scanf("%d", &tmp);
			b[tmp] = true;
		}
		dfs(1);
		for (int i = 1; i <= n; ++i)
			if (b[i]) {
				if (sg[i] == 0 && max2 < f[i])
					max2 = f[i];
				else if (sg[i] == 1 && max1 < f[i])
					max1 = f[i];
			}
		if (max1 > max2)
			printf("MengMengDa!\n");
		else
			printf("So sad...\n");
	}
	return 0;
}