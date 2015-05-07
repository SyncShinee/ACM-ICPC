#include <cstdio>
#include <cstring>
#include <queue>
#define MAX_NODE  51
#define SIGMA_SIZE  10
using namespace std;
struct node {
	int rel, pos, sta;
}tnode, now;
int f[1001][MAX_NODE][51][4];
int n, m, tmp, key;
void print(int rel, int pos, int sta) {
	if (rel + pos + sta == 0)
		return;
	print(f[rel][pos][sta][1],f[rel][pos][sta][2],f[rel][pos][sta][3]);
	putchar(f[rel][pos][sta][0]+'0');
}
struct Trie {
	int ch[MAX_NODE][SIGMA_SIZE], val[MAX_NODE], fail[MAX_NODE], last[MAX_NODE], num;
	void clear() {
		memset(ch, 0, sizeof(ch));
		memset(val, 0, sizeof(val));
		num = 1;
	}

	void insert(char *s, int v) {
		int len = strlen(s), rt = 0, c;
		for (int i = 0; i < len; ++i) {
			c = s[i]-'0';
			if (!ch[rt][c]) {
				ch[rt][c] = num++;
			}
			rt = ch[rt][c];
		}
		val[rt] = v;
	}
	void build() {
		queue<int> q;
		fail[0] = 0;
		for (int i = 0; i < SIGMA_SIZE; ++i) {
			int u = ch[0][i];
			if (u) {
				fail[u] = 0;
				last[u] = 0;
				q.push(u);
			}
		}
		while (!q.empty()) {
			int now = q.front();
			q.pop();
			for (int i = 0; i < SIGMA_SIZE; ++i) {
				int u = ch[now][i];
				if (!u) {
					ch[now][i] = ch[fail[now]][i];
					continue;
				}
				int v = fail[now];
				while (v && !ch[v][i])
					v = fail[v];
				fail[u] = ch[v][i];
				last[u] = val[fail[u]] ? fail[u] : last[fail[u]];
				q.push(u);
			}
		}
	}
	void solve() {
		queue<node> bfs; 
		tnode.rel = tnode.pos = tnode.sta = 0;
		f[0][0][0][0] = 0;
		f[0][0][0][1] = f[0][0][0][2] = f[0][0][0][3] = -1;
		bfs.push(tnode);
		while (!bfs.empty()) {
			now = bfs.front();
			bfs.pop();
			for (int i = 0; i < SIGMA_SIZE; ++i) {
				int u = ch[now.pos][i];
				tnode.rel = (now.rel*10 + i) % n;
				tnode.pos = u;
				tnode.sta = now.sta;
				tmp = u;
				while (tmp) {
					if (val[tmp]) {
						tnode.sta |= (1 << (val[tmp]-1));
					}
					tmp = last[tmp];
				}
				if (f[tnode.rel][tnode.pos][tnode.sta][0] > -1)
					continue;
				f[tnode.rel][tnode.pos][tnode.sta][0] = i;
				f[tnode.rel][tnode.pos][tnode.sta][1] = now.rel;
				f[tnode.rel][tnode.pos][tnode.sta][2] = now.pos;
				f[tnode.rel][tnode.pos][tnode.sta][3] = now.sta;
				if (tnode.rel == 0 && tnode.sta == key) {
					print(tnode.rel, tnode.pos, tnode.sta);
					printf("\n");
					return;
				}
				bfs.push(tnode);
			}
		}
	}
}ac;

int main() {
	char s[8][16];
	//freopen("out1.txt", "w", stdout);
	while (~scanf("%d%d", &n, &m)) {
		key = (1 << m)-1;
		ac.clear();
		for (int i = 1; i <= m; ++i) {
			scanf("%s", s[i]);
			ac.insert(s[i], i);
		}
		ac.build();
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < ac.num; ++j)
				for (int t = 0; t <= key; ++t)
					f[i][j][t][0] = -1;
		ac.solve();
	}
	return 0;
}