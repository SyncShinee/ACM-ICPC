#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <set>

using namespace std;

const int maxn = 5e5 + 100;
const int M = 500000;
int fa[maxn], num[maxn], r[maxn];
vector<int> a[maxn];
int n;

int getFa(int x) {
    if(fa[x] == x)
	return x;
    return fa[x] = getFa(fa[x]);
}
void getUnion(int x, int y) {
    x = getFa(x);
    y = getFa(y);
    if(x == y)
	return;
    if(r[x] < r[y]) {
	num[y] += num[x];
	fa[x] = y;
    }
    else {
	num[x] += num[y];
	fa[y] = x;
	if(r[x] == r[y]) {
	    r[y]++;
	}
    }
}
void solve() {
    for(int i = 0; i <= M; i++) {
	fa[i] = i;
	num[i] = 1;
	r[i] = 0;
    }
    int res = 0;
    for(int i = 1; i <= n; i++) {
	//bn = 0;
	set<int> s;
	int cnt = 0;
	for(int j = 0; j < a[i].size(); j++) {
	    int t = getFa(a[i][j]);
	    if(s.find(t) == s.end()) {
		s.insert(t);
		cnt += num[t];
	    }
	}
	if(cnt == a[i].size()) {
	    // printf("****   %d\n", i);
	    res++;
	    for(int j = 1; j < a[i].size(); j++) {
		getUnion(getFa(a[i][0]), getFa(a[i][j]));
	    }
	}
    }
    printf("%d\n", res);
}

int main() {
    freopen("c.txt", "r", stdin);
    while(scanf("%d", &n) != EOF) {
	for(int i = 1; i <= n; i++) {
	    a[i].clear();
	    int m;
	    scanf("%d", &m);
	    for(int j = 0; j < m; j++) {
		int t;
		scanf("%d", &t);
		a[i].push_back(t);
	    }
	}
	solve();
    }
    return 0;
}
