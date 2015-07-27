/*#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>
#define INF 1000000000
#define N 10010
using namespace std;
struct edge {
	int to, val, next;
}e[N << 1];

int head[N], subtree_size[N], side, n;
bool centroid[N];
int tds[N], len_tds, ans[N], num, qr[N], ds[N], len_ds;

void build(int x, int y, int z) {
	e[side].to = y;
	e[side].val = z;
	e[side].next = head[x];
	head[x] = side++;
}

pair <int, int> find_centroid(int x, int pre, int sum) {
	pair <int, int> ret = make_pair(INF, -1);
	int m = 0;
	subtree_size[x] = 1;
	for (int i = head[x]; ~i; i = e[i].next) {
		if (centroid[e[i].to] || e[i].to == pre) {
			continue;
		}
		ret = min(ret, find_centroid(e[i].to, x, sum));
		m = max(m, subtree_size[e[i].to]);
		subtree_size[x] += subtree_size[e[i].to];
	}
	m = max(m, sum - subtree_size[x]);
	return min(ret, make_pair(m, x));
}

void deal(int x, int pre, int value) {
	tds[len_tds++] = value;
	for (int i = head[x]; ~i; i = e[i].next) {
		if (centroid[e[i].to] || e[i].to == pre) {
			continue;
		}
		deal(e[i].to, x, e[i].val + value);
	}
}

void count_pair(int a[], int len, int flag) {
	sort(a, a + len);
	for (int t = 0; t < num; ++t) {
		int l = 0, r = len - 1;
		while (l < r) {
			if (a[l] + a[r] == qr[t]) {
				if (a[l] == a[r]) {
					ans[t] += flag * (r - l + 1) * (r - l) / 2;
					break;
				}
				else {
					int i = l, j = r;
					while (a[i] == a[l])
						i++;
					while (a[j] == a[r])
						j--;
					ans[t] += flag * (i - l) * (r - j);
					l = i;
					r = j;
				}
			}
			else if (a[l] + a[r] > qr[t]) {
				r--;
			}
			else {
				l++;
			}
		}
	}
}

void solve_subproblem(int x) {
	int u = find_centroid(x, -1, subtree_size[x]).second;
	centroid[u] = true;
	len_ds = 0;
	ds[len_ds++] = 0;
	for (int i = head[u]; ~i; i = e[i].next) {
		if (centroid[e[i].to])
			continue;
		len_tds = 0;
		deal(e[i].to, u, e[i].val);
		subtree_size[e[i].to] = len_tds;
		count_pair(tds, len_tds, -1);
		for (int j = 0; j < len_tds; ++j) {
			ds[len_ds++] = tds[j];
		}
	}
	count_pair(ds, len_ds, 1);
	for (int i = head[u]; ~i; i = e[i].next) {
		if (centroid[e[i].to])
			continue;
		solve_subproblem(e[i].to);
	}
}
int main() {
	int x, y;
	while (scanf("%d", &n), n) {
		memset(head, -1, sizeof(head));
		memset(centroid, 0, sizeof(centroid));
		memset(ans, 0, sizeof(ans));
		side = 0;
		for (int i = 1; i <= n; ++i) {
			while (scanf("%d", &x) && x) {
				scanf("%d", &y);
				build(i, x, y);
				build(x, i, y);
			}
		}
		num = 0;
		while (scanf("%d", &x) && x) {
			qr[num++] = x;
		}
		subtree_size[1] = n;
		solve_subproblem(1);
		for (int i = 0; i < num; ++i) {
			if (ans[i]) {
				puts("AYE");
			}
			else {
				puts("NAY");
			}
		}
		puts(".");
	}
	return 0;
}*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>
#define INF 1000000000
#define N 10010
using namespace std;
struct edge {
	int to, val, next;
}e[N << 1];

int head[N], subtree_size[N], side, n;
bool ans[N], centroid[N];
int tds[N], len_tds, num, qr[N];
set <int> st;

void build(int x, int y, int z) {
	e[side].to = y;
	e[side].val = z;
	e[side].next = head[x];
	head[x] = side++;
}

pair <int, int> find_centroid(int x, int pre, int sum) {
	pair <int, int> ret = make_pair(INF, -1);
	int m = 0;
	subtree_size[x] = 1;
	for (int i = head[x]; ~i; i = e[i].next) {
		if (centroid[e[i].to] || e[i].to == pre) {
			continue;
		}
		ret = min(ret, find_centroid(e[i].to, x, sum));
		m = max(m, subtree_size[e[i].to]);
		subtree_size[x] += subtree_size[e[i].to];
	}
	m = max(m, sum - subtree_size[x]);
	return min(ret, make_pair(m, x));
}

void deal(int x, int pre, int value) {
	tds[len_tds++] = value;
	for (int i = head[x]; ~i; i = e[i].next) {
		if (centroid[e[i].to] || e[i].to == pre) {
			continue;
		}
		deal(e[i].to, x, e[i].val + value);
	}
}

void solve_subproblem(int x) {
	int u = find_centroid(x, -1, subtree_size[x]).second;
	centroid[u] = true;
	st.clear();
	st.insert(0);
	for (int i = head[u]; ~i; i = e[i].next) {
		if (centroid[e[i].to])
			continue;
		len_tds = 0;
		deal(e[i].to, u, e[i].val);
		subtree_size[e[i].to] = len_tds;
		for (int t = 0; t < num; ++t) {
			if (ans[t])
				continue;
			for (int j = 0; j < len_tds; ++j) {
				if (st.find(qr[t] - tds[j]) != st.end()) {
					ans[t] = true;
					break;
				}
			}
		}
		for (int j = 0; j < len_tds; ++j)
			st.insert(tds[j]);
	}
	for (int i = head[u]; ~i; i = e[i].next) {
		if (centroid[e[i].to])
			continue;
		solve_subproblem(e[i].to);
	}
}
int main() {
	int x, y;
	while (scanf("%d", &n), n) {
		memset(head, -1, sizeof(head));
		memset(centroid, 0, sizeof centroid);
		memset(ans, 0, sizeof(ans));
		side = 0;
		for (int i = 1; i <= n; ++i) {
			while (scanf("%d", &x) && x) {
				scanf("%d", &y);
				build(i, x, y);
				build(x, i, y);
			}
		}
		num = 0;
		while (scanf("%d", &x) && x) {
			qr[num++] = x;
		}
		subtree_size[1] = n;
		solve_subproblem(1);

		for (int i = 0; i < num; ++i) {
			if (ans[i]) {
				puts("AYE");
			}
			else {
				puts("NAY");
			}
		}
		puts(".");
	}
	return 0;
}