#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <queue>
#define N 128
#define M 1024
#define MOD 1000000007
#define EPS 1e-9
using namespace std;
int n, m, ans;
char s[N][N];
int a[N];
bool flag[N];
int main() {
	scanf("%d", &n);gets(s[0]);
	for (int i = 0; i < n; ++i) 
		gets(s[i]);
	for (int i = 0; i < n; ++i)
		scanf("%d", &a[i]);
	while (true) {
		bool tmp = false;
		for (int i = 0; i < n; ++i) {
			if (a[i] == 0) {
				tmp = true;
				for (int j = 0; j < n; ++j) {
					a[j] -= s[i][j] - '0';
				}
				flag[i] = true;
				ans ++;
			}
		}
		if (!tmp) {
			break;
		}
	}
	printf("%d\n", ans);
	for (int i = 0; i < n; ++i)
		if (flag[i]) {
			printf("%d ", i+1);
		}
	return 0;
}