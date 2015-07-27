#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <queue>
#define N 1024
#define M 1024
#define MOD 1000000007
#define EPS 1e-9
using namespace std;
int n, m, flag[256];
char s[64][64];
int main() {
	scanf("%d%d", &n, &m);
	gets(s[0]);
	for (int i = 0; i < n; ++i)
		gets(s[i]);
	int ans = 0;
	for (int i = 0; i < n-1; ++i) 
		for (int j = 0; j < m-1; ++j) {
			flag['a'] = flag['f'] = flag['c'] = flag['e'] = 0;
			flag[s[i][j]] = flag[s[i+1][j]] = flag[s[i][j+1]] = flag[s[i+1][j+1]] = 1;
			if (flag['a'] ==1 &&  flag['f'] == 1 && flag['c'] == 1 && flag['e'] == 1)
				ans++;
		}
	printf("%d\n", ans);
	return 0;
}