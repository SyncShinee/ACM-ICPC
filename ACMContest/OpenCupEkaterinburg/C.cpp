#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>

using namespace std;

const int maxn = 1e3 + 100;
struct node{
    int id, val;
    node(int _id = 0, int _val = 0) {
	id = _id;
	val = _val;
    }
};
int cmp(node a, node b) {
    if(a.val == b.val) {
	return a.id > b.id;
    }
    return a.val < b.val;
}
node f[maxn][maxn];
int n, k;
int ans[maxn];

void solve() {
    f[1][1].id = 1;
    f[1][1].val = k;
    for(int i = 2; i <= n; i++) {
	sort(f[i - 1] + 1, f[i - 1] + i, cmp);
	int t = (i + 1) / 2 - 1;
	int sum = 0;
	for(int j = 1; j <= t; j++) {
	    sum += f[i - 1][j].val + 1;
	}
	if(k >= sum) {
	    for(int j = 1; j <= t; j++) {
		f[i][j].val = f[i - 1][j].val + 1;
		f[i][j].id = f[i - 1][j].id;
	    }
	    for(int j = t + 1; j <= i - 1; j++) {
		f[i][j].val = 0;
		f[i][j].id = f[i - 1][j].id;
	    }
	    f[i][i].id = i;
	    f[i][i].val = k - sum;
	}
	else {
	    f[i][i].id = i;
	    f[i][i].val = -1;
	    for(int j = 1; j <= i - 1; j++) {
		f[i][j] = f[i - 1][j];
	    }
	}
    }
    memset(ans, 0, sizeof(ans));
    for(int i = n; i >= 1; i--) {
	if(f[i][i].val != -1) {
	    for(int j = n; j > i; j--) {
		printf("%d ", -1);
	    }
	    for(int j = 1; j <= i; j++) {
		ans[f[i][j].id] = f[i][j].val;
	    }
	    for(int j = i; j >= 1; j--) {
		printf("%d%c", ans[j], (j == 1 ? '\n' : ' '));
	    }
	    break;
	}
    }


    
    /*for(int i = 1; i <= n; i++) {
	f[i].id = i;
	f[i].val = -1;
    }
    f[1].val = k;
    f[1].id = 1;
    for(int i = 2; i <= n; i++) {
	sort(f + 1, f + 1 + (i - 1), cmp);
	int t = (i + 1) / 2 - 1;
	int sum = 0;
	for(int j = 1; j <= t; j++) {
	    sum += f[j].val + 1;
	}
	if(k >= sum) {
	    for(int j = 1; j <= t; j++) {
		f[j].val++;
	    }
	    for(int j = t + 1; j <= i - 1;j++) {
		f[j].val = 0;
	    }
	    f[i].val = k - sum;
	    f[i].id = i;
	}
	else {
	    break;
	}
    }
    for(int i = n; i >= 1; i--) {
	ans[f[i].id] = f[i].val;
    }
    for(int i = n; i >= 1; i--) {
	printf("%d%c", ans[i], (i == 1 ? '\n' : ' '));
	}*/
}
int main() {
    //freopen("C.txt", "r", stdin);
    while(scanf("%d%d", &n, &k) != EOF) {
	solve();
    }
    return 0;
}
