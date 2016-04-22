#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#define FI first
#define SE second
using namespace std;
const int N = 10010;
typedef pair <int, int>  PII;

PII p[N], l[N];
int a[N];
int belong[N], sta[N];
int n, m, M;
const int OFFSET = 1000000;
struct ANS {
    int num, x;
    ANS(int _n = 0, int _x = 0) : num(_n), x(_x) {}
}ans;

bool operator < (const ANS &A, const ANS &B) {
    return A.num < B.num || A.num == B.num && A.x > B.x;
}

void getL() {
    M = 0;
    sort(p, p + m);
    int ll = p[0].FI, rr = p[0].SE;
    for (int i = 1; i < m; ++ i) {
	if (p[i].FI > rr) {
	    l[M].FI = ll, l[M++].SE = rr;
	    ll = p[i].FI, rr = p[i].SE;
	}
	else {
	    rr = max(rr, p[i].SE);
	}
    }
    l[M].FI = ll;
    l[M++].SE = rr;
}

int numIn[3000010], numOut[3000010];

void solve() {
    int tmp = 0;
    for (int i = 0; i < n; ++ i) {
	//bool flag = false;
	for (int j = 0; j < M; ++ j) {
	    numIn[l[j].FI - a[i] + OFFSET] ++;
	    numOut[l[j].SE - a[i] + OFFSET] ++;
	}
    }
    int nw = 0;
    for (int i = 0; i <= 3 * OFFSET; ++ i) {
	nw += numIn[i];
	ans = max(ans, ANS(nw, abs(i - OFFSET)));
	nw -= numOut[i];
    }
}
int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt" ,"w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++ i) {
	scanf("%d", &a[i]);
    }
    for (int i = 0; i < m; ++ i) {
	scanf("%d%d", &p[i].FI, &p[i].SE);
    }
    getL();
    solve();
    printf("%d %d\n", ans.x, ans.num);
    return 0;
}
