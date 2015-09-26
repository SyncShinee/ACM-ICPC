#include <cstdio>
#include <algorithm>
#include <ctring>
#define lson l, mid - 1, rt << 1
#define rson mid + 1, r, rt << 1 | 1
using namespace std;
const int N = 50010;
const int DSIZE = 5;
struct kd_node {
	int d[DSIZE];
}p[N];
struct kdTree {
	int D;
	kd_node Tree[N << 2];
	bool operator < (const kd_node &A, const kd_node &B) {
		return A.d[D] < B.d[D];
	}
	void update(int o, int s) {
		for (int i = 0; i < k; ++ i) {
			Tree[o].d[i]
		}
	}
}kd;
int main() {
	while (~scanf("%d%d", &n, &k)) {
		for (int i = 0; i < n; ++ i) {
			for (int j = 0; j < k; ++ j) {
				scanf("%d", &p[i].d[j]);
			}
		}

	}
	return 0;
}