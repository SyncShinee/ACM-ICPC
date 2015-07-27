#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define INF 2000000007
#define N 40010
using namespace std;

struct node {
	int to, val;
}e;

vector <node> gra[N];
int n, k, ans;
bool centroid[N];
int subtree_size[N];
vector <int> ds, tds;

pair<int, int> find_centroid(int x, int pre, int t) {
	pair<int, int> ret = make_pair(INF, -1);
	int s = 1, m = 0;
	subtree_size[x] = 1;
	for (int i = 0; i < gra[x].size(); ++i) {
		int v = gra[x][i].to;
		if (v == pre || centroid[v]) 
			continue;
		ret = min(ret, find_centroid(v, x, t));

		m = max(m, subtree_size[v]);
		s += subtree_size[v];
		subtree_size[x] += subtree_size[v];
	}
	m = max(m, t - s);
	ret = min(ret, make_pair(m, x));
	return ret;
}

void deal(int x, int pre, int value, vector<int> &dist) {
	dist.push_back(value);
	for (int i = 0; i < gra[x].size(); ++i) {
		int v = gra[x][i].to;
		if (v == pre || centroid[v])
			continue;
		deal(v, x, value + gra[x][i].val, dist);
	}
}

int count_pairs(vector<int> dist) {
	int ret = 0;
	sort(dist.begin(), dist.end());
	int l = 0, r = dist.size()-1;
	while (l < r) {
		while (l < r && dist[r] + dist[l] > k) {
			r--;
		}
		ret += r - l;
		l++;
	}
	return ret;
}

void solve_subproblem(int x) {
	int u = find_centroid(x, -1, subtree_size[x]).second;
	centroid[u] = true;
	for (int i = 0; i < gra[u].size(); ++i) {
		if (centroid[gra[u][i].to])
			continue;
		solve_subproblem(gra[u][i].to);
	}
	ds.clear();
	ds.push_back(0);
	for (int i = 0; i < gra[u].size(); ++i) {
		if (centroid[gra[u][i].to])
			continue;
		tds.clear();
		deal(gra[u][i].to, u, gra[u][i].val, tds);
		subtree_size[gra[u][i].to] = tds.size();
		ans -= count_pairs(tds);
		ds.insert(ds.end(), tds.begin(), tds.end());
	}
	ans += count_pairs(ds);
	centroid[u] = false;
}

int main() {
	int x, y;
	char s[8];
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i) {
		gra[i].clear();
	}
	memset(centroid, 0, sizeof centroid);
	for (int i = 1; i < n; ++i) {
		scanf("%d%d%d%s", &x, &y, &e.val, s);
		e.to = y;
		gra[x].push_back(e);
		e.to = x;
		gra[y].push_back(e);
	}
	scanf("%d", &k);
	ans = 0;
	subtree_size[1] = n;
	solve_subproblem(1);
	printf("%d\n", ans);
	return 0;
}