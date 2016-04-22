#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 4e5 + 100;
const int MAXNODE = 4 * maxn + 100;
const int INF = 1e8;

int flag[MAXNODE], tag[MAXNODE], dist[MAXNODE], id[MAXNODE];
int d[maxn];
int x[maxn], l[maxn], r[maxn];
int m1, m2;
int y[maxn];

struct node {
    int x, id;
    node(int _x = 0, int _id = 0) {
	x = _x;
	id = _id;
    }
    bool operator < (const node b) const {
	return x < b.x;
    }
};

node a[maxn];
int n;

void pushUpAll(int rt) {
    int lrt = (rt << 1), rrt = lrt + 1;
    if(flag[lrt] == 1) {
	flag[rt] = flag[rrt];
	dist[rt] = dist[rrt];
	id[rt] = id[rrt];
    }
    else if(flag[rrt] == 1) {
	flag[rt] = flag[lrt];
	dist[rt] = dist[lrt];
	id[rt] = id[lrt];
    }
    else {
	flag[rt] = 0;
	dist[rt] = dist[lrt];
	id[rt] = id[lrt];
	if(dist[rrt] < dist[lrt]) {
	    dist[rt] = dist[rrt];
	    id[rt] = id[rrt];
	}
    }
}
void pushDown(int rt) {
    int lrt = (rt << 1), rrt = lrt + 1;
    tag[rrt] = min(tag[rrt], tag[rt]);
    dist[rrt] = min(dist[rrt], tag[rt]);

    tag[lrt] = min(tag[lrt], tag[rt]);
    dist[lrt] = min(dist[lrt], tag[rt]);
}

void update1(int pos, int rt, int l, int r) {
    if(l == r && l == pos) {
	flag[rt] = 1;
	return;
    }
    pushDown(rt);
    int lrt = (rt << 1), rrt = lrt + 1;
    int m = (l + r) / 2;
    if(pos <= m) {
	update1(pos, lrt, l, m);
    }
    else {
	update1(pos, rrt, m + 1, r);
    }
    pushUpAll(rt);
}
void update2(int L, int R, int val,  int rt, int l, int r) {
    if(L <= l && R >= r) {
	tag[rt] = min(tag[rt], val);
	dist[rt] = min(dist[rt], val);
	return;
    }
    pushDown(rt);
    int lrt = (rt << 1), rrt = lrt + 1, m = (l + r) / 2;
    if(L <= m) {
	update2(L, R, val, lrt, l, m);
    }
    if(R >= m + 1) {
	update2(L, R, val, rrt, m + 1, r);
    }
    pushUpAll(rt);
}
void dfs(int rt, int l, int r) {
    if(l == r) {
	flag[rt] = 0;
	tag[rt] = INF;
	dist[rt] = INF;
	id[rt] = l;

	if(a[l].x == x[1]) {
	    tag[rt] = dist[rt] = 0;
	}
	return;
    }
    flag[rt] = 0;
    tag[rt] = INF;
    dist[rt] = INF;
    id[rt] = INF;
    int lrt = (rt << 1), rrt = lrt + 1, m = (l + r) / 2;
    dfs(lrt, l, m);
    dfs(rrt, m + 1, r);
    pushUpAll(rt);
}

void solve() {
    n = m1 + m2;
    for(int i = 1; i <= m1; i++) {
	a[i].x = x[i];
	a[i].id = i;
	d[i] = INF;
    }
    for(int i = 1; i <= m2; i++) {
	a[i + m1] = y[i];
	a[i + m1].id = i + m1;
	d[i + m1] = INF;
    }
    sort(a + 1, a + 1 + n);
    /*for(int i = 1; i <= n; i++) {
	printf("111   %d  %d\n", a[i].id, a[i].x);
	}*/
    dfs(1, 1, n);
    while(1) {
	int u = id[1], ud = dist[1];
	//	printf("22   %d  %d %d\n", u, ud, flag[1]);
	if(ud == INF) {
	    break;
	}
	if(flag[1] == 1) {
	    break;
	}
	d[a[u].id] = ud;
	//printf("33  %d\n", a[u].id);

	update1(u, 1, 1, n);
	if(a[u].id > m1) {
	    continue;
	}
	int low, high;
	low = lower_bound(a + 1, a + 1 + n, node(a[u].x - r[a[u].id], 0)) - a;
	high = upper_bound(a + 1, a + 1 + n, node(a[u].x - l[a[u].id], 0)) - a - 1;
	if(low <= n && high >= 1) {
	    update2(low, high, ud + 1, 1, 1, n);
	}
	//printf("44  %d  %d  %d  %d\n", low, high, dist[1], id[1]);
	low = lower_bound(a + 1, a + 1 + n, node(a[u].x + l[a[u].id], 0)) - a;
	high = upper_bound(a + 1, a + 1 + n, node(a[u].x + r[a[u].id], 0)) - a - 1;
	if(low <= n && high >= 1) {
	    update2(low, high, ud + 1, 1, 1, n);
	}
	//printf("444  %d  %d %d %d\n", low, high, dist[1], id[1]);
    }
    for(int i = 1; i <= m2; i++) {
	if(d[i + m1] == INF) {
	    printf("-1");
	}
	else {
	    printf("%d", d[i + m1]);
	}
	if(i == m2) {
	    printf("\n");
	}
	else {
	    printf(" ");
	}
    }
}


int main() {
    //freopen("C.txt", "r", stdin);
    while(scanf("%d", &m1) != EOF) {
	for(int i = 1; i <= m1; i++) {
	    scanf("%d%d%d", &x[i], &l[i], &r[i]);
	}
	scanf("%d", &m2);
	for(int i = 1; i <= m2; i++) {
	    scanf("%d", &y[i]);
	}
	solve();
    }
    return 0;
}
