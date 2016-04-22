#include <cstdio>
#include <algorithm>
#include <cstring>
#define lson rt << 1
#define rson rt << 1 | 1
using namespace std;
const int N = 4e5 + 10;
int n;
char str[N];

int sa[N], t1[N], t2[N], c[N];
int Rank[N], height[N];

void buildsa(char *s, int n, int m) {
	int i, k, p, a1, a2, *x = t1, *y = t2;
	memset(c, 0, m << 2);
	for (i = 0; i < n; ++ i) ++ c[x[i] = s[i]];
	for (i = 1; i < m; ++ i) c[i] += c[i - 1];
	for (i = n - 1; i >= 0; -- i) sa[--c[x[i]]] = i;
	for (k = 1, p = 0; k < n; k <<= 1, p = 0) {
		for (i = n - k; i < n; ++ i) y[p ++] = i;
		for (i = 0; i < n; ++ i) if (sa[i] >= k) y[p ++] = sa[i] - k;
		memset(c, 0, m << 2);
		for (i = 0; i < n; ++ i) ++ c[x[y[i]]];
		for (i = 1; i < m; ++ i) c[i] += c[i - 1];
		for (i = n - 1; i >= 0; -- i) sa[-- c[x[y[i]]]] = y[i];
		swap(x, y), p = 1, x[sa[0]] = 0;
		for (i = 1; i < n; ++ i) {
			a1 = sa[i - 1] + k < n ? y[sa[i - 1] + k] : -1;
			a2 = sa[i] + k < n ? y[sa[i] + k] : -1;
			x[sa[i]] = (y[sa[i - 1]] == y[sa[i]] && a1 == a2) ? p - 1 : p ++;
		}
		if (p >= n) break; m = p;
	}
	for (i = 0; i < n; ++ i) Rank[sa[i]] = i;
	for (i = 0, k = 0; i < n; ++ i) {
		if (k) -- k; if (!Rank[i]) continue;
		int j = sa[Rank[i] - 1];
		while (s[i + k] == s[j + k]) ++ k;
		height[Rank[i]] = k;
	}
}
char s[N];
struct node {
    int len, x;
}T[N << 1];

bool operator < (const node &A, const node &B) {
    return A.x < B.x;
}
void pushup(int rt) {
    if (T[lson].len > T[rson].len) {
	T[rt] = T[lson];
    }
    else {
	T[rt] = T[rson];
    }
}
void update(int x, int y, int rt, int l, int r) {
    if (l == r && l == x) {
	T[rt].len = y;
	T[rt].x = x;
	return;
    }
    int mid = (l + r) >> 1;
    if (x <= mid) {
	update(x, y, lson, l, mid);
    }
    else {
	update(x, y, rson, mid + 1, r);
    }
    pushup(rt);
}
node query(int x, int rt, int l, int r) {
    if (x <= l) {
	return T[rt];
    }
    int mid = (l + r) >> 1;
    node ret = query(x, rson, mid + 1, r);
    if (mid >= x) {
	ret = max(ret, query(x, lson, l, mid));
    }
    return ret;
}

int sgn(int x) {
    if (x < 0) return -1;
    if (x > 0) return 1;
    return 0;
}

struct Ans {
    int len, s1x, s1y, s2x, s2y;
}ans;

int main() {
    scanf("%s", s);
    int len = strlen(s);
    s[len] = '$';
    scanf("%s", s + len + 1);
    int n = strlen(s);
    buildsa(s, n, 128);
    for (int i = 1; i < n; ++ i) {
	if (sgn(sa[i - 1] - len) * sgn(sa[i] - len) == -1) {
	    if (sa[i - 1] < len) {
	       	update(sa[i - 1], height[i], 1, 0, n - 1);
	    }
	    else {
	       	update(sa[i], height[i], 1, 0, n - 1);
	    }
	}
    }
    
    for (int i = 1; i < n; ++ i) {
	if (sgn(sa[i - 1] - len) * sgn(sa[i] - len) == -1) {
	    if (sa[i - 1] < len) {
		node tmp = query(sa[i - 1] + height[i], 1, 0, n - 1);
		if (ans.len < height[i] + tmp.len) {
		    ans.len = tmp.len + height[i];
		    ans.s1x = sa[i - 1];
		    ans.s1y = sa[i - 1] + height[i];
		    ans.s2x = tmp.x;
		    ans.s2y = tmp.x + tmp.len;
		}
	    }
	    else {
		node tmp = query(sa[i] + height[i], 1, 0, n - 1);
		if (ans.len < height[i] + tmp.len) {
		    ans.len = tmp.len + height[i];
		    ans.s1x = sa[i];
		    ans.s1y = sa[i] + height[i];
		    ans.s2x = tmp.x;
		    ans.s2y = tmp.x + tmp.len;
		}
	    }
	}
    }
    
    for (int i = ans.s1x; i < ans.s1y; ++ i) {
	printf("%c", s[i]);
    }
    puts("");
    for (int i = ans.s2x; i < ans.s2y; ++ i) {
	printf("%c", s[i]);
    }
    puts("");
    return 0;
}
