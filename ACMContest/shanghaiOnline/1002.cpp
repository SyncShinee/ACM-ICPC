#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 10010;
const int INF = 1e9 + 7;
const int M = 1731793;
const int base = 29;
const int M2 = 1987311;
const int base2 = 23;

struct node {
	int hs_val, len;
}tds1[N], tds2[N], second_tds1[N], second_tds2[N];
char v[N], tplt[N];
int tplt_len, n;
int qianzhui[N], houzhui[N], head[N], side, centroid[N], subtree_size[N], ds1[M], ds2[M], len_ds, len_tds, upd1[N], upd2[N], len_upd1, len_upd2;
bool ans;
int p1[N];
int p2[N];
int second_qianzhui[N], second_houzhui[N], second_ds1[M2], second_ds2[M2], second_upd1[N], second_upd2[N], second_len_upd1, second_len_upd2;
void prep2()
{
	p2[0] = 1;
	for(int i = 1;i<N;i++)
	{
		p2[i] = p2[i-1]*base2%M2;
	}
	p1[0] = 1;
	for(int i = 1;i<N;i++)
	{
		p1[i] = p1[i-1]*base%M;
	}
}
int update_hou(int old, char ch)
{
	int newz = (old * base%M + ch-'a')%M;
	return newz;
}

int update_qian(int old, char ch, int lll)
{
	lll--;
	int newz = ((ch-'a')*(ll)p1[lll] + old)%M;
	return newz;
}
int update_hou2(int old, char ch)
{
	int newz = (old * base2%M + ch-'a')%M2;
	return newz;
}

int update_qian2(int old, char ch, int lll)
{
	lll--;
	int newz = ((ch-'a')*(ll)p2[lll] + old)%M2;
	return newz;
}
struct edge {
	int to, nxt;
}e[N << 1];
void build(int x, int y) {
	e[side].to = y;
	e[side].nxt = head[x];
	head[x] = side++;
}
void get_subtree_size(int x, int pre) {
	subtree_size[x] = 1;
	for (int i = head[x]; ~i; i = e[i].nxt) {
		if (centroid[e[i].to] || e[i].to == pre) {
			continue;
		}
		get_subtree_size(e[i].to, x);
		subtree_size[x] += subtree_size[e[i].to];
	}
}
pair <int, int> find_centroid(int x, int pre, int sum) {
	pair <int, int> ret = make_pair(INF, -1);
	int m = 0;
	for (int i = head[x]; ~i; i = e[i].nxt) {
		if (centroid[e[i].to] || e[i].to == pre) {
			continue;
		}
		ret = min(ret, find_centroid(e[i].to, x, sum));
		m = max(m, subtree_size[e[i].to]);
	}
	m = max(m, sum - subtree_size[x]);
	return min(ret, make_pair(m, x));
}

