#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 256;
struct node {
	char name[64];
	int num;
}p[N];
bool operator < (const node &A, const node &B) {
	return A.num > B.num || A.num == B.num && strcmp(A.name, B.name) < 0;
}
int main() {
	int n, m;
	char s[64];
	while (scanf("%d", &n), n) {
		for (int i = 0; i < n; ++ i) {
			scanf("%s%d", p[i].name, &p[i].num);
		}
		sort(p, p + n);
		scanf("%d", &m);
		for (int i = 0; i < n; ++ i) {
			printf("%s %d\n", p[i].name, p[i].num);
		}
		while (m --) {
			scanf("%s", s);
			int ans1 = 0, ans2 = 1, pos;
			for (int i = 0; i < n; ++ i) {
					ans1++;
				if (strcmp(p[i].name, s) == 0) {
					pos = i;
					break;
				}
			}
			while (pos > 0 && p[pos - 1].num == p[pos].num) {
				ans2++;
				ans1--;
				pos--;
			}
			if (ans2 == 1) printf("%d\n", ans1);
			else printf("%d %d\n", ans1, ans2);
		}
	}
	return 0;
}