#include <cstdio>
#include <cstring>
#include <map>
using namespace std;
struct node {
	int a, b, c, d;
	friend bool operator < (node x, node y) {
		if (x.a == y.a && x.b == y.b && x.c == y.c)
			return x.d < y.d;
		if (x.a == y.a && x.b == y.b)
			return x.d < y.c;
		if (x.a == y.a)
			return x.b < y.b;
		return x.a < y.a;
	}
}ip[1024], mask[64];
map<unsigned int, int> mp;
unsigned int tmp;
int main() {
	int T, n, m;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++cas) {
		scanf("%d%d", &n, &m);
		printf("Case #%d:\n", cas);
		for (int i = 0; i < n; ++i)
			scanf("%d.%d.%d.%d", &ip[i].a, &ip[i].b, &ip[i].c, &ip[i].d);
		for (int i = 0; i < m; ++i)
			scanf("%d.%d.%d.%d", &mask[i].a, &mask[i].b, &mask[i].c, &mask[i].d);
		for (int i = 0; i < m; ++i) {
			int ans = 0;
			mp.clear();
			for (int j = 0; j < n; ++j) {
				tmp = ip[j].a & mask[i].a;
				tmp = tmp * 256 + (ip[j].b & mask[i].b);
				tmp = tmp * 256 + (ip[j].c & mask[i].c);
				tmp = tmp * 256 + (ip[j].d & mask[i].d);
				//printf("tmp =====%d\n", tmp);
				if (mp[tmp] == 0) {
					mp[tmp] = 1;
					//printf("1111\n" );
					ans++;
				}
			}
			
			printf("%d\n", ans);
		}
	}
	return 0;
}