void deal(int x, int pre, int hs_ls, int value1, int value2, int second_value1, int second_value2) {
	hs_ls++;
	value1 = update_hou(value1, v[x]);
	value2 = update_qian(value2, v[x], hs_ls);
	second_value1 = update_hou2(second_value1, v[x]);
	second_value2 = update_qian2(second_value2, v[x], hs_ls);
	
	if (hs_ls >= tplt_len) return;
	tds1[len_tds].hs_val = value1;
	tds1[len_tds].len = hs_ls;
	tds2[len_tds].hs_val = value2;
	tds2[len_tds].len = hs_ls;
	second_tds1[len_tds].hs_val = second_value1;
	second_tds1[len_tds].len = hs_ls;
	second_tds2[len_tds].hs_val = second_value2;
	second_tds2[len_tds++].len = hs_ls;
	for (int i = head[x]; ~i; i = e[i].nxt) {
		if (centroid[e[i].to] || e[i].to == pre) {
			continue;
		}
		deal(e[i].to, x, hs_ls, value1, value2, second_value1, second_value2);
	}
}
void solve_subproblem(int x) {
	if (ans) {
		return;
	}
	get_subtree_size(x, -1);
	int u = find_centroid(x, -1, subtree_size[x]).second;
	centroid[u] = true;
	int tmp = update_hou(0, v[u]);
	len_upd1 = 0;
	len_upd2 = 0;
	upd1[len_upd1++] = tmp;
	upd2[len_upd2++] = tmp;
	ds1[tmp] = ds2[tmp] = 1;
	tmp = update_hou2(0, v[u]);
	second_len_upd1 = 0;
	second_len_upd2 = 0;
	second_upd1[second_len_upd1++] = tmp;
	second_upd2[second_len_upd2++] = tmp;
	second_ds1[tmp] = second_ds2[tmp] = 1;
	for (int i = head[u]; ~i; i = e[i].nxt) {
		if (centroid[e[i].to]) {
			continue;
		}
		len_tds = 0;
		deal(e[i].to, u, 0, 0, 0, 0, 0);
		for (int j = 0; j < len_tds; ++ j) {
			if (tds1[j].hs_val == houzhui[tds1[j].len] && ds2[qianzhui[tplt_len - tds1[j].len]] && second_tds1[j].hs_val == second_houzhui[second_tds1[j].len] && second_ds2[second_qianzhui[tplt_len - second_tds1[j].len]]) {
				ans = true;
				return;
			}
			if (tds2[j].hs_val == qianzhui[tds2[j].len] && ds1[houzhui[tplt_len - tds2[j].len]]&&second_tds2[j].hs_val == second_qianzhui[second_tds2[j].len] && second_ds1[second_houzhui[tplt_len - second_tds2[j].len]]) {
				ans = true;
				return;
			}
		}
		for (int j = 0; j < len_tds; ++ j) {
			int tmp = update_qian(tds1[j].hs_val, v[u], tds1[j].len + 1);
			ds1[tmp] = 1;
			upd1[len_upd1++] = tmp;
			tmp = update_hou(tds2[j].hs_val, v[u]);
			ds2[tmp] = 1;
			upd2[len_upd2++] = tmp;


			tmp = update_qian2(second_tds1[j].hs_val, v[u], second_tds1[j].len + 1);
			second_ds1[tmp] = 1;
			second_upd1[second_len_upd1++] = tmp;
			tmp = update_hou2(second_tds2[j].hs_val, v[u]);
			second_ds2[tmp] = 1;
			second_upd2[second_len_upd2++] = tmp;
		}
	}
	for (int i = 0; i < len_upd1; ++ i) {
		ds1[upd1[i]] = 0;
		second_ds1[second_upd1[i]] = 0;
	}
	for (int i = 0; i < len_upd2; ++ i) {
		ds2[upd2[i]] = 0;
		second_ds2[second_upd2[i]] = 0;
	}
	for (int i = head[u]; ~i; i = e[i].nxt) {
		if (centroid[e[i].to]) {
			continue;
		}
		solve_subproblem(e[i].to);
	}
}
int main() {
	freopen("in.txt", "r", stdin);
	prep2();
	int T, x, y;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++ cas) {
		memset(centroid, 0, sizeof centroid);
		memset(head, -1, sizeof head);
		side = 0;
		ans = false;
		scanf("%d", &n);
		for (int i = 1; i < n; ++ i) {
			scanf("%d%d", &x, &y);
			build(x, y);
			build(y, x);
		}
		scanf("%s", v + 1);
		scanf("%s", tplt);
		tplt_len = strlen(tplt);
		int now = 0;
		for (int i = 0; i < tplt_len; ++ i) {
			now = update_hou(now, tplt[i]);
			qianzhui[i + 1] = now;
		}
		now = 0;
		for (int i = tplt_len - 1; i >= 0; -- i) {
			now = update_qian(now, tplt[i], tplt_len - i);
			houzhui[tplt_len - i] = now;
		}
		now = 0;
		for (int i = 0; i < tplt_len; ++ i) {
			now = update_hou2(now, tplt[i]);
			second_qianzhui[i + 1] = now;
		}
		now = 0;
		for (int i = tplt_len - 1; i >= 0; -- i) {
			now = update_qian2(now, tplt[i], tplt_len - i);
			second_houzhui[tplt_len - i] = now;
		}
		solve_subproblem(1);
		printf("Case #%d: ", cas);
		if (ans) {
			puts("Find");
		}
		else {
			puts("Impossible");
		}
	}
	return 0;
}