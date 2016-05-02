#include <cstdio>
#include <cstring>
using namespace std;
char s[2048];
int num[128];
int ans[16];
int main() {
	int T;
	freopen("A-large.in", "r", stdin);
	//freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++ cas) {
		scanf("%s", s);
		
		int len = strlen(s);
		memset(num, 0, sizeof num);
		for (int i = 0; i < len; ++ i) {
			num[s[i]]++;
		}
		ans[6] = num['X'];
		ans[4] = num['U'];
		ans[5] = num['F'] - ans[4];
		ans[7] = num['V'] - ans[5];
		ans[2] = num['W'];
		ans[0] = num['Z'];
		ans[1] = num['O'] - ans[4] - ans[2] - ans[0];
		ans[3] = num['R'] - ans[0] - ans[4];
		ans[8] = num['T'] - ans[3] - ans[2];
		ans[9] = num['I'] - ans[8] - ans[6] - ans[5];
		printf("Case #%d: ", cas);
		for (int i = 0; i <= 9; ++ i) {
			for (int j = 0; j < ans[i]; ++ j) printf("%d", i);
		}
		puts("");
	}
}