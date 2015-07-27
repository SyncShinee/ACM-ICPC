#pragma comment(linker,"/STACK:102400000,102400000")
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#define N 100010
using namespace std;
int n, head[N], side;
struct edge {
	int to, val, next;
}e[N << 1];
int mark[N], INF, ans[N];
void build(int x, int y, int z) {
	e[side].to = y;
	e[side].val = z;
	e[side].next = head[x];
	head[x] = side++;
}
struct Distance {
	int dis, idx;
	Distance(){}
	Distance(int _dis, int _idx) {
		dis = _dis;
		idx = _idx;
	}
	friend bool operator < (Distance x, Distance y) {
		return x.dis < y.dis || x.dis == y.dis && x.idx < y.idx;
	}
}dist[N], ds[N], tds[N], fds[N], ftds[N];
queue <int> q;
bool inq[N];
int subtree_size[N], len_ds, len_tds;
bool centroid[N];


void compute_subtree_size(int x, int pre) {
	
	for (int i = head[x]; ~i; i = e[i].next) {
		if (e[i].to == pre || centroid[e[i].to]) {
			continue;
		}
		compute_subtree_size(e[i].to, x);
		
	}
}

pair<int, int> find_centroid(int x, int pre, int sum) {
	pair <int, int> ret = make_pair(INF, -1);
	int mx = 0;
	subtree_size[x] = 1;
	for (int i = head[x]; ~i; i = e[i].next) {
		if (centroid[e[i].to] || e[i].to == pre) 
			continue;
		ret = min(ret, find_centroid(e[i].to, x, sum));
		mx = max(mx, subtree_size[e[i].to]);
		subtree_size[x] += subtree_size[e[i].to];
	}
	mx = max(mx, sum - subtree_size[x]);
	return min(ret, make_pair(mx, x));
}

void deal(int x, int pre, int value) {
	tds[len_tds] = Distance(dist[x].dis - value, dist[x].idx);
	ftds[len_tds++] = Distance(value, x);
	for (int i = head[x]; ~i; i = e[i].next) {
		if (e[i].to == pre || centroid[e[i].to]) {
			continue;
		}
		deal(e[i].to, x, value + e[i].val);
	}
}

void count_pairs(Distance a[], Distance fa[], int len, int mul) {
	sort(a, a + len);
	sort(fa, fa + len);
	int i = 0, j = 0;
	for (int i = 0; i < len; ++i) {
		while (j < len && a[j] < fa[i])
			++j;
		ans[fa[i].idx] += mul * (len - j);
	}
}

void solve_subproblem(int x) {
	int u = find_centroid(x, -1, subtree_size[x]).second;
	centroid[u] = true;
	len_ds = 0;
	ds[len_ds] = dist[u];
	fds[len_ds++] = Distance(0, u);
	for (int i = head[u]; ~i; i = e[i].next) {
		if (centroid[e[i].to])
			continue;
		len_tds = 0;
		deal(e[i].to, u, e[i].val);
		subtree_size[e[i].to] = len_tds;
		count_pairs(tds, ftds, len_tds, -1);
		for (int j = 0; j < len_tds; ++j) {
			ds[len_ds] = tds[j];
			fds[len_ds++] = ftds[j];
		}
	}
	count_pairs(ds, fds, len_ds, 1);
	for (int i = head[u]; ~i; i = e[i].next) {
		if (centroid[e[i].to])
			continue;
		solve_subproblem(e[i].to);
	}
}



int main() {
	int x, y, z;
	while (~scanf("%d", &n)) {
		memset(head, -1, sizeof head);
		memset(inq, 0, sizeof inq);
		memset(dist, 0x7f, sizeof dist);
		INF = dist[0].dis;
		side = 0;
		for (int i = 1; i < n; ++i) {
			scanf("%d%d%d", &x, &y, &z);
			build(x, y, z);
			build(y, x, z);
		}
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &mark[i]);
			if (mark[i]) {
				q.push(i);
				dist[i].dis = 0;
				dist[i].idx = i;
				inq[i] = true;
			}
		}
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			inq[u] = false;
			for (int i = head[u]; ~i; i = e[i].next) {
				Distance tmpd = Distance(dist[u].dis + e[i].val, dist[u].idx);
				if (tmpd < dist[e[i].to]) {
					dist[e[i].to] = tmpd;
					if (!inq[e[i].to]) {
						q.push(e[i].to);
						inq[e[i].to] = true;
					}
				}
			}
		}
		memset(centroid, 0, sizeof centroid);
		memset(ans, 0, sizeof ans);
		subtree_size[1] = n;
		solve_subproblem(1);
		int ret = 0;
		for (int i = 1; i <= n; ++i) {
			if (mark[i])
				continue;
			ret = max(ret, ans[i]);
		}
		printf("%d\n", ret);
	}
	return 0;
}