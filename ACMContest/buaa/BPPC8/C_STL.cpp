#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
long long n, a, b, TT, tmp, tmp2, sum;
long long val[10240], id[10240], f[10240];
struct node {
	long long x, idx, value;
	friend bool operator <(node t, node k) {
		return t.value > k.value;
	}
}tnode;
struct adapt {
	long long time, x, y, add;
	friend bool operator <(adapt t, adapt k) {
		return t.time < k.time;
	}
}p[20480];
priority_queue<node> q;
long long gf(long long x) {
	if (f[x] == x)
		return x;
	return (f[x] = gf(f[x]));
}
int main() {
	long long T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &a, &b);
		memset(id, 0, sizeof(id));
		while (!q.empty())
			q.pop();
		for (long long i = 1; i <=n; ++i) {
			f[i] = i;
			id[i] = 0;
			scanf("%d", &val[i]);
			tnode.idx = 0;
			tnode.x = i;
			tnode.value = val[i];
			q.push(tnode);
		}
		for (long long i = 0; i < a; ++i) {
			scanf("%d%d%d", &p[i].time, &p[i].x, &p[i].y);
			p[i].add = 0;
		}
		for (long long i = a; i < a+b; ++i) {
			scanf("%d%d%d", &p[i].time, &p[i].x, &p[i].y);
			p[i].add = 1;
		}
		sort(p, p+a+b);
		long long j = 0;
		long long ans = 0;
		TT = 0;
		for (long long i = 1; i < n; ++i) {
			while (p[j].time == i && j < a+b) {
				tnode.x = gf(p[j].x);
				if (p[j].add) 
					val[f[p[j].x]] += p[j].y;
				else
					val[f[p[j].x]] -= p[j].y;
				tnode.value = val[f[p[j].x]];
				tnode.idx = ++TT;
				id[f[p[j].x]] = TT;
				q.push(tnode);
				j++;
			}
			tnode = q.top();
			//printf("------%d %d %d %d\n", tnode.x, id[tnode.x], tnode.idx, tnode.value);
			while (tnode.idx < id[tnode.x]) {
				//printf("-%d %d %d %d\n", tnode.x, id[tnode.x], tnode.idx, tnode.value);
				q.pop();
				tnode = q.top();
			}
			//printf("final------%d %d %d %d\n", tnode.x, id[tnode.x], tnode.idx, tnode.value);
			//4 5 6printf("%d  %d\n", tnode.x, tnode.);
			sum = tnode.value;
			tmp = tnode.x;
			q.pop();
			tnode = q.top();
			//printf("------%d %d %d %d\n", tnode.x, id[tnode.x], tnode.idx, tnode.value);
			while (tnode.idx < id[tnode.x]) {
				//printf("-%d %d %d %d\n", tnode.x, id[tnode.x], tnode.idx, tnode.value);
				q.pop();
				tnode = q.top();
			}
			//printf("final------%d %d %d %d\n", tnode.x, id[tnode.x], tnode.idx, tnode.value);
			sum += tnode.value;
			tmp2 = tnode.x;
			q.pop();
			f[tmp] = tmp2;
			tnode.x = tmp2;
			tnode.value = sum;
			val[tmp2] = sum;
			ans += (long long)sum;
			tnode.idx = ++TT;
			id[tmp2] = TT;
			q.push(tnode);
			//printf("sum----------%d-%d-%d-%d-%d\n", tmp2, val[tmp2], tnode.idx, id[tmp2], sum);
		}
		printf("%lld\n", ans);
	}
	//scanf("%d", &n);
	return 0;
}
