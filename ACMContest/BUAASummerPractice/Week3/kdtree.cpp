#include <cstdio>
#include <algorithm>
#include <cstring>
#define lson Tree[now].son[0]
#define rson Tree[now].son[1]
using namespace std;
const int N = 50010;
struct T {
	int d[5], mx[5], mn[5], son[2], sum;
}Tree[N];

struct node {
	int d[5], sum;
	node (int d0 = 0, int d1 = 0, int d2 = 0, int d3 = 0, int d4 = 0, int s = 0) {
		d[0] = d0;
		d[1] = d1;
		d[2] = d2;
		d[3] = d3;
		d[4] = d4;
		sum = s;
	}
}p[N];

int ans, rt, pos[5], D, n, m, lastans;

bool operator < (const node &A, const node &B) {
	return A.d[D] < B.d[D];
}
void update(int o, int s) {
	for (int i = 0; i < 5; ++ i) {
		Tree[o].mx[i] = max(Tree[o].mx[i], Tree[s].mx[i]);
		Tree[o].mn[i] = min(Tree[o].mn[i], Tree[s].mn[i]);
	}
	Tree[o].sum += Tree[s].sum;
}
int build (int l, int r, int d) {
	D = d;
	int now = l + r >> 1;
	nth_element(p + l, p + now, p + r + 1);
	Tree[now].sum = p[now].sum;
	for (int i = 0; i < 5; ++ i) {
		Tree[now].d[i] = Tree[now].mx[i] = Tree[now].mn[i] = p[now].d[i];
	}
	if (l < now) {
		lson = build(l, now - 1, (d + 1) % 5);
		update(now, lson);
	}
	else
		lson = 0;
	if (now < r) {
		rson = build(now + 1, r, (d + 1) % 5);
		update(now, rson);
	}
	else
		rson = 0;
	return now;
}
bool check(int now) {
	for (int i = 0; i < 5; ++ i) {
		if (pos[i] < Tree[now].mn[i]) {
			return false;
		}
	}
	return true;
}
bool inside(int now) {
	for (int i = 0; i < 5; ++ i) {
		if ( pos[i] < Tree[now].mx[i]) {
			return false;
		}
	}
	return true;
}
int query(int now) {
	int ret = 0;
	if (!now) {
		return 0;
	}
	if (!check(now)) {
		return 0;
	}
	if (inside(now)) {
		return Tree[now].sum;
	}
	bool flag = true;
	for (int i = 0; i < 5; ++ i) {
		if (pos[i] < p[now].d[i]) {
			flag = false;
			break;
		}
	}
	if (flag)
		ret = 1;
	ret += query(lson) + query(rson);
	return ret;
}
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int main() {
	int _T;
//	freopen("in.txt", "r", stdin);
	scanf("%d", &_T);
	while (_T --) {
		//memset(p, 0, sizeof p);
		//memset(Tree, 0, sizeof Tree);
		lastans = 0;
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++ i) {
			for (int j = 0; j < 5; ++ j) {
				//scanf("%d", &p[i].d[j]);
				p[i].d[j] = read();
			}
			p[i].sum = 1;
		}
		rt = build(1, n, 0);
		//printf("rt ==== %d\n", rt);
		scanf("%d", &m);
		while (m --) {
			for (int i = 0; i < 5; ++ i) {
				//scanf("%d", &pos[i]);
				pos[i] = read();
				pos[i] ^= lastans;
				//pos[i][0] = 0;
			}
			lastans = query(rt);
			printf("%d\n", lastans);
		}
	}
	return 0;
}