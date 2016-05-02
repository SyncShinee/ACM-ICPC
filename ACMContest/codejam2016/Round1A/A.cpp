#include <cstdio>
#include <algorithm>
#include <set>
#include <map>
#include <cstring>
using namespace std;
const int N = 2048;
struct node {
	char ch;
	int id;
	node(int _i = 0, char _c = 0) : id(_i), ch(_c) {}
} C[N];
bool operator < (const node &A, const node &B) {
	return A.ch < B.ch || A.ch == B.ch && A.id < B.id;
} 
int n;
void update(int x, char val) {
	node tmp = node(x, val);
	while (x <= n) {
		C[x] = max(C[x], tmp);
		x += x & -x;
	}
}
node get_max(int x) {
	node ret = node(n + 1, 0);
	while (x) {
		ret = max(ret, C[x]);
		x -= x & -x;
	}
	return ret;
}
char s[1024], ans[1024];
int main() {
	int T;
	freopen("A-large.in", "r", stdin);
	freopen("out.txt" ,"w", stdout);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++ cas) {
		scanf("%s", s + 1);
		n = strlen(s + 1);
		memset(C, 0, sizeof C);
		memset(ans, 0, sizeof ans);
		for (int i = 1; i <= n; ++ i) {
			update(i, s[i]);
		}
		int last = n, fr = 1, nr = n;
		while (last) {
			//printf("%d\n", last);
			node tmp = get_max(last);
			ans[fr++] = s[tmp.id];
			for (int i = 0; i < last - tmp.id; ++ i) {
				//printf("%d %d\n", nr, last);
				ans[nr--] = s[last - i];
			}
			last = tmp.id - 1;
		}
		printf("Case #%d: %s\n", cas, ans + 1);
	}
	return 0;
}