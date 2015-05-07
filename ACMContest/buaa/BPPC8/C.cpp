#include <cstdio>
#include <cstring>
#include <algorithm>
#define INF 1000000007
using namespace std;
struct min_heap {
	long long h[20480], cnt, origin[20480], num[20480];
	void clear() {
		cnt = 0;
	}
	long long pre(long long n) {
		return n>>1;
	}
	long long lch(long long n) {
		return n<<1;
	}
	long long rch(long long n) {
		return (n<<1)+1;
	}
	void insert(long long x, long long nu) {
		long long p = ++cnt;
		while (p > 1 && nu < num[h[pre(p)]] ) {
			h[p] = h[pre(p)];
			origin[pre(p)] = p;
			p = pre(p);
		}
		h[p] = x;
		origin[x] = p;
		num[x] = nu;
		//printf("---%d %d %d %d %d\n", p, origin[x], num[x], h[p], x);
	}
	void pop() {
		if(cnt == 0)
			return;
		long long p = 1, tmp = h[cnt], to;
		h[cnt--] = 0;
		while (p <= cnt) {
			to = -INF;
			if (lch(p) <= cnt && num[tmp] > num[h[lch(p)]])
				to = lch(p);
			if (rch(p) <= cnt && num[tmp] > num[h[rch(p)]] && (to == -INF || num[h[to]] > num[h[rch(p)]]))
				to = rch(p);
			if (to != -INF) {
				h[p] = h[to];
				origin[h[to]] = p;
				p = to;
			}
			else {
				h[p] = tmp;
				origin[tmp] = p;
				break;
			}
		}
	}
	void up(long long x, long long y) {
		num[x] -= y;
		long long p = origin[x];
		//printf("p%lld pre%lld h[p]%lld h[pre]%lld origin%lld num%lld\n", p, pre(p), h[p], h[pre(p)], origin[x], num[x]);
		while (p > 1 && num[x] < num[h[pre(p)]] ) {
			//printf("p%lld pre%lld h[p]%lld h[pre]%lld origin%lld num%lld\n", p, pre(p), h[p], h[pre(p)], origin[x], num[x]);
			h[p] = h[pre(p)];
			origin[pre(p)] = p;
			p = pre(p);
		}
		h[p] = x;
		origin[x] = p;
	}
	void down(long long x, long long y) {
		num[x] += y;
		long long p = origin[x], tmp = h[p], to;
		while (p <= cnt) {
			to = -INF;
			if (lch(p) <= cnt && num[tmp] > num[h[lch(p)]])
				to = lch(p);
			if (rch(p) <= cnt && num[tmp] > num[h[rch(p)]] && (to == -INF || num[h[to]] > num[h[rch(p)]]))
				to = rch(p);
			//printf("p%lld to%lld h[p]%lld  origin%lld num%lld\n", p, to, h[p], origin[x], num[x]);
			if (to != -INF) {
				h[p] = h[to];
				origin[h[to]] = p;
				p = to;
			}
			else {
				h[p] = tmp;
				origin[tmp] = p;
				break;
			}
		}
	}
	long long top() {
		return num[h[1]];
	}
	long long top_source() {
		return h[1];
	}
	long long size() {
		return cnt;
	}
}heap;
struct adapt{
	long long time, x, y, add;
	friend bool operator <(adapt t, adapt k) {
		return t.time < k.time;
	}
}p[20480];
long long f[20480], ans, n, a, b, t;
long long gf(long long x) {
	//printf("digui%d %d\n", x, f[x]);
	if (f[x] == x)
		return x;
	return (f[x] = gf(f[x]));
}
void merge() {
	long long i = heap.top_source(), tmp = heap.top();
	heap.pop();
	long long j = heap.top_source();
	//printf("jjj%d\n", j);
	//printf("%d %d\n", tmp, heap.top_source());
	ans += (tmp+heap.top());
	//printf("%d\n", ans);
	f[i] = j;
	//printf("f[i]%lld\n", f[i]);
	heap.down(j, tmp);
}
int main() {
	long long T;
	scanf("%lld", &T);
	while (T--) {
		scanf("%lld%lld%lld", &n, &a, &b);
		ans = 0;
		heap.clear();
		memset(f, 0, sizeof(f));
		
		for (long long i = 1; i <= n; ++i) {
			scanf("%lld", &t);
			heap.insert(i, t);
		}
		for (long long i = 0; i < a; ++i) {
			scanf("%lld%lld%lld", &p[i].time, &p[i].x, &p[i].y);
			p[i].add = 0;
		}
		for (long long i = a; i < a+b; ++i) {
			scanf("%lld%lld%lld", &p[i].time, &p[i].x, &p[i].y);
			p[i].add = 1;
		}
		sort(p, p+a+b);
		for (long long i = 1; i <= n; ++i)
			f[i] = i;
		long long j = 0;
		//printf("%d\n", p[0].time);
		for (long long i = 1; i < n; ++i) {
			while (j < a+b && p[j].time == i ) {
				if (p[j].add)
					heap.down(gf(p[j].x), p[j].y);
				else
					heap.up(gf(p[j].x), p[j].y);
				j++;
			}
			//printf("%d\n", heap.top());
			merge();
		}
		printf("%lld\n", ans);
	}
	return 0;
}

