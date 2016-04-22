#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int maxn = 1e6 + 100;
const int key = 1000;

int vis[maxn];
vector<int> p;
vector<int> b[maxn];
int n, a[maxn], sum[maxn];
struct node1{
    int no, val;
    node1(int _no = 0, int _val = 0) {
	no = _no;
	val = _val;
    }
    
};
struct node2{
    int no, val;
    node2(int _no = 0, int _val = 0) {
	no = _no;
	val = _val;
    }
  
};
node1 q[maxn];
node2 h[maxn];
int ansl, ansi, ansj, anss;
int qn, hn;

void pre() {
    //printf("fdsf");
    for(int i = 0; i <= key; i++)
	vis[i] = 0;
    p.clear();
    for(int i = 2; i <= key; i++) {
	if(vis[i] == 0) {
	    p.push_back(i);
	    for(int j = i + i; j <= key; j += i) {
		vis[j] = 1;
	    }
	}
    }
    // printf("dsafa");
}
void solve() {
    ansl = 0;
    for(int i = 0; i <= key * key; i++) {
	b[i].clear();
    }
    for(int i = 1; i <= n; i++) {
	int t = a[i];
	for(int j = 0; j < p.size(); j++) {
	    if(t % p[j] == 0) {
		b[p[j]].push_back(i);
	    }
	    while(t % p[j] == 0) {
		t /= p[j];
	    }
	}
	if(t != 1) {
	    b[t].push_back(i);
	}
    }
    
    for(int i = 2; i <= key * key; i++) {
	if(b[i].size() == 0)
	    continue;
	sum[0] = -(b[i][0] - 2);
	for(int j = 1; j < b[i].size(); j++) {
	    sum[j] = sum[j - 1] + 1 - (b[i][j] - b[i][j - 1] - 1);
	}
	qn = 0;
	for(int j = 0; j < b[i].size(); j++) {
	    if(qn == 0 || sum[j] < q[qn - 1].val) {
		q[qn] = node1(b[i][j], sum[j]);
		qn++;
	    }
	}
	hn = 0;
	for(int j = b[i].size() - 1; j >= 0; j--) {
	    if(hn == 0 || sum[j] > h[hn - 1].val) {
		h[hn] = node2(b[i][j], sum[j]);
		hn++;
	    }
	}
	for(int j = 0; j < hn / 2; j++) {
	    swap(h[j], h[hn - 1 - j]);
	}
	
	int qp = 0, hp = 0;
	while(qp < qn) {
	    while(hp + 1 < hn && h[hp + 1].val >= q[qp].val - 1) {
		hp++;
	    }
	    if(h[hp].no >= q[qp].no) {
		int tmp = h[hp].no - q[qp].no + 1 + h[hp].val - (q[qp].val - 1);
		if(tmp > ansl) {
		    ansl = tmp;
		    ansi = q[qp].no;
		    ansj = h[hp].no;
		    anss = h[hp].val - (q[qp].val - 1);
		}
	    }
	    qp++;
	}
    }
    //printf("--------  %d  %d  %d\n", ansi, ansj, anss);
    int tmp = min(ansi - 1, anss);
    ansi = ansi - tmp;
    anss -= tmp;
    tmp = min(anss, n - ansj);
    ansj += tmp;
    printf("%d %d\n", ansi, ansj);
}

int main() {
    //freopen("D.txt", "r", stdin);
    //printf("dsfd");
    pre();
    while(scanf("%d", &n) != EOF) {
	for(int i = 1; i <= n; i++) {
	    scanf("%d", &a[i]);
	}
	int flag = 1;
	for(int i = 1; i <= n; i++) {
	    if(a[i] != 1) {
		flag = 0;
		break;
	    }
	}
	if(flag == 0)
	    solve();
	else {
	    printf("0 0\n");
	}
	}
    return 0;
}
