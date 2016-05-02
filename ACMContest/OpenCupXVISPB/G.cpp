#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
char s[16][4];
int a[16], b[16], d[16];
int ap[16];
int r[4], c[4];
bool tag[16];
int calc(int p[], int n) {
    int ret = 0;
    memset(tag, 0, sizeof tag);
    for (int i = 0; i < n; ++ i) {
	if (!tag[i]) {
	    ret ++;
	    int t = p[i];
	    tag[i] = true;
	    while (t != i) {
		tag[t] = true;
		t = p[t];
	    }
	}
    }
    return n - ret;
}
vector<int> pp;
void prt(int p[], int n, int l) {
    int ret = 0;
    memset(tag, 0, sizeof tag);
    for (int i = 0; i < n; ++ i) {
	if (!tag[i]) {
	    ret ++;
	    int t = p[i];
	    tag[i] = true;
	    pp.clear();
	    pp.push_back(i);
	    while (t != i) {
		pp.push_back(t);
		tag[t] = true;
		t = p[t];
	    }
	    for (int i = pp.size() - 1; i > 0; -- i) {
		if (l == 0) {
		    printf("%c-%c\n", pp[i] + 'a', pp[i - 1] + 'a');
		}
		else if (l == 1) {
		    printf("%d-%d\n", pp[i] + 1, pp[i - 1] + 1);
		}
		else {
		    printf("%c%d-%c%d\n", pp[i] / 4 + 'a', pp[i] % 4 + 1, pp[i - 1] / 4 + 'a', pp[i - 1] % 4 + 1);
		}
	    }
	}
    }
}

int ans1[4], ans2[4], ans3[16];

int main() {
    //freopen("input001.txt", "r", stdin);
    for (int i = 0; i < 16; ++ i) {
	scanf("%s", s[i]);
    }
    for (int i = 0; i < 16; ++ i) {
	b[i] = atoi(s[i]) - 1;
    }
    int ans = 1e9 + 7;
    r[0] = 0;
    r[1] = 1;
    r[2] = 2;
    r[3] = 3;
    do {
	
	for (int i = 0; i < 4; ++ i) {
	    for (int j = 0; j < 4; ++ j) {
		ap[r[i] * 4 + j] = b[i * 4 + j];
	    }
	}
	for (int i = 0; i < 16; ++ i) {
	    a[i] = ap[i];
	}
	
	c[0] = 0;
	c[1] = 1;
	c[2] = 2;
	c[3] = 3;
	do {
	    for (int i = 0; i < 4; ++ i) {
		for (int j = 0; j < 4; ++ j) {
		    ap[i * 4 + c[j]] = a[i * 4 + j];
		}
	    }
	    for (int i = 0; i < 16; ++ i) {
		d[i] = ap[i];
	    }
	    int tmp_ans = calc(r, 4) + calc(c, 4) + calc(d, 16);
	    if (tmp_ans < ans) {
		ans = tmp_ans;
		//	puts("here");
	
		for (int i = 0; i < 4; ++ i) {
		    ans1[i] = r[i];
		    ans2[i] = c[i];
		}
		for (int i = 0; i < 16; ++ i) {
		    ans3[i] = d[i];
		}
	    }
	}while (next_permutation(c, c + 4));
    }while (next_permutation(r, r + 4));
    printf("%d\n", ans);
    prt(ans1, 4, 0);
    prt(ans2, 4, 1);
    prt(ans3, 16, 2);
    return 0;
}
