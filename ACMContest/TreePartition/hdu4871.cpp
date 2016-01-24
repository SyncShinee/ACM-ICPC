#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <map>
#include <queue>
#include <ctype.h>
#define N 30010
#define INF 1000000000
using namespace std;

const int MSIZE = 65536;
struct edge {
	int to, val, next;
}e[N << 1];

int head[N], subtree_size[N], side, n, k, m, len_tds, dist[N];
vector <pair<int, int> > gra[N];
bool centroid[N], inq[N];
queue <int> q;
pair <int, int> tds[N], ans;
map <int, pair <int, int> > ds;

void spfa(int x) {
	memset(inq, 0, sizeof inq);
	memset(dist, 0x7f, sizeof dist);
	dist[x] = 0;
	inq[x] = true;
	q.push(x);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		inq[u] = false;
		for (int i = 0; i < gra[u].size(); ++i) {
			int v = gra[u][i].first;
			int w = gra[u][i].second;
			if (dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				if (!inq[v]) {
					q.push(v);
					inq[v] = true;
				}
			}
		}
	}
}

void build (int x, int y, int z) {
	e[side].to = y;
	e[side].val = z;
	e[side].next = head[x];
	head[x] = side++;
}

void build_graph(int x) {
	inq[x] = true;
	for (int i = 0; i < gra[x].size(); ++i) {
		int v = gra[x][i].first, w = gra[x][i].second;
		if (!inq[v] && dist[v] == dist[x] + w) {
			build(x, v, w);
			build(v, x, w);
			build_graph(v);
		}
	}
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

void deal(int x, int pre, pair<int, int> value) {
	pair <int, int> tmp = make_pair(value.first + 1, value.second);
	tds[len_tds++] = tmp;
	for (int i = head[x]; ~i; i = e[i].next) {
		if (centroid[e[i].to] || e[i].to == pre)
			continue;
		deal(e[i].to, x, make_pair(tmp.first, tmp.second + e[i].val));
	}
}

void solve_subproblem(int x) {
	int u = find_centroid(x, -1, subtree_size[x]).second;
	centroid[u] =true;
	ds.clear();
	ds[0] = make_pair(0, 1);
	for (int i = head[u]; ~i; i = e[i].next) {
		if (centroid[e[i].to])
			continue;
		len_tds = 0;
		deal(e[i].to, u, make_pair(0, e[i].val));
		subtree_size[e[i].to] = len_tds;
		for (int j = 0; j < len_tds; ++j) {
			int nu = tds[j].first + 1, su = tds[j].second;
			if (ds.count(k - nu)) {
				if (ans.first < su + ds[k - nu].first) {
					ans.first = su + ds[k - nu].first;
					ans.second = ds[k - nu].second;
				}
				else if (ans.first == su + ds[k - nu].first) {
					ans.second += ds[k - nu].second;

				}
			}
		}
		for (int j = 0; j < len_tds; ++j) {
			int nu = tds[j].first, su = tds[j].second;
			if (ds.count(nu)) {
				if (ds[nu].first < su) {
					ds[nu] = make_pair(su, 1);
				}
				else if (ds[nu].first == su) {
					ds[nu].second++;
				}
			}
			else {
				ds[nu] = make_pair(su, 1);
			}
		}
	}
	for (int i = head[u]; ~i; i = e[i].next) {
		if (centroid[e[i].to])
			continue;
		solve_subproblem(e[i].to);
	}
}

struct Reader {
	char buffer[MSIZE], c;
	int l, r;
	Reader(): l(0), r(0) {}
	char readchar() {
		if (l == r) {
			l = 0;
			r = fread(buffer, 1, MSIZE, stdin);
		}
		return buffer[l++];
	}
	int read() {
		c = readchar();
		while (!isdigit(c)) c = readchar();
		int res = 0;
		while (isdigit(c)) res = res * 10 + c - '0', c = readchar();
		return res;
	}
}R;

int main() {
	int T, x, y, z;
	//scanf("%d", &T);
	T = R.read();
	while (T--) {
		//scanf("%d%d%d", &n, &m, &k);
		n = R.read(), m = R.read(), k = R.read();
		for (int i = 1; i <= n; ++i)
			gra[i].clear();
		for (int i = 0; i < m; ++i) {
			//scanf("%d%d%d", &x, &y, &z);
			x = R.read(), y = R.read(), z = R.read();
			gra[x].push_back(make_pair(y, z));
			gra[y].push_back(make_pair(x, z));
		}
		spfa(1);
		for (int i = 1; i <= n; ++i)
			sort(gra[i].begin(), gra[i].end());
		memset(centroid, 0, sizeof centroid);
		memset(head, -1, sizeof head);
		side = 0;
		memset(inq, 0, sizeof inq);
		build_graph(1);
		ans = make_pair(0, 0);
		subtree_size[1] = n;
		solve_subproblem(1);
		printf("%d %d\n", ans.first, ans.second);
	}
	return 0;
}