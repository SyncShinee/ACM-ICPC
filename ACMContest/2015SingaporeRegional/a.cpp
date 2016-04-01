#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long ll;

const int maxn = 200 * 200 * 200 + 100;
const int N = 200 + 10;
int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
int a[200 + 10][200 + 10];
int s[maxn], sn;
int nxt[maxn];
int p[N], pn;
int si, sj;
bool vis[N][N][N];
int li[N][N][N], lj[N][N][N];
int n;

struct Hash {
    int M, p;
    Hash(int _m = 0, int _p = 0) {
	M = _m;
	p = _p;
    }
    int a[maxn], pc[maxn];
    void inital() {
	a[0] = s[0] % M;
	for(int i = 1; i < sn; i++) {
	    a[i] = ((ll)a[i - 1] * (ll)p % M + s[i]) % M;
	}
	pc[0] = 1;
	for(int i = 1; i < sn + 1; i++) {
	    pc[i] = (ll)pc[i - 1] * (ll)p % M;
	}
    }
    int val(int i, int j) {
	int r = a[j];
	if(i == 0)
	    return r;
	int l = (ll)a[i - 1] * (ll)pc[j - i + 1] % M;
	int ans = r - l;
	if(ans < 0)
	    ans += M;
	return ans;
    }
    int equal(int a, int b, int c, int d) {
	int ta = val(a, b);
	int tb = val(c, d);
	//printf("%d  %d\n", ta, tb);
	if(ta == tb)
	    return 1;
	return 0;
    }
};
Hash ha = Hash(1000000007, 17777), hb = Hash(1000000001, 40001);


char str[200 + 10];

int check(int x, int y) {
    if(a[x][y] == 1)
	return 0;
    return 1;
}

void getNext() {
    int j = 0, k = -1;
    nxt[0] = -1;
    while(j < sn) {
	if(k == -1 || s[j] == s[k]) {
	    nxt[++j] = ++k;
	}
	else {
	    k = nxt[k];
	}
    }
}

void solve() {
    memset(vis, 0, sizeof(vis));
    vis[si][sj][0] = 1;
    int nowi = si, nowj = sj, nowp = 0;
    while(1) {
	//	printf("***  %d  %d %d ", nowi, nowj, p[nowp]);
	int ni = nowi + dx[p[nowp]], nj = nowj + dy[p[nowp]], np = (nowp + 1) % pn;
	//printf("%d  %d\n", ni, nj);
	if(check(ni, nj)) {
	    ;
	}
	else {
	    ni = nowi;
	    nj = nowj;
	}
	li[ni][nj][np] = nowi;
	lj[ni][nj][np] = nowj;
	nowi = ni;
	nowj = nj;
	nowp = np;
	if(vis[ni][nj][np] == 1) {
	    break;
	}
	vis[ni][nj][np] = 1;
    }
    sn = 0;
    int lasti = -1, lastj = -1;
    while(vis[nowi][nowj][nowp] != 0) {
	vis[nowi][nowj][nowp] = 0;
	if(lasti == -1 || (nowi != lasti || nowj != lastj) ) {
	    s[sn] = nowi * n + nowj;
	    sn++;
	}
	lasti = nowi;
	lastj = nowj;
	nowi = li[lasti][lastj][nowp];
	nowj = lj[lasti][lastj][nowp];
	nowp--;
	if(nowp < 0)
	    nowp += pn;
    }
    
    ha.inital();
    hb.inital();
    int ans;
    for(int len = 1; len <= sn; len++) {
	if(sn % len != 0)
	    continue;
	//printf("-- %d\n", len);
	int now = 0, flag = 1;
	while(now < sn) {
	    if(!ha.equal(0, len - 1, now, now + len - 1) || !hb.equal(0, len - 1, now, now + len - 1)) {
		flag = 0;
		break;
	    }
	    now += len;
	}
	if(flag) {
	    ans = len;
	    break;
	}
    }
    
    /*    for(int i = 0; i < sn; i++) {
	printf("%d %d\n", s[i] / n, s[i] % n);
    }
    printf("\n");*/
    //getNext();
    /*for(int i = 0; i <= sn; i++) {
	printf("%d ", nxt[i]);
    }
    printf("\n");*/
    /*int t = sn - nxt[sn];
    if(sn % t == 0) {
	printf("%d\n", t);
    }
    else {
	printf("%d\n",sn);
	}*/
    printf("%d\n", ans);
}

int main() {
    freopen("a.txt", "r", stdin);
    while(scanf("%d", &n) != EOF) {
	scanf("%s", str);
	pn = strlen(str);
	for(int i = 0; i < pn; i++) {
	    if(str[i] == '^')
		p[i] = 0;
	    if(str[i] == '>')
		p[i] = 1;
	    if(str[i] == 'v')
		p[i] = 2;
	    if(str[i] == '<')
		p[i] = 3;
	}
	for(int i = 0; i < n; i++) {
	    scanf("%s", str);
	    for(int j = 0; j < n; j++) {
		if(str[j] == 'R') {
		    si = i;
		    sj = j;
		    a[i][j] = 0;
		}
		else if(str[j] == '#') {
		    a[i][j] = 1;
		}
		else {
		    a[i][j] = 0;
		}
	    }
	}
	solve();
    }
    return 0;
}
