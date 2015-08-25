#pragma comment(linker,"/STACK:102400000,102400000")
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
typedef long long ll;
const int N = 100010, INF = 1e9+7;
struct edge {
	int to, val, nxt;
}e[N << 1];
int head[N], side, subtree_size[N], n;
bool centroid[N];
int ans[16];
int tds[N], len_tds, Q, qr[16];
int mp[N<<1];
int used[N], len_used;

void build(int x, int y, int z) {
	e[side].to = y;
	e[side].val = z;
	e[side].nxt = head[x];
	head[x] = side++;
}

pair <int, int> find_centroid(int x, int pre, int sum) {
	pair <int, int> ret = make_pair(INF, -1);
	int m = 0;
	subtree_size[x] = 1;
	for (int i = head[x]; ~i; i = e[i].nxt) {
		int v = e[i].to;
		if (centroid[v] || v == pre) {
			continue;
		}
		ret = min(ret, find_centroid(v, x, sum));
		m = max(m, subtree_size[v]);
		subtree_size[x] += subtree_size[v];
	}
	m = max(m, sum - subtree_size[x]);
	return min(ret, make_pair(m, x));
}

void deal(int x, int pre, int value) {
	tds[len_tds++] = value;
	for (int i = head[x]; ~i; i = e[i].nxt) {
		int v = e[i].to;
		if (centroid[v] || v == pre) {
			continue;
		}
		deal(v, x, e[i].val ^ value);
	}
}

void solve_subproblem(int x) {
	int u = find_centroid(x, -1, subtree_size[x]).second;
	centroid[u] = true;
	len_used = 0;
	used[len_used++] = 0;
	mp[0] = 1;
	for (int i = head[u]; ~i; i = e[i].nxt) {
		int v = e[i].to;
		if (centroid[v])
			continue;
		len_tds = 0;
		deal(v, u, e[i].val);
		subtree_size[v] = len_tds;
		for (int t = 0; t < Q; ++t) {
			for (int j = 0; j < len_tds; ++j) {
				int tmp = qr[t] ^ tds[j];
				ans[t] += mp[tmp];
			}
		}
		for (int j = 0; j < len_tds; ++j) {
			if (mp[tds[j]] == 0) used[len_used++] = tds[j];
			mp[tds[j]]++;
		}
	}
	for (int i = 0; i < len_used; ++ i) mp[used[i]] = 0;
	for (int i = head[u]; ~i; i = e[i].nxt) {
		int v = e[i].to;
		if (centroid[v])
			continue;
		solve_subproblem(v);
	}
}
inline bool scan_d(int &ret) {
char c; int sgn;
if(c=getchar(),c==EOF) return 0; 
while(c!='-'&&(c<'0'||c>'9')) c=getchar();
sgn=(c=='-')?-1:1;
ret=(c=='-')?0:(c-'0');
while(c=getchar(),c>='0'&&c<='9') ret=ret*10+(c-'0');
ret*=sgn;
return 1;
}
inline void out(int x) {
	if(x>9) out(x/10);
	putchar(x%10+'0');
}
int main() {
	//freopen("in.txt", "r", stdin);
	int T, x, y, z;
	scan_d(T);
	while (T--) {
		scan_d(n);
		side = 0;
		for (int i = 0; i <= n; ++ i) head[i] = -1;
		for (int i = 1; i < n; ++ i) {
			scan_d(x), scan_d(y), scan_d(z);
			build(x, y, z);
			build(y, x, z);
		}
		scan_d(Q);
		for (int i = 0; i < Q; ++ i) {
			scan_d(qr[i]);
		}
		for (int i = 0; i <= n; ++ i)
			centroid[i] = 0;
		subtree_size[1] = n;
		for (int i = 0; i < Q; ++ i) {
			if (qr[i] == 0) ans[i] = n;
			else ans[i] = 0;
		}
		solve_subproblem(1);
		for (int i = 0; i < Q; ++ i) {
			out(ans[i]);
			puts("");
		}
	}
	return 0;
}