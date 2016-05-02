#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
using namespace std;
const int N = 2024;
map<string, int> mp1, mp2;
vector <int> G[N];
int num1, num2;
int match[N];
int used[N];
char s1[N][26], s2[N][26];
bool dfs(int x) {
	used[x] = true;
	for (int i = 0; i < G[x].size(); ++ i) {
		int v = G[x][i], w = match[v];
		if (w < 0 || (!used[w] && dfs(w))) {
			match[v] = x;
			match[x] = v;
			return 1;
		}
	}
	return 0;
}
int main() {
	int T;
	freopen("C-large-practice.in", "r", stdin);
	freopen("out.txt", "w", stdout);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++ cas) {
		int n;
		scanf("%d", &n);
		num1 = num2 = 0;
		mp1.clear();
		mp2.clear();
		for (int i = 1; i <= n + n; ++ i) {
			G[i].clear();
		}
		for (int i = 1; i <= n; ++ i) {
			scanf("%s%s", s1[i], s2[i]);
			int t1, t2;
			if (mp1.count(s1[i])) {
				t1 = mp1[s1[i]];
			}
			else {
				mp1[s1[i]] = ++num1;
				t1 = num1;
			}
			if (mp2.count(s2[i])) {
				t2 = mp2[s2[i]];
			}
			else {
				mp2[s2[i]] = ++num2;
				t2 = num2;
			}
			G[t1].push_back(n + t2);
		}
		memset(match, -1, sizeof match);
		int ans = 0;
		for (int i = 1; i <= num1; ++ i) {
			if (match[i] == -1) {
				memset(used, 0, sizeof used);
				if (dfs(i)) {
					ans++;
				}
			}
		}
		printf("Case #%d: ", cas);
		//printf("%d %d %d\n",num1, num2, ans);
		printf("%d\n", n - num1 - num2 + ans);
	}
	return 0;
}