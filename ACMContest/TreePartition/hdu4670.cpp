#pragma comment(linker,"/STACK:102400000,102400000")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#define N 50010
#define INF 1000000000
using namespace std;
typedef unsigned long long ull;
struct edge {
	int to, next;
}e[N << 1];
int head[N], subtree_size[N], side, n, k, len_tds;
long long p[N];
bool centroid[N];
long long ans, a;

map <ull, long long> mp;
ull tds[N], w[N];

void build(int x, int y) {
	e[side].to = y;
	e[side].next = head[x];
	head[x] = side++;
}

ull mul(ull x, ull y) {
	ull ret = 0;
	for (ull i = 0; i < k; ++i) {
		ull tmpx = (x & (3ull << (i << 1))) >> (i << 1);
		ull tmpy = (y & (3ull << (i << 1))) >> (i << 1);
		ret |= ((tmpx + tmpy) % 3) << (i << 1);
	}
	return ret;
}

ull inv(ull x) {
	ull ret = 0;
	for (ull i = 0; i < k; ++i) {
		ull tmpx = (x & (3ull << (i << 1))) >> (i << 1);
		if (tmpx == 1) {
			ret |= 2ull << (i << 1);
		}
		else if (tmpx == 2) {
			ret |= 1ull << (i << 1);
		}
	}
	return ret;
}

pair <int, int> find_centroid(int x, int pre, int sum) {
	pair <int, int> ret = make_pair(INF, -1);
	int m = 0;
	subtree_size[x] = 1;
	for (int i = head[x]; ~i; i = e[i].next) {
		if (centroid[e[i].to] || e[i].to == pre)
			continue;
		ret = min(ret, find_centroid(e[i].to, x, sum));
		m = max(m, subtree_size[e[i].to]);
		subtree_size[x] += subtree_size[e[i].to];
	}
	m = max(m, sum - subtree_size[x]);
	return min(ret, make_pair(m, x));
}

void deal(int x, int pre, ull value) {
	ull tmp = mul(value, w[x]);
	tds[len_tds++] = tmp;
	for (int i = head[x]; ~i; i = e[i].next) {
		if (centroid[e[i].to] || e[i].to == pre) 
			continue;
		deal(e[i].to, x, tmp);
	}
}

void solve_subproblem(int x) {
	int u = find_centroid(x, -1, subtree_size[x]).second;
	centroid[u] = true;
	mp.clear();
	mp[0] = 1;
	if (w[u] == 0)
		ans++;
	for (int i = head[u]; ~i; i = e[i].next) {
		if (centroid[e[i].to])
			continue;
		len_tds = 0;
		deal(e[i].to, u, 0);
		subtree_size[e[i].to] = len_tds;
		for (int j = 0; j < len_tds; ++j) {
			ull tmp = mul(tds[j], w[u]);
			tmp = inv(tmp);
			if (mp.count(tmp))
				ans += mp[tmp];
			//printf("debug2---tds  %llu inv  %llu  ans %d\n", tds[j], tmp, ans);
		}
		for (int j = 0; j < len_tds; ++j) {
			mp[tds[j]]++;
		}
	}
	//printf("debug--%d %d\n", u, ans);
	for (int i = head[u]; ~i; i = e[i].next) {
		if (centroid[e[i].to])
			continue;
		solve_subproblem(e[i].to);
	}
}

int main() {
	int x, y;
	while (~scanf("%d", &n)) {
		memset(head, -1, sizeof(head));
		memset(centroid, 0, sizeof centroid);
		memset(w, 0, sizeof(w));
		side = 0;
		scanf("%d", &k);
		for (int i = 0; i < k; ++i) 
			scanf("%I64d", &p[i]);
		for (int i = 1; i <= n; ++i) {
			scanf("%I64d", &a);
			ull tmp;
			for (ull j = 0; j < k; ++j) {
				tmp = 0;
				while (a % p[j] == 0) {
					a /= p[j];
					tmp++;
				}
				w[i] |= (tmp % 3) << (j << 1);
			}
		}
		for (int i = 1; i < n; ++i) {
			scanf("%d%d", &x, &y);
			build(x, y);
			build(y, x);
		}
		ans = 0;
		subtree_size[1] = n;
		solve_subproblem(1);
		printf("%I64d\n", ans);
	}
	return 0;
}