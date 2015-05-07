#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
int n, a[100010], last[100010], front[100010];
queue<int> q;
bool inq[100010];
int main() {
	int i;
	while (~scanf("%d", &n)) {
		memset(inq,0,sizeof(inq));
		for (i = 0; i < n; ++i)
			scanf("%d", &a[i]);
		for (int i = 0; i < n; ++i) {
			if (!inq[a[i]]) {
				inq[a[i]] = true;
				q.push(a[i]);
				last[a[i]]
			}
		}
	}
	return 0;
